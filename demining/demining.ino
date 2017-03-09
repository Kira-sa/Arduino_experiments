//simple arduino-based game for 23fev
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
#define keyLen 9

#define C4  262
#define CS4 277
#define D4  294
#define DS4 311
#define E4  330
#define F4  349
#define FS4 370
#define G4  392
#define GS4 415
#define A4  440
#define AS4 466
#define B4  494
#define C5  523

int win[3][3] = {{C4, E4, G4}, {4, 4, 4}};
int lose[3][3] = {{C4, C4, C4}, {4, 4, 4}};
// playSong(win[0], win[1], sizeof(win[0])/2); // играем победную мелодию
// playSong(lose[0], lose[1], sizeof(lose[0])/2);//играем проигрышную мелодию

char key[keyLen] = "34176855";
unsigned long previousMills = 0;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long interval = 1000;
// unsigned long interval = 300;
int t_minutes = 44;
int t_seconds = 59;
int stage = 0;
bool updateScreen = false;
bool isDisabled = false;
bool penalty = false;
bool sound = true;
char pass[keyLen] = {0};
int passC = 0;

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

void setup() {
  Serial.begin(9600); //debug
  pinMode(speakerPin, OUTPUT);

  lcd.init();
  lcd.backlight();
  shStart();
}

void loop() {
  char btn = customKeypad.getKey();
  if (btn && !isDisabled) {
    Serial.println(btn);
    Serial.println("Start new game");
    playGame();
  }
}

void servoPing() {
  myservo.attach(servPin);
  for(int pos = 0; pos < 100; pos += 1) { //от 0 до 180 градусов с шагом в 1 градус 
    myservo.write(pos);
    delay(20);
  } 
  for(int pos = 100; pos >= 1; pos -= 1) {
    myservo.write(pos);
    delay(20);
  }
  myservo.detach();  
}

void playSong(int melody[], int duration[], int count) {
  for (int i = 0; i < count; i++){
    playNote(melody[i], duration[i]);
  }
}

void playNote(int note, int duration) {
  tone(speakerPin, note, 1000 / duration);
  delay((1000 / duration) * 1.3);
  noTone(speakerPin);
}

void shStart() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press any key...");
}

void shUpdatedTimer() {
  lcd.setCursor(7, 1);
  lcd.print("        ");
  lcd.setCursor((t_minutes > 9) ? 7 : 8, 1);
  lcd.print(t_minutes);
  lcd.setCursor(9, 1);
  lcd.print(":");
  lcd.setCursor(10, 1);
  lcd.print(t_seconds);
  if(sound) 
    playNote(C5, 8); // every second beep :)
}

void shGameOver() {
  lcd.clear();
  lcd.setCursor(1, 1);
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
    if ((stage == 0)||(stage == 4))
      shUpdatedTimer();
    if ((t_minutes<=0)&&(t_seconds<=0))
      return 1;
  }
  return 0;
}

void clearPassword() {
  for(int i = 0; i < keyLen; i++) {
    pass[i] = {0};
  }
  shEmptyPass();
}

bool checkPassword() {
  for(int i = 0; i < keyLen; i++) {
    if (pass[i] != key[i]) {
      if(sound)
        playSong(lose[0], lose[1], sizeof(lose[0])/2); //todo
      return false;
    }
  }
  return true;
}

void shMain() {
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

void shMenu() {
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

void shHelp() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HELP");
  lcd.setCursor(0, 2);
  lcd.print("To disable bomb");
  lcd.setCursor(0, 3);
  lcd.print("Input right password");
}

void shEditTimer() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("EDIT");
  lcd.setCursor(0, 2);
  lcd.print("Error: Access denied");
}

void shUpdatedPassword() { //перерисовать ячейки с паролем
  lcd.setCursor(5, 2);
  lcd.print(pass);
}

void shEmptyPass() {
  lcd.setCursor(5, 2);
  lcd.print("        ");
}

void shPassword() {
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("PASS:");
  lcd.setCursor(12, 3);
  lcd.print("9:RETURN");
  shUpdatedPassword();
}

void shWin() {
//  servoPing();
  lcd.clear();
  lcd.setCursor(1, 1);
  lcd.print("object deactivated");
  if(sound)
    playSong(win[0], win[1], sizeof(win[0])/2);
}

void playGame() {
  Serial.println("play game");
  startTime = millis();
  shMain();
  int passC = 0;
  int count = 0;
  for(;;) {
    int timeCounter = changeTimer();
    if(timeCounter > 0) {
      shGameOver();
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
              passC = 0;
              stage = 0;
              updateScreen = true;
            }
            else {
              pass[passC] = btn;
              passC++;
              shUpdatedPassword();
              if(passC == keyLen-1) {
                if(checkPassword()) {//если правильный вывести победу и выйти из цикла(совсем), иначе - сброс пароля и по новой
                  delay(500);
                  stage = 0;
                  clearPassword();
                  shWin();
                  isDisabled = true;
                  return;
                }
                else if(penalty)
                  t_minutes--;
                // Serial.print("result: ");
                // Serial.println(pass);
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
          shMain();
          break;
        case 1:
          shMenu();
          break;
        case 2: 
          shHelp();
          break;
        case 3:
          shEditTimer();
          break;
        case 4:
          shPassword();
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

