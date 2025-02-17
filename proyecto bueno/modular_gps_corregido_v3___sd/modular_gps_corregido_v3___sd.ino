#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <BMP280_DEV.h> 
#include <Wire.h>
#include <I2C_RTC.h>
#include <SPI.h>
#include <SD.h>
const int chipSelect = 10;
TinyGPS gps;
SoftwareSerial ss(4, 3);
float temperature, pressure, altitude;            // Create the temperature, pressure, and altitude variables
BMP280_DEV bmp280;                                // Instantiate (create) a BMP280_DEV object and set-up for I2C operation (address 0x77)

static DS1307 RTC;
static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_str(const char *str, int len);

void setup() {
  Serial.begin(9600);
  bmp280.begin(BMP280_I2C_ALT_ADDR);                                  // Default initialization, place the BMP280 into SLEEP_MODE 
  //bmp280.setPresOversampling(OVERSAMPLING_X4);    // Set the pressure oversampling to X4
  //bmp280.setTempOversampling(OVERSAMPLING_X1);    // Set the temperature oversampling to X1
  //bmp280.setIIRFilter(IIR_FILTER_4);              // Set the IIR filter to setting 4
  bmp280.setTimeStandby(TIME_STANDBY_2000MS);     // Set the standby time to 2 seconds
  bmp280.startNormalConversion();                 // Start BMP280 continuous conversion in NORMAL_MODE  
  RTC.begin();

  RTC.setHourMode(CLOCK_H24);
  //RTC.setHourMode(CLOCK_H24);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
  if (RTC.getHourMode() == CLOCK_H24)
  {
     RTC.setMeridiem(HOUR_PM);
  }
  Serial.println("Sats Latitude  Longitude   Alt     Chars    Sentences Checksum   temp   presion   Alt      Date       Time                          ");
  Serial.println("     (deg)     (deg)       (m)      RX      RX        Fail         K      kPa      m    (DD-MM-YYYY HH:MM:SS)");
  Serial.println("------------------------------------------------------------------------------------------------------------------------");

  ss.begin(9600);
}

void loop() {
  float flat, flon;
  String dataString = "";
  unsigned long age, date, time, chars = 0;
  unsigned short sentences = 0, failed = 0;
  if (bmp280.getMeasurements(temperature, pressure, altitude))    // Check if the measurement is complete
{
   File dataFile = SD.open("datalog.txt", FILE_WRITE);
  dataFile.println(temperature);
    dataFile.close();
  print_int(gps.satellites(), TinyGPS::GPS_INVALID_SATELLITES, 5);
  gps.f_get_position(&flat, &flon);
  print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
  print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 12, 6); // Adjust the length to 12 characters
  print_float(gps.f_altitude(), TinyGPS::GPS_INVALID_F_ALTITUDE, 9, 2); // Adjust the length to 9 characters
 
  gps.stats(&chars, &sentences, &failed);
  print_int(chars, 0xFFFFFFFF, 8);
  print_int(sentences, 0xFFFFFFFF, 10);
  print_int(failed, 0xFFFFFFFF, 9);
  Serial.print("  ");
  Serial.print(temperature+273.15);                    // Display the results    
  Serial.print(" ");
  Serial.print(" ");

  Serial.print(pressure/10);    
  Serial.print(" ");
  Serial.print(" ");

  Serial.print(altitude);

 

  Serial.print("  ");

  Serial.print(RTC.getDay());
  Serial.print("-");
  Serial.print(RTC.getMonth());
  Serial.print("-");
  Serial.print(RTC.getYear());

  Serial.print(" ");

  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.print(RTC.getMinutes());
  Serial.print(":");
Serial.print(RTC.getSeconds());
Serial.print(" ");
Serial.println();

    // print to the serial port too:


 
  // Asegurémonos de que no haya ningún caracter no deseado que cause un salto de línea
  while (Serial.available() > 0) {
    Serial.read(); // Descartar cualquier caracter en el búfer de entrada
  }

  smartdelay(100);
}

}

static void smartdelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void print_float(float val, float invalid, int len, int prec) {
  if (val == invalid) {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  } else {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i = flen; i < len; ++i)
      Serial.print(' ');
  }
  smartdelay(0);
}
static void print_int(unsigned long val, unsigned long invalid, int len) {
  char sz[32];
  if (val == invalid)
    strcpy(sz, "*******");
  else
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i = strlen(sz); i < len; ++i)
    sz[i] = ' ';
  if (len > 0)
    sz[len - 1] = ' ';
  Serial.print(sz);
  smartdelay(0);
}

static void print_str(const char *str, int len) {
  int slen = strlen(str);
  for (int i = 0; i < len; ++i)
    Serial.print(i < slen ? str[i] : ' ');
  smartdelay(0);
}
