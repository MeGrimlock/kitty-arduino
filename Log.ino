void log_json_int(char* key, int value) {
    // write a single json key value pair

        Serial.print("{\"");
        Serial.print(key);
        Serial.print("\": ");
        Serial.print(value);
        Serial.println("}");

}

void log_json_float(char* key, float value) {
    // write a single json key value pair

        Serial.print("{\"");
        Serial.print(key);
        Serial.print("\": ");
        Serial.print(value);
        Serial.println("}");

}
