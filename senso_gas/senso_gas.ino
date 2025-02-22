                                       /*
  Capitulo 28 de Arduino desde cero en Español.
  Programa que demuestra el funcionamiento del sensor de gas natural MQ-5 imprimiendo
  en el monitor serial y serial plotter los valores obtenidos cuando el sensor es
  expuesto a gas butano.

  Autor: bitwiseAr  

*/

int VALOR;      // almacena valor leido del sensor


void setup(){
  Serial.begin(9600);   // inicializa comunicacion serie a 9600 bps
  // entradas analogicas no requieren inicializacion
}

void loop(){
  VALOR = analogRead(A0); // lee entrada A0 y asigna a variable VALOR
  Serial.println(VALOR);  // imprime en monitor serial el valor
  delay(500);     // breve demora de medio segundo

  if (VALOR >= 200 ){
    
    Serial.println("corre");
    delay(1000);
  }
}
