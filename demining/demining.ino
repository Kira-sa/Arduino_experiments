//arduino-based game for 23fev
// 

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Key.h>
#include <Keypad.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x27,20,4);

//2-7 pins reserved for keypad
#define speakerPin 12
#define servPin    13
#define keyLen 6

int key[keyLen] = {1, 2, 3, 4, 5, 6};
unsigned long previousMills = 0;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long interval = 1000;
int t_minutes = 59;
int t_seconds = 59;

const byte ROWS = 3;
const byte COLS = 3;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'}
};
byte rowPins[ROWS] = {4, 3, 2};
byte colPins[COLS] = {5, 6, 7};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

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
  int btn = customKeypad.getKey();
  if (btn) {
    switch(btn){
      case 1:
        Serial.println("start new game");
        playGame();
        break;
      //
      default:
        Serial.println("unknown command");
    }
  }
}

void showStartScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME!...");
}
void showTimerScreen() {
  lcd.clear();
  showUpdatedTimer();
  lcd.setCursor(3, 0);
  lcd.print("pass:");
}
void showUpdatedTimer() {
  lcd.setCursor(0, 4);
  lcd.print(t_minutes);
  lcd.setCursor(0, 6);
  lcd.print(":");
  lcd.setCursor(0, 7);
  lcd.print(t_seconds);
}

void gameOver() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Game Over");
}

void changeTimer() {
  unsigned  long now = millis();
  if((now - startTime) >= interval) {
    startTime = now;
    if(t_seconds > 0)
      t_seconds--;
    else {
      t_minutes--;
      t_seconds = 59;
    }
    showUpdatedTimer();
    if ((t_minutes<=0)&&(t_seconds<=0))
      gameOver();
  }
}

void playGame() {
  Serial.println("play game");
  startTime = millis();
  //ожидание нажатия кнопок для ввода/удаления/подтверждения введенного пароля разблокировки
  //при правильном пароле - showEndGame(), при неправильном продолжаем играть(?)/уменьшение количества попыток
  char pass[keyLen] = {0};
  int count = 0;
  for(;;) {
    changeTimer();
    int btn = 0; //wait button
    if (btn < 10) {
      //todo: обновить экран, показать введенную цифру
      pass[count] = btn;
      count++;
    }
    if(btn == 11) {
      //ok?
    }
    if(btn == 12) { // сброс введенной последовательности
      count = 0;
      for(int i = 0; i < keyLen; i++)
        pass[i] = 0;
    }
  }
}
