
#ifndef BEENHERE
//#include <SPI.h>
#include "Post.h"
#endif


/*****
  Purpose:  SetAutoNotch
  Paramter list:

  Return value:  void
*****/
void SetAutoNotch() {
  float prob;
  float note;
  int noteFlag;
  float noteAve = 0;
  float noteOld = 0;
  float tiny = .9;
  long xNew = 0;
  long xave = 0;
  //Serial.println("in setAutoNotch");
  int i;
  long xFinal = 0;
  long xAveOld = 0;
  int  holdFlag = 0;
  //------------
  //NotchHold.initButton(&tft, 300, 70, BUTTON_W + 20, BUTTON_H, ILI9488_WHITE, ButtonColorsOff[2], ButtonColorsTextOff[2], "Hold Off", BUTTON_TEXTSIZE);
  NotchHold.drawButton();
  //----------------
  while (digitalRead(FREQENCODERSWITCH) != LOW) {
    //if (notefreq.available() and holdFlag != 1) {
    //prob = notefreq.probability();
    //================

    xave = 0;
    int i = 0;
    while ( i < 26) {
      // xNew = notefreq.read();
      prob = notefreq.probability();
      MyDelay(1);
      if (prob > .9 ) {
        xave = xave + xNew;
        i++;
      }
    }

    xave = xave / 25;
    //Serial.print("xave= "); Serial.println(xave);

    if ((xNew / 10) < (xave / 10) + 50 and  xNew / 10 > (xave / 10) - 50) {
      xFinal = xNew;
      //Serial.print("xNew= "); Serial.println(xNew);
    }
    //Serial.println(" ");
    xAveOld = xave;
    notchFreq = xFinal;
    //==============
    //if (prob > .95) {
    Notch.setNotch(0, notchFreq, 5);
    Notch.setNotch(1, notchFreq, 5);
    Notch.setNotch(2, notchFreq, 5);
    Notch.setNotch(3, notchFreq, 5);
    //Serial.print("prob= ");Serial.println(prob);

    displayNotchFilter();
    // }

  //}
  //Serial.println("after if ");
  //delay(50);
  //if (myTouch.dataAvailable()) {
    GetTouchCoordinates2();
    if ((caltx > 300 - (BUTTON_W + 20) / 2) and (caltx < 300 + (BUTTON_W + 20) / 2) and (calty > 70 - BUTTON_H / 2) and (calty <  70 + BUTTON_H / 2)) {
      Serial.println("hold pressed");
      switch (holdFlag) {
        case 0:
          holdFlag = 1;
         // NotchHold.initButton(&tft, 300, 70, BUTTON_W + 20, BUTTON_H, ILI9488_WHITE, ButtonColorsOn[2], ButtonColorsTextOn, "Hold On", BUTTON_TEXTSIZE);
          NotchHold.drawButton();
          break;
        case 1:
          holdFlag = 0;
        //  NotchHold.initButton(&tft, 300, 70, BUTTON_W + 20, BUTTON_H, ILI9488_WHITE, ButtonColorsOff[2], ButtonColorsTextOff[2], "Hold Off", BUTTON_TEXTSIZE);
          NotchHold.drawButton();
          break;
      }

    }
  //}

}
ButtonOff(2);
}

/*****
  Purpose:  Set ALC Threshold
  Paramter list:

  Return value:  void
*****/
void SetALC() {
  int knee_dBFS_LOld;
  while (digitalRead(FREQENCODERSWITCH) != LOW) {

    unsigned char result = rotaryFreq.process();
    knee_dBFS_L = knee_dBFS_L + freqEncoderMovement ;
    if (knee_dBFS_L < -96) knee_dBFS_L = -96;
    if (knee_dBFS_L > 0) knee_dBFS_L = 0;

    freqEncoderMovement = 0;
    if (knee_dBFS_L != knee_dBFS_LOld) {
      tft.fillRect(110, 40 * lastButtonindex1, 70, 25, ILI9488_BLACK);
      tft.setTextSize(2);
      tft.setTextColor(ILI9488_WHITE);
      tft.setCursor(102, (40 * lastButtonindex1) + BUTTONMAIN_Y - 8);

      tft.print(knee_dBFS_L);
      //Serial.print("CWCenterFreq2=  "); Serial.println(CWCenterFreq2);

      knee_dBFS_LOld = knee_dBFS_L;

    }
  }
}



