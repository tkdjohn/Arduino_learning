#ifndef BEENHERE
#include "Pre.h"
#endif


/*****
  Purpose: Select Button
  Parameter list:
    void
  Return value;
   void
*****/
/*****
  Purpose:  Set Parameters for EQ Filters

  Paramter list:
    void

  Return value:  void
*****/
void SetEQFilters() {
  //tft.setFont(ili9488_t3_font_ArialBold);
  int   freqBandOld = 0;
  int   yLevelOld = 0;
  int buttonNumber3 = 0;
  boolean istouched = false;
  eqFlag = 1;
  while (digitalRead(FREQENCODERSWITCH) != LOW) {
    freqISR();
    SecondEncoderISR();

    freqBand = freqBand +  freqEncoderMovement;
    if (freqBand > 7) {
      freqBand = 7;
    } if (freqBand < 0) {
      freqBand = 0;
    }
    freqEncoderMovement = 0;

    yLevel[freqBand] = yLevel[freqBand] +  8 * secondEncoderMovement;
    if (yLevel[freqBand] > 200) {
      yLevel[freqBand] = 200;
    } if (yLevel[freqBand] < 0) {
      yLevel[freqBand] = 1;
    }
    secondEncoderMovement = 0;

    if (freqBand != freqBandOld ) {
      tft.fillRect(xOrigin + 41 + 32 * (freqBandOld), yOrigin - yLevel[freqBandOld], 30, yLevel[freqBandOld], iLI9488_CYAN);
      tft.drawRect(xOrigin + 41 + 32 * (freqBandOld), yOrigin - yLevel[freqBandOld], 30, yLevel[freqBandOld], iLI9488_BLUE);
      tft.fillRect(xOrigin + 41 + 32 * freqBand, yOrigin - yLevel[freqBand], 30, yLevel[freqBand], iLI9488_GREEN);
      tft.drawRect(xOrigin + 41 + 32 * freqBand, yOrigin - yLevel[freqBand], 30, yLevel[freqBand], iLI9488_BLUE);

      freqBandOld = freqBand;
    }


    if (yLevel[freqBand] != yLevelOld) {
      tft.fillRect(xOrigin + 41 + 32 * (freqBand ), yOrigin - yLevel[freqBand], 30, yLevel[freqBand], iLI9488_CYAN);
      tft.drawRect(xOrigin + 41 + 32 * (freqBand ), yOrigin - yLevel[freqBand], 30, yLevel[freqBand], iLI9488_BLUE);
      tft.fillRect(xOrigin + 41 + 32 * freqBand, yOrigin - yLevelOld, 30, yLevelOld, iLI9488_BLACK);
      tft.drawRect(xOrigin + 41 + 32 * freqBand, yOrigin - yLevelOld, 30, yLevelOld, iLI9488_BLACK);
      tft.fillRect(xOrigin + 41 + 32 * freqBand, yOrigin - yLevel[freqBand], 30, yLevel[freqBand], iLI9488_GREEN);
      tft.drawRect(xOrigin + 41 + 32 * freqBand, yOrigin - yLevel[freqBand], 30, yLevel[freqBand], iLI9488_BLUE);
      tft.drawLine(xOrigin + 41, yOrigin - 95, xOrigin + 295, yOrigin - 95, iLI9488_BLUE);
      tft.setTextSize(2);

      //secondEncoderMovement = 0;
      freqEncoderMovement = 0;

      yLevelOld  =  yLevel[freqBand];
      ydBLevel[freqBand] = map(yLevel[freqBand], 0, 200, -12, 12);

      bandGain[freqBand] = pow(10, (ydBLevel[freqBand] / 20));
      if (ydBLevel[freqBand] <= -12) {
        bandGain[freqBand] = 0;
      }
      EqGainSetL();

    }
    //on/off button read

    istouched = ts.touched();
    if (istouched) {
      long x1 = 0;
      long y1 = 0;
      for (int k = 1; k < 11; k++) {
        TS_Point p = ts.getPoint();
        delay(5);
        x1 = x1 + p.x;
        y1 = y1 + p.y;
      }
      xx = map(x1, 4000, 39000, 0, 320);
      yy = map(y1, 2800, 38000, 0, 240);
      if ((xx > BOXSPACEX * 3) and xx < (BOXSPACEX * 3 + BOXSIZEX - 6) and yy < BOXSIZEY + 1 ) {
        buttonNumber3 = 1;
        //Serial.print("buttonNumber3= "); Serial.println(buttonNumber3);
      }
      if ((xx > BOXSPACEX * 4) and xx < (BOXSPACEX * 4 + BOXSIZEX - 6) and yy < BOXSIZEY + 1) {
        buttonNumber3 = 2;
      }

      switch (buttonNumber3) {

        case 1: //on
          tft.fillRect(254, 1, 63, 15, iLI9488_BLACK);
          tft.setCursor(255, 4);
          tft.print("EQ");
          M4.gain(0, 1);  //
          M4.gain(1, 0);
          M4.gain(2, 0);
          M4.gain(3, 0);

          eqFlag = 0;
          break;
        case 2: //Off
          tft.fillRect(254, 1, 63, 15, iLI9488_BLACK);
          //tft.setCursor(255, 4);
          //tft.print("EQ Off");
          M4.gain(0, 0);  //
          M4.gain(1, 1);
          M4.gain(2, 0);
          M4.gain(3, 0);
          eqFlag = 0;
          break;
      }
    }
  }
  eqFlag = 0;
  MyDelay(100);
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
  EQ_Mix2.gain(2, bandGain[6]);     //  2000
  EQ_Mix2.gain(3, -(bandGain[7]));   //  3300


  EQ_Mix3.gain(0, 1);  // Combine Mixers 5 & 6
  EQ_Mix3.gain(1, 1);
  EQ_Mix3.gain(2, 0);

  CompMix.gain(0, 1);  //
  CompMix.gain(1, 0);
  CompMix.gain(2, 0);
  CompMix.gain(3, 0);

}

/*****
  Purpose:  Function to set Filter Parameters
  Return value:  void

  Note: Gain Values in dB +/- max of about 20dB either way  8-14-18
*****/
void SetupFilters() {

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
