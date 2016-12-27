// new candy dispenser for 2016-2017

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x27,20,4);

#define led_1Pin 2
#define led_2Pin 3
#define led_3Pin 4
#define led_4Pin 5
#define led_5Pin 6

#define Btn_1Pin 7
#define Btn_2Pin 8
#define Btn_3Pin 9
#define Btn_4Pin 10
#define Btn_5Pin 11 //start game pin

#define speakerPin 12
#define servPin 13

#define B0  31
#define C1  33
#define CS1 35
#define D1  37
#define DS1 39
#define E1  41
#define F1  44
#define FS1 46
#define G1  49
#define GS1 52
#define A1  55
#define AS1 58
#define B1  62
#define C2  65
#define CS2 69
#define D2  73
#define DS2 78
#define E2  82
#define F2  87
#define FS2 93
#define G2  98
#define GS2 104
#define A2  110
#define AS2 117
#define B2  123
#define C3  131
#define CS3 139
#define D3  147
#define DS3 156
#define E3  165
#define F3  175
#define FS3 185
#define G3  196
#define GS3 208
#define A3  220
#define AS3 233
#define B3  247
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
#define CS5 554
#define D5  587
#define DS5 622
#define E5  659
#define F5  698
#define FS5 740
#define G5  784
#define GS5 831
#define A5  880
#define AS5 932
#define B5  988
#define C6  1047
#define CS6 1109
#define D6  1175
#define DS6 1245
#define E6  1319
#define F6  1397
#define FS6 1480
#define G6  1568
#define GS6 1661
#define A6  1760
#define AS6 1865
#define B6  1976
#define C7  2093
#define CS7 2217
#define D7  2349
#define DS7 2489
#define E7  2637
#define F7  2794
#define FS7 2960
#define G7  3136
#define GS7 3322
#define A7  3520
#define AS7 3729
#define B7  3951
#define C8  4186
#define CS8 4435
#define D8  4699
#define DS8 4978

#define songs 2

// tone / duration / button
int song1[3][5] = {{C4, G3, G3, A3, G3}, {4, 2, 4, 2, 4}, {5, 4, 3, 4, 5}};

int el[3][8] = {
  {C4, A4, A4, G4, A4, F4, C4, C4}, 
  {4, 4, 4, 4, 4, 4, 4, 4},
  {1, 5, 5, 4, 5, 3, 1, 1}};

int el1[3][14] = {
  {C4, A4, A4, G4, A4, F4, C4, C4, C4, A4, A4, AS4, G4, C5}, 
  {4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,   4,  2},
  {1,  5,  5,  4,  5,  3,  1,  1,  1,  4,  4,  5,   3,  5}
};

int el2[3][14] = {
  {C5, D4, D4, AS4, AS4, A4, G4, F4, F4, A4, A4, G4, A4, F4}, 
  {4,  4,  4,  4,   4,   4,  4,  4,  4,  4,  4,  4,  4,  2},
  {5,  1,  1,  5,   5,   4,  3,  2,  2,  5,  5,  4,  5,  2}
};

int el_f[3][28] = {
  {C4, A4, A4, G4, A4, F4, C4, C4, C4, A4, A4, AS4, G4, C5, C5, D4, D4, AS4, AS4, A4, G4, F4, F4, A4, A4, G4, A4, F4},
  {4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,   4,  2,  4,  4,  4,  4,   4,   4,  4,  4,  4,  4,  4,  4,  4,  2},
  {1,  5,  5,  4,  5,  3,  1,  1,  1,  4,  4,  5,   3,  5,  5,  1,  1,  5,   5,   4,  3,  2,  2,  5,  5,  4,  5,  2}
};

int knz1[3][13] = {
  {B3, B3, B4, FS4, A4, G4, E4, D4, D4, D5, C5, C5, B4},
  {4,  4,  4,  4,   4,  4,  2,  4,  4,  4,  4,  4,  4 },
  {1,  1,  5,  3,   5,  4,  3,  2,  2,  5,  4,  4,  3}
};

