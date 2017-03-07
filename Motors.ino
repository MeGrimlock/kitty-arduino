void setupMotors(){
  rudder.attach(rudderPin, MIN_RUDDER_PWM, MAX_RUDDER_PWM);
  sail.attach(sailPin, MIN_SAIL_PWM, MAX_SAIL_PWM);
  // set default positions
  rudder.writeMicroseconds(1500);
  sail.writeMicroseconds(1500);
}

void set_rudder(int amount) {
    // set the rudder to amount
    amount = constrain(amount, MIN_RUDDER_PWM, MAX_RUDDER_PWM);
    rudder.writeMicroseconds(amount);
    log_json_int("rudder", amount);
}

void set_sail(int amount) {
    // set the sail to amount
    amount = constrain(amount, MIN_SAIL_PWM, MAX_SAIL_PWM);
    sail.writeMicroseconds(amount);
    log_json_int("sail", amount);
}

void testMotor(){
  for (int i=1000;i<2500;i++){
  
  }
}
