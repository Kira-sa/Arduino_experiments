//arduino-based game for 23fev
// 

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x27,20,4);

//pins
#define Btn_1Pin   7
#define Btn_2Pin   8
#define Btn_3Pin   9
#define Btn_4Pin   10
#define Btn_5Pin   11 //start game pin?
#define speakerPin 12
#define servPin    13

//data
#define keyLen 6

int key[keyLen] = {1, 2, 3, 4, 5, 6};

//показ оставшегося времени до детонации на дисплее,
//ввод ключа
//сервик отпускает ключ если всё правильно
//пищалка срабатывает на нажатия кнопок, победу/поражение


void setup() {
  Serial.begin(9600); //debug
  pinMode(speakerPin, OUTPUT);

  pinMode(Btn_1Pin, INPUT);
  pinMode(Btn_2Pin, INPUT);
  pinMode(Btn_3Pin, INPUT);
  pinMode(Btn_4Pin, INPUT);
  pinMode(Btn_5Pin, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 4);
  lcd.print("Try to solve it!");

  showStartScreen();
}

void loop() {
  //ожидание нажатия кнопки, переписать для использования матрицы кнопок
  int btn1 = digitalRead(Btn_1Pin);
  int btn2 = digitalRead(Btn_2Pin);
  int btn3 = digitalRead(Btn_3Pin);
  int btn4 = digitalRead(Btn_4Pin);
  int btn5 = digitalRead(Btn_5Pin);
  int btn = 0;
  if(btn1 == HIGH) {
    btn = 1;
  }

  //обработка нажатия 
  switch(btn):
    case 1:
      Serial.println("start new game");
      playGame();
      break;
    default:
      Serial.println("unknown command");
}

void showStartScreen() {
  //todo: добавить анимацию многоточия
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME!...");
}

void playGame() {
  Serial.println("play game");
  //todo: сделать здесь что-нибудь
  //запуск таймера
  //обновление экрана: отображение таймера и строки для ввода пароля
  //ожидание нажатия кнопок для ввода/удаления/подтверждения введенного пароля разблокировки
  //при правильном пароле - showEndGame(), при неправильном продолжаем играть(?)/уменьшение количества попыток
  int btn = 0;
  switch(btn):
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6;
    case 7:
    case 8:
    case 9:
    case 11: //OK
      break;
    case 12: //CLEAR
      break;
    default:
      Serial.println("unknown command");
  
}

int playRound() {
  //todo: игровой раунд
}
