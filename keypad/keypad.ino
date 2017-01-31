#include <Key.h>
#include <Keypad.h>

const byte ROWS = 3;
const byte COLS = 3;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'}
};
byte rowPins[ROWS] = {4, 3, 2};
byte colPins[COLS] = {5, 6, 7};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


void setup() {
  Serial.begin(9600);

}

void loop() {
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
}
