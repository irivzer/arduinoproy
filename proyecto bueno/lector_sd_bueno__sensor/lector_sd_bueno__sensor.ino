#include <SD.h>
#include <BMP280_DEV.h>                           // Include the BMP280_DEV.h library
float temperature, pressure, altitude; 
BMP280_DEV bmp280;
File myFile;

void setup() {
  Serial.begin(9600);
    bmp280.begin(BMP280_I2C_ALT_ADDR);                                // Default initialisation, place the BMP280 into SLEEP_MODE 
  //bmp280.setPresOversampling(OVERSAMPLING_X4);    // Set the pressure oversampling to X4
  //bmp280.setTempOversampling(OVERSAMPLING_X1);    // Set the temperature oversampling to X1
  //bmp280.setIIRFilter(IIR_FILTER_4);              // Set the IIR filter to setting 4
  bmp280.setTimeStandby(TIME_STANDBY_2000MS);     // Set the standby time to 2 seconds
  bmp280.startNormalConversion();                 // Start BMP280 continuous conversion in NORMAL_MODE  

  Serial.print("Iniciando SD ...");

  // Inicialización de la tarjeta SD en el pin 10
  if (!SD.begin(10)) {
    Serial.println("No se pudo inicializar");
    return;
  }

  Serial.println("Inicialización exitosa");
  
}

void loop() {
  // Abrir el archivo "datalog.txt" en modo de escritura
 if (bmp280.getMeasurements(temperature, pressure, altitude))    // Check if the measurement is complete
  {
  myFile = SD.open("datalog.txt", FILE_WRITE);
 
  if (myFile) {
    Serial.print("Escribiendo SD: ");

    // Escribir en el archivo los valores de tiempo y los valores de los sensores
    myFile.print("Tiempo(ms)=");
    myFile.print(millis());
    myFile.print(temperature+273.15);
    myFile.print(millis());
    myFile.print(", sensor1=");
    myFile.print(pressure/10);
    myFile.print(", sensor2=");
    myFile.print(altitude);


    // Cerrar el archivo después de escribir
    myFile.close();

    // Imprimir en el puerto serie los valores de tiempo y los valores de los sensores
        Serial.print("Tiempo(ms)=");
    Serial.print(millis());
    Serial.print("    ");
     Serial.print(temperature+273.15);                    // Display the results    
    Serial.print(F("*K   "));
    Serial.print(pressure/10);    
    Serial.print(F("kPa   "));
    Serial.print(altitude);
    Serial.println(F("m"));  
    


  } else {
    // Si no se puede abrir el archivo, imprimir un mensaje de error en el puerto serie
    Serial.println("Error al abrir el archivo");
  }

  // Esperar 100 milisegundos antes de volver a realizar el bucle
  delay(1000);
}
 }
  
