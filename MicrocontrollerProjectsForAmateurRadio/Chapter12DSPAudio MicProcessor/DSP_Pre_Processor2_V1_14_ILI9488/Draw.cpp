#ifndef BEENHERE
#include "Pre.h"
#endif



/*****
  Purpose: Sign-on screen

  Paramter list:
    void

  Return value:
    void
*****/
void Splash()
{
  int row, col;
  tft.fillScreen(iLI9488_BLACK);

  row = 240 / 5;
  col = 320 / 4;
  //tft.setFont(&FreeSerif18pt7b);
  tft.setTextSize(2);         // 18 characters per line with this size
  tft.setTextColor(iLI9488_MAGENTA, iLI9488_BLACK);
  tft.setCursor(80, 40);
  tft.print(" Programmable");
  tft.setCursor(40, 70);
  tft.print(" Audio Pre-Processor");
  //tft.setFont(&FreeSerif12pt7b);
  tft.setTextColor(iLI9488_WHITE, iLI9488_BLACK);
  tft.setTextSize(1);
  col = 320 / 2;
  tft.setCursor(col, 100);
  tft.print("by");

  tft.setTextSize(2);       // 26 characters per line
  tft.setCursor(0, 0);
  tft.setTextColor(iLI9488_GREEN, iLI9488_BLACK);
  tft.setCursor(70,  135);
  tft.print("Al Peter, AC8GY");
  tft.setCursor(50, 165);
  tft.print("Jack Purdum, W8TEE");

  //Serial.println("Splash");
  MyDelay(3000UL);

}
/*****
  Purpose: Compressor Screen Button
  Parameter list:
    void
  Return value;
   void
*****/
void DrawCompressorButtons() {
  //Serial.print("DrawCompressorButtons= ");
  tft.setTextColor(iLI9488_WHITE);

  tft.setCursor(150, 51);
  tft.print(thresh1);
  tft.setCursor(150, 51 + (BOXSPACEY)  );
  tft.print(thresh2);
  tft.setCursor(150, 51 + (BOXSPACEY) * 2 );
  tft.print(micGainSet);
  tft.setTextColor(iLI9488_BLACK);
  //tft.setFont(ili9488_t3_font_ArialBold);
  int i = 0;
  for (i = 0; i < 4; i++ ) {               //Draw  buttons
    tft.fillRoundRect(compButtons[i].tx + 1, compButtons[i].ty + 12, compButtons[i].ww + 20 , compButtons[i].hh, 5, iLI9488_GREEN);
    tft.drawRoundRect(compButtons[i].tx, compButtons[i].ty + 11, compButtons[i].ww + 20, compButtons[i].hh, 5, iLI9488_WHITE);

    tft.setCursor(16, 51 + BOXSPACEY * i );
    tft.print(CompButtonNames[i]);

  }
  //Draw Set Button
  tft.fillRoundRect(compButtons[4].tx + 1, compButtons[4].ty + 12, compButtons[4].ww + 20 , compButtons[4].hh, 5, iLI9488_MAROON);
  tft.drawRoundRect(compButtons[4].tx, compButtons[4].ty + 11, compButtons[4].ww + 20, compButtons[4].hh, 5, iLI9488_WHITE);
  tft.setTextColor(iLI9488_WHITE);
  tft.setCursor(16, 51 + BOXSPACEY * 4 );
  tft.print(CompButtonNames[4]);

  tft.drawRect(0,  34, 310, 205, iLI9488_RED);
  SetCompressorPrameters();
}

