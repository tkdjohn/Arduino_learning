#ifndef BEENHERE
//#include <SPI.h>
#include "Post.h"
#endif

/*****
  Purpose: Exit Button
  Parameter list:
    void
  Return value;
    void
*****/
void DrawExitButton() {
 // Exit.initButton(&tft, 400, 70, BUTTON_W + 20, BUTTON_H, ILI9488_WHITE, ILI9488_CYAN, ILI9488_BLACK, "Exit", BUTTON_TEXTSIZE);
  Exit.drawButton();
}

/*****
  Purpose: Turn on individual button
  Parameter list:
    void
  Return value;
    void
*****/
int ButtonOn(int j) {
  //ButtonV[j].initButton(&tft, BUTTONMAIN_X, (40 * j) + BUTTONMAIN_Y, BUTTON_W, BUTTON_H, ILI9488_WHITE, ButtonColorsOn[j], ButtonColorsTextOn, ButtonNamesV[j], BUTTON_TEXTSIZE);
  ButtonV[j].drawButton();
  /*tft.fillRect(110, (40 * j) + 4, 110, 20, ILI9488_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ILI9488_RED);
  tft.setCursor(110, (40 * j) + BUTTONMAIN_Y - 8);
  tft.print("      On");*/
}
/*****
  Purpose: Turn off individual button
  Parameter list:
    void
  Return value;
    void
*****/
int ButtonOff(int j) {
  tft.fillRect(xOrigin - 8, yOrigin - 230, 251, 260, ILI9488_BLACK); // Clear Graph area
  //ButtonV[j].initButton(&tft, BUTTONMAIN_X, (40 * j) + BUTTONMAIN_Y, BUTTON_W, BUTTON_H, ILI9488_WHITE, ButtonColorsOff[j], ButtonColorsTextOff[j], ButtonNamesV[j], BUTTON_TEXTSIZE);
  ButtonV[j].drawButton();
  /*tft.fillRect(110, (40 * j) + 4, 110, 20, ILI9488_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ILI9488_RED);
  tft.setCursor(110, (40 * j) + BUTTONMAIN_Y - 8);
  tft.print("      Off");*/
}
/*****
  Purpose: Draw Top Logo
  Parameter list:
    void
  Return value;
    void
*****/
void DrawLogo()
{
  tft.setTextSize(2);
  tft.setFont();
  tft.setTextColor(ILI9488_YELLOW);
  tft.setCursor(260, 0);
  tft.print("DSP Post Processor");
  tft.setTextColor(ILI9488_CYAN);
  tft.setCursor(300, 20);
  tft.print("AC8GY W8TEE");

}
/*****
  Purpose: Draw set Buttons
  Parameter list:
    void
  Return value;
    void
*****/
void DrawSetButtons()
{

  tft.fillRect(xOrigin - 2, 38, 280, 241, ILI9488_BLACK);
  for (int j = 0; j < 8; j++) {
  //  ButtonSet[j].initButton(&tft, BUTTONSET_X, BUTTONSET_Y + j * 40, BUTTON_W, BUTTON_H, ILI9488_WHITE, ButtonColorsOff[j], ButtonColorsTextOff[j], ButtonNamesV[j], BUTTON_TEXTSIZE);
    ButtonSet[j].drawButton();
  }

}
/*****
  Purpose: Draw Main Screen Buttons
  Parameter list:
    void
  Return value;
    void
*****/
void DrawLeftButtons()
{
  tft.fillRect(0, 0, 480, 319, ILI9488_BLACK);

  for (int j = 0; j < 8; j++) {
   // ButtonV[j].initButton(&tft, BUTTONMAIN_X, BUTTONMAIN_Y + j * 40, BUTTON_W, BUTTON_H, ILI9488_WHITE, ButtonColorsOff[j], ButtonColorsTextOff[j], ButtonNamesV[j], BUTTON_TEXTSIZE);
    ButtonV[j].drawButton();
  }

}

/*****
  Purpose: Draw Main Menu Buttons
  Parameter list:
    void
  Return value;
    void
*****/
void DrawTopButtons() {

  for (int j = 0; j < 2; j++) {
    //ButtonH[j].initButton(&tft, 250 + j * BUTTON_W2 + BUTTON_SPACING_X + j * 4, 15, BUTTON_W2, BUTTON_H, ILI9488_WHITE, ILI9488_NAVY, ILI9488_WHITE, (char *)ButtonNamesH[j], BUTTON_TEXTSIZE);
    ButtonH[j].drawButton();
  }


}
/*****
  Purpose:  Draw the EQ  display axies and tick marks

  Paramter list:
    void

  Return value:  void
*****/
void CreateEQDisplayAxis() {
  int position;

  tft.fillRect(xOrigin - 2, 41, 245, 265, ILI9488_BLACK); // Clear data area
 // tft.setTextSize(2);
 // tft.setFont();
 // tft.setTextColor(ILI9488_WHITE);
 // tft.setCursor(0, 0);

  tft.drawFastVLine(xOrigin + 11, yOrigin - 230, 229, ILI9488_WHITE); //Draw Y Axis
  tft.drawLine(xOrigin + 11, yOrigin, xOrigin + 240, yOrigin, ILI9488_WHITE); //Draw X axis


  for (int iFreq = 0; iFreq < 8; iFreq++) {

    tft.fillRect(xOrigin + 12 + 28 * iFreq, yOrigin - yLevel[iFreq], 28, yLevel[iFreq], ILI9488_CYAN);
    tft.drawRect(xOrigin + 12 + 28 * iFreq, yOrigin - yLevel[iFreq], 28, yLevel[iFreq], ILI9488_BLUE);

    tft.setCursor(xOrigin + 17 + 28 * iFreq, yOrigin + 7);
    tft.setTextSize(1);
    tft.print(eqFreq[iFreq]);
  }
  tft.drawLine(xOrigin, yOrigin - 100, xOrigin + 224, yOrigin - 100, ILI9488_BLACK);
  tft.setCursor(xOrigin - 8, yOrigin - 10);
  tft.setTextColor(ILI9488_WHITE);
  tft.print("-12");
  tft.setCursor(xOrigin - 8, yOrigin - 105);
  tft.setTextColor(ILI9488_WHITE);
  tft.print(" 0");
  tft.setCursor(xOrigin - 8, yOrigin - 205);
  tft.setTextColor(ILI9488_WHITE);
  tft.print("+12");


  tft.drawRect(225,  40, 255, 272, ILI9488_BLUE);

}
