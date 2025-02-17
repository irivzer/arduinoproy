#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

int segundo,minuto,hora,dia,mes;
long anio; //variable año
DateTime HoraFecha;

void setup () {
  Serial.begin(9600);
  rtc.begin(); //Inicializamos el RTC
  
}

void loop () {
    HoraFecha = rtc.now(); //obtenemos la hora y fecha actual
    
    segundo=HoraFecha.second();
    minuto=HoraFecha.minute();
    hora=HoraFecha.hour();
    dia=HoraFecha.day();
    mes=HoraFecha.month();
    anio=HoraFecha.year();
if (dia <= 9)
{
      Serial.print("0");
    Serial.print(dia);
    Serial.print("/");
    Serial.print(mes);
    Serial.print("/");
    Serial.print(anio);
  
    Serial.print("   ");
  Serial.print(hora);
    Serial.print(":");
    Serial.print(minuto);
    Serial.print(":");
    Serial.print(segundo);
    Serial.println();
    delay(1000);
  
}
else 
{
      Serial.print(dia);
    Serial.print("/");
    Serial.print(mes);
    Serial.print("/");
    Serial.print(anio);
    
    Serial.print("   ");
 Serial.print(hora);
    Serial.print(":");
    Serial.print(minuto);
    Serial.print(":");
    Serial.print(segundo);
    Serial.println();
    delay(1000);
}
    //Enviamos por el puerto serie la hora y fecha.

}
