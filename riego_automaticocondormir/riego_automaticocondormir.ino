#include "LowPower.h"

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int LED = 12;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;

void setup() {
  Serial.begin(9600);
  // Configura el pin del botón como entrada con resistencia pull-up interna
pinMode(LED,OUTPUT);

}

void loop() {
  // Lee el estado del botón

  sensorValue = analogRead(analogInPin);
   outputValue = map(sensorValue, 0, 1023, 0, 255);

  // Si el botón está presionado (estado bajo)
  if (outputValue >= 100){
    Serial.println("se detecto el boton ");
    // Enciende el LED
    digitalWrite(LED, LOW);
    Serial.println("up");
    delay(5000);
    digitalWrite(LED, HIGH);
    Serial.println("down");
    delay(5000);
    digitalWrite(LED, LOW);
    Serial.println("up ");
    delay(5000);
    digitalWrite(LED, HIGH);
    Serial.println("down ");
    delay(1000);
      for (int i = 0 ;  i  <  3 ; i++)
             LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  } else {
    Serial.println("NO SE DETECTO "   );
    // Apaga el LED
    digitalWrite(LED, LOW);
    digitalWrite(LED, LOW);
    delay(1000);
    for (int i = 0 ;  i  <  3 ; i++)
             LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
  Serial.println("RIEGO NORMAL");
   digitalWrite(LED, LOW);
    delay(5000);
    digitalWrite(LED, HIGH);
    delay(5000);
    digitalWrite(LED, LOW);
    delay(5000);
    digitalWrite(LED, HIGH);
    delay(1000);
       for (int i = 0 ;  i  <  3 ; i++)
             LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    
}
