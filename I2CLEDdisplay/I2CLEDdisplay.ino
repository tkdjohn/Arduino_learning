#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // wants teh LiquidCrystal I2C library

LiquidCrystal_I2C lcd(0x3F, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
bool firstPass = true;
void setup() {
  lcd.init();  // initialize the lcd
  lcd.backlight();
  Serial.begin(115200);
}

void loop() {
  if (firstPass) {
    lcd.print("ABCDEFGHIJKLMNO\P");
    delay(100);
    lcd.print("QRSTUVWXYZ123456");
    firstPass = false;
  }

  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    int charsDisplayed = 0;
    int shifts = 0;
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      char buffer[65];
      size_t size = Serial.readBytes(buffer, 64);
      buffer[size] = '\0';
      charsDisplayed += size;
      Serial.print(buffer);
      Serial.print("|");
      lcd.print(buffer);
      while (charsDisplayed > shifts + 16) {

        lcd.scrollDisplayLeft();
        shifts++;
        delay(150);
      }
    }
    Serial.println("");
  }
}

void writeToDisplay(char *)
