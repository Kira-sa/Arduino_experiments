#define debug_pin        2 // toggle
#define buzzer_pin       3
#define laser_pin        4
#define first_light      5  //6,7,8 - reserved
#define last_light       9
#define prepared_pin     10 // индикатор патрона в патроннике
#define load_button_pin  11 //button
#define prepfire_pin     12 //button
#define fire_pin         13 //button

#define lights_count     5

#define reload_tone 60
#define reload_duration 150
#define reload_count 1

#define prepfire_tone 120
#define prepfire_duration 100
#define prepfire_count 2

#define fire_tone 700
#define fire_duration 100
#define fire_count 2

#define fail_tone 40
#define fail_duration 150
#define fail_count 3

int prepared = 0;
int bullets = 0;
int prepared_stat = 0;


void setup() {
//  Serial.begin(9600);
  
  pinMode(fire_pin, INPUT);
  pinMode(debug_pin, INPUT);
  pinMode(prepfire_pin, INPUT);
  pinMode(load_button_pin, INPUT);

  pinMode(laser_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(prepared_pin, OUTPUT);
  
  for (int i=0; i< lights_count; i++){
    pinMode(first_light+i, OUTPUT);
  }
  check_lights();
}

void playSong(int _tone, int duration, int count) {
  for (int i=0; i < count; i++) {
    tone(buzzer_pin, _tone, duration);
    delay(100);
//    noTone(10);
//    Serial.write("playsong\n");
  }
}

void reload(){
  if(bullets < 5) {
      bullets++;    
    }
  playSong(reload_tone, reload_duration, reload_count);
}

void prepare(){
  if (bullets > 0){
      prepared = 1;
      bullets--;
    }
  playSong(prepfire_tone, prepfire_duration, prepfire_count);
} 

void trigger(){
  if (prepared == 1){
      digitalWrite(laser_pin, HIGH);
      delay(22);
      digitalWrite(laser_pin, LOW);
      playSong(fire_tone, fire_duration, fire_count);
    }
  else {
      playSong(fail_tone, fail_duration, fail_count);
    }
    prepared = 0;
}

void upgrade_lights(){
  for(int i = 0; i < lights_count; i++ ){
      digitalWrite(last_light - i, LOW);
    }  
  for(int i = 0; i < bullets; i++ ){
      digitalWrite(last_light - i, HIGH);
    }
  if(prepared == 1){
      digitalWrite(prepared_pin, HIGH);
    }
  else {
      digitalWrite(prepared_pin, LOW);
    }
}

void check_lights(){
  for(int i = 0; i < lights_count; i++ ){
      digitalWrite(last_light - i + 1, HIGH);
      delay(100);
      digitalWrite(last_light - i + 1, LOW);
    }  
  for(int i = lights_count; i >= 0; i-- ){
      digitalWrite(last_light - i + 1, HIGH);
      delay(100);
      digitalWrite(last_light - i + 1, LOW);
    }  
}

void loop() {
  int load = digitalRead(load_button_pin);
  int prep = digitalRead(prepfire_pin);
  int fire = digitalRead(fire_pin);
  int debug = digitalRead(debug_pin);

  if (debug == HIGH) {
      bullets = 5;
      prepared = 1;
    }
  else {
      if (load == HIGH) {
      reload();
      upgrade_lights();
      delay(300);
      }
    if (prep == HIGH) {
      if (prepared_stat == 0){
          prepared_stat = 1;
          prepare();
          upgrade_lights();
        }
      delay(300);
      }
    else {
      prepared_stat = 0;
      }
    }
  if (fire == HIGH) {
      trigger();
      upgrade_lights();
      delay(100);
      }
  upgrade_lights();
//  delay(10);
}
