//arduino-based game for 23fev
// 

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//#include <Servo.h>
#include <Key.h>
#include <Keypad.h>

//Servo myservo;
LiquidCrystal_I2C lcd(0x27,20,4);

//2-7 pins reserved for keypad
#define speakerPin 12
//#define servPin    13
#define keyLen 6

int key[keyLen] = {1, 2, 3, 4, 5, 6};
unsigned long previousMills = 0;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long interval = 1000;
int t_minutes = 59;
int t_seconds = 59;
int stage = 0;
bool updateScreen = false;

// stages:
// 0 - start screen with timer
// 1 - menu screen
// 2 - help screen
// 3 - edit timer
// 4 - disable 
// 

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

  lcd.init();
  lcd.backlight();

  showStartScreen();
}

void loop() {
  char btn = customKeypad.getKey();
  if (btn) {
    Serial.println(btn);
    Serial.println("Start new game");
    int game = playGame();
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
  lcd.setCursor((t_minutes > 9) ? 7 : 8, 1);
  lcd.print(t_minutes);
  lcd.setCursor(9, 1);
  lcd.print(":");
  lcd.setCursor(10, 1);
  lcd.print(t_seconds);
}

void gameOver() {
  Serial.println("Game Over!");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Game Over");
}

int changeTimer() {
  unsigned long now = millis();
  if((now - startTime) >= interval) {
    startTime = now;
    if(t_seconds > 0)
      t_seconds--;
    else if (t_seconds == 0) {
      t_minutes--;
      t_seconds = 59;
    }
    if ((stage == 0)||(stage == 4))//на каких экранах показывать таймер?
      showUpdatedTimer();
    if ((t_minutes<=0)&&(t_seconds<=0))
      return 1;
  }
  return 0;
}

void showMainScreen() {
  Serial.println("showMainScreen()");
  lcd.clear();
  lcd.setCursor((t_minutes > 9) ? 7 : 8, 1);
  lcd.print(t_minutes);
  lcd.setCursor(9, 1);
  lcd.print(":");
  lcd.setCursor(10, 1);
  lcd.print(t_seconds);
  lcd.setCursor(0, 3);
  lcd.print("1:Edit");
  lcd.setCursor(14, 3);
  lcd.print("3:Help");
}

void showMenuScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MENU");
  lcd.setCursor(0, 1);
  lcd.print("1.Edit timer");
  lcd.setCursor(0, 2);
  lcd.print("2.Disable bomb");
  lcd.setCursor(0, 3);
  lcd.print("3.Return");
}

void showHelpScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HELP");
  lcd.setCursor(0, 1);
  lcd.print("Please read manual :)");
}

void showEditTimerScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("EDIT");
  lcd.setCursor(0, 1);
  lcd.print("Error: No access");
}

void showDisableScreen() {
  lcd.clear();
  // set timer on screen
  lcd.setCursor(0, 2);
  lcd.print("PASS:");
}

int playGame() {
  Serial.println("play game");
  startTime = millis();
  showMainScreen();
  char pass[keyLen] = {0};
  int count = 0;
  for(;;) {
    int timeCounter = changeTimer();
    if(timeCounter > 0) {
      gameOver();
      return 0;
    }
    char btn = customKeypad.getKey();
    if (btn!=0){
      Serial.println(btn);
      switch(stage) {
        case 0:// main screen
          if (btn == '1') {
            Serial.println("from main screen to menu");
            stage = 1;
            updateScreen = true;
          } 
          else if (btn == '3') {
            Serial.println("from main screen to help");
            stage = 2;
            updateScreen = true;
          }
          else 
            Serial.println("unknown");
        break;    
        case 1:// menu
          if (btn == '1') {
            stage = 3;
            updateScreen = true;
            // show change timer screen
          } 
          else if (btn == '2') {
            stage = 4;
            updateScreen = true;
            // show disable bomb
          }
          else if (btn == '3') {
            stage = 0;
            updateScreen = true;
            //return to main screen
          }
        break;
        case 2:// help screen
          if (btn == '1') {
            stage = 0;
            updateScreen = true;
          } 
        break;
        case 3:// edit timer
          if (btn == '1') {
            stage = 0;
            updateScreen = true;
          }   
          break;
        case 4:// disable 
          if (btn == '9') {
            stage = 0;
            updateScreen = true;
          }
          else {
            // перейти к проверке ввода пароля, 9 -> clear, когда поле пароля пусто 9 -> back
          }  
        break;
        default:
          Serial.println("unknown stage value");
        break;
      }
    }
    if (updateScreen) {
      Serial.println("updateScreen == true");
      switch(stage) {
        case 0:
          showMainScreen();
          break;
        case 1:
          showMenuScreen();
          break;
        case 2: 
          showHelpScreen();
          break;
        case 3:
          showEditTimerScreen();
          break;
        case 4:
          showDisableScreen();
          break;
        default:
          Serial.println("changing screen on stage error ");
          Serial.println(stage);
          stage = 0;
      }
      updateScreen = false;
    }
    //
  }
  return 1;
}
// stages:
// 0 - start screen with timer
// 1 - menu screen
// 2 - help screen
// 3 - edit timer
// 4 - disable 

        // char btn = customKeypad.getKey();
        // Serial.println(btn);
        // if (btn == 1) {
        // } 
        // else if (btn == 2) {
        // }
