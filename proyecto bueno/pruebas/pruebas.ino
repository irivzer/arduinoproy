int BOTON = 53;
int LED = 13;

void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
pinMode(53,INPUT);



}

void loop() {
  int a = digitalRead(BOTON);
  if(a == HIGH){ 
    digitalWrite(LED,HIGH);
    
  }
  else
  {digitalWrite(LED,LOW);
  
  // put your main code here, to run repeatedly:

  }
}
