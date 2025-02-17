#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial ss(4, 3);

static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_str(const char *str, int len);

void setup() {
  Serial.begin(9600);
  Serial.println("Testing TinyGPS library v. " + String(TinyGPS::library_version()));
  Serial.println("by Mikal Hart");
  Serial.println();
  Serial.println("Sats Latitude  Longitude   Alt     Chars Sentences Checksum");
  Serial.println("     (deg)     (deg)       (m)      RX    RX        Fail");
  Serial.println("-------------------------------------------------------------");

  ss.begin(9600);
}

void loop() {
  float flat, flon;
  unsigned long age, date, time, chars = 0;
  unsigned short sentences = 0, failed = 0;

  print_int(gps.satellites(), TinyGPS::GPS_INVALID_SATELLITES, 5);
  gps.f_get_position(&flat, &flon);
  print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
  print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 12, 6); // Ajusta la longitud a 12 caracteres
  print_float(gps.f_altitude(), TinyGPS::GPS_INVALID_F_ALTITUDE, 9, 2); // Ajusta la longitud a 9 caracteres
  gps.stats(&chars, &sentences, &failed);
  print_int(chars, 0xFFFFFFFF, 6);
  print_int(sentences, 0xFFFFFFFF, 10);
  print_int(failed, 0xFFFFFFFF, 9);
  Serial.println();

  smartdelay(1000);
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
