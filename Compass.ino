void setupCompass(){
  //Serial.println("Compass library test (HMC5843 and HMC5883L)");
  I2c.begin();
  I2c.timeOut(20);

  I2c.setSpeed(true);

  if (!compass.init()) {
      Serial.println("compass initialisation failed!");
      while (1) ;
  }

  compass.set_orientation(AP_COMPASS_COMPONENTS_DOWN_PINS_FORWARD); // set compass's orientation on aircraft.
  compass.set_offsets(0,0,0); // set offsets to account for surrounding interference
  compass.set_declination(ToRad(0.0)); // set local difference between magnetic north and true north

  #ifdef DEBUG
    Serial.print("Compass auto-detected as: ");
    switch( compass.product_id ) {
      case AP_COMPASS_TYPE_HIL:
          Serial.println("HIL");
          break;
      case AP_COMPASS_TYPE_HMC5843:
          Serial.println("HMC5843");
          break;
      case AP_COMPASS_TYPE_HMC5883L:
          Serial.println("HMC5883L");
          break;
      default:
          Serial.println("unknown");
          break;
    }
  #endif
}

void getCompass(){

  static float min[3], max[3], offset[3];
  compass.accumulate();
  compass.read();
  if (!compass.healthy) {
      Serial.println("not healthy");
      return;
  }
  heading = compass.calculate_heading(0,0); // roll = 0, pitch = 0 for this example
	compass.null_offsets();

  // capture min
  if( compass.mag_x < min[0] )
      min[0] = compass.mag_x;
  if( compass.mag_y < min[1] )
      min[1] = compass.mag_y;
  if( compass.mag_z < min[2] )
      min[2] = compass.mag_z;

  // capture max
  if( compass.mag_x > max[0] )
      max[0] = compass.mag_x;
  if( compass.mag_y > max[1] )
      max[1] = compass.mag_y;
  if( compass.mag_z > max[2] )
      max[2] = compass.mag_z;

  // calculate offsets
  offset[0] = -(max[0]+min[0])/2;
  offset[1] = -(max[1]+min[1])/2;
  offset[2] = -(max[2]+min[2])/2;
  
#ifdef DEBUG
  // display all to user
  Serial.printf("Heading: %.2f (%3u,%3u,%3u) I2cerr=%u ",
                ToDeg(heading),
                compass.mag_x,
                compass.mag_y,
                compass.mag_z, 
		      I2c.lockup_count());

  // display offsets
  Serial.printf("\t offsets(%.2f, %.2f, %.2f)",
                offset[0], offset[1], offset[2]);
                
  Serial.println();
#endif  
}
