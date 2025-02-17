#include <TinyGPS.h>
#include <SoftwareSerial.h>
TinyGPS gps;
SoftwareSerial serialgps(4, 3);
float latitude, longitude;
unsigned long fix_age;
float altitudes;
unsigned int satellites;
void setup() {
  Serial.begin(9600);
  serialgps.begin(9600);
}
void loop() {
  if (serialgps.available() > 0) {
    if (gps.encode(serialgps.read())) {
      gps.f_get_position(&latitude, &longitude, &fix_age);
      altitudes = gps.f_altitude();
      satellites = gps.satellites();
      if (satellites <= 40)
      {
        Serial.print(latitude, 6);
        Serial.print(",   "); Serial.print(longitude, 6);
        Serial.print(",  "); Serial.print(altitudes);
        Serial.print(",   "); Serial.println(satellites);
        delay(100);
      }
    }
  }
}
