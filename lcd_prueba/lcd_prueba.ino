// Arduprofe Prueba de Modulo I2C para LCD 2x16 By: http://dinastiatecnologica.com
// Debe instalar la libreria LiquidCrystal_I2C para que le funcione el programa
// Debe descargar la Libreria 
/* 
 Conexiones del I2C al Arduino:
 I2C ---->  Arduino
 SCL        A5      
 SDA        A4
 VCC        5V
 GND        GND  
*/

#include<Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); // dependiendo del fabricante del LCD el codigo 0x27 puede cambiar
                                  // 0x3F , 0x20 , 0x38 , 
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ai"); // Mensaje a desplegar
  lcd.setCursor(0,1);
  lcd.print("Lofiuuuuu "); // Mensaje 2 a desplegar
 
}
void loop() { 
  for(int c=0;c<10;c++){
    lcd.print("hola");
  }
}
  
