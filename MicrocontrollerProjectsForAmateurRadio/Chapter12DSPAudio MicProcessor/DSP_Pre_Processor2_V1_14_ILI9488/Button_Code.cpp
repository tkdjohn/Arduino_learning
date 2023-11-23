#ifndef BEENHERE
#include "Pre.h"
#endif



void ReadButtons() {
  //int buttonPushFlag = 0;



  //if (yy < BOXSIZEY + 1 ) {
    for (int j = 0; j < 3; j++) {
      if ((xx > BOXSPACEX * j) and xx < (BOXSIZEX + BOXSPACEX * j) and yy < BOXSIZEY + 1 ) {
        buttonNumber = j;
      }
    }
  //}
  //Serial.print("buttonNumber= "); Serial.println(buttonNumber);
  switch (buttonNumber) {
    case 0:  //EQ
      RefreshMenuButtons();
      eqFlag=1;
      compFlag=0;
      DrawEQDisplay();
      SetEQFilters();
      eqFlag=0;
      RefreshMenuButtons();
      tft.fillRect(xOrigin, BOXSIZEY + 1, 320, 240 - BOXSIZEY , iLI9488_BLACK);
      break;
    case 1: // Compressor
eqFlag=0;
      compFlag=1;
      RefreshMenuButtons();
      DrawCompressorButtons();
      RefreshMenuButtons();
      tft.fillRect(xOrigin, BOXSIZEY + 1, 320, 240 - BOXSIZEY, iLI9488_BLACK);
      break;
    case 2: // FFT

      RefreshMenuButtons();
      CreateFFTAxis();
      displayAudioSpectrum();
      tft.fillRect(xOrigin, BOXSIZEY + 1, 320, 240 - BOXSIZEY, iLI9488_BLACK);
      //buttonNumber = 4;
      break;

  }

}//void Read Buttons

/*****
  Purpose: Refresh Buttons
  Parameter list:
    void
  Return value;
  void
*****/
void RefreshMenuButtons() {
  tft.setTextColor(iLI9488_WHITE);
  tft.fillRoundRect(buttons[oldButtonNumber].tx + 1, buttons[oldButtonNumber].ty + 1, buttons[oldButtonNumber].ww - 2, buttons[oldButtonNumber].hh - 2, 5, iLI9488_BLUE);
  tft.setCursor(buttons[oldButtonNumber].tx + 6, buttons[oldButtonNumber].ty + 10);
  tft.print(ButtonNames[oldButtonNumber]);
  //tft.fillRoundRect(buttons[buttonNumber].tx + 1, buttons[buttonNumber].ty + 1, buttons[buttonNumber].ww - 2, buttons[buttonNumber].hh - 2, 5, iLI9488_MAROON);
 // tft.setCursor(buttons[buttonNumber].tx + 6, buttons[buttonNumber].ty + 10);
  //tft.print(ButtonNames[buttonNumber]);
  oldButtonNumber = buttonNumber;
  pageFlag=0;
}



/*****
  Purpose: Set EQ Parameters
  Parameter list:
   void
  Return value;
   void
*****/
void SetEQ() {
  DrawEQDisplay();
}