/*****
  Purpose:  Define a function to configure the Left Audio AGC

  Paramter list:
    boolean use_HP_filter
    float knee_dBFS_L
    float comp_ratio_L
    float attack_sec_L
    float release_sec_L

  Return value:  void
*****/
void SetupMyCompressors_L(boolean use_HP_filter_L, float knee_dBFS_L, float comp_ratio_L, float attack_sec_L, float release_sec_L) {
  //comp_L.enableHPFilter(use_HP_filter);
 //comp_L.setThresh_dBFS(knee_dBFS_L);
  //comp_L.setCompressionRatio(comp_ratio_L);
  //comp_L.setPreGain_dB(gain_dB_L);  //set the gain of the Right-channel gain processor
  float fs_Hz = AUDIO_SAMPLE_RATE;
  //comp_L.setAttack_sec(attack_sec_L, fs_Hz);
  //comp_L.setRelease_sec(release_sec_L, fs_Hz);
}

/*****
  Purpose:  Function to set Filter Parameters
  Return value:  void

  Note: Gain Values in dB +/- max of about 20dB either way  8-14-18
*****/
void SetupFilters() {
  //=========================      Setup Left Channel Receive audio EQ   changed 2019-01-17
  lpFreq = 1500;
  float lpQ = .75;
  hpFreq = 400;
  LP1.setLowpass(0, lpFreq * 2.11, lpQ);
  LP1.setLowpass(1, lpFreq * 2.11, lpQ);
  LP1.setLowpass(2, lpFreq * 2.11, lpQ);
  LP1.setLowpass(3, lpFreq * 2.11, lpQ);

  LP2.setLowpass(0, lpFreq * 2.11, lpQ);
  LP2.setLowpass(1, lpFreq * 2.11, lpQ);
  LP2.setLowpass(2, lpFreq * 2.11, lpQ);
  LP2.setLowpass(3, lpFreq * 2.11, lpQ);

  LP3.setLowpass(0, lpFreq * 2.11, lpQ);
  LP3.setLowpass(1, lpFreq * 2.11, lpQ);
  LP3.setLowpass(2, lpFreq * 2.11, lpQ);
  LP3.setLowpass(3, lpFreq * 2.11, lpQ);

  LP4.setLowpass(0, lpFreq * 2.11, lpQ);
  LP4.setLowpass(1, lpFreq * 2.11, lpQ);
  LP4.setLowpass(2, lpFreq * 2.11, lpQ);
  LP4.setLowpass(3, lpFreq * 2.11, lpQ);

  LP5.setLowpass(0, lpFreq * 2.11, lpQ);
  LP5.setLowpass(1, lpFreq * 2.11, lpQ);
  LP5.setLowpass(2, lpFreq * 2.11, lpQ);
  LP5.setLowpass(3, lpFreq * 2.11, lpQ);

  LP6.setLowpass(0, lpFreq * 2.11, lpQ);
  LP6.setLowpass(1, lpFreq * 2.11, lpQ);
  LP6.setLowpass(2, lpFreq * 2.11, lpQ);
  LP6.setLowpass(3, lpFreq * 2.11, lpQ);

  LP7.setLowpass(0, lpFreq * 2.11, lpQ);
  LP7.setLowpass(1, lpFreq * 2.11, lpQ);
  LP7.setLowpass(2, lpFreq * 2.11, lpQ);
  LP7.setLowpass(3, lpFreq * 2.11, lpQ);

  LP8.setLowpass(0, lpFreq * 2.11, lpQ);
  LP8.setLowpass(1, lpFreq * 2.11, lpQ);
  LP8.setLowpass(2, lpFreq * 2.11, lpQ);
  LP8.setLowpass(3, lpFreq * 2.11, lpQ);

  HP_1.setHighpass(0, hpFreq * .5, lpQ);
  HP_1.setHighpass(1, hpFreq * .5, lpQ);
  HP_1.setHighpass(2, hpFreq * .5, lpQ);
  HP_1.setHighpass(3, hpFreq * .5, lpQ);

  HP_2.setHighpass(0, hpFreq * .5, lpQ);
  HP_2.setHighpass(1, hpFreq * .5, lpQ);
  HP_2.setHighpass(2, hpFreq * .5, lpQ);
  HP_2.setHighpass(3, hpFreq * .5, lpQ);

  HP_3.setHighpass(0, hpFreq * .5, lpQ);
  HP_3.setHighpass(1, hpFreq * .5, lpQ);
  HP_3.setHighpass(2, hpFreq * .5, lpQ);
  HP_3.setHighpass(3, hpFreq * .5, lpQ);

  HP_4.setHighpass(0, hpFreq * .5, lpQ);
  HP_4.setHighpass(1, hpFreq * .5, lpQ);
  HP_4.setHighpass(2, hpFreq * .5, lpQ);
  HP_4.setHighpass(3, hpFreq * .5, lpQ);

  tft.fillRect(110, 6, 120, 20, ILI9488_BLACK);
  /*tft.setTextSize(2);
    tft.setTextColor(ILI9488_RED);
    tft.setCursor(110,  BUTTONMAIN_Y - 8);
    tft.print("      Off");*/
  notchFreq = 1000;
  Notch.setNotch(0, notchFreq, 20);
  Notch.setNotch(1, notchFreq, 20);
  Notch.setNotch(2, notchFreq, 20);
  Notch.setNotch(3, notchFreq, 20);
  tft.setCursor(110,  40 + BUTTONMAIN_Y - 8);
  //tft.print("      Off");
  CWFilterQ = 3;
  CW_1.setBandpass(0, CWFILTERFREQUENCY, CWFilterQ);
  CW_1.setBandpass(1, CWFILTERFREQUENCY, CWFilterQ);
  CW_1.setBandpass(2, CWFILTERFREQUENCY, CWFilterQ);
  CW_1.setBandpass(3, CWFILTERFREQUENCY, CWFilterQ);

  CW_2.setBandpass(0, CWFILTERFREQUENCY, CWFilterQ);
  CW_2.setBandpass(1, CWFILTERFREQUENCY, CWFilterQ);
  CW_2.setBandpass(2, CWFILTERFREQUENCY, CWFilterQ);
  CW_2.setBandpass(3, CWFILTERFREQUENCY, CWFilterQ);

  CW_3.setBandpass(0, CWFILTERFREQUENCY, CWFilterQ);
  CW_3.setBandpass(1, CWFILTERFREQUENCY, CWFilterQ);
  CW_3.setBandpass(2, CWFILTERFREQUENCY, CWFilterQ);
  CW_3.setBandpass(3, CWFILTERFREQUENCY, CWFilterQ);

  CW_4.setBandpass(0, CWFILTERFREQUENCY, CWFilterQ);
  CW_4.setBandpass(1, CWFILTERFREQUENCY, CWFilterQ);
  CW_4.setBandpass(2, CWFILTERFREQUENCY, CWFilterQ);
  CW_4.setBandpass(3, CWFILTERFREQUENCY, CWFilterQ);
  tft.setCursor(110,  120 + BUTTONMAIN_Y - 8);
  //tft.print("      Off");
  eqFreq[0] = 150;
  eqFreq[1] = 240;
  eqFreq[2] = 370;
  eqFreq[3] = 590;
  eqFreq[4] = 900;
  eqFreq[5] = 1300;
  eqFreq[6] = 2000;
  eqFreq[7] = 3300;
  EQ_1.setBandpass(0, eqFreq[0], .9); //Band 1 140Hz, Q =.9
  EQ_1.setBandpass(1, eqFreq[0], .9);
  EQ_1.setBandpass(2, eqFreq[0], .9);
  EQ_1.setBandpass(3, eqFreq[0], .9);

  EQ_2.setBandpass(0, eqFreq[1], .9); //Band 2 240Hz
  EQ_2.setBandpass(1, eqFreq[1], .9);
  EQ_2.setBandpass(2, eqFreq[1], .9);
  EQ_2.setBandpass(3, eqFreq[1], .9);

  EQ_3.setBandpass(0, eqFreq[2], .9); //Band 3 370Hz
  EQ_3.setBandpass(1, eqFreq[2], .9);
  EQ_3.setBandpass(2, eqFreq[2], .9);
  EQ_3.setBandpass(3, eqFreq[2], .9);

  EQ_4.setBandpass(0, eqFreq[3], .9);  // Band 4 590Hz
  EQ_4.setBandpass(1, eqFreq[3], .9);
  EQ_4.setBandpass(2, eqFreq[3], .9);
  EQ_4.setBandpass(3, eqFreq[3], .9);

  EQ_5.setBandpass(0, eqFreq[4], .9);  // Band 5 900Hz
  EQ_5.setBandpass(1, eqFreq[4], .9);
  EQ_5.setBandpass(2, eqFreq[4], .9);
  EQ_5.setBandpass(3, eqFreq[4], .9);

  EQ_6.setBandpass(0, eqFreq[5], .9); // Band 6 1300Hz
  EQ_6.setBandpass(1, eqFreq[5], .9);
  EQ_6.setBandpass(2, eqFreq[5], .9);
  EQ_6.setBandpass(3, eqFreq[5], .9);

  EQ_7.setBandpass(0, eqFreq[6], .9);// Band 7  2000Hz
  EQ_7.setBandpass(1, eqFreq[6], .9);
  EQ_7.setBandpass(2, eqFreq[6], .9);
  EQ_7.setBandpass(3, eqFreq[6], .9);

  EQ_8.setBandpass(0, eqFreq[7], .9); // Band 8 3300 Hz
  EQ_8.setBandpass(1, eqFreq[7], .9);
  EQ_8.setBandpass(2, eqFreq[7], .9);
  EQ_8.setBandpass(3, eqFreq[7], .9);
}
/*****
  Purpose:  Function to set gains for the 8-Band Receive EQ

  Paramter list:
    float band1Gain_L
    float band2Gain_L
    float band3Gain_L
    float band4Gain_L
    float band5Gain_L
    float band6Gain_L
    float band7Gain_L
    float band8Gain_L

  Return value:  void

  Note: Gain Values in dB +/- max of about 20dB either way  8-14-18
*****/
void EqGainSetL() {
  EQ_Mix1.gain(0,  bandGain[0] );     //  140 // Set Band Gains 0= off, 1= unity changed 2019-01-17
  EQ_Mix1.gain(1, -bandGain[1]);          //  240
  EQ_Mix1.gain(2, bandGain[2] );     //  370
  EQ_Mix1.gain(3, -bandGain[3]);          //  590

  EQ_Mix2.gain(0, bandGain[4]);           //  900
  EQ_Mix2.gain(1, -(bandGain[5]));  //  1300
  //EQ_Mix2.gain(2, bandGain[6] + .05);     //  2000
  //EQ_Mix2.gain(3, -(bandGain[7] + .3));   //  3300
  EQ_Mix2.gain(2, bandGain[6]);     //  2000
  EQ_Mix2.gain(3, -(bandGain[7]));   //  3300


  EQ_Mix3.gain(0, 1);  // Combine Mixers 5 & 6
  EQ_Mix3.gain(1, 1);
  EQ_Mix3.gain(2, 0);
}

