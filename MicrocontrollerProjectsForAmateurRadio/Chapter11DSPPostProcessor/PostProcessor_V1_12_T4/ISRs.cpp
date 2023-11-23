#ifndef BEENHERE
//#include <SPI.h>
#include "Post.h"
#endif
/*****
  Purpose: The ISR to detect the rotary encoder's direction of movement

  Parameter list:
    void

  Return value:
    void

  CAUTION: This encoder is used for multiple purposes, all sensing direction change
*****/
void DrawButtonswOff() {

  for (int j = 0; j < 8; j++) {
    M4.gain(0, 1);  //
    M4.gain(1, 0);
   // ButtonV[j].initButton(&tft, BUTTONMAIN_X, (40 * j) + BUTTONMAIN_Y, BUTTON_W, BUTTON_H, ILI9488_WHITE, ButtonColorsOff[j], ButtonColorsTextOff[j], ButtonNamesV[j], BUTTON_TEXTSIZE);
    ButtonV[j].drawButton();
    /*tft.fillRect(110, (40 * j) + 4, 120, 20, ILI9488_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9488_RED);
    tft.setCursor(110, (40 * j) + BUTTONMAIN_Y - 8);
    tft.print("      Off");*/
  }
  tft.drawRect(100,  0, 125, 311, ILI9488_RED);
  tft.drawRect(225,  40, 255, 272, ILI9488_BLUE);
  //M4.gain(1, 1);
}
/*****
  Purpose: The ISR to detect the rotary encoder's direction of movement

  Parameter list:
    void

  Return value:
    void

  CAUTION: This encoder is used for multiple purposes, all sensing direction change
*****/
int freqISR() {
  unsigned char result1 = rotaryFreq.process();

  //freqEncoderMovement = 0;

  if (result1 == DIR_CW) {
    freqEncoderMovement = 1;
    MyDelay(50);
  } else if (result1 == DIR_CCW) {
    freqEncoderMovement = -1;
    MyDelay(50);
  }
  //if (freqEncoderMovement != 0) {
  //  //Serial.print("freqEncoderMovement= ");Serial.println(freqEncoderMovement);
  //}
  return freqEncoderMovement;
}

/*****
  Purpose: The ISR to detect the rotary encoder's direction of movement

  Parameter list:
    void

  Return value:
    void

  CAUTION: This encoder is used for multiple purposes, all sensing direction change
*****/
int SecondEncoderISR() {
  unsigned char result2 = rotarySecond.process();

  //secondEncoderMovement = 0;

  if (result2 == DIR_CW) {
    secondEncoderMovement = 1;
    MyDelay(50);
  } else if (result2 == DIR_CCW) {
    secondEncoderMovement = -1;
    MyDelay(50);
  }
  return secondEncoderMovement;
}


/*****
  Purpose: LP Filter ISR

  Parameter list:
    void
  Return value;
    void
*****/
void LPFilterISR() {
  int j = 0;
  if (digitalRead(LPFILTERPIN) == LOW) {
    ButtonOn(0);
    //if (NotchFlag = 1) {

    //}
    M1.gain(0, 1);//LP
    M1.gain(1, 0);//
    M3.gain(0, 1);//
    M3.gain(1, 0);//
    M4.gain(2, 0);//
    ButtonOn(0);
    LPFlag = 1;
  }
  else {
    tft.fillRect(xOrigin + 1, yOrigin - 230, 240, 229, ILI9488_BLACK);
    ButtonOff(0);
    M1.gain(0, 0);//LP
    M1.gain(1, 1);//
    LPFlag = 0;
  }
}

/*****
  Purpose: Notch Filter ISR

  Parameter list:
    void
  Return value;
    void
*****/
void notchFilterISR() {
  int j = 1;
  if (digitalRead(NOTCHFILTERPIN) == LOW) {

    M2.gain(0, 0);//
    M2.gain(1, 1);//
    // M3.gain(1, 0);//
    //  M4.gain(2, 0);//
    ButtonOn(1);

    NotchFlag = 1;
  }
  else {
    ButtonOff(1);

    M2.gain(0, 1);//
    M2.gain(1, 0);//
    // M3.gain(1, 0);//
    // M4.gain(2, 0);//

    NotchFlag = 0;
  }
}

/*****
  Purpose:Auto Notch Filter ISR

  Parameter list:
    void
  Return value;
    void
*****/
void AutoNotchFilterISR() {
  int j = 1;
  if (digitalRead(AUTONOTCHFILTERPIN) == LOW) {
    ButtonOn(2);
    //CreateFFTAxis();
    //SetAutoNotch();
    M2.gain(0, 0);//
    M2.gain(1, 1);//
    // M3.gain(1, 0);//
    //  M4.gain(2, 0);//
    NotchFlag = 1;
  }
  else {
    ButtonOff(2);

    M2.gain(0, 1);//
    M2.gain(1, 0);//
    // M3.gain(1, 0);//
    // M4.gain(2, 0);//

    NotchFlag = 0;
  }
}

/*****
  Purpose: CW Filter ISR

  Parameter list:
    void
  Return value;
    void
*****/
void CWFilterISR() {
  int  j = 2;
  if (digitalRead(CWFILTERPIN) == LOW) {

    M3.gain(0, 0);//
    M3.gain(1, 1);//
    M3.gain(2, 0);
    M3.gain(3, 0);
    ButtonOn(3);

    CWFlag = 1;
  }
  else {
    M3.gain(0, 1);//
    M3.gain(1, 0);//
    ButtonOff(3);

    CWFlag = 0;
  }
}

/*****
  Purpose: EQ Filter ISR
  Parameter list:
    void
  Return value;
    void
*****/
void EQFilterISR() {
  int  j = 3;
  if (digitalRead(EQFILTERPIN) == LOW) {
    M4.gain(0, 0);  //
    M4.gain(1, 1);  //
    M4.gain(2, 0);
    ButtonOn(4);
    EQFlag = 1;
  }
  else {
    M4.gain(0, 1);  //
    M4.gain(1, 0);  //
    M4.gain(2, 0);
    ButtonOff(4);
    EQFlag = 0;
  }
}

/*****
  Purpose: ALC ISR

  Parameter list:
    void
  Return value;
    void
*****/
void ALCISR() {
  int j = 4;
  if (digitalRead(ALCPIN) == LOW) {
    j = 4;
    M5.gain(0, 1);//LP
    M5.gain(1, 0);//
    M5.gain(1, 0);//
    M5.gain(2, 0);//
    ButtonOn(5);

    ALCFlag = 1;
  }
  else {
    j = 4;
    M5.gain(0, 0);//ALC
    M5.gain(1, 1);//
    ButtonOff(5);

    ALCFlag = 0;
  }
}

/*****
  Purpose: FFT ISR

  Parameter list:
    void
  Return value;
    void
*****/
void fftISR() {

}
