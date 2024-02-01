#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

const int colc = 16;
const int rowc = 2;

LiquidCrystal_I2C lcd(0x27,colc,rowc);

int redLed = 10;
int greenLed = 11;
int buzzer = 12;
int data_length =0;
int melody = 3000;
String data;
String master = "1234";


char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //pinout baris
byte colPins[COLS] = {5, 4, 3, 2}; //pinout column

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void printScreen(String msg){
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(msg);
}

void setup() {
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.backlight();
  lcd.display();
  lcd.print("Enter Pass");
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
}

void playSound(int note,int duration){
  tone(buzzer,note, duration);
  delay(1000);
  noTone(buzzer);
}

void loop() {
  char customKey = customKeypad.getKey();

  if(customKey){
    playSound(melody,500);

    data += customKey;
    data_length++;
  }

  if(data_length == 4){
    lcd.clear();
    if(data == master){
      printScreen("Access Granted");
      digitalWrite(greenLed,HIGH);
      playSound(1500,200);
      digitalWrite(greenLed,LOW);
    }else{
      printScreen("Access Denied");
      digitalWrite(redLed,HIGH);
      playSound(1000,200);
      digitalWrite(redLed,LOW);
    }
    lcd.clear();
    printScreen("Enter Pass");
    data = "";
    data_length = 0;
  }

}
