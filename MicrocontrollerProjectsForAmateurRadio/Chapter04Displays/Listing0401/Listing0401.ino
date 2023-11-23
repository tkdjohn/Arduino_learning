/*****
  This software is licensed un the GNU General Public License, Version 3, as presetned in
  https://www.gnu.org/licenses/gpl-3.0.txt. You may use this software for non-commercial use. 
  For commercial use, contact the authors:
  Jack Purdum, W8TEE
  Al Peter, AC8GY

  This header file must be copied into all copies and deriviative works of this software
  and remain the very first thing in the primary source code file.
  
*****/
//                            Compiled with the Arduino Nano
#define DEBUG

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>   // https://github.com/lucasmaziero/LiquidCrystal_I2C

LiquidCrystal_I2C lcd(0x27, 16, 2); // Create LCD object: I2C device address 0x27, 16x2 display

void setup()
{
  lcd.begin();        // initialize the LCD

  lcd.backlight();        // Turn on the blacklight and print a message.
  lcd.print(" CQ CQ DE W8TEE");
}

void loop()
{
  char spaces[17] = "                "; // 16 spaces with room for null
  char message[]  = " CQ CQ DE W8TEE";
  static int row  = 0;
  
  if (row != 0) {
    lcd.setCursor(0, 0);      // Clear out row 0
    lcd.print(spaces);
    lcd.setCursor(0, row);    // show message on row = 1
    lcd.print(message);
    row = 0;
  } else {
    lcd.setCursor(0, 1);      // Clear out row 1
    lcd.print(spaces);        
    lcd.setCursor(0, row);    // Show message on row = 0
    lcd.print(message);
    row = 1;
  }
  delay(500UL);               // Pause for a half second...
}
