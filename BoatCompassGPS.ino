// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: t -*-

#define THISFIRMWARE "Sailbot Dewi-Cloudstat"

#include <FastSerial.h>
#include <AP_Common.h>
#include <AP_GPS.h>
#include <AP_Math.h>
#include <I2C.h>
#include <AP_Compass.h> // Compass Library

#include <AP_ADC.h> // ArduPilot Mega ADC Library

FastSerialPort0(Serial);
FastSerialPort1(Serial1);

GPS         *gps;
AP_GPS_Auto GPS(&Serial1, &gps);

#define T6 1000000
#define T7 10000000

#define ToRad(x) (x*0.01745329252)  // *pi/180
#define ToDeg(x) (x*57.2957795131)  // *180/pi

AP_Compass_HMC5843 compass;

unsigned long timer;

float heading;

//--------------------------------------Dewi-----------------------------------------

#include <EEPROM.h>
#include <Servo.h>

//#define DEBUG

#define MIN_SAIL_PWM 1100
#define MAX_SAIL_PWM 2000
#define MIN_RUDDER_PWM 1060
#define MAX_RUDDER_PWM 1920

#define COMPASS_OFFSET 77

Servo rudder;
Servo sail;

int rudderPin = 7;
int sailPin = 8;
int windSensorPin = A0;

int offset; // wind sensor offset


//----------------------------------------------------------------------------------

void setup(){
  Serial.begin(115200);
  Serial1.begin(38400);
  Serial.println(String(THISFIRMWARE)+" "+String(__FILE__)+" "+String(__VERSION__)+" "+String(__DATE__)+String(__TIME__));
  
  setupGps();
  setupCompass();
  setupDewi();
}

void loop(){
  int wind_angle;
  float bearing;
  char current_line[10];  // allocate some space for the request string
  read_line(current_line);
  switch (current_line[0]) {
      case 'c':        
          //bearing = read_compass() - COMPASS_OFFSET;  // compensate for offset
          //bearing = mod(bearing);  // wrap around
          getCompass();
          bearing=heading;
          log_json_float("compass", ToDeg(bearing));
          break;
      case 'w':
          wind_angle = read_wind_sensor() - offset;  // compensate for offset
          wind_angle = mod(wind_angle);  // wrap around
          log_json_int("wind", wind_angle);
          break;
      case 'r':
          set_rudder(get_amount(current_line));
          break;
      case 's':
          set_sail(get_amount(current_line));
          break;
      case 'o':
          //store_offset(read_wind_sensor());
          //offset = get_stored_offset();
          break;
  }
 delay(19) ;
}