/*****
  Purpose: Display Notch Filter

  Parameter list:
    void
  Return value;
    void
*****/
void displayNotchFilter() {
  int offSetFreq = 50;
  if (notchFreq < 50) {
    notchFreq = 50;
  }
  if (notchFreq > 5000) {
    notchFreq = 5000;
  }
  xScreenPos2 = map(notchFreq, 0L, 5000L, 235, 460); // Map to screen coodinates

  if (notchFreq > 4000) {
    offSetFreq = 50;
  }
  else {
    offSetFreq = 0;
  }
  tft.fillRect(xScreenPos2 - 50 - offSetFreq, yOrigin - 135, 110 + offSetFreq, 20, ILI9488_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ILI9488_WHITE);
  tft.setCursor(xScreenPos2 - offSetFreq, yOrigin - 130);
  tft.print(notchFreq);

  tft.drawLine(xScreenPosOld - 10, yOrigin - 140, xScreenPosOld, yOrigin, ILI9488_BLACK); //Erase old Left Slant Line
  tft.drawLine(xScreenPosOld, yOrigin, xScreenPosOld + 10, yOrigin - 140, ILI9488_BLACK); //Erase old Right Slant Line

  tft.drawLine(xScreenPos2 - 10, yOrigin - 140, xScreenPos2, yOrigin, ILI9488_YELLOW); //Left Slant Line
  tft.drawLine(xScreenPos2, yOrigin, xScreenPos2 + 10, yOrigin - 140, ILI9488_YELLOW); //Right Slant Line

  xScreenPosOld = xScreenPos2;
  if (notchFreq < 1200) {
    tft.drawFastVLine(xOrigin, yOrigin - 230, 229, ILI9488_WHITE); //Draw Y Axis
  }
}

