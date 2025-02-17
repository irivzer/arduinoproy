const int pin13 = 13;

void setup() {
    pinMode(pin13, OUTPUT);
    digitalWrite(pin13, LOW);
    Serial.begin(9600); // Configura la velocidad de comunicación serial
}

void loop() {
    if (Serial.available() > 0) { // Si hay datos en el puerto serial
        char command = Serial.read(); // Lee el comando
        if (command == 'u') { // Comando 'u' para tecla arriba
            digitalWrite(pin13, HIGH); // Activa el pin 13
        } else if (command == 'd') { // Comando 'd' para tecla abajo
            digitalWrite(pin13, LOW); // Apaga el pin 13
        }
    }
}
