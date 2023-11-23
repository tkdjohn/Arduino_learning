#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // wants teh LiquidCrystal I2C library

LiquidCrystal_I2C lcd(0x3F, 40, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
bool firstPass = true;
void setup() {
  lcd.init();  // initialize the lcd
  lcd.backlight();
  Serial.begin(115200);
}

void loop() {
  if (firstPass) {
    lcd.print("ABCDEFGHIJKLMNOP");
    lcd.setCursor(0,1);
    delay(100);
    lcd.print("QRSTUVWXYZ123456");
    firstPass = false;
  }

  
}

void serialEvent() {
  int colsSent = 0;
  int shifts = 0;

  // read all the available characters
  while (Serial.available()) {
    lcd.home();
    lcd.clear();
  
    char buffer[17];
    size_t size1 = Serial.readBytes(buffer, 16);
    buffer[size1] = '\0';
    lcd.print(buffer);

    size_t size2 = 0;
    if (Serial.available()) {
      lcd.setCursor(0,1);
      size2 = Serial.readBytes(buffer, 16);
      buffer[size2] = '\0';
      lcd.print(buffer);
    }

    colsSent = max(size1, size2);
    delay(250);
    for (int shifts = 16; colsSent > shifts; shifts++) {
      lcd.scrollDisplayLeft();
      delay(200);
    }  
    delay(1000);
    //Serial.println(buffer);
  }
}
