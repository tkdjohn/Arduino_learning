#ifndef BEENHERE
#include "ProgPS.h"
#endif
#include <Arduino.h>

/*****
  Purpose: Select the items in the "Time" config menu

  Parameter list:
    void
  Return value:
    void
*****/
void calVoltage()
{
  int status;

  Setpoint = DACConvert(12);

  Setpoint = DACConvert(12);
  DoDACOut();
  DoScreenPrintVoltage();
  for (int i = 1; i <= 100; i++) {
    voltIn =  (((float)analogRead(PA3) / 4096) * voltInCal);
    currentIn = currentIn + ((float)analogRead(PB1)) / 1258;
    MyDelay(1);
  }
  voltIn = voltIn / 100;
  myDisplay.drawRect(0, 95, 350, 210, RED);
  myDisplay.setCursor(0, 120);
  myDisplay.setTextColor(YELLOW, BLACK);
  myDisplay.println(" 1. Adj Coarse for");
  myDisplay.println("    output voltage=12.0");
  myDisplay.println(" 2. Adj Fine for");
  myDisplay.println("    screen reading=12.0");
  myDisplay.println(" 3. Press Menu to Save/Exit");
  DoDACOut();
  DoScreenPrintVoltage();

  while (digitalRead(MENUENCODERSWITCH) != LOW) {
    if (en1State != 0) {       //Adjust output =20.0
      Setpoint = DACConvert(12);
      setPointCal = (float)(setPointCal + eCounter1 / 50.);
      Setpoint = DACConvert(12);
      DoDACOut();
      DoScreenPrintVoltage();
      myDisplay.setCursor(0, 265);
      myDisplay.setTextColor(YELLOW, BLACK);
      myDisplay.print(" 1. ");
      myDisplay.setTextColor(WHITE, BLACK);
      myDisplay.print(" SetPointCal = ");
      myDisplay.fillRect(255, 245, 70, 25, BLUE);
      myDisplay.setCursor(260, 265);
      myDisplay.setTextColor(WHITE, BLACK);
      myDisplay.print(setPointCal, 2);
      en1State = 0;
      eCounter1 = 0;
    }
    if (en3State != 0) {      //Adjust Readout to = 12.0
      encoderRead3();
      voltInCal = (float)(voltInCal + (float)encoder3Reading / 200 );
     
      Setpoint = DACConvert(12);
      DoDACOut();
      DoScreenPrintVoltage();
      myDisplay.setCursor(0, 295);
      myDisplay.setTextColor(YELLOW, BLACK);
      myDisplay.print(" 2. ");

      myDisplay.setTextColor(WHITE, BLACK);
      myDisplay.print(" voltInCal = ");
      myDisplay.fillRect(255, 275, 70, 25, BLUE);
      myDisplay.setCursor(260, 295);
      myDisplay.setTextColor(WHITE, BLACK);
      myDisplay.print(voltInCal, 3);

      en3State = 0;
      eCounter3 = 0;
    }
  }
   myUnion.num = voltInCal;
  status = EEPROM.write( (uint16) 24,   myUnion.myBytes[0]);
  status = EEPROM.write( (uint16) 26,   myUnion.myBytes[1]);
  if (status) {
    Serial.print("EEPROM voltInCal write bad, Status = ");
    Serial.println(status);
  }

  myUnion.num = setPointCal;
  status = EEPROM.write( (uint16) 28,   myUnion.myBytes[0]);
  status = EEPROM.write( (uint16) 30,   myUnion.myBytes[1]);
  if (status) {
    Serial.print("EEPROM setPointCal write bad, Status = ");
    Serial.println(status);
  }

}
