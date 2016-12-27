#include <Servo.h>

Servo myservo;

#define servPin 13
#define speakerPin 12
#define firstkey 2
#define keycount 5

#define A3  4545  //110
#define Bb3 4291  //116.5
#define B3  4048  //123.5
#define C3  3822  //130.8
#define Db3 3607  //138.6
#define D3  3406  //146.8
#define Eb3 413  //155.6
#define E3  3034  //164.8
#define F3  2864  //174.6
#define Fs3 2702  //185
#define G3  2551  //196
#define Ab3 2407  //207.7

#define A4  2273  //220
#define Bb4 2145  //233.1
#define B4  2025  //246.9
#define C4  1911  //261.6
#define Db4 1804  //277.2
#define D4  1702  //293.7
#define Eb4 1607  //311.1
#define E4  1517  //49.6
#define F4  144  //349.2
#define Fs4 1351  //370
#define G4  1275  //392
#define Ab4 1204  //415.3

#define A5  1136  //440
#define Bb5 1073  //466
#define B5  1012  //494
#define C5  956   //523
#define Db5 902   //554
#define D5  851   //587
#define Eb5 804   //622
#define E5  759   //659
#define F5  716   //698
#define Fs5 676   //740
#define G5  638   //784
#define Ab5 602   //831
#define A6  572   //доп

#define R   0

#define PIN_RESET 7 // -> 1
#define PIN_SCE   8 // -> 2
#define PIN_DC    9  // -> 3
#define PIN_SDIN  10  // -> 4
#define PIN_SCLK  11  // -> 5
                // +3.3 -> 6
                //  GND -> 7 
                //  GND -> 8
               
#define LCD_C     LOW
#define LCD_D     HIGH
#define LCD_X     84
#define LCD_Y     48

int pos = 0;

bool gap = true;
long timer = 0;

int count  = 1;
int countM = 1;

int gameRound = 0;
long tempo = 10000;
int pause = 1000;
int rest_count = 100;

char disp_tab[]={'0','1','2','3','4','5','6','7','8','9'};

static const byte ASCII[][5] = {
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20  
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x42, 0x61, 0x51, 0x49, 0x46} // 4 2
,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x4, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c ¥
,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j 
,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ←
,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f →
};

void LcdCharacter(char character) {
  LcdWrite(LCD_D, 0x00);
  for (int index = 0; index < 5; index++)
  {
    LcdWrite(LCD_D, ASCII[character - 0x20][index]);
  }
  LcdWrite(LCD_D, 0x00);
}

void LcdClear(void) {
  for (int index = 0; index < LCD_X * LCD_Y / 8; index++)
  {
    LcdWrite(LCD_D, 0x00);
  }
}

void LcdInitialise(void) {
  pinMode(PIN_SCE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_SDIN, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);
  LcdWrite(LCD_C, 0x21 );  // LCD Extended Commands.
  LcdWrite(LCD_C, 0xB1 );  // Set LCD Vop (Contrast). 
  LcdWrite(LCD_C, 0x04 );  // Set Temp coefficent. //0x04
  LcdWrite(LCD_C, 0x14 );  // LCD bias mode 1:48. //0x13
  LcdWrite(LCD_C, 0x0C );  // LCD in normal mode.
  LcdWrite(LCD_C, 0x20 );
  LcdWrite(LCD_C, 0x0C );
}

void LcdString(char *characters) {
  while (*characters)
  {
    LcdCharacter(*characters++);
  }
}

void LcdWrite(byte dc, byte data) {
  digitalWrite(PIN_DC, dc);
  digitalWrite(PIN_SCE, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_SCE, HIGH);
}

void gotoXY(int x, int y) {
  LcdWrite( 0, 0x80 | x);  // Column.
  LcdWrite( 0, 0x40 | y);  // Row.  
}

void dispcountt(int count) {
  LcdCharacter(disp_tab[count/10000]);
  LcdCharacter(disp_tab[count/1000%10]);
  LcdCharacter(disp_tab[count/100%10]);
  LcdCharacter(disp_tab[count%100/10]);
  LcdCharacter(disp_tab[count%10]);
}

//============================================================

int variants = 4;

int games = 4;
int melody1[2][9] = {{E5, Eb5, E5, Eb5, E5, B5, D5, C5, A5}, 
  {4, 4, 4, 4, 4, 4, 4, 4, 64}
};

