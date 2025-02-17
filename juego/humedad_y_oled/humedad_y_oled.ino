#include <DHT.h>
#define DHTPIN 2     // El pin al que está conectado el sensor DHT11
#define DHTTYPE DHT11   // Tipo de sensor DHT (DHT11, DHT22, AM2302, etc.)
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
DHT dht(DHTPIN, DHTTYPE);
const int pin = 9;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

byte compteur;
void setup() {
  Serial.begin(9600);
  Serial.println("Leyendo sensor DHT11...");
  dht.begin();
   pinMode(pin, OUTPUT);  //definir pin como salida
  Serial.println("OLED intialized");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  // text display tests
  display.setTextSize(1.8);
  display.setTextColor(WHITE);
}

void loop() {
  delay(1000);  // Espera 2 segundos entre lecturas

  float temperatura = dht.readTemperature();  // Lee la temperatura en grados Celsius
  float humedad = dht.readHumidity();        // Lee la humedad relativa
  
  // Verifica si la lectura del sensor fue exitosa
  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("Error al leer el sensor DHT11!");
    return;
  }
   for (compteur = 0 ; compteur < 25 ; compteur++) {
      display.clearDisplay();
    display.setCursor(0, 0);
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C\t");
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.println("%");
  display.println("Temperatura: ");
  display.print(temperatura);
  display.println(" C\t");
  display.println("Humedad: ");
  display.print(humedad);
  display.println("");
    display.display();
    }
    if (humedad >= 50){
    digitalWrite(pin, HIGH);
    }
    else
    digitalWrite(pin, LOW);
}
