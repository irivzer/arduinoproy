#include <SoftwareSerial.h>
#include <BMP280_DEV.h>  
#include <TinyGPS.h>
#include <Wire.h>
#include <I2C_RTC.h>

float temperature, pressure, altitude;            // Create the temperature, pressure and altitude variables
BMP280_DEV bmp280; 
/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/

TinyGPS gps;
SoftwareSerial ss(4, 3);

static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_date(TinyGPS &gps);
static void print_str(const char *str, int len);
static DS1307 RTC;

    
void setup()
{
  Serial.begin(9600);
 bmp280.begin(BMP280_I2C_ALT_ADDR);                                // Default initialisation, place the BMP280 into SLEEP_MODE 
  //bmp280.setPresOversampling(OVERSAMPLING_X4);    // Set the pressure oversampling to X4
  //bmp280.setTempOversampling(OVERSAMPLING_X1);    // Set the temperature oversampling to X1
  //bmp280.setIIRFilter(IIR_FILTER_4);              // Set the IIR filter to setting 4
  bmp280.setTimeStandby(TIME_STANDBY_1000MS);     // Set the standby time to 2 seconds
  bmp280.startNormalConversion();                 // Start BMP280 continuous conversion in NORMAL_MODE  
  Serial.println("Sats HDOP Latitude  Longitude  Fix  Date       Time     Date Alt     Chars Sentences Checksum");
  Serial.println("          (deg)     (deg)      Age                      Age  (m)      RX    RX        Fail");
  Serial.println("-------------------------------------------------------------------------------------------------------------------------------------");

  ss.begin(9600);
  RTC.begin();
   RTC.setHourMode(CLOCK_H12);
    if (RTC.getHourMode() == CLOCK_H12)
  {
     RTC.setMeridiem(HOUR_PM);
  }
}

void loop()

{

  float flat, flon;
  unsigned long age, date, time, chars = 0;
  unsigned short sentences = 0, failed = 0;

  if (bmp280.getMeasurements(temperature, pressure, altitude))    // Check if the measurement is complete
  {

     Serial.print(temperature+273.15);                    // Display the results    
    Serial.print(F("*K   "));
    Serial.print(pressure/10);    
    Serial.print(F("kPa   "));
    Serial.print(altitude);
    Serial.println(F("m"));   
switch (RTC.getWeek())
  {
    case 1:
      Serial.print("SUN");
      break;
    case 2:
      Serial.print("MON");
      break;
    case 3:
      Serial.print("TUE");
      break;
    case 4:
      Serial.print("WED");
      break;
    case 5:
      Serial.print("THU");
      break;
    case 6:
      Serial.print("FRI");
      break;
    case 7:
      Serial.print("SAT");
      break;
  }
  
  
  
   Serial.print(" ");
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



  if (RTC.getHourMode() == CLOCK_H12)
  {
    switch (RTC.getMeridiem()) {
      case HOUR_AM :
        Serial.print(" AM");
        break;
      case HOUR_PM :
        Serial.print(" PM");
        break;
    }
  }
    Serial.print(" ");
  print_int(gps.satellites(), TinyGPS::GPS_INVALID_SATELLITES, 5);
  print_int(gps.hdop(), TinyGPS::GPS_INVALID_HDOP, 5);
  gps.f_get_position(&flat, &flon, &age);
  print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
  print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 11, 6);
  print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
  print_date(gps);
  print_float(gps.f_altitude(), TinyGPS::GPS_INVALID_F_ALTITUDE, 7, 2);

 


  gps.stats(&chars, &sentences, &failed);
  print_int(chars, 0xFFFFFFFF, 6);
  print_int(sentences, 0xFFFFFFFF, 10);
  print_int(failed, 0xFFFFFFFF, 9);
  Serial.println();
  } 
  smartdelay(1);
}

static void smartdelay(unsigned long ms)
{
unsigned long start = millis();
  while (millis() - start < ms) { 
    while (ss.available())
      gps.encode(ss.read());
  } // Aquí se cierra el bucle while
}
static void print_float(float val, float invalid, int len, int prec)
{
  if (val == invalid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartdelay(0);
}

static void print_int(unsigned long val, unsigned long invalid, int len)
{
  char sz[32];
  if (val == invalid)
    strcpy(sz, "*******");
  else
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartdelay(0);
}

static void print_date(TinyGPS &gps)
{
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
    Serial.print("********** ******** ");
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
        month, day, year, hour, minute, second);
    Serial.print(sz);
  }
  print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
  smartdelay(0);
}

static void print_str(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartdelay(0);
}