/*****
  Purpose: Display CW Filters

  Parameter list:
    void
  Return value;
    void
*****/
void displayCWFilter() {
  int offSetPosition = 0;

  switch (CWFilter) {
    case 1:
      offSetPosition = 0;
      CWFilterQ = 3;
      break;
    case 2:
      offSetPosition = 5;
      CWFilterQ = 1.5;
      break;
    case 3:
      offSetPosition = 10;
      CWFilterQ = .7;
      break;
  }
  xScreenPos2 = map(CWCenterFreq2, 0L, 5000L, 235, 460); // Map to screen coodinates

  tft.fillRect(xScreenPos2 - 5, yOrigin - 165, 50, 20, ILI9488_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ILI9488_WHITE);
  tft.setCursor(xScreenPos2, yOrigin - 160);
  tft.print(CWCenterFreq2);

  tft.drawLine(xScreenPos2old - 15 - offSetPositionOld, yOrigin - 1, xScreenPos2old - 5 - offSetPositionOld, yOrigin - 139, ILI9488_BLACK); //Left slant line
  tft.drawLine(xScreenPos2old + 15 + offSetPositionOld, yOrigin - 1, xScreenPos2old + 5 + offSetPositionOld, yOrigin - 139, ILI9488_BLACK); //Right slant line
  tft.drawLine(xScreenPos2old - 5 - offSetPositionOld, yOrigin - 139, xScreenPos2 + 5 + offSetPositionOld, yOrigin - 139, ILI9488_BLACK); //Top Horizontal line

  tft.drawLine(xScreenPos2 - 15 - offSetPosition, yOrigin - 1, xScreenPos2 - 5 - offSetPosition, yOrigin - 139, ILI9488_YELLOW); //Right slant line
  //tft.fillRect(xOrigin, yOrigin - 139, 20, 145, ILI9488_BLACK);
  tft.drawLine(xScreenPos2 + 15 + offSetPosition, yOrigin - 1, xScreenPos2 + 5 + offSetPosition, yOrigin - 139, ILI9488_YELLOW); //Left slant line
  tft.drawLine(xScreenPos2 - 5 - offSetPosition, yOrigin - 139, xScreenPos2 + 5 + offSetPosition, yOrigin - 139, ILI9488_YELLOW); //Top Horizontal line

  offSetPositionOld = offSetPosition;
  //tft.drawFastVLine(xOrigin, yOrigin - 230, 229, ILI9488_WHITE); //Draw Y Axis
  xScreenPos2old = xScreenPos2;
}
/*****
  Purpose: Display HP Filter Cut-off Frequency

  Parameter list:
    void
  Return value;
    void
*****/
void displayHPCutoff() {
  int offSetFreq = 0;
  if (hpFreq < 150) {
    hpFreq = 150;
  }
  if (hpFreq > 1000) {
    hpFreq = 1000;
  }
  xScreenPos4 = map(hpFreq, 0L, 5000L, 235, 460); // Map to screen coodinates


  tft.fillRect(xOrigin + 49 , yOrigin - 199, 180 , 20, ILI9488_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ILI9488_WHITE);
  tft.setCursor(xOrigin + 50 , yOrigin - 200);
  tft.print("HP Freq:  "); tft.print(hpFreq);

  tft.drawLine(xScreenPosOld4 - 5, yOrigin - 2, xScreenPosOld4, yOrigin - 139, ILI9488_BLACK);
  tft.drawLine(xScreenPos2, yOrigin - 140, xScreenPosOld4, yOrigin - 139, ILI9488_BLACK); //Horizontal Line

  tft.drawLine(xScreenPos4 - 5, yOrigin - 2, xScreenPos4, yOrigin - 139, ILI9488_CYAN);
  tft.drawLine(xScreenPos4, yOrigin - 139, xScreenPos2, yOrigin - 139, ILI9488_YELLOW); //Horizontal Line
  xScreenPosOld4 = xScreenPos4;
  //if (hpFreq < 1200) {
  tft.drawFastVLine(xOrigin, yOrigin - 230, 229, ILI9488_WHITE); //Draw Y Axis
  //}
}

