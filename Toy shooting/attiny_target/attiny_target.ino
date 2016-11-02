#define inPin0 A1
#define inPot  A3
#define ledPin 4

void setup(void) {
//  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(100);
}

void loop(void) {
  int pinRead0 = analogRead(inPin0);
  int pinPot = analogRead(inPot);
//  Serial.println(pinPot);
//    Serial.println(pinRead0);
  if (pinRead0 > pinPot) {
//    Serial.println(pinRead0);
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
//  }

  delay(100);
}
