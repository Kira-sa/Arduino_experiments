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

char key[keyLen] = "12345";
unsigned long previousMills = 0;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
// unsigned long interval = 1000;
unsigned long interval = 300;

int t_minutes = 59;
int t_seconds = 59;
int stage = 0;
bool updateScreen = false;
bool isDisabled = false;
char pass[keyLen] = {0};
int passC = 0;

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
  if (btn && !isDisabled) {
    Serial.println(btn);
    Serial.println("Start new game");
    playGame();
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
  lcd.setCursor(7, 1);
  lcd.print("        ");
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

void clearPassword() {
  for(int i = 0; i < keyLen; i++) {
    pass[i] = {0};
  }
  showEmptyPass();
}

bool checkPassword() {
  for(int i = 0; i < keyLen; i++) {
    if (pass[i] != key[i])
      return false;
  }
  return true;
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

void showUpdatedPassword() { //перерисовать ячейки с паролем
  lcd.setCursor(5, 2);
  lcd.print(pass);
}

void showEmptyPass() {
  lcd.setCursor(5, 2);
  lcd.print("        ");
}

void showPasswordScreen() {
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("PASS:");
  lcd.setCursor(12, 3);
  lcd.print("9:CLEAR");
  showUpdatedPassword();
}

void showWinScreen() {
  lcd.clear();
  lcd.setCursor(1, 1);
  lcd.print("object deactivated");
}

void playGame() {
  Serial.println("play game");
  startTime = millis();
  showMainScreen();
  int passC = 0;
  int count = 0;
  for(;;) {
    int timeCounter = changeTimer();
    if(timeCounter > 0) {
      gameOver();
      return;
    }
    char btn = customKeypad.getKey();
    if (btn!=0){
      Serial.println(btn);
      switch(stage) {
        case 0:// main screen
          if (btn == '1') {
            stage = 1;
            updateScreen = true;
          } 
          else if (btn == '3') {
            stage = 2;
            updateScreen = true;
          }
        break;    
        case 1:// menu
          if (btn == '1') {// show change timer screen
            stage = 3;
            updateScreen = true;
          } 
          else if (btn == '2') {// show disable bomb
            stage = 4;
            updateScreen = true;
          }
          else if (btn == '3') {//return to main screen
            stage = 0;
            updateScreen = true;
          }
        break;
        case 2:// help screen
          if (btn != 0) {
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
        case 4:// disable timer
          if (passC <= keyLen) {
            if (btn == '9') {
              clearPassword();
              stage = 0;
              updateScreen = true;
            }
            else {
              pass[passC] = btn;
              passC++;
              showUpdatedPassword();
              if(passC == keyLen-1) {
                if(checkPassword()) {//если правильный вывести победу и выйти из цикла(совсем), иначе - сброс пароля и по новой
                  delay(500);
                  stage = 0;
                  clearPassword();
                  showWinScreen();
                  isDisabled = true;
                  return;
                }
                Serial.print("result: ");
                Serial.println(pass);
                clearPassword();
                passC = 0;
              }
              Serial.print("passC = ");
              Serial.println(passC);
            }  
          }
        break;
        default:
          Serial.println("unknown stage value");
        break;
      }
    }
    if (updateScreen) {
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
          // showDisableScreen();
          showPasswordScreen();
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
  return;
}
// stages:
// 0 - start screen with timer
// 1 - menu screen
// 2 - help screen
// 3 - edit timer
// 4 - disable 
// 5 - disable pass input

