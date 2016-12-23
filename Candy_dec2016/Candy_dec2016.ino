// new candy dispenser

#include <Servo.h>

Servo myservo;

#define Btn_1Pin 7
#define Btn_2Pin 8
#define Btn_3Pin 9
#define Btn_4Pin 10
#define Btn_5Pin 11 //start game pin

#define led_1Pin 2
#define led_2Pin 3
#define led_3Pin 4
#define led_4Pin 5
#define led_5Pin 6

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
int song1[3][5] = {{C3, D3, E3, D3, C3 }, {1000, 1000, 1000, 1000, 1000}, {1, 1, 1, 1, 1}};

int win[3][3] = {{C3, E3, G3}, {64, 64, 64}, {1, 3, 5}};
int lose[3][3] = {{Eb3, Bb3, F3}, {64, 64, 128}, {5, 3, 1}};

long tempo = 10000;
int pause = 2000;
int difficulty = 0;
int rest_count = 100;
int pos = 0;
int keyCount = 5;

void setup() {
  Serial.begin(9600); //debug
  pinMode(speakerPin, OUTPUT);
  pinMode(Btn_1Pin, OUTPUT);
  pinMode(Btn_2Pin, OUTPUT);
  pinMode(Btn_3Pin, OUTPUT);
  pinMode(Btn_4Pin, OUTPUT);
  pinMode(Btn_5Pin, OUTPUT);

  pinMode(led_1Pin, OUTPUT);
  pinMode(led_2Pin, OUTPUT);
  pinMode(led_3Pin, OUTPUT);
  pinMode(led_4Pin, OUTPUT);
  pinMode(led_5Pin, OUTPUT);

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
  Serial.println("...playing");
  for (int i = 0; i < count; i++){
    Serial.println(i);
    digitalWrite(led_1Pin + led[i], HIGH);
    playTone(melody[i], duration[i] * tempo);
    digitalWrite(led_1Pin + led[i], LOW);
    delayMicroseconds(pause);
  }
}

void playNote(int note, int duration, int led) {
  digitalWrite(led_1Pin + led, HIGH);
  playTone(note, duration * tempo);
  digitalWrite(led_1Pin + led, LOW);
  delayMicroseconds(pause);
}

int checkAnswer(int melody[], int songNumber[]) {
  Serial.println("checking answer");
  int result = 0;

  for (int j = 0; j < sizeof(songNumber[2]); j++) {
    int answerKey = songNumber[j];
    for(;;){
      for (int i = 0; i < keyCount; i++) {
        int keyPin = Btn_1Pin + i;
        int keyUp = digitalRead(keyPin);
        if(keyUp == HIGH) {
          Serial.println("wait button");
          Serial.println(answerKey);
          if(i == answerKey){
            playNote(melody[j], 32, i); //сыграть ноту и моргнуть светодиодом
            //ToDo: обновить информацию на экране (реализовать прогресс прохождения мелодии)
            delay(300);
            result++;
          }
          else return 0; //проиграл
        }
      }
    }
  }
  Serial.print("result ");
  Serial.println(result);
  return result; //победил?
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
  int result = 0;
  switch(0) {
    case 0:
      Serial.println("start play song1");
      playSong(song1[0], song1[1], sizeof(song1[0])/2, song1[2]);
      result = checkAnswer(song1[0] ,song1[2]);
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
  //ToDo:  проверяем результат и награждаем игрока если он победил
  if (result > 0) {
    //ToDo: обновляем экран, сообщяя о победе
    Serial.println("You WIN!");
    playSong(win[0], win[1], sizeof(win[0])/2, win[2]); // играем победную мелодию
    //ToDo: даем конфетки в зависимости от выбранной сложности
    for (int i = 0; i < difficulty; i++){
      getCandy();  
    }
  }
  else {
    //ToDo: обновляем экран, сообщяя о проигрыше
    Serial.println("You LOSE!");
    playSong(lose[0], lose[1], sizeof(lose[0])/2, lose[2]);//играем проигрышную мелодию
  }
  delay(1000);
}

void loop() {
  //ToDo: нарисовать начальный экран, и пока не нажмут старт обрабатывать нажатия на остальные кнопки
  int start = digitalRead(Btn_5Pin);
  if(start == HIGH) {
    Serial.println("start new game");
    playGame();
  }
}