int knz2[3][13] = {
  {D5, C5, A4, FS4, C5, B4, B4, B3, B3, B4, A4, A4, G4},
  {4,  4,  4,  4,   4,  4,  2,  4,  4,  4,  4,  4,  4 },
  {5,  4,  3,  2,   3,  2,  2,  1,  1,  5,  4,  4,  3}
};

int abba1[3][37] = {
  {CS4, D4, E4, CS5, CS4, D4, E4, B4, CS4, DS4, F4, 0, A4, GS4, FS4, FS4, GS4, FS4, E4, E4, E4, FS4, E4, E4, E4, FS4, E4, D4, CS4, CS4, CS4, D4, E4, E4, D4, CS4, B3},
  {8,   8,  4,  2,   8,   8,  4,  2,  8,   8,   4,  8, 2,  8,   8,   4,   4,   4,   8,  8,  2,  4,   8,  8,  4,  4,   4,  8,  8,   4,   4,   4,  4,  8,  8,  8,   2},
  {1,   2,  3,  5,   1,   2,  3,  5,  1,   2,   3,  1, 1,  1,   1,   1,   1,   1,   1,  1,  1,  1,   1,  1,  1,  1,   1,  1,  1,   1,   1,   1,  1,  1,  1,  1,   1}
};

int win[3][3] = {{A5, A5, A5}, {4, 4, 4}, {1, 3, 5}};
int lose[3][3] = {{D2, D2, D2}, {4, 4, 4}, {5, 3, 1}};

int difficulty = 1;
const char* s_difficulty[] = {"Demo", "Normal", "Hard"};
//0 - demo
//1 - normal
//2 - hard
int pos = 0;

byte tag[8] = {
  B00000,
  B10001,
  B01010,
  B00100,
  B10001,
  B01010,
  B00100
};
byte emptyCube[8] = {
  B00000,
  B11111,
  B10001,
  B10001,
  B10001,
  B11111,
  B00000
};
byte fullCube[8] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000
};

byte elk1[8] = {
  B00001,
  B00001,
  B00011,
  B00001,
  B00011,
  B00111,
  B00111,
  B01111
};
byte elk2[8] = {
  B10000,
  B10000,
  B10000,
  B11000,
  B10000,
  B11000,
  B11100,
  B11110
};
byte elk3[8] = {
  B00011,
  B00111,
  B01111,
  B11111,
  B11111,
  B00011,
  B00000,
  B00000
};
byte elk4[8] = {
  B11000,
  B11100,
  B11110,
  B11111,
  B11111,
  B11000,
  B00000,
  B00000
};

void setup() {
  // Serial.begin(9600); //debug
  pinMode(speakerPin, OUTPUT);
  pinMode(A1, INPUT_PULLUP);

  pinMode(Btn_1Pin, INPUT);
  pinMode(Btn_2Pin, INPUT);
  pinMode(Btn_3Pin, INPUT);
  pinMode(Btn_4Pin, INPUT);
  pinMode(Btn_5Pin, INPUT);

  pinMode(led_1Pin, OUTPUT);
  pinMode(led_2Pin, OUTPUT);
  pinMode(led_3Pin, OUTPUT);
  pinMode(led_4Pin, OUTPUT);
  pinMode(led_5Pin, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 4);
  lcd.print("HAPPY NEW YEAR!");

  showStartScreen();
}

void playSong(int melody[], int duration[], int count, int led[]) {
  // Serial.println("...playing");
  for (int i = 0; i < count; i++){
    int noteDuration = 1000 / duration[i];
    digitalWrite(led_1Pin + led[i] - 1, HIGH);
    tone(speakerPin, melody[i], noteDuration);
    digitalWrite(led_1Pin + led[i] - 1, LOW);
    delay(noteDuration * 1.3); //pause
    noTone(speakerPin);
  }
}

