const int pinLED = 13;
const int pinMicrophone = 2;
 
void setup ()
{
  pinMode (pinLED, OUTPUT);
  pinMode (pinMicrophone, INPUT);
}
 
void loop ()
{
  bool soundDetected = digitalRead(pinMicrophone);
  if (soundDetected)
  {
    digitalWrite (pinLED, HIGH);
    delay(100);
  }
  else
  {
    digitalWrite (pinLED, LOW);
    delay(10);
  }
}
