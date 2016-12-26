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

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define songs 2

// tone / duration / button
int song1[3][5] = {{NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3}, {4, 2, 4, 2, 4}, {4, 3, 2, 3, 4}};

int win[3][3] = {{NOTE_A5, NOTE_A5, NOTE_A5}, {4, 4, 4}, {0, 2, 4}};
int lose[3][3] = {{NOTE_D2, NOTE_D2, NOTE_D2}, {4, 4, 4}, {4, 2, 0}};

boolean gameOver, gameStarted;

long tempo = 10000;
int pause = 1000;
int difficulty = 1;
const char* s_difficulty[] = {"Demo", "Normal", "Hard"};
//0 - demo
//1 - normal
//2 - hard
int rest_count = 100;
int pos = 0;
int keyCount = 5;
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


void setup() {
  Serial.begin(9600); //debug
  pinMode(speakerPin, OUTPUT);

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

void playTone(int tone, int duration) {
  long elapsed_time = 0;
  if (tone > 0) {
    while (elapsed_time < duration) {
      digitalWrite(speakerPin, HIGH);
      delay(tone);
      digitalWrite(speakerPin, LOW);
      delay(tone); 
      elapsed_time += (tone * 2);
    }
  }
  else {
    for (int j = 0; j < rest_count; j++) {
      delay(duration);
    }
  }
}

void playSong(int melody[], int duration[], int count, int led[]) {
  Serial.println("...playing");
  for (int i = 0; i < count; i++){
    int noteDuration = 1000 / duration[i];
    digitalWrite(led_1Pin + led[i], HIGH);
    tone(speakerPin, melody[i], noteDuration);
    digitalWrite(led_1Pin + led[i], LOW);
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
    for(int i = 0; i < keyCount; i++) {
      int keyPin = Btn_1Pin + i;
      int keyUp = digitalRead(keyPin);
      if(keyUp == HIGH) {
        Serial.print("Button: ");
        Serial.println(keyPin - 7);
        return keyPin - 7;
      }
    }
  }
}

int checkAnswer(int melody[], int songNumber[], int songLen) {
  Serial.println("checking answer");
  int result = 0;
  int completed = 0;

  for (int i = 0; i < songLen; i++) {
    Serial.print("song len = ");
    Serial.println(songLen);
    int answerKey = songNumber[i];
    Serial.print("answer = ");
    Serial.println(answerKey);

    int button = waitButton();

    if(button == answerKey) {
      //ToDo - обновить информацию на экране
      playNote(melody[i], 32, button);
      delay(200);
      result++;
    }
    else return 0;
  }
  Serial.print("result ");
  Serial.println(result);
  return result; 
}

void giveCandy() {
  myservo.attach(servPin);
  for(pos = 0; pos < 180; pos += 1) { //от 0 до 180 градусов с шагом в 1 градус 
    myservo.write(pos);
    delay(20);                       //ждём 15ms пока серва займёт новое положение
  } 
  for(pos = 180; pos >= 1; pos -= 1) {
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

  Serial.println("start play song1");
  Serial.println(sizeof(song1[0])/2);

  playSong(song1[0], song1[1], sizeof(song1[0])/2, song1[2]);
  int result = checkAnswer(song1[0] ,song1[2], sizeof(song1[0]) / 2);
  return result;
}

int playNormal() {
  showProgress();

  int result = 0;
  int songNumber = random(2); //нормальных песен

  switch(songNumber) {
    case 0:
      playSong(song1[0], song1[1], sizeof(song1[0])/2, song1[2]);
      result = checkAnswer(song1[0] ,song1[2], sizeof(song1[0]) / 2);
      break;
    case 1:
      playSong(song1[0], song1[1], sizeof(song1[0])/2, song1[2]);
      result = checkAnswer(song1[0] ,song1[2], sizeof(song1[0]) / 2);
      break;
  }
  return result;
}

int playHard() {
  showProgress();

  int result = 0;
  int songNumber = random(2); //сложных песен

  switch(songNumber) {
    case 0:
      playSong(song1[0], song1[1], sizeof(song1[0])/2, song1[2]);
      result = checkAnswer(song1[0] ,song1[2], sizeof(song1[0]) / 2);
      break;
    case 1:
      playSong(song1[0], song1[1], sizeof(song1[0])/2, song1[2]);
      result = checkAnswer(song1[0] ,song1[2], sizeof(song1[0]) / 2);
      break;
  }
  return result;
}

int playAnimation() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Some cute animation");
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
    Serial.println("You WIN!");
    playSong(win[0], win[1], sizeof(win[0])/2, win[2]); // играем победную мелодию
    for (int i = 0; i < difficulty; i++){
      giveCandy();  
    }
  }
  else {
    showLose();
    Serial.println("You LOSE!");
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
  for (int i = 0; i < 4; i++) {
    if (i == difficulty) {
      lcd.createChar(1, fullCube);
      lcd.setCursor(i + i * 3, 3);
      lcd.write(byte(1));
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

  if(start == HIGH) {
    Serial.println("start new game");
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
    difficulty = -1;
    updateLvl();
    //показать что-нибудь красивое, например падающие снежинки :)
  }
}
