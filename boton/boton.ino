int led = 50;
int led2 = 51;
int boton = 52;
int boton2 =53;

void setup() {
  // put your setup code here, to run once:
pinMode(led, OUTPUT);
pinMode(boton, INPUT);
pinMode(boton2, INPUT);
}

void loop() {


 if (digitalRead(boton) == HIGH){
   digitalWrite(led, HIGH); 
   } else {
   digitalWrite(led, LOW);
   }
if (digitalRead(boton2) == LOW) {
  digitalWrite(led2, HIGH);
}else{
  digitalWrite (led2, LOW);
}
}
 
