#include <TinyGPS.h>
#include <SoftwareSerial.h>
TinyGPS gps;
SoftwareSerial serialgps(4, 3);
float latitude, longitude;
unsigned long fix_age;
float altitude;
unsigned int satellites;

void setup() {
  Serial.begin(9600);
  serialgps.begin(9600);
}

void loop() {
  if (serialgps.available() > 0) {
    if (gps.encode(serialgps.read())) {
      gps.f_get_position(&latitude, &longitude, &fix_age);
      altitude = gps.f_altitude();
      satellites = gps.satellites();
      
      Serial.print("Latitud: "); Serial.print(latitude, 6);
      Serial.print(", Longitud: "); Serial.print(longitude, 6);
      Serial.print(", Altura: "); Serial.print(altitude);
      Serial.print(", Satélites: "); Serial.println(satellites);
    }
  }
}
