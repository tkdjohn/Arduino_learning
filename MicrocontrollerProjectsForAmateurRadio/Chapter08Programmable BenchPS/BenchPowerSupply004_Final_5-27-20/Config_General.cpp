#ifndef BEENHERE
#include "ProgPS.h"
#endif
#include <Arduino.h>
#define NUMCYCLES    0
#define STARTVOLT    1
#define ENDVOLT      2
#define DURATION     3
#define NUMSTEPS     4
#define GENERALEXIT  6
#define PULSEWIDTH   5

/*****
  Purpose: Display the "Gereral" config menu

  Parameter list:
    void
  Return value:
    void
*****/
void DisplayGeneral()
{
  myDisplay.fillRect(0, FONTROWOFFSET + 8, DISPLAYWIDTH, DISPLAYHEIGHT - FONTROWOFFSET, BLACK);
  myDisplay.setCursor(10, 105);
  myDisplay.setFont(&FreeSerif9pt7b);
  myDisplay.setTextColor(WHITE, BLACK);
  myDisplay.print("Use Menu SW to select, encoder to change, Menu SW to Save:");
  myDisplay.setFont(&FreeSerif12pt7b);
  myDisplay.setTextColor(GREEN, BLACK);
  for (int i = 0; i < 7; i++) {
    myDisplay.setCursor(100, y[i]);
    myDisplay.print(GeneralChar[i]);
  }
  myDisplay.fillRect(255, 129, 70, 23, BLACK);
  myDisplay.setCursor(260, 130);
  myDisplay.setTextColor(WHITE, BLACK);
  myDisplay.print(numFunctionCycles);
  
  myDisplay.fillRect(255, 154, 70, 23, BLACK);
  myDisplay.setCursor(260, 155);
  myDisplay.setTextColor(WHITE, BLACK);
  myDisplay.print(startSetpointLevelVolts);
  
  myDisplay.fillRect(255, 179, 70, 23, BLACK);
  myDisplay.setCursor(260, 180);
  myDisplay.setTextColor(WHITE, BLACK);
  myDisplay.print(maxVoltageLevel);
  
  myDisplay.fillRect(255, 204, 70, 23, BLACK);
  myDisplay.setCursor(260, 205);
  myDisplay.setTextColor(WHITE, BLACK);
  myDisplay.print(functionDuration);

  myDisplay.fillRect(255, 229, 70, 23, BLACK);
  myDisplay.setCursor(260, 230);
  myDisplay.setTextColor(WHITE, BLACK);
  myDisplay.print(numberOfSteps);

  myDisplay.fillRect(255, 254, 70, 23, BLACK);
  myDisplay.setCursor(260, 255);
  myDisplay.setTextColor(WHITE, BLACK);
  myDisplay.print(pulseTopWidth);
}

/*****
  Purpose: Display the "Gereral" settings

  Parameter list:
    void
  Return value:
    void
*****/
void DisplayGeneralSettings() {
  myDisplay.setCursor(160, 100 );
  myDisplay.print(numFunctionCycles);
  myDisplay.setCursor(160, 125 );
  myDisplay.print(startSetpointLevelVolts);
}