int melody2[2][28] = {
  {C4, A5, A5, G4, A5, F4, C4, C4, C4, A5, A5, Bb5, G4, C5, C5, D4, D4, Bb5, Bb5, A5, G4, F4, F4, A5, A5, G4, A5, F4}, 
  {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 96, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 96}
};

int melody3[2][26] {
  {Db4, Db4, Db4, B4, A4, A4, A4, B4, Db4, E4, A5, Db5, Ab4, Ab4, A5, Fs4, Fs4, G4, E5, A5, Ab4, Ab4, Fs4, Fs4, E5, E5},
  {4,  4,  4,  64, 4, 4, 16, 16, 4,  4, 4, 4,  64,  48,  16, 96,  16,  16, 96, 16, 16,  48,  16,  4,  4, 64}
};

// int melody4 [2][] {
//   {Fs4, B5, B5, C5, B5, },
//   {}
// };

int el[2][8] = {
  {C4, A5, A5, G4, A5, F4, C4, C4}, 
  {4, 4, 4, 4, 4, 4, 4, 4}
};

int answers[4] = {2, 1, 3, 2};

int win[2][3] = {{C4, E4, G4}, {64, 64, 64}};

int lose[2][3] = {{Eb4, Bb4, F3}, {64, 64, 128}};

int MAX_COUNT = sizeof(melody1) / 2;

//============================================================

void setup() {
  Serial.begin (9600);

  // myservo.attach(servPin);
  pinMode(speakerPin, OUTPUT);
  // pinMode(ledPin, OUTPUT);
  
  LcdInitialise();
  LcdClear();
  gotoXY(0, 0);
  LcdString("    Happy   ");
  LcdString("    new     ");
  LcdString("    2016    ");
  LcdString("    year!   ");
}

void drowNewCounter(int counter, int line) { //drowNewCounter(count, 5);
  count++;
  gotoXY(0, line);
  LcdString("==");
  gotoXY(16, line);
  dispcountt(counter);
  LcdString("==");
}

void playTone(int tone, long duration) {
  long elapsed_time = 0;
  if (tone > 0) {
    while (elapsed_time < duration) {
      digitalWrite(speakerPin,HIGH);
      delayMicroseconds(tone);
      digitalWrite(speakerPin, LOW);
      delayMicroseconds(tone); 
      elapsed_time += (tone * 2);
    } 
  }
  else {
    for (int j = 0; j < rest_count; j++) {
      delayMicroseconds(duration);
    }
  }
}

void playSong(int melody[], int beats[], int count) {
  for (int i=0; i < count; i++) {
    playTone(melody[i], beats[i] * tempo);
    delayMicroseconds(pause);
  }
}

void loop() {
  boolean start = digitalRead(firstkey);
  if(!start) {
    goPlayGame();
    gameRound++;
  }
}

void getCandy() {
  myservo.attach(servPin);
  for(pos = 0; pos < 180; pos += 1)  // от 0 до 180 градусов
  {                                  // с шагом в 1 градус 
    myservo.write(pos);
    delay(20);                       // ждём 15ms пока серва займёт новое положение
  } 
  for(pos = 180; pos>=1; pos-=1)
  {
    myservo.write(pos);
    delay(20);
  }
  myservo.detach();
}

void goPlayGame() {
  int betaAnswer = random(4);
  drowNewCounter(betaAnswer, 5);
  //gameRound = (gameRound + random(10)) % games;
  // drowNewCounter(gameRound, 5);

  delayMicroseconds(pause * 3);
  //int answerKey = answers[gameRound % variants];
  int answerKey = betaAnswer;
  switch(gameRound % variants){
    case 0: 
      playSong(el[0], el[1], sizeof(el[0]) / 2);
      break;
    case 1: 
      playSong(melody1[0], melody1[1], sizeof(melody1[0]) / 2);
      break;
    case 2:
      playSong(melody2[0], melody2[1], sizeof(melody2[0]) / 2);
      break;
    case 3:
      playSong(melody3[0], melody3[1], sizeof(melody3[0]) / 2);
      break;
  }
  for(;;){
    for (int i = 0; i < keycount - 1; ++i) {
      int keyPin = i + firstkey + 1;
      boolean keyUp = digitalRead(keyPin);

      if(!keyUp) {
        if(i == answerKey) {
          playSong(win[0], win[1], sizeof(win[0]) / 2);    //win
          getCandy();
          return;
        }
        else {
          playSong(lose[0], lose[1], sizeof(lose[0]) / 2);//lose
          return;
        }
      }
    }
  }
}
