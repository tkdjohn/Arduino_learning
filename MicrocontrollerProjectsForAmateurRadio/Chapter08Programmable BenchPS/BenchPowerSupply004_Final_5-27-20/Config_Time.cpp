#ifndef BEENHERE
#include "ProgPS.h"
#endif
#include <Arduino.h>


#define TIMESEC   0
#define TIMEMIN   1
#define TIMEHR    2
#define TIMEEXIT    3
#define VOLTCAL   0
#define CURRENTCAL  1

/*****
  Purpose: Display the "Time" config menu

  Parameter list:
    void
  Return value:
    void
*****/
void displayTimeCategories()
{
  myDisplay.fillRect(0, FONTROWOFFSET + 8, DISPLAYWIDTH, DISPLAYHEIGHT - FONTROWOFFSET, BLACK);
  myDisplay.setFont(&FreeSerif12pt7b);
  myDisplay.setTextColor(GREEN, BLACK);
  for (int i = 0; i <= 3; i++) {
    myDisplay.setCursor(10, 130 + 25 * i);
    myDisplay.print(TimeChar[i]);
  }
}
/*****
  Purpose: Display the "Time" config menu

  Parameter list:
    void
  Return value:
    void
*****/
void displaySetTime()
{
  myDisplay.fillRect(0, FONTROWOFFSET + 8, 180, DISPLAYHEIGHT - FONTROWOFFSET, BLACK);
  myDisplay.setFont(&FreeSerif12pt7b);
  myDisplay.setTextColor(GREEN, BLACK);
  for (int i = 0; i <= 3; i++) {
    myDisplay.setCursor(10, 130 + 25 * i);
    myDisplay.print(TimeChar[i]);
  }
  myDisplay.fillRect(155, 112, 70, 23, BLACK);
  myDisplay.setCursor(160, 130);
  myDisplay.setTextColor(WHITE, BLACK);
  myDisplay.print(outTimeSec);
  myDisplay.fillRect(155, 137, 70, 23, BLACK);
  myDisplay.setCursor(160, 155);
  myDisplay.setTextColor(WHITE, BLACK);
  myDisplay.print(outTimeMin);
  myDisplay.fillRect(155, 162, 70, 23, BLACK);
  myDisplay.setCursor(160, 180);
  myDisplay.setTextColor(WHITE, BLACK);
  myDisplay.print(outTimeHour);
}

/*****
  Purpose: Select the items in the "Time" config menu

  Parameter list:
    void
  Return value:
    void
*****/
void SelectTime()
{
  choiceTime = 0;
  myDisplay.setTextColor(CYAN, BLACK);
  myDisplay.setCursor(10, y[choiceTime]);
  while (digitalRead(MENUENCODERSWITCH) != LOW) {
    MyDelay(200);
    lastChoiceTime = choiceTime;
    if (en2State != 0) {
      choiceTime = encoder2 + choiceTime;
      if (choiceTime < 0) {
        choiceTime = 3;
      }
      if (choiceTime > 3) {
        choiceTime = 0;
      }
      //Serial.print("choiceTime="); Serial.println(choiceTime);
      myDisplay.setTextColor(CYAN, BLACK);
      myDisplay.setCursor(10, y[choiceTime]);
      myDisplay.print(TimeChar[choiceTime]);
      myDisplay.setTextColor(GREEN, BLACK);
      myDisplay.setCursor(10, y[lastChoiceTime]);
      myDisplay.print(TimeChar[lastChoiceTime]);
      lastChoiceTime = choiceTime;
      en2State = 0;
    }
    else {
      myDisplay.setTextColor(CYAN, BLACK);
      myDisplay.setCursor(10, y[choiceTime]);
      myDisplay.print(TimeChar[choiceTime]);
    }
  }
}
/*****
  Purpose: Change the item in the "Time" config menu

  Parameter list:
    void
  Return value:
    void
*****/
void ChangeTimeSelection()
{
  int greenRectFlag;
  delay(200);
  switch (choiceTime) {
    case TIMESEC:
      greenRectFlag = 0;
      while (digitalRead(MENUENCODERSWITCH) != LOW) {
        if (greenRectFlag == 0) {
          myDisplay.fillRect(155, 112, 70, 23, DKGREEN);
          myDisplay.setCursor(160, 130);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(outTimeSec);
          greenRectFlag = 1;
        }
        //Serial.println("In ChangeTimeSelection while");
        if (en2State != 0) {
          outTimeSec = outTimeSec + encoder2;
          myDisplay.fillRect(155, 112, 70, 23, DKGREEN);
          myDisplay.setCursor(160, 130);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(outTimeSec);
          en2State = 0;
        }
      }
      status = EEPROM.write(8, outTimeSec);
      if (status) {
        Serial.print("EEPROM outTimeSec write bad, Status = ");
        Serial.println(status);
      }
      displaySetTime();
      SelectTime();
      ChangeTimeSelection();
      break;
    case TIMEMIN:
      greenRectFlag = 0;
      while (digitalRead(MENUENCODERSWITCH) != LOW) {
        if (greenRectFlag == 0) {
          myDisplay.fillRect(155, 137, 70, 23, DKGREEN);
          myDisplay.setCursor(160, 155);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(outTimeMin);
          greenRectFlag = 1;
        }
        if (en2State != 0) {
          outTimeMin = outTimeMin + encoder2;
          myDisplay.fillRect(155, 137, 70, 23, DKGREEN);
          myDisplay.setCursor(160, 155);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(outTimeMin);
          en2State = 0;
        }
      }
      status = EEPROM.write(12,  outTimeMin);
      if (status) {
        Serial.print("EEPROM outTimeMin write bad, Status = ");
        Serial.println(status);
      }
      displaySetTime();
      SelectTime();
      ChangeTimeSelection();
      break;

    case TIMEHR:
      greenRectFlag = 0;
      while (digitalRead(MENUENCODERSWITCH) != LOW) {
        if (greenRectFlag == 0) {
          myDisplay.fillRect(155, 162, 70, 23, DKGREEN);
          myDisplay.setCursor(160, 180);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(outTimeHour);
          greenRectFlag = 1;
        }
        if (en2State != 0) {
          outTimeHour = outTimeHour + encoder2;

          myDisplay.fillRect(155, 162, 70, 23, DKGREEN);
          myDisplay.setCursor(160, 180);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(outTimeHour);
          en2State = 0;
        }
      }
      status = EEPROM.write(16, outTimeHour);
      if (status) {
        Serial.print("EEPROM kochSpeed write bad, Status = ");
        Serial.println(status);
      }
      displaySetTime();
      SelectTime();
      ChangeTimeSelection();
      break;
    case TIMEEXIT:
      break;
  }
}
