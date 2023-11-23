#ifndef BEENHERE
#include "ProgPS.h"
#endif
#include <Arduino.h>
/*****
  Purpose: To draw the on-screen keypad
  Paramter list:
    void
  Return value:
    void
*****/
void DrawKeyPad()
{
  myDisplay.setCursor(0, 140);
  myDisplay.setTextColor(YELLOW, BLACK);
  myDisplay.setFont(&FreeSerif9pt7b);
  myDisplay.println(" Adjust with Menu Encoder");
  myDisplay.println(" Press Menu to move");
  myDisplay.println(" to next digit");
  myDisplay.println(" ");
  myDisplay.setTextColor(CYAN, BLACK);
  myDisplay.println(" Press Coarse SW to Exit");
  myDisplay.setFont(&FreeSerif12pt7b);
  int ixyCount = 0;
  for (int iy = 0; iy < 4; iy++) {
    for (int ix = 0; ix < 3; ix++) {
      myDisplay.drawRect(300 + ix * 50, 230 - iy * 40, 45, 35, WHITE);
      myDisplay.fillRect(301 + ix * 50, 231 - iy * 40, 43, 33, DKGREEN);
      myDisplay.setCursor(315 + ix * 50, 255 - iy * 40);
      myDisplay.print(keyPadChar[ixyCount]);
      ixyCount++;
    }
  }
}

/*****
  Purpose: To move the selection highlight around for a digit on the keypad
  Paramter list:
    void
  Return value:
    void
*****/
void selectKeyPadDigit()
{
  if (en2State == 1) {
    //Serial.print("eCounter2=  ");Serial.println(eCounter2);
    MyDelay(100);
    if (eCounter2 < 0) {
      eCounter2 = 0;
    }
    if (eCounter2 >= 11) {
      eCounter2 = 11;
    }
    if (abs((eCounter2 - oldeCounter2)) > 0) {
      DrawKeyPad();
      myDisplay.fillRect(keyPadXCoord[eCounter2] + 1, keyPadYCoord[eCounter2] + 1, 43, 33, BLUE);
      myDisplay.setCursor(keyPadXCoord[eCounter2] + 15,  keyPadYCoord[eCounter2] + 25);
      myDisplay.setTextColor(WHITE, DKGREEN);
      myDisplay.print(keyPadChar[eCounter2]);
      oldeCounter2 = eCounter2;
      en2State = 0;
    }
  }
}

/*****
  Purpose: To select the highlighted digits and add  to the voltage reading setpoint
          3 digits can be selected in format xx.x
  Paramter list:
    void
  Return value:
    void
*****/
void ReadKeypad()
{
  outputOnOffFlag = 1;
  Setpoint =0;
  while ( digitalRead(COARSEENCODERSWITCH) != 0) {
    //Serial.print("digitalRead(COARSEENCODERSWITCH)=  "); Serial.println(digitalRead(COARSEENCODERSWITCH));
    selectKeyPadDigit();
    //Serial.print("keypadDigitCounter=  "); Serial.println(keypadDigitCounter);
    int numPadFlag = 0;
    while (digitalRead(MENUENCODERSWITCH) == 0) {
      // Serial.print("numPadFlag=  "); Serial.println(numPadFlag);
      numPadFlag = 1;
      //Serial.print("numPadFlag=  "); Serial.println(numPadFlag);
    }
    if (numPadFlag == 1) {
      MyDelay(50);
      int numKeypad1 = atoi(keyPadChar[eCounter2]);
      numKeypad = numKeypad1;
      //Serial.print("numKeypad=  "); Serial.println(numKeypad);
      switch (keypadDigitCounter) {
        case 0:
          numKeypad2 = numKeypad * .1;
          keypadDigitCounter++;
          Setpoint = DACConvert(numKeypad2);
          DoDACOut();
          DoScreenPrintVoltage();
          break;
        case 1:
          numKeypad2 = numKeypad2 * 10 + numKeypad * .1;
          keypadDigitCounter++;
          Setpoint = DACConvert(numKeypad2);
          DoDACOut();
          DoScreenPrintVoltage();
          break;
        case 2:
          numKeypad2 = numKeypad2 * 10 + numKeypad * .1;
          keypadDigitCounter++;
          if (numKeypad2 <= 0)
          {
            numKeypad2 = 0;
          }
          if (numKeypad2 > 25)
          {
            numKeypad2 = 25;
          }
          Setpoint = DACConvert(numKeypad2);
          DoDACOut();
          DoScreenPrintVoltage();
          break;
        default:
          keypadDigitCounter = 3;
          break;
      }
      if (keyPadChar[eCounter2] == "B" ) { //Backspace
        keypadDigitCounter--;
        numKeypad2 = int( numKeypad2);
        numKeypad2 = numKeypad2 / 10;
        //Serial.print("numKeypad2=  "); Serial.println (numKeypad2);
      }

      if (keyPadChar[eCounter2] == "C" ) { //Clear
        numKeypad2 = 0;
        keypadDigitCounter = 0;
      }
      numPadFlag = 0;
    }
    //Serial.print("numKeypad2=  "); Serial.println(numKeypad2);
    Setpoint = DACConvert(numKeypad2);
    DoDACOut();
    DoScreenPrintVoltage();
  }
}
