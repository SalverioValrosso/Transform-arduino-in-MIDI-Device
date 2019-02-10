#include <LiquidCrystal_I2C.h>
#include "pitches.h"

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

void setup() {
  //Serial.begin(31250);
  Serial.begin(115200);
   noTone(8);
  lcd.begin(20, 4);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {



  static uint8_t header = 0;
  static uint8_t data1 = 0;
  static bool third_byte = false;

  if (Serial.available() >= 1) {

    uint8_t data = Serial.read();

    if (data & 0b10000000) { // if msb == 1 (header byte)
      header = data;
      third_byte = false;

    } else if ((header & 0xF0)) {

      if (!third_byte) {
        data1 = data;
        third_byte = true;

      } else {
        third_byte = false;
        uint8_t data2 = data;
        uint8_t channel = header & 0x0F;
        int a, b, c;
        a = channel;
        b = data1;
        c = data2;
        if ((header & 0xF0) == 0xB0) {
          handleCC(a, b, c);
        }
        if ((header & 0xF0) != 0xB0) {
          note(a, b, c);
        }
      }
    }
  }

}

void handleCC(uint8_t channel, uint8_t data1, uint8_t data2) {

  

  lcd.setCursor(0, 0);
  lcd.print("               ");
  lcd.setCursor(0, 0);
  lcd.print("CC COMMAND");
  lcd.setCursor(0, 1);
  lcd.print(channel + 1);
  lcd.setCursor(0, 2);
  lcd.print(data1);
  lcd.setCursor(0, 3);
  lcd.print("   ");
  lcd.setCursor(0, 3);
  lcd.print(data2);

}
void note(uint8_t channel, uint8_t data1, uint8_t data2) {
 if(data2>0){
 tone(8, data1);
 }else{
 noTone(8);
  
 }
  
  switch (data1 % 12) {
    case 0 : if (data2 > 0) {
        digitalWrite(11, 1);
      } else {
        digitalWrite(11, 0);
      }
      break;

    case 1 : if (data2 > 0) {
        digitalWrite(10, 1);
      } else {
        digitalWrite(10, 0);
      }
      break;

    case 2 : if (data2 > 0) {
        digitalWrite(9, 1);
      } else {
        digitalWrite(9, 0);
      }
      break;

    case 3 : if (data2 > 0) {
        digitalWrite(8, 1);
      } else {
        digitalWrite(8, 0);
      }
      break;

    case 4 : if (data2 > 0) {
        digitalWrite(7, 1);
      } else {
        digitalWrite(7, 0);
      }
      break;

    case 5 : if (data2 > 0) {
        digitalWrite(6, 1);
      } else {
        digitalWrite(6, 0);
      }
      break;

    case 6 : if (data2 > 0) {
        digitalWrite(5, 1);
      } else {
        digitalWrite(5, 0);
      }
      break;

    case 7 : if (data2 > 0) {
        digitalWrite(4, 1);
      } else {
        digitalWrite(4, 0);
      }
      break;

  }

  lcd.setCursor(0, 0);
  lcd.print("             ");
  lcd.setCursor(0, 0);
  lcd.print("Nota on/off");
  lcd.setCursor(0, 1);
  lcd.print(channel + 1);
  lcd.setCursor(0, 2);
  lcd.print(data1);
  lcd.setCursor(0, 3);
  lcd.print("   ");
  lcd.setCursor(0, 3);
  lcd.print(data2);

}
