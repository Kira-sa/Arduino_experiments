#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
//sda - A4
//scl - A5

void start() {
  lcd.clear();
  lcd.setCursor(1,1);
  lcd.print("Press key to start");  
}

void gameOverFunction()
{
  delay(1000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Game Over!");
  lcd.setCursor(4,1);
  lcd.print("Score: ");
  lcd.print("13!");
  delay(1500);
}

void setup() {
  lcd.init();
  lcd.backlight();
  start();
}

void loop() {
  gameOverFunction();

}
