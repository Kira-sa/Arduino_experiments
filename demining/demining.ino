//arduino-based game for 23fev
// 

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x27,20,4);

//pins
#define speakerPin 12
#define servPin 13

//data
#define keyLen 6

//показ оставшегося времени до детонации на дисплее,
//ввод ключа
//сервик отпускает ключ если всё правильно
//пищалка срабатывает на нажатия кнопок, победу/поражение

//
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