/*****
  Purpose: Select the items in the "General" config menu

  Parameter list:
    void
  Return value:
    void
*****/
void SelectGeneral()
{
  choice = 0;
  //myDisplay.setTextColor(CYAN, BLACK);
  myDisplay.setCursor(100, y[choice]);
  while (digitalRead(MENUENCODERSWITCH) != LOW) {
    lastChoice = choice;

    if (en2State != 0) {

      MyDelay(200);
      choice = encoder2 + choice;
      if (choice < 0) {
        choice = 6;
      }
      if (choice > 7) {
        choice = 0;
      }
      //Serial.print("choice="); Serial.println(choice);
      myDisplay.setTextColor(CYAN, BLACK);
      myDisplay.setCursor(100, y[choice]);
      myDisplay.print(GeneralChar[choice]);
      myDisplay.setTextColor(GREEN, BLACK);
      myDisplay.setCursor(100, y[lastChoice]);
      myDisplay.print(GeneralChar[lastChoice]);
      lastChoice = choice;
      en2State = 0;
    }
    else {
      myDisplay.setTextColor(CYAN, BLACK);
      myDisplay.setCursor(100, y[choice]);
      myDisplay.print(GeneralChar[choice]);
    }
  }
}
/*****
  Purpose: Change the item in the "General" config menu

  Parameter list:
    void
  Return value:
    void
*****/
void ChangeGeneralSelection()
{
  int greenRectFlag;


  delay(200);
  switch (choice) {
    case NUMCYCLES:
      greenRectFlag = 0;
      while (digitalRead(MENUENCODERSWITCH) != LOW) {
        if (greenRectFlag == 0) {
          myDisplay.fillRect(255, 111, 70, 25, BLUE);
          myDisplay.setCursor(260, 130);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(numFunctionCycles);
          greenRectFlag = 1;
        }
        if (en2State != 0) {
          numFunctionCycles = numFunctionCycles + encoder2;
          myDisplay.fillRect(255, 111, 70, 25, BLUE);
          myDisplay.setCursor(260, 130);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(numFunctionCycles);
          en2State = 0;
        }
      }

      status = EEPROM.write(42,   numFunctionCycles);         //================
      if (status) {
        Serial.print("EEPROM numFunctionCycles write bad, Status = ");
        Serial.println(status);
      }
      
      DisplayGeneral();
      SelectGeneral();
      ChangeGeneralSelection();
      break;
      
    case STARTVOLT:
      greenRectFlag = 0;
      while (digitalRead(MENUENCODERSWITCH) != LOW) {
        if (greenRectFlag == 0) {
          myDisplay.fillRect(255, 136, 70, 25, BLUE);
          myDisplay.setCursor(260, 155);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(startSetpointLevelVolts);
          greenRectFlag = 1;
        }
        if (en2State != 0) {
          startSetpointLevelVolts = startSetpointLevelVolts + encoder2;

          myDisplay.fillRect(255, 136, 70, 25, BLUE);
          myDisplay.setCursor(260, 155);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(startSetpointLevelVolts);
          en2State = 0;
        }
      }
      myUnion.num = startSetpointLevelVolts;
      status = EEPROM.write( (uint16) 46,   myUnion.myBytes[0]);  //================
      status = EEPROM.write( (uint16) 48,   myUnion.myBytes[1]);
      if (status) {
        Serial.print("EEPROM startSetpointLevelVolts write bad, Status = ");
        Serial.println(status);
      }
      
      DisplayGeneral();
      SelectGeneral();
      ChangeGeneralSelection();
      break;

    case ENDVOLT:
      greenRectFlag = 0;
      while (digitalRead(MENUENCODERSWITCH) != LOW) {
        if (greenRectFlag == 0) {
          myDisplay.fillRect(255, 161, 70, 25, BLUE);
          myDisplay.setCursor(260, 180);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(maxVoltageLevel);
          greenRectFlag = 1;
        }
        if (en2State != 0) {
          maxVoltageLevel = maxVoltageLevel + encoder2;

          myDisplay.fillRect(255, 151, 70, 25, BLUE);
          myDisplay.setCursor(260, 180);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(maxVoltageLevel);
          en2State = 0;
        }
      }
      myUnion.num = maxVoltageLevel;
      status = EEPROM.write( (uint16) 20,   myUnion.myBytes[0]);  //===================
      status = EEPROM.write( (uint16) 22,   myUnion.myBytes[1]);
      if (status) {
        Serial.print("EEPROM maxVoltageLevel write bad, Status = ");
        Serial.println(status);
      }
      DisplayGeneral();
      SelectGeneral();
      ChangeGeneralSelection();
      break;

    case DURATION:
      greenRectFlag = 0;
      while (digitalRead(MENUENCODERSWITCH) != LOW) {
        if (greenRectFlag == 0) {
          myDisplay.fillRect(255, 186, 70, 25, BLUE);
          myDisplay.setCursor(260, 205);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(functionDuration);
          greenRectFlag = 1;
        }
        if (en2State != 0) {
          functionDuration = functionDuration + encoder2*100;
          myDisplay.fillRect(255, 186, 70, 25, BLUE);
          myDisplay.setCursor(260, 205);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(functionDuration);
          en2State = 0;
        }
      }
      status = EEPROM.write(0,   functionDuration);    //=========================
      if (status) {
        Serial.print("EEPROM functionDuration write bad, Status = ");
        Serial.println(status);
      }

      DisplayGeneral();
      SelectGeneral();
      ChangeGeneralSelection();
      break;

    case NUMSTEPS:
      greenRectFlag = 0;
      while (digitalRead(MENUENCODERSWITCH) != LOW) {
        if (greenRectFlag == 0) {
          myDisplay.fillRect(255, 211, 70, 25, BLUE);
          myDisplay.setCursor(260, 230);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(numberOfSteps);
          greenRectFlag = 1;
        }
        if (en2State != 0) {
          numberOfSteps = numberOfSteps + encoder2;

          myDisplay.fillRect(255, 211, 70, 25, BLUE);
          myDisplay.setCursor(260, 230);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(numberOfSteps);
          en2State = 0;

        }
      }
      status = EEPROM.write(4, numberOfSteps);     //=========================
      if (status) {
        Serial.print("EEPROM numberOfSteps write bad, Status = ");
        Serial.println(status);
      }

      DisplayGeneral();
      SelectGeneral();
      ChangeGeneralSelection();
      break;

    case GENERALEXIT:
      break;

      case PULSEWIDTH:
      greenRectFlag = 0;
      while (digitalRead(MENUENCODERSWITCH) != LOW) {
        if (greenRectFlag == 0) {
          myDisplay.fillRect(255, 236, 70, 25, BLUE);
          myDisplay.setCursor(260, 255);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(pulseTopWidth);
          greenRectFlag = 1;
        }
        if (en2State != 0) {
          pulseTopWidth = pulseTopWidth + encoder2*100;
          myDisplay.fillRect(255, 236, 70, 25, BLUE);
          myDisplay.setCursor(260, 255);
          myDisplay.setTextColor(WHITE, BLACK);
          myDisplay.print(pulseTopWidth);
          en2State = 0;
        }
      }
      status = EEPROM.write(38,   pulseTopWidth);   //=========================
      if (status) {
        Serial.print("EEPROM pulseTopWidth write bad, Status = ");
        Serial.println(status);
      }

      DisplayGeneral();
      SelectGeneral();
      ChangeGeneralSelection();
      break;
  }
}