/*****
  Purpose: Display Filter Cut-off Frequency

  Parameter list:
    void
  Return value;
    void
*****/
void displayLPCutoff() {
  int offSetFreq = 0;
  if (lpFreq < 50) {
    lpFreq = 50;
  }
  if (lpFreq > 5000) {
    lpFreq = 5000;
  }
  xScreenPos2 = map(lpFreq, 0L, 5000L, 235, 460); // Map to screen coodinates


  tft.fillRect(xOrigin + 49 , yOrigin - 172, 180 , 20, ILI9488_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ILI9488_WHITE);
  tft.setCursor(xOrigin + 50 , yOrigin - 170);
  tft.print("LP Freq:  "); tft.print(lpFreq);

  tft.drawLine(xScreenPosOld2 + 30, yOrigin, xScreenPosOld2, yOrigin - 139, ILI9488_BLACK);
  tft.drawLine(xScreenPos4, yOrigin - 139, xScreenPosOld2, yOrigin - 139, ILI9488_BLACK);

  tft.drawLine(xScreenPos2 + 30, yOrigin, xScreenPos2, yOrigin - 139, ILI9488_YELLOW);
  tft.drawLine(xScreenPos4, yOrigin - 139, xScreenPos2, yOrigin - 139, ILI9488_YELLOW); //Horizontal line
  xScreenPosOld2 = xScreenPos2;
  //if (lpFreq < 1200) {
  //tft.drawFastVLine(xOrigin, yOrigin - 230, 229, ILI9488_WHITE); //Draw Y Axis
  // }
}
/*****
  Purpose:  Set Parameters for CW Filters

  Paramter list:
    void

  Return value:  void
*****/
void SetCWFilters() {
  tft.fillRect(xOrigin + 1, yOrigin - 230, 240, 229, ILI9488_BLACK);
  //DrawExitButton();

  int rotaryFlag = 0;
  exitFlag = 0;
  unsigned char result;
  // long freqIncr;
  CWCenterFreq2 = CWFILTERFREQUENCY;
  long   CWFilterOld;
  long   CWCenterFreq2Old;

  while (digitalRead(FREQENCODERSWITCH) != LOW ) {

    unsigned char result = rotaryFreq.process();
    CWFilter = CWFilter + secondEncoderMovement ;
    if (CWFilter < 1) CWFilter = 1;
    if (CWFilter > 3) CWFilter = 3;

    CWCenterFreq2 = CWCenterFreq2 +  10 * freqEncoderMovement;
    if (CWCenterFreq2 < 400) {
      CWCenterFreq2 = 400;
    }
    freqEncoderMovement = 0;
    secondEncoderMovement = 0;
    if (CWFilter != CWFilterOld or CWCenterFreq2 != CWCenterFreq2Old) {
      tft.fillRect(103, 40 * lastButtonindex1, 117, 25, ILI9488_BLACK);
      tft.setTextSize(2);
      tft.setTextColor(ILI9488_WHITE);
      tft.setCursor(104, (40 * lastButtonindex1) + BUTTONMAIN_Y - 8);
      tft.print("CW");
      tft.print(CWFilter); tft.print("  "); tft.print(CWCenterFreq2);
      //Serial.print("CWCenterFreq2=  "); Serial.println(CWCenterFreq2);
      displayCWFilter();
      CWFilterOld = CWFilter;
      CWCenterFreq2Old = CWCenterFreq2;
      //MyDelay(10);

      CW_1.setBandpass(0, CWCenterFreq2, CWFilterQ);
      CW_1.setBandpass(1, CWCenterFreq2, CWFilterQ);
      CW_1.setBandpass(2, CWCenterFreq2, CWFilterQ);
      CW_1.setBandpass(3, CWCenterFreq2, CWFilterQ);

      CW_2.setBandpass(0, CWCenterFreq2, CWFilterQ);
      CW_2.setBandpass(1, CWCenterFreq2, CWFilterQ);
      CW_2.setBandpass(2, CWCenterFreq2, CWFilterQ);
      CW_2.setBandpass(3, CWCenterFreq2, CWFilterQ);

      CW_3.setBandpass(0, CWCenterFreq2, CWFilterQ);
      CW_3.setBandpass(1, CWCenterFreq2, CWFilterQ);
      CW_3.setBandpass(2, CWCenterFreq2, CWFilterQ);
      CW_3.setBandpass(3, CWCenterFreq2, CWFilterQ);

      CW_4.setBandpass(0, CWCenterFreq2, CWFilterQ);
      CW_4.setBandpass(1, CWCenterFreq2, CWFilterQ);
      CW_4.setBandpass(2, CWCenterFreq2, CWFilterQ);
      CW_4.setBandpass(3, CWCenterFreq2, CWFilterQ);
      //displayCWFilter();
    }
    CWFilterOld = CWFilter;
    CWCenterFreq2Old != CWCenterFreq2;
    //DoExitButton();
    //Serial.println(exitFlag);
    if (exitFlag == 1) {
      break;
    }
  }
  ButtonOff(3);
}


