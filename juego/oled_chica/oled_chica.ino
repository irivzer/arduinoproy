#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

byte compteur;

void setup() {
  Serial.begin(9600);

  Serial.println("OLED intialized");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void loop() {


  for (compteur = 0 ; compteur < 25 ; compteur++) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("las");
    display.println("mejores");
    display.println("cobijas");
 
    display.display();
    delay(1000);
  }
}