/*****
  Purpose: Select Button
  Parameter list:
    void
  Return value;
   void
*****/
void ButtonDraw() {
  int ii = 0;
  //tft.drawRoundRect(buttons[0].tx, buttons[0].ty, buttons[0].ww, buttons[0].hh, 5, iLI9488_WHITE);
  //tft.drawRoundRect(buttons[0].tx + 1, buttons[0].ty + 1, buttons[0].ww - 2, buttons[0].hh - 2, 5, iLI9488_WHITE);

  for ( ii = 0; ii < 3; ii++ ) {               //Draw first 3 buttons
    tft.fillRoundRect(buttons[ii].tx + 1, buttons[ii].ty + 1, buttons[ii].ww - 2, buttons[ii].hh - 2, 5, iLI9488_BLUE);
    tft.drawRoundRect(buttons[ii].tx, buttons[ii].ty, buttons[ii].ww, buttons[ii].hh, 5, iLI9488_WHITE);
    tft.setCursor(buttons[ii].tx, buttons[ii].ty + 10);
    tft.setTextColor(iLI9488_WHITE);
    //tft.setFont(ili9488_t3_font_ArialBold);

    tft.print(ButtonNames[ii]);

    //ii++;
  }




  for ( ii = 0; ii < 2; ii++ ) {           //Draw on/off buttons

    tft.fillRoundRect(onOffButtons[ii].tx + 1, onOffButtons[ii].ty + 1, onOffButtons[ii].ww - 2, onOffButtons[ii].hh - 2, 5, iLI9488_MAROON);
    tft.drawRoundRect(onOffButtons[ii].tx, onOffButtons[ii].ty, onOffButtons[ii].ww, onOffButtons[ii].hh, 5, iLI9488_WHITE);
    tft.setCursor(onOffButtons[ii].tx + 6, onOffButtons[ii].ty + 10);
    
    //tft.setFont(ili9488_t3_font_ArialBold);
    //tft.setTextSize(1);
    tft.print(onOffButtonsNames[ii]);


  }
}


/*****
  Purpose:  Draw the EQ  display axies and tick marks

  Paramter list:
    void

  Return value:  void
*****/
void DrawEQDisplay() {
  //int position;
  tft.fillRect(xOrigin, BOXSIZEY + 2, 320, 240 - BOXSIZEY + 2, iLI9488_BLACK);
  tft.setFont(Arial_9);
  tft.drawRect(0,  35, 290, 200, iLI9488_BLACK); // Clear data area


  tft.drawFastVLine(xOrigin + 40, yOrigin - 180, 180, iLI9488_YELLOW); //Draw Y Axis
  tft.drawLine(xOrigin + 40, yOrigin, xOrigin + 295, yOrigin, iLI9488_YELLOW); //Draw X axis


  for (int iFreq = 0; iFreq < 8; iFreq++) {

    tft.fillRect(xOrigin + 41 + 32 * iFreq, yOrigin - yLevel[iFreq], 30, yLevel[iFreq], iLI9488_CYAN);
    tft.drawRect(xOrigin + 41 + 32 * iFreq, yOrigin - yLevel[iFreq], 30, yLevel[iFreq], iLI9488_BLUE);

    tft.setCursor(xOrigin + 43 + 32 * iFreq, yOrigin + 6);

    tft.print(EQTextFreq[iFreq]);
  }

  tft.setCursor(xOrigin + 5, yOrigin - 10);
  tft.setTextColor(iLI9488_WHITE);
  tft.print(" -12");
  tft.setCursor(xOrigin + 5, yOrigin - 100);
  tft.setTextColor(iLI9488_WHITE);
  tft.print("  0");
  tft.setCursor(xOrigin + 5, yOrigin - 177);
  tft.setTextColor(iLI9488_WHITE);
  tft.print(" +12");
  tft.drawFastHLine(xOrigin + 32, yOrigin, 8, iLI9488_YELLOW); //Tick Marks
  tft.drawFastHLine(xOrigin + 32, yOrigin - 95, 8, iLI9488_YELLOW);
  tft.drawFastHLine(xOrigin + 32, yOrigin - 180, 8, iLI9488_YELLOW);

  tft.drawRect(0,  34, 310, 205, iLI9488_RED);

}