void playNote(int note, int duration, int led) {
  int noteDuration = 1000 / duration;
  digitalWrite(led_1Pin + led, HIGH);
  tone(speakerPin, note, 1000 / duration);
  digitalWrite(led_1Pin + led, LOW);
  delay(noteDuration * 1.3);
  noTone(speakerPin);
}

int waitButton() {
  for(;;) {
    for(int i = 0; i < 5; i++) {
      int keyPin = Btn_1Pin + i;
      int keyUp = digitalRead(keyPin);
      if(keyUp == HIGH) {
        // Serial.print("Button: ");
        // Serial.println(keyPin - 7);
        return keyPin - 7;
      }
    }
  }
}

void showHint(int answer) {
  lcd.createChar(0, B00001);
  lcd.setCursor(15 + answer, 0);
  lcd.write(byte(0));
}

int checkAnswer(int melody[], int songNumber[], int songLen) {
  // Serial.println("checking answer");
  int result = 0;
  int completed = 0;

  for (int i = 0; i < songLen; i++) {
    int answerKey = songNumber[i] - 1;
    int button = waitButton();
    showHint(answerKey);
    // Serial.print("song len = ");
    // Serial.println(songLen);
    // Serial.print("answer = ");
    // Serial.println(answerKey);

    if(button == answerKey) {
      completed++;
      lcd.setCursor(9, 2);
      lcd.print(completed);
      lcd.setCursor(11, 2);
      lcd.print("/");
      lcd.setCursor(12, 2);
      lcd.print(songLen);

      playNote(melody[i], 32, button);
      delay(200);
      result++;
    }
    else return 0;
  }
  // Serial.print("result ");
  // Serial.println(result);
  return result; 
}

void giveCandy() {
  myservo.attach(servPin);
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

void showProgress() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(s_difficulty[difficulty]);
  lcd.setCursor(0, 2);
  lcd.print("Progress: ");
}

void showWin() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("* * ********** * * *");
  lcd.setCursor(0, 1);
  lcd.print("* * *YOU WIN!* * * *");
  lcd.setCursor(0, 2);
  lcd.print("* * ********** * * *");
  lcd.setCursor(0, 3);
  lcd.print("HAPPY NEW 2017 YEAR!");
}

void showLose() {
  lcd.clear();
  lcd.setCursor(5, 1);
  lcd.print("GAME OVER...");
  lcd.setCursor(0, 3);
  lcd.print("HAPPY NEW 2017 YEAR!");
}

int playDemo() {
  showProgress();

  // Serial.println("start play song1");
  // Serial.println(sizeof(song1[0])/2);

  playSong(song1[0], song1[1], sizeof(song1[0])/2, song1[2]);
  int result = checkAnswer(song1[0] ,song1[2], sizeof(song1[0]) / 2);
  return result;
}

int playNormal() {
  showProgress();

  int result = 0;
  int songNumber = random(5); //нормальных песен

  switch(songNumber) {
    case 0:
      playSong(el[0], el[1], sizeof(el[0])/2, el[2]);
      result = checkAnswer(el[0] ,el[2], sizeof(el[0]) / 2);
      break;
    case 1:
      playSong(el1[0], el1[1], sizeof(el1[0])/2, el1[2]);
      result = checkAnswer(el1[0] ,el1[2], sizeof(el1[0]) / 2);
      break;
    case 2:
      playSong(el2[0], el2[1], sizeof(el2[0])/2, el2[2]);
      result = checkAnswer(el2[0] ,el2[2], sizeof(el2[0]) / 2);
      break;
    case 3:
      playSong(knz1[0], knz1[1], sizeof(knz1[0])/2, knz1[2]);
      result = checkAnswer(knz1[0] ,knz1[2], sizeof(knz1[0]) / 2);
      break;
    case 4:
      playSong(knz2[0], knz2[1], sizeof(knz2[0])/2, knz2[2]);
      result = checkAnswer(knz2[0] ,knz2[2], sizeof(knz2[0]) / 2);
      break;
    default:
      return result;
  }
  return result;
}