/*****
  Purpose:  Set Parameters for Lowpass Filters

  Paramter list:
    void

  Return value:  void
*****/
void SetLPFilters() {

  tft.fillRect(xOrigin + 1, yOrigin - 230, 240, 229, ILI9488_BLACK);
  int rotaryFlag = 0;
  unsigned char result1;
  unsigned char result2;
  long freqIncr;
  long   lpFreqOld;
  long   hpFreqOld;
  float lpQ;

  while (digitalRead(FREQENCODERSWITCH) != LOW) {

    result2 = rotarySecond.process();
    hpFreq = hpFreq + 20 * freqEncoderMovement;
    result1 = rotaryFreq.process();
    lpFreq = lpFreq + 100 * secondEncoderMovement;

    //Serial.println(freqEncoderMovement);Serial.println(lpFreq);

    freqEncoderMovement = 0;
    secondEncoderMovement = 0;
    if (lpFreq != lpFreqOld) {
      tft.fillRect(170, 3, 53, 25, ILI9488_BLACK);
      tft.setTextSize(2);
      tft.setTextColor(ILI9488_WHITE);
      tft.setCursor(172, (40 * lastButtonindex1) + BUTTONMAIN_Y - 8);
      tft.print(lpFreq);

      displayLPCutoff();
      lpFreqOld = lpFreq;
      //MyDelay(100);

      //}
      lpQ = .73;
      LP1.setLowpass(0, lpFreq * 2.11, lpQ);
      LP1.setLowpass(1, lpFreq * 2.11, lpQ);
      LP1.setLowpass(2, lpFreq * 2.11, lpQ);
      LP1.setLowpass(3, lpFreq * 2.11, lpQ);

      LP2.setLowpass(0, lpFreq * 2.11, lpQ);
      LP2.setLowpass(1, lpFreq * 2.11, lpQ);
      LP2.setLowpass(2, lpFreq * 2.11, lpQ);
      LP2.setLowpass(3, lpFreq * 2.11, lpQ);

      LP3.setLowpass(0, lpFreq * 2.11, lpQ);
      LP3.setLowpass(1, lpFreq * 2.11, lpQ);
      LP3.setLowpass(2, lpFreq * 2.11, lpQ);
      LP3.setLowpass(3, lpFreq * 2.11, lpQ);

      LP4.setLowpass(0, lpFreq * 2.11, lpQ);
      LP4.setLowpass(1, lpFreq * 2.11, lpQ);
      LP4.setLowpass(2, lpFreq * 2.11, lpQ);
      LP4.setLowpass(3, lpFreq * 2.11, lpQ);

      LP5.setLowpass(0, lpFreq * 2.11, lpQ);
      LP5.setLowpass(1, lpFreq * 2.11, lpQ);
      LP5.setLowpass(2, lpFreq * 2.11, lpQ);
      LP5.setLowpass(3, lpFreq * 2.11, lpQ);

      LP6.setLowpass(0, lpFreq * 2.11, lpQ);
      LP6.setLowpass(1, lpFreq * 2.11, lpQ);
      LP6.setLowpass(2, lpFreq * 2.11, lpQ);
      LP6.setLowpass(3, lpFreq * 2.11, lpQ);

      LP7.setLowpass(0, lpFreq * 2.11, lpQ);
      LP7.setLowpass(1, lpFreq * 2.11, lpQ);
      LP7.setLowpass(2, lpFreq * 2.11, lpQ);
      LP7.setLowpass(3, lpFreq * 2.11, lpQ);

      LP8.setLowpass(0, lpFreq * 2.11, lpQ);
      LP8.setLowpass(1, lpFreq * 2.11, lpQ);
      LP8.setLowpass(2, lpFreq * 2.11, lpQ);
      LP8.setLowpass(3, lpFreq * 2.11, lpQ);



    }
    if (hpFreq != hpFreqOld) {
      tft.fillRect(105, 3, 50, 25, ILI9488_BLACK);
      tft.setTextSize(2);
      tft.setTextColor(ILI9488_WHITE);
      tft.setCursor(110, (40 * lastButtonindex1) + BUTTONMAIN_Y - 8);
      tft.print(hpFreq);

      displayHPCutoff();
      hpFreqOld = hpFreq;
     float hpQ=.775;
      // MyDelay(100);

      HP_1.setHighpass(0, hpFreq * .5, hpQ);
      HP_1.setHighpass(1, hpFreq * .5, hpQ);
      HP_1.setHighpass(2, hpFreq * .5, hpQ);
      HP_1.setHighpass(3, hpFreq * .5, hpQ);

      HP_2.setHighpass(0, hpFreq * .5, hpQ);
      HP_2.setHighpass(1, hpFreq * .5, hpQ);
      HP_2.setHighpass(2, hpFreq * .5, hpQ);
      HP_2.setHighpass(3, hpFreq * .5, hpQ);

      HP_3.setHighpass(0, hpFreq * .5, hpQ);
      HP_3.setHighpass(1, hpFreq * .5, hpQ);
      HP_3.setHighpass(2, hpFreq * .5, hpQ);
      HP_3.setHighpass(3, hpFreq * .5, hpQ);

      HP_4.setHighpass(0, hpFreq * .5, hpQ);
      HP_4.setHighpass(1, hpFreq * .5, hpQ);
      HP_4.setHighpass(2, hpFreq * .5, hpQ);
      HP_4.setHighpass(3, hpFreq * .5, hpQ);
    }

    // }
  }
  ButtonOff(0);
}

