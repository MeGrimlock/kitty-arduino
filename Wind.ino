int read_wind_sensor() {
    /*
    int pulse_length = 0;
    pulse_length = pulseIn(windSensorPin, HIGH, 2000);
    int magic = 29;
    int wind_angle = ((pulse_length * 10) / magic);
    return wind_angle;*/
    return analogRead(0);
}
