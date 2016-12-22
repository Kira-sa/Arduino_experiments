// new candy dispenser

#include <Servo.h>

Servo myservo;

#define Btn_1Pin 0
#define Btn_2Pin 1
#define Btn_3Pin 2
#define Btn_4Pin 3
#define Btn_5Pin 4 //start game pin

#define led_1Pin 5
#define led_1Pin 6
#define led_1Pin 7
#define led_1Pin 8
#define led_1Pin 9

#define speakerPin 12
#define servPin 13

//NOTES
#define A3  4545  //110
#define Bb3 4291  //116.5
#define B3  4048  //123.5
#define C3  3822  //130.8
#define Db3 3607  //138.6
#define D3  3406  //146.8
#define Eb3 3213  //155.6
#define E3  3034  //164.8
#define F3  2864  //174.6
#define Fs3 2702  //185
#define G3  2551  //196
#define Ab3 2407  //207.7

#define songs 2

// tone / duration / button
int song1[3][5] = {{C3, D3, E3, D3, C3 }, {32, 32, 32, 32, 32}, {1, 2, 3, 2, 1}};

int win[3][3] = {{C3, E3, G3}, {64, 64, 64}, {1, 3, 5}};
int lose[3][3] = {{Eb3, Bb3, F3}, {64, 64, 128}, {5, 3, 1}};

long tempo = 10000;
int pause = 1000;
int difficulty = 0;
int rest_count = 100;
int pos = 0;

void setup() {
  Serial.begin(9600); //debug
  pinMode(speakerPin, OUTPUT);
}

void playTone(int tone, int duration) {
  long elapsed_time = 0;
  if (tone > 0) {
    while (elapsed_time < duration) {
      digitalWrite(speakerPin, HIGH);
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

void playSong(int melody[], int duration[], int count, int led[]) {
  for (int i = 0; i < count; i++){
    digitalWrite(led_1Pin + led[i], HIGH);
    playTone(melody[i], duration[i] * tempo);
    digitalWrite(led_1Pin + led[i], LOW);
    delayMicroseconds(pause);
  }
}

int checkAnswer() {
  return 0;
}

void getCandy() {
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

void playGame() {
  difficulty = 1;
  //ToDo: обновляем картинку на экране
  int songNumber = random(songs); 
  switch(songNumber) {
    case 0:
      playSong(song1[0], song1[1], sizeof(song1[0])/2, song1[2]);
      break;
    case 1:
//      playSong();
      break;
    case 2:
//      playSong();
      break;
    default:
//      playSong(); //error
      break;
  }
  //ToDo: ждем когда игрок введет необходимую последовательность
  int result = checkAnswer();
  //ToDo:  проверяем результат и награждаем игрока если он победил
  if (result > 0) {
    //ToDo: обновляем экран, сообщяя о победе
    playSong(win[0], win[1], sizeof(win[0])/2, win[2]); // играем победную мелодию
    //ToDo: даем конфетки в зависимости от выбранной сложности
    for (int i = 0; i < difficulty; i++){
      getCandy();  
    }
  }
  else {
    //ToDo: обновляем экран, сообщяя о проигрыше
    playSong(lose[0], lose[1], sizeof(lose[0])/2, lose[2]);//играем проигрышную мелодию
  }
}

void loop() {
  //ToDo: нарисовать начальный экран, и пока не нажмут старт обрабатывать нажатия на остальные кнопки
  boolean start = digitalRead(Btn_5Pin);
  if(!start) {
    playGame();
  }
}

