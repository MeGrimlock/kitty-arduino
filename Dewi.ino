void setupDewi(){
  pinMode(windSensorPin, INPUT);
  setupMotors();
  Serial.println("{\"started\": true}");
  delay(10);
}

void read_line(char* line) {
    // read characters from serial into line until a newline character
    char c;
    int index;
    for (index = 0; index < 5; index++) {
        // wait until there is a character
        while (Serial.available() == 0);
        // read a character
        c = Serial.read();
        if (c == '\n' || c== '\r') {
            line[index]='\0';
            break;
        }
        else {
            line[index] = c;
        }
    }
    // terminate the string
    line[index+1] = '\0';
}

int get_amount(char* line) {
    // return the number in a string such as "r1200" as an int
    int amount;
    amount = (int) strtol(line + 1, NULL, 10);
    return amount;
}

int mod(int angle) {
    if (angle > 359) {
        return mod(angle - 359);
    }
    else if (angle < 0) {
        return mod(359 + angle);
    }
    else {
        return angle;
    }
}

