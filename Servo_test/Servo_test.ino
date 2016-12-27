#include <Servo.h>

Servo myservo;

#define servPin1 13
#define servPin2 1
int pos = 0;

void setup() {

}

void runServo() {
  myservo.attach(servPin1);
  for(pos = 0; pos < 170; pos += 1) { //от 0 до 180 градусов с шагом в 1 градус 
    myservo.write(pos);
    delay(20);                       //ждём 15ms пока серва займёт новое положение
  } 
  for(pos = 170; pos >= 1; pos -= 1) {
    myservo.write(pos);
    delay(20);
  }
  myservo.detach();
}

void loop() {
  runServo();
}
