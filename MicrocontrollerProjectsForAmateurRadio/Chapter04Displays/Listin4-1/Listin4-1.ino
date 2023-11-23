/*
                              LICENSE AGREEMENT

  This program source code and its associated hardware design at subject to the GNU General Public License version 2,
  https://opensource.org/licenses/GPL-2.0
  with the following additional conditions:
  1. Any commercial use of the hardware or software is prohibited without express, written, permission of the authors.
  2. This entire comment, unaltered, must appear at the top of the primary source file. In the Arduino IDE environemnt, this comment must
  appear at the top of the INO file that contains setup() and loop(). In any other environmentm, it must appear in the file containing
  main().
  3. This notice must appear in any derivative work, regardless of language used.

*/
/*
  for the 16x2 LCD display.
*/
 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>    //  https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
//                                  Compile with: Arduino Nano

// Set the LCD I2C address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print(" CQ CQ DE W8TEE");
}

void loop()
{
  char spaces[17] = "                "; // Save room for null
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
    lcd.setCursor(0, row);    // Show mesage on row = 0
    lcd.print(message);
    row = 1;
  }
  delay(500UL);               // Pause for a half second...
}
