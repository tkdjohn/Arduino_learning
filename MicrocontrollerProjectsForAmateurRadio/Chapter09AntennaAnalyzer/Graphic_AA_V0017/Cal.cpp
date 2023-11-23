#ifndef BEENHERE
#include "AT.h"
#endif
#include <Arduino.h>



/*****
  Purpose: To get a band menu choice
  Argument list:
    ILI9488 tft      the display object
  Return value:
    int                       the menu selected
*****/
void Zero()
{
  char *bridgeReading[] = {" Vm ", " Vz ", " Vrz ", "Exit"};

  int i, indexCal, where = 0;
  int VmCalAve = 0;
  int VzCalAve = 0;
  int VrzCalAve = 0;

  tft.fillRect(0, 0, PIXELWIDTH, PIXELHEIGHT, ILI9488_BLACK);
  tft.setTextColor(ILI9488_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(5, 0);
  tft.print("Zero Calibrate");
  tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
  tft.setTextSize(1);
  tft.setFont(&FreeSerif9pt7b);
  tft.setCursor(0, 190);
  tft.print("Cal Instructions:");
  tft.setCursor(0, 215);
  tft.print("1. Insert shorting Jumper         2. Select V to zero");
  tft.setCursor(0, 240);
  tft.print("3. Use Freq Encoder to zero       4. Press Freq Sw to save");
  tft.setCursor(0, 265);
  tft.print("4. Repeat for next V");
  tft.setCursor(0, 290);
  tft.print("5. Select Exit and press Menu SW to finish");
  tft.setFont();
  tft.setTextSize(2);
  tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
    tft.setCursor(100, 30);
  tft.print("V       Reading     Cal Value");
  for (int i = 0; i < 4; i++) {

    tft.setCursor(100, 70 + i * 28);
    tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
  
    tft.print(bridgeReading[i]);

  }
  tft.setCursor(100, 70);
  tft.setTextColor(ILI9488_BLUE, ILI9488_WHITE);
  tft.print(bridgeReading[0]);
  digitalWrite(MENUENCODERSWITCH, HIGH);
  MyDelay(100L);

  indexCal = 0;
  frequencyEncoderMovement = 0;

  while (1) {

    for (int i = 0; i < 4; i++) {

      tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
      switch (i) {
        case 0:
          SendFrequency(0);
          ReadSWRValue();
          tft.setCursor(210, 70 + i * 28);
          VmCalAve = VmCalAve * .9 + .1 * aveVm;
          tft.print(VmCalAve);

          break;

        case 1:
          SendFrequency(0);
          ReadSWRValue();
          tft.setCursor(210, 70 + i * 28);
          VzCalAve = VzCalAve * .9 + .1 * aveVz;
          tft.print(aveVz);
          break;

        case 2:
          SendFrequency(0);
          ReadSWRValue();
          tft.setCursor(210, 70 + i * 28);
          VrzCalAve = VrzCalAve * .9 + .1 * aveVrz;
          tft.print(aveVrz);

          break;
      }
    }
    if (menuEncoderMovement) {
      if (menuEncoderMovement == 1) {
        indexCal++;
        if (indexCal == 4) {        // wrap to first index
          indexCal = 0;
        }
      }
      if (menuEncoderMovement == -1) {
        indexCal--;
        if (indexCal < 0) {        // wrap to last index
          indexCal = 3;
        }
      }
      menuEncoderMovement = 0;
      tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
      for (int i = 0; i < 4; i++) {
        tft.setCursor(100, 70 + i * 28);
        tft.print(bridgeReading[i]);
      }
      tft.setTextColor(ILI9488_BLUE, ILI9488_WHITE);
      tft.setCursor(100, 70 + indexCal * 28);
      tft.print(bridgeReading[indexCal]);
    }

    switch (indexCal) {
      case 0 :
        if (frequencyEncoderMovement != 0) {     //Change digit value
          tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
          ReadSWRValue();
          VmCal += frequencyEncoderMovement * 10 ;
          tft.setCursor(210, 70 + indexCal * 28);
          tft.print(aveVm);
          tft.setCursor(350, 70 + indexCal * 28);
          tft.print(VmCal);
          frequencyEncoderMovement = 0;
        }
        if (digitalRead(FREQUENCYENCODERSWITCH) == LOW) {
          //Save VmCal
          tft.setCursor(5, 70 + indexCal * 28);
          tft.print("Saved!");
        }
        break;
      case 1 :
        if (frequencyEncoderMovement != 0) {     //Change digit value
          VzCal += frequencyEncoderMovement * 10 ;
          tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
          ReadSWRValue();
          tft.setCursor(210, 70 + indexCal * 28);
          tft.print(aveVz);
          tft.setCursor(350, 70 + indexCal * 28);
          tft.print(VzCal);
          frequencyEncoderMovement = 0;
        }
        if (digitalRead(FREQUENCYENCODERSWITCH) == LOW) {
          //Save VzCal
          tft.setCursor(5, 70 + indexCal * 28);
          tft.print("Saved!");
        }
        break;
      case 2 :
        if (frequencyEncoderMovement != 0) {     //Change digit value
          VrzCal += frequencyEncoderMovement * 10 ;
          tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
          ReadSWRValue();

          tft.setCursor(210, 70 + indexCal * 28);
          tft.print(aveVrz);
          tft.setCursor(350, 70 + indexCal * 28);
          tft.print(VrzCal);
          frequencyEncoderMovement = 0;
        }
        if (digitalRead(FREQUENCYENCODERSWITCH) == LOW) {
          //Save VrzCal
          tft.setCursor(5, 70 + indexCal * 28);
          tft.print("Saved!");
        }
        break;

      case 3 :
        if (digitalRead(MENUENCODERSWITCH) == LOW) {
          MakeMenuSelection();
        }
        break;


    }

  }

}
/*****
  Purpose: To get a band menu choice
  Argument list:
    ILI9488 tft      the display object
  Return value:
    int                       the menu selected
*****/
void Calibrate()
{
  char *bridgeReading[] = { " 25 Ohm", " 50 ohm", " 200 ohm", "Exit & Store"};
  //int currBand[] = {160, 80 , 40, 30, 20, 17 , 15 , 12 , 10};
  int i, indexCal, where = 0;
  float RValueAve = 0;
  float yCal25Temp = 0;
  float yCal50Temp = 0;
  float yCal200Temp = 0;

  tft.fillRect(0, 0, PIXELWIDTH, PIXELHEIGHT, ILI9488_BLACK);
  tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
   tft.setCursor(0, 0);

  tft.print("Calibrate Linearity");
  tft.setCursor(100, 30);
  tft.print("Cal R       RValue       Diff.");
  tft.setCursor(0, 190);
  tft.setTextSize(1);
    tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
  tft.setFont(&FreeSerif9pt7b);
  tft.print("Cal Instructions:");
  tft.setCursor(0, 215);
  tft.print("1. Insert Cal Resistor    2. Select Cal R Value");
  tft.setCursor(0, 240);
  tft.print("3. Press Menu Sw          4. Repeat for next Cal R.");
  tft.setCursor(0, 265);
  tft.print("4. Repeat for next Cal Resistor");
  tft.setCursor(0, 290);
  tft.print("5. Select Exit and press Menu SW to finish");
  tft.setFont();
  tft.setTextSize(2);
  for (int i = 0; i < 4; i++) {

    tft.setCursor(100, 70 + i * 28);
    tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
    tft.print(bridgeReading[i]);

  }
  tft.setCursor(100, 70);
  tft.setTextColor(ILI9488_BLUE, ILI9488_WHITE);
  tft.print(bridgeReading[0]);
  digitalWrite(MENUENCODERSWITCH, HIGH);
  MyDelay(100L);

  indexCal = 0;
  frequencyEncoderMovement = 0;
  SendFrequency(1000000);
  ReadSWRValue();
  RValueAve = RValue;
  while (1) {

    for (int i = 0; i < 4; i++) {

      tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
      switch (i) {


        case 0:

          ReadSWRValue();
          tft.setCursor(250, 70 + i * 28);
          RValueAve = RValueAve * .95 + .05 * RValue;
          MyDelay(10);
          tft.print(RValueAve);

          break;

        case 1:

          ReadSWRValue();
          tft.setCursor(250, 70 + i * 28);
          RValueAve = RValueAve * .95 + .05 * RValue;
          MyDelay(10);
          tft.print(RValueAve);

          break;

        case 2:

          ReadSWRValue();
          tft.setCursor(250, 70 + i * 28);
          RValueAve = RValueAve * .95 + .05 * RValue;
          tft.print(RValueAve);
          break;

      }
    }
    if (menuEncoderMovement) {
      if (menuEncoderMovement == 1) {
        indexCal++;
        if (indexCal == 8) {        // wrap to first index
          indexCal = 0;
        }
      }
      if (menuEncoderMovement == -1) {
        indexCal--;
        if (indexCal < 0) {        // wrap to last index
          indexCal = 7;
        }
      }
      menuEncoderMovement = 0;
      tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
      for (int i = 0; i < 4; i++) {
        tft.setCursor(100, 70 + i * 28);
        tft.print(bridgeReading[i]);
      }
      tft.setTextColor(ILI9488_BLUE, ILI9488_WHITE);
      tft.setCursor(100, 40 + indexCal * 28);
      tft.print(bridgeReading[indexCal]);
    }

    switch (indexCal) {

        break;

      case 0 :
        ReadSWRValue();
        tft.setTextColor(ILI9488_CYAN, ILI9488_BLACK);
        tft.setCursor(250, 70 + indexCal * 28);
        RValueAve = RValueAve * .95 + .05 * RValue;
        tft.print(RValueAve, 2);
        tft.setCursor(400, 70 + indexCal * 28);
        tft.print(25. - RValueAve, 2);
        if (digitalRead(MENUENCODERSWITCH) == LOW) {
          yCal25Temp = 25. - RValueAve;
          tft.setCursor(5, 70 + indexCal * 28);
          tft.print("Saved!");
        }
        break;

      case 1 :
        ReadSWRValue();
        tft.setCursor(250, 70 + indexCal * 28);
        RValueAve = RValueAve * .95 + .05 * RValue;
        tft.print(RValueAve, 2);
        tft.setCursor(400, 70 + indexCal * 28);
        tft.print(50. - RValueAve, 1);
        if (digitalRead(MENUENCODERSWITCH) == LOW) {
          yCal50Temp = 50 - RValueAve;
          tft.setCursor(5, 70 + indexCal * 28);
          tft.print("Saved!");
        }
        break;

      case 2 :
        ReadSWRValue();
        tft.setCursor(250, 70 + indexCal * 28);
        RValueAve = RValueAve * .95 + .05 * RValue;
        tft.print(RValueAve, 2);
        tft.setCursor(400, 70 + indexCal * 28);
        tft.print(200. - RValueAve, 2);
        if (digitalRead(MENUENCODERSWITCH) == LOW) {
          yCal50Temp = 200 - RValueAve;
          tft.setCursor(5, 70 + indexCal * 28);
          tft.print("Saved!");
        }
        break;
      case 3 :
        if (digitalRead(MENUENCODERSWITCH) == LOW) {
          yCal25 = yCal25Temp; //Difference value between actual and readout RValue from Cal routine
          yCal50 = yCal50Temp;
          yCal200 = yCal200Temp;
          MakeMenuSelection();
        }
        break;

    }

  }

}

/*****
  Purpose: To calibrate SWR
  Parameter list:
  void
  Return value:
  void
*****/
void calSWR() {
  int zeroIndex = 0;
  //while (digitalRead(MENUENCODERSWITCH) != LOW) {
  int endFlag = 0;
  while (1) {
    if (digitalRead(MENUENCODERSWITCH) == LOW) {
      endFlag = 1;
      delay(100);
    }
    if (endFlag == 1) {
      endFlag = 0;
      //MakeMenuSelection();
      ShowMainDisplay();
      // SendFrequency(0);
      loop();
      // break;
    }
    ReadSWRValue();

    if (menuEncoderMovement) {                             // Must be i (CW) or -1 (CCW)
      if (menuEncoderMovement == 1) {
        zeroIndex++;
      }
      if (menuEncoderMovement == -1) {
        zeroIndex--;
      }
      delay(10);
      menuEncoderMovement = 0;
      zeroAveVz = zeroIndex;
    }

    tft.setTextColor(ILI9488_YELLOW, ILI9488_BLACK);
    tft.setCursor(150, 40);
    tft.print("Value");
    tft.setTextColor(ILI9488_YELLOW, ILI9488_BLACK);
    tft.setCursor(300, 40);
    tft.print("Cal Factor");
    tft.setTextSize(2);
    tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
    tft.setCursor(30, 70);
    tft.print(" aveVm= ");
    tft.setTextColor(ILI9488_BLUE, ILI9488_WHITE);
    tft.setCursor(30, 100);
    tft.print(" aveVz= ");
    tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
    tft.setCursor(30, 130);
    tft.print(" aveVrz= ");



    tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
    tft.setCursor(150, 70);
    tft.print(aveVm);
    tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
    tft.setCursor(150, 100);
    tft.print(aveVz);
    tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
    tft.setCursor(150, 130);
    tft.print(aveVrz);

  }
}


/*void CalZero()
  {
  int i;
  double sum[2] = {0.0, 0.0};

  double FWD = 0.0;
  double REV = 0.0;
  double rawVm;
  double rawVrz;
  double rawVz;
  double VmSum;
  double VrzSum;
  double VzSum;

  float aveVm;
  float  aveVrz;
  float  aveVz;

  double dBValueVm;
  double dBValueVrz;
  double dBValueVz;

  double linVm;
  double linVrz;
  double linVz;

  double linFWDSum;
  double linREVSum;
  double aveLinFWD;
  double aveLinREV;

  double dBValueDiff;
  double linValueDiff;
  double VSWR2;
  double rawValueDiff;
  int numSamples = 50;
  double calGain = 1;
  double ZMag;
  double cosAngle;
  double angle;
  double RValue;
  double XValue;
  double reflCoeff;

  double VsRefCount = 2130;
  double VsRefLogAmpV = 1.716064453;
  double VsRefVoltage = .551;
  double voltPerdB = .0255;
  double VsLinVoltage;
  double VmLinVoltage;
  double VzLinVoltage;
  double gainFactor;

  SendFrequency(7150000L);
  delay(10);
  for (i = 0; i < numSamples; i++) {
    rawVm = analogRead(VM);
    VmSum  += rawVm;
    rawVrz = analogRead(VRZ);
    VrzSum  += rawVrz;
    rawVz = analogRead(VZ);
    VzSum  += rawVz;


  }
  #ifdef DEBUG
  #endif
  #ifdef DEBUG
  Serial.print("     zeroIncrement = "); Serial.println(zeroIncrement);
  #endif
  //aveVm = ((double)VmSum / numSamples)+30;
  // aveVrz = ((double)VrzSum / numSamples)-50;
  //aveVz = ((double)VzSum / numSamples)-39;

  aveVm = ((double)VmSum / numSamples);
  aveVrz = ((double)VrzSum / numSamples) ;
  aveVz = ((double)VzSum / numSamples);
  #ifdef DEBUG

  Serial.println(" ");
  Serial.print("     aveVrz = "); Serial.println(aveVrz);
  Serial.print("     aveVm = "); Serial.println(aveVm);
  Serial.print("     aveVz = "); Serial.println(aveVz);
  #endif

  gainFactor = (double)(500.0 + zeroIncrement) / 500.0;

  linVm = (aveVm * 3.3 / (4096.*1.837));
  linVrz = (aveVrz * 3.3 / (4096.*1.837));
  linVz = (aveVz * 3.3 / (4096.*1.837));
  #ifdef DEBUG
  Serial.print("gainFactor = "); Serial.println(gainFactor, 4);
  Serial.print("linVrz = "); Serial.println(linVrz, 4);
  Serial.print("linVm = "); Serial.println(linVm, 4);
  Serial.print("linVz = "); Serial.println(linVz, 4);
  #endif
  ZMag = linVz * 50 / linVm;
  cosAngle = (linVm * linVm + linVz * linVz - 4 * linVrz * linVrz) / (2 * linVm * linVz);
  angle = acos(cosAngle);
  RValue = ZMag / (sqrt(1 + tan(angle) * tan(angle)));
  XValue = RValue * tan(angle);

  reflCoeff = sqrt(((RValue - 50) * (RValue - 50) + XValue * XValue) / ((RValue + 50) * (RValue + 50) + XValue * XValue));
  VSWR = (1 + reflCoeff) / (1 - reflCoeff);
  #ifdef DEBUG
  Serial.println("  ");
  Serial.print("     linVm = "); Serial.println(linVm, 4);
  Serial.print("     linVrz = "); Serial.println(linVrz, 4);

  Serial.print("     linVz = "); Serial.println(linVz, 4);
  Serial.print("     ZMag = "); Serial.print(ZMag);
  Serial.print("     angle(deg) = "); Serial.print(angle * 360. / 2.828);

  Serial.print("     RValue = "); Serial.print(RValue);
  Serial.print("     XValue = "); Serial.print(XValue);
  Serial.print("   reflCoeff = "); Serial.println(reflCoeff);
  Serial.print("VSWR = "); Serial.println(VSWR);
  #endif
  tft.setCursor(100, 70);
  tft.print(zeroIncrement);
  tft.setCursor(100, 100);
  tft.print("linVm  ");
  tft.print(linVm, 4);
  tft.setCursor(100, 130);
  tft.print("linVrz  ");
  tft.print(linVrz, 4);
  tft.setCursor(100, 160);
  tft.print("linVz  ");
  tft.print(linVz, 4);

  }*/