int playHard() {
  showProgress();

  int result = 0;
  int songNumber = random(2); //сложных песен

  switch(songNumber) {
    case 0:
      playSong(el_f[0], el_f[1], sizeof(el_f[0])/2, el_f[2]);
      result = checkAnswer(el_f[0] ,el_f[2], sizeof(el_f[0]) / 2);
      break;
    case 1:
      playSong(abba1[0], abba1[1], sizeof(abba1[0])/2, abba1[2]);
      result = checkAnswer(abba1[0] ,abba1[2], sizeof(abba1[0]) / 2);
      break;
    default:
      return result;
  }
  return result;
}

int playAnimation() {
  lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("Some cute animation"); 
  lcd.createChar(0, elk1);
  lcd.setCursor(5, 2);
  lcd.write(byte(0));
  lcd.createChar(1, elk2);
  lcd.setCursor(6, 2);
  lcd.write(byte(1));
  lcd.createChar(2, elk3);
  lcd.setCursor(5, 3);
  lcd.write(byte(2));
  lcd.createChar(3, elk4);
  lcd.setCursor(6, 3);
  lcd.write(byte(3));

  lcd.setCursor(9, 1);
  lcd.print("2017"); 

  delay(10000);
  return 1;
}

void playGame() {
  int result = 0;
  switch(difficulty) {
    case 0:
      result = playDemo();
      break;
    case 1:
      result = playNormal();
      break;
    case 2:
      result = playHard();
      break;
    case 3:
      result = playAnimation();
      break;
  }

  if (result > 0) {
    showWin();
    // Serial.println("You WIN!");
    playSong(win[0], win[1], sizeof(win[0])/2, win[2]); // играем победную мелодию
    for (int i = 0; i < difficulty; i++){
      if (difficulty > 2 ) break;
      giveCandy();  
    }
  }
  else {
    showLose();
    // Serial.println("You LOSE!");
    playSong(lose[0], lose[1], sizeof(lose[0])/2, lose[2]);//играем проигрышную мелодию
  }
  delay(1000);
}

void showStartScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO CANDYGAME");

  lcd.setCursor(2, 1);
  lcd.print("chose difficulty:");
  
  for (int i = 0; i < 4; i++) {
    lcd.createChar(0, tag);
    lcd.setCursor(i + i * 3, 2);
    lcd.write(byte(0));
  }

  updateLvl();
  lcd.setCursor(15, 3);
  lcd.print("START");
}

void updateLvl() {
  const char* s[] = {"Demo", "Norm", "Hard", "Img"};

  for (int i = 0; i < 4; i++) {
    if (i == difficulty) {
      lcd.createChar(1, fullCube);
      lcd.setCursor(i + i * 3, 3);
      lcd.write(byte(1));
      lcd.setCursor(16, 2);
      lcd.print(s[difficulty]);
    }
    else {
      lcd.createChar(2, emptyCube);
      lcd.setCursor(i + i * 3, 3);
      lcd.write(byte(2));
    }
  }
}

void loop() {
  int btn1  = digitalRead(Btn_1Pin);
  int btn2  = digitalRead(Btn_2Pin);
  int btn3  = digitalRead(Btn_3Pin);
  int btn4  = digitalRead(Btn_4Pin);
  int start = digitalRead(Btn_5Pin);
  int a = analogRead(1);

  if (a > 500)
  {
//    Serial.println(a);
    giveCandy();
  }

  if(start == HIGH) {
//    Serial.println("start new game");
    playGame();
    delay(500);
    showStartScreen();
  }
  else if(btn1 == HIGH) { //demo lvl
    difficulty = 0;
    updateLvl();
  }
  else if(btn2 == HIGH) { //normal lvl
    difficulty = 1;
    updateLvl();
  }
  else if(btn3 == HIGH) { //hard lvl
    difficulty = 2;
    updateLvl();
  }
  else if(btn4 == HIGH) { //специальный экран
    difficulty = 3;
    updateLvl();
    //показать что-нибудь красивое, например падающие снежинки :)
  }
}