/*****
  Purpose:  Set Parameters for Notch Filters

  Paramter list:
    void

  Return value:  void
*****/
void SetNotchFilters() {

  tft.fillRect(xOrigin + 1, yOrigin - 230, 240, 229, ILI9488_BLACK);
  int rotaryFlag = 0;
  unsigned char result;
  long freqIncr;
  long   notchFreqOld;
  while (digitalRead(FREQENCODERSWITCH) != LOW) {
    //Serial.println(lastButtonindex1);

    unsigned char result = rotaryFreq.process();
    notchFreq = notchFreq + 50 * freqEncoderMovement;

    //Serial.println(freqEncoderMovement);
    //  Serial.println(lpFreq);
    freqEncoderMovement = 0;
    if (notchFreq != notchFreqOld) {
      tft.fillRect(105, 42, 100, 25, ILI9488_BLACK);
      tft.setTextSize(2);
      tft.setTextColor(ILI9488_WHITE);
      tft.setCursor(110, (40 * lastButtonindex1) + BUTTONMAIN_Y - 8);
      tft.print(notchFreq);
      displayNotchFilter();
      notchFreqOld = notchFreq;
      MyDelay(100);
      //}
      Notch.setNotch(0, notchFreq, 20);
      Notch.setNotch(1, notchFreq, 20);
      Notch.setNotch(2, notchFreq, 20);
      Notch.setNotch(3, notchFreq, 20);

    }

  }
  ButtonOff(1);
}


