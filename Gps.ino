void setupGps(){
  #ifdef DEBUG
    Serial.println("GPS AUTO library test");
  #endif
  gps = &GPS;
  gps->init(GPS::GPS_ENGINE_AIRBORNE_2G);
}

void getGps(){
  gps->update();
  if (gps->new_data) {
      if (gps->fix) {
          Serial.print("Lat: ");
          print_latlon(&Serial,gps->latitude);
          Serial.print(" Lon: ");
          print_latlon(&Serial,gps->longitude);
          Serial.printf(" Alt: %.2fm GSP: %.2fm/s CoG: %d SAT: %d TIM: %lu STATUS: %u\n",
                        (float)gps->altitude / 100.0,
                        (float)gps->ground_speed / 100.0,
                        (int)gps->ground_course / 100,
                        gps->num_sats,
                        gps->time,
                        gps->status());
      } else {
          Serial.println("No fix");
      }
      gps->new_data = false;
  }
}

// print_latlon - prints an latitude or longitude value held in an int32_t
// probably this should be moved to AP_Common
void print_latlon(BetterStream *s, int32_t lat_or_lon)
{
    int32_t dec_portion, frac_portion;
    int32_t abs_lat_or_lon = labs(lat_or_lon);

    // extract decimal portion (special handling of negative numbers to ensure we round towards zero)
    dec_portion = abs_lat_or_lon / T7;

    // extract fractional portion
    frac_portion = abs_lat_or_lon - dec_portion*T7;

    // print output including the minus sign
    if( lat_or_lon < 0 ) {
        s->printf_P(PSTR("-"));
    }
    s->printf_P(PSTR("%ld.%07ld"),(long)dec_portion,(long)frac_portion);
}
