#include <SoftwareSerial.h> // libreria que permite establecer pines digitales
 #include <Servo.h>
        // para comunicacion serie

SoftwareSerial miBT(50, 51);  // pin 10 como RX, pin 11 como TX
Servo servoMotor;

char Dato = 0;
int LED = 52;
void setup(){
  Serial.begin(9600);   // comunicacion de monitor serial a 9600 bps
  Serial.println("Listo");  // escribe Listo en el monitor
  miBT.begin(9600);    // comunicacion serie entre Arduino y el modulo a 38400 bps
servoMotor.attach(9);
}

void loop(){
if (miBT.available()){       // si hay informacion disponible desde modulo
   
   Dato = miBT.read();
   if (Dato == '3'){
   digitalWrite(LED, HIGH);
   servoMotor.write(2);
   }
   if (Dato == '1'){
   digitalWrite(LED, LOW);
   servoMotor.write(90);
  
   }
   if (Dato == '4'){
   digitalWrite(LED, LOW);
   servoMotor.write(180);
   }
 
}
   // lee Bluetooth y envia a monitor serial de Arduino

if (Serial.available())     // si hay informacion disponible desde el monitor serial
   miBT.write(Serial.read());   // lee monitor serial y envia a Bluetooth

}
