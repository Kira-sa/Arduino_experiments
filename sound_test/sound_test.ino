#define speakerPin 12

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
#define C4  262 // ------
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

int song1[3][5] = {
	{C4, G3, G3, A3, G3}, 
	{4, 2, 4, 2, 4}, 
	{4, 3, 2, 3, 4}};

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
	{4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,   4,  2},
	{1,  5,  5,  4,  5,  3,  1,  1,  1,  4,  4,  5,   3,  5}
};

int el_f[3][28] = {
	{C4, A4, A4, G4, A4, F4, C4, C4, C4, A4, A4, AS4, G4, C5, C5, D4, D4, AS4, AS4, A4, G4, F4, F4, A4, A4, G4, A4, F4},
	{4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,   4,  2,  4,  4,  4,  4,   4,   4,  4,  4,  4,  4,  4,  4,  4,  2},
	{1,  5,  5,  4,  5,  3,  1,  1,  1,  4,  4,  5,   3,  5,  1,  5,  5,  4,   5,   3,  1,  1,  1,  4,  4,  5,  3,  5}
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

void setup() {
  pinMode(speakerPin, OUTPUT);
}

void playSong(int melody[], int duration[], int count, int led[]) {
  Serial.println("...playing");
  for (int i = 0; i < count; i++){
    int noteDuration = 1000 / duration[i];
    tone(speakerPin, melody[i], noteDuration);
    delay(noteDuration * 1.3); //pause
    noTone(speakerPin);
  }
}

void loop() {
  // playSong(song1[0], song1[1], sizeof(song1[0])/2, song1[2]);
  // delay(600);
  // playSong(el1[0], el1[1], sizeof(el1[0])/2, el1[2]);
  // delay(100);
  // playSong(el2[0], el2[1], sizeof(el2[0])/2, el2[2]);
  // playSong(knz1[0], knz1[1], sizeof(knz1[0])/2, knz1[2]);
  // playSong(knz2[0], knz2[1], sizeof(knz2[0])/2, knz2[2]);
  playSong(abba1[0], abba1[1], sizeof(abba1[0])/2, abba1[2]);
  delay(600);




	delay(400000);
}
