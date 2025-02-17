const int sensorPin = A1; // Pin analógico para la lectura

void setup() {
  Serial.begin(9600); // Inicializa la comunicación serial
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Lee el valor analógico del pin A0
  float voltage = (sensorValue * 5.0) / 1023.0; // Calcula el voltaje
  Serial.print("Voltaje: ");
  Serial.println(voltage); // Imprime el voltaje en el monitor serial
  delay(100); // Espera 100 milisegundos
}
