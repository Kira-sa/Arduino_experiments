#define inputPin A0 
 
void setup()
{
  pinMode(inputPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.println(analogRead(inputPin));
  delay(40);
}