/*****
  Purpose:  Set Parameters for EQ Filters

  Paramter list:
    void

  Return value:  void
*****/
void SetEQFilters() {
  //tft.fillRect(xOrigin + 1, yOrigin - 230, 240, 229, ILI9488_BLACK);
  int rotaryFlag = 0;
  unsigned char result;

  int   freqBandOld = 0;
  int   yLevelOld = 0;

  while (digitalRead(FREQENCODERSWITCH) != LOW) {
    //Serial.println(lastButtonindex1);
    //Serial.println("in while");
    unsigned char result = rotaryFreq.process();
    freqBand = freqBand +  freqEncoderMovement;
    if (freqBand > 7) {
      freqBand = 7;
    } if (freqBand < 0) {
      freqBand = 0;
    }

    yLevel[freqBand] = yLevel[freqBand] +  10 * secondEncoderMovement;
    if (yLevel[freqBand] > 200) {
      yLevel[freqBand] = 200;
    } if (yLevel[freqBand] < 0) {
      yLevel[freqBand] = 0;
    }

    if (freqBand != freqBandOld ) {
      tft.fillRect(xOrigin + 12 + 28 * (freqBandOld), yOrigin - yLevel[freqBandOld], 28, yLevel[freqBandOld], ILI9488_CYAN);
      tft.drawRect(xOrigin + 12 + 28 * (freqBandOld), yOrigin - yLevel[freqBandOld], 28, yLevel[freqBandOld], ILI9488_BLUE);
      tft.fillRect(xOrigin + 12 + 28 * freqBand, yOrigin - yLevel[freqBand], 28, yLevel[freqBand], ILI9488_GREEN);
      tft.drawRect(xOrigin + 12 + 28 * freqBand, yOrigin - yLevel[freqBand], 28, yLevel[freqBand], ILI9488_BLUE);

      freqBandOld = freqBand;
    }
    freqEncoderMovement = 0;

    if (yLevel[freqBand] != yLevelOld) {
      tft.fillRect(xOrigin + 12 + 28 * (freqBand - freqEncoderMovement), yOrigin - yLevel[freqBand], 28, yLevel[freqBand], ILI9488_CYAN);
      tft.drawRect(xOrigin + 12 + 28 * (freqBand - freqEncoderMovement), yOrigin - yLevel[freqBand], 28, yLevel[freqBand], ILI9488_BLUE);
      tft.fillRect(xOrigin + 12 + 28 * freqBand, yOrigin - yLevelOld, 28, yLevelOld, ILI9488_BLACK);
      tft.drawRect(xOrigin + 12 + 28 * freqBand, yOrigin - yLevelOld, 28, yLevelOld, ILI9488_BLACK);
      tft.fillRect(xOrigin + 12 + 28 * freqBand, yOrigin - yLevel[freqBand], 28, yLevel[freqBand], ILI9488_GREEN);
      tft.drawRect(xOrigin + 12 + 28 * freqBand, yOrigin - yLevel[freqBand], 28, yLevel[freqBand], ILI9488_BLUE);
      tft.drawLine(xOrigin, yOrigin - 100, xOrigin + 224, yOrigin - 100, ILI9488_BLACK);
      tft.setTextSize(2);

      secondEncoderMovement = 0;
      freqEncoderMovement = 0;

      yLevelOld  =  yLevel[freqBand];
      ydBLevel[freqBand] = map(yLevel[freqBand], 0, 200, -12, 12);
    
      bandGain[freqBand] = pow(10, (ydBLevel[freqBand] / 20));
      if(ydBLevel[freqBand]<=-12){ 
        bandGain[freqBand]=0;
        }
      EqGainSetL();
Serial.print("freqBand= ");Serial.print(freqBand);Serial.print("  bandGain[freqBand]= ");Serial.println(bandGain[freqBand]);
      //  Serial.println(" ");
    }
  }
  ButtonOff(4);
}
