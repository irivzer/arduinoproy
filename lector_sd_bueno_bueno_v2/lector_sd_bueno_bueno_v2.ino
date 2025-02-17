#include <SD.h>
#include <BMP280_DEV.h>                           // Include the BMP280_DEV.h library
#include <Wire.h>
#include "RTClib.h"
float temperature, pressure, altitude; 
int segundo,minuto,hora,dia,mes;
long anio; //variable año
DateTime HoraFecha;
BMP280_DEV bmp280;
File myFile;
RTC_DS1307 rtc;

void setup() 
{
     Serial.begin(9600);
     rtc.begin(); //Inicializamos el RTC
     bmp280.begin(BMP280_I2C_ALT_ADDR);                                // Default initialisation, place the BMP280 into SLEEP_MODE 
     //bmp280.setPresOversampling(OVERSAMPLING_X4);    // Set the pressure oversampling to X4
     //bmp280.setTempOversampling(OVERSAMPLING_X1);    // Set the temperature oversampling to X1
     //bmp280.setIIRFilter(IIR_FILTER_4);              // Set the IIR filter to setting 4
     bmp280.setTimeStandby(TIME_STANDBY_1000MS);     // Set the standby time to 2 seconds
     bmp280.startNormalConversion();                 // Start BMP280 continuous conversion in NORMAL_MODE  

     Serial.print("Iniciando SD ...");

     // Inicialización de la tarjeta SD en el pin 10
     if (!SD.begin(10)) 
     {
         Serial.println("No se pudo inicializar");
         return;
     }

     Serial.println("Inicialización exitosa");
  
}

void loop() 
{
  // Abrir el archivo "datalog.txt" en modo de escritura
 if (bmp280.getMeasurements(temperature, pressure, altitude))    // Check if the measurement is complete
  {
      // Escribir en el archivo los valores de tiempo y los valores de los sensores
    HoraFecha = rtc.now(); //obtenemos la hora y fecha actual
        segundo=HoraFecha.second();
        minuto=HoraFecha.minute();
        hora=HoraFecha.hour();
        dia=HoraFecha.day();
        mes=HoraFecha.month();
        anio=HoraFecha.year();
     
  myFile = SD.open("datalog.txt", FILE_WRITE);
 
   if (myFile) 
   {
      Serial.print("Escribiendo SD: ");
      myFile.print(temperature+273.15);                    // Display the results    
      myFile.print(("    "));
      myFile.print(pressure);    
      myFile.print(("    "));
      myFile.print(altitude);
      myFile.print(("   ")); 
     
          //Enviamos por el puerto serie la hora y fecha.
      if (dia <= 9)
      {
         myFile.print("0");
         myFile.print(dia);
         myFile.print("/");
         myFile.print(mes);
         myFile.print("/");
         myFile.print(anio);
         myFile.print("   ");
         myFile.print(hora);
         myFile.print(":");
         myFile.print(minuto);
         myFile.print(":");
         myFile.print(segundo);
         myFile.println();
    }
    else 
     {
         myFile.print(dia);
         myFile.print("/");
         myFile.print(mes);
         myFile.print("/");
         myFile.print(anio);    
         myFile.print("   ");
         myFile.print(hora);
         myFile.print(":");
         myFile.print(minuto);
         myFile.print(":");
         myFile.print(segundo);
         myFile.println();
    }
 myFile.close();      // Cerrar el archivo después de escribir
      // Imprimir en el puerto serie los valores de tiempo y los valores de los sensores
      Serial.print(temperature+273.15);                    // Display the results    
      Serial.print(("    "));
      Serial.print(pressure);    
      Serial.print(("    "));
      Serial.print(altitude);
      Serial.print(("   "));  
          //Enviamos por el puerto serie la hora y fecha.
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
    }
   }
    
   else 
   {
    // Si no se puede abrir el archivo, imprimir un mensaje de error en el puerto serie
    Serial.println("Error al abrir el archivo");
   }

   // Esperar 100 milisegundos antes de volver a realizar el bucle
  delay(100);
  }
}
  
