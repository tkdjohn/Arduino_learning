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
void DoExitButton() {
   //Serial.println("DoExitButton");
 // if (myTouch.dataAvailable()) {
    //Serial.println("myTouch");
    GetTouchCoordinates2();
    if ((caltx > 400 - (BUTTON_W + 20) / 2) and (caltx < 400 + (BUTTON_W + 20) / 2) and (calty > 70 - BUTTON_H / 2) and (calty <  70 + BUTTON_H / 2)) {
      exitFlag = 1;
      //Serial.println(exitFlag);
     
    }
  //}
}


/*****
  Purpose: Select Function Buttons to Set parameters
  Parameter list:
    void
  Return value;
    void
*****/
void SelectButtonToSet() {
  int buttonPushFlag = 0;
  //Serial.print("setButtonOn  "); Serial.println(setButtonOn);
  //--------------------------------Read left buttons
  //while (myTouch.dataAvailable() and setButtonOn == 1) //Debounce routine

  //{
    buttonPushFlag = 1;
    GetTouchCoordinates2();
    //Serial.print("on/off  ");
    //Serial.print("caltx  "); Serial.print(caltx);
    //Serial.print("   calty  "); Serial.println(calty);
    //Serial.print("lastButtonindex4  "); Serial.println(lastButtonindex1);
    MyDelay(100);
  //}
  //Serial.print("buttonPushFlag=  ");Serial.println(buttonPushFlag);
  if (buttonPushFlag == 1) {
    for (int j = 0; j < 8; j++) {
      if ((caltx > BUTTONSET_X - BUTTON_W / 2) and (caltx < BUTTONSET_X + BUTTON_W / 2) and (calty > 40 * j + BUTTONSET_Y - BUTTON_H / 2) and (calty < 40 * j + BUTTONSET_Y + BUTTON_H / 2)) {
        //Serial.print("Button pressed="); Serial.println(j + 1);
       // ButtonV[j].initButton(&tft, BUTTONSET_X, 40 * j + BUTTONSET_Y, BUTTON_W, BUTTON_H, ILI9488_WHITE, ILI9488_GREEN, ILI9488_BLACK, ButtonNamesV[j], BUTTON_TEXTSIZE);
        ButtonV[j].drawButton();
        //Serial.print("lastButtonindex4= "); Serial.println(lastButtonindex4);
        //ButtonV[lastButtonindex4].initButton(&tft, BUTTONSET_X, (40 * lastButtonindex4) + BUTTONSET_Y, BUTTON_W, BUTTON_H, ILI9488_WHITE, ILI9488_BLUE, ILI9488_WHITE, ButtonNamesV[lastButtonindex1], BUTTON_TEXTSIZE);
        ButtonV[lastButtonindex4].drawButton();
        lastButtonindex4 = j;

        switch (lastButtonindex4) {
          case 0:  //LP Filter
            // Serial.print(lastButtonindex4); Serial.print(ButtonNamesV[lastButtonindex4]); Serial.println("  hcode here");
            CreateFFTAxis();
            SetLPFilters();
            break;
          case 1: // Notch Filter
            // Serial.print(lastButtonindex1); Serial.print(ButtonNamesV[lastButtonindex1]); Serial.println("  code here");
            CreateFFTAxis();
            SetNotchFilters() ;
            break;
          case 2: // CW Filter
            // Serial.print(lastButtonindex1); Serial.print(ButtonNamesV[lastButtonindex1]); Serial.println("  code here");
            CreateFFTAxis();
            SetCWFilters();;

            break;
          case 3: //EQ
            //Serial.print(lastButtonindex1); Serial.print(ButtonNamesV[lastButtonindex1]); Serial.println("  code here");

            CreateEQDisplayAxis();
            break;
          case 4: //ALC
            //Serial.print(lastButtonindex1); Serial.print(ButtonNamesV[lastButtonindex1]); Serial.println("  code here");
            ALCOnOff();
            break;
          case 5: //NR
            // Serial.print(lastButtonindex1); Serial.print(ButtonNamesV[lastButtonindex1]); Serial.println("  code here");

            break;

        }
      }
    }
  }
  buttonPushFlag = 0;
}

/*****
  Purpose: Read Function Screen Buttons
  Parameter list:
    void
  Return value;
    void
*****/
void ReadButtons() {
  //Serial.print("In ReadButtons  ");
  int buttonPushFlag = 0;
  unsigned char result;
  int chan1Flag = 0;
  int chan2Flag = 0;
  tft.setTextSize(2);
  tft.setTextColor(ILI9488_WHITE);

 // while (myTouch.dataAvailable())  //Debounce routine
 // {

    buttonPushFlag = 1;
    GetTouchCoordinates2();
    //Serial.print("on/off  ");
    //Serial.print("caltx  "); Serial.print(caltx);
    //Serial.print("   calty  "); Serial.println(calty);
    //Serial.print("lastButtonindex1  "); Serial.println(lastButtonindex1);
    MyDelay(100);
  //}
  //Serial.print("buttonPushFlag=  ");Serial.println(buttonPushFlag);
  if (buttonPushFlag == 1) {

    //--------------------------------Read left buttons

    for (int j = 0; j < 8; j++) {
      if ((caltx > BUTTONMAIN_X - BUTTON_W / 2) and (caltx < BUTTONMAIN_X + BUTTON_W / 2) and (calty > 40 * j + BUTTONMAIN_Y - BUTTON_H / 2) and (calty < 40 * j + BUTTONMAIN_Y + BUTTON_H / 2)) {
        //Serial.print("Button pressed="); Serial.println(j + 1);
        //ButtonV[j].initButton(&tft, BUTTONMAIN_X, 40 * j + BUTTONMAIN_Y, BUTTON_W, BUTTON_H, ILI9488_WHITE, ILI9488_GREEN, ILI9488_BLACK, ButtonNamesV[j], BUTTON_TEXTSIZE);
        ButtonV[j].drawButton();
        //Serial.println(lastButtonindex1);
      //  ButtonV[lastButtonindex1].initButton(&tft, BUTTONMAIN_X, (40 * lastButtonindex1) + BUTTONMAIN_Y, BUTTON_W, BUTTON_H, ILI9488_WHITE, ILI9488_BLUE, ILI9488_WHITE, ButtonNamesV[lastButtonindex1], BUTTON_TEXTSIZE);
        ButtonV[lastButtonindex1].drawButton();
        lastButtonindex1 = j;

        switch (lastButtonindex1) {
          case 0:  //LP Filter
            CreateFFTAxis();
            SetLPFilters();
            break;
          case 1: // Notch Filter
            // Serial.print(lastButtonindex1); Serial.print(ButtonNamesV[lastButtonindex1]); Serial.println("  code here");
            CreateFFTAxis();
            SetNotchFilters() ;
            break;
          case 2: // Auto Notch
            // Serial.print(lastButtonindex1); Serial.print(ButtonNamesV[lastButtonindex1]); Serial.println("  code here");

            CreateFFTAxis();
            SetAutoNotch();

            break;
          case 3: //CW Filter
            // Serial.print(lastButtonindex1); Serial.print(ButtonNamesV[lastButtonindex1]); Serial.println("  code here");
            CreateFFTAxis();
            SetCWFilters();
            break;
          case 4: //EQ
            CreateEQDisplayAxis();
            SetEQFilters();
            break;
          case 5: //ALC
            // Serial.print(lastButtonindex1); Serial.print(ButtonNamesV[lastButtonindex1]); Serial.println("  code here");
            SetALC();
            break;
          case 6: //NR
            //Serial.print(lastButtonindex1); Serial.print(ButtonNamesV[lastButtonindex1]); Serial.println("  code here");

            break;
          case 7:  //FFT
            //Serial.print(lastButtonindex1); Serial.print(ButtonNamesV[lastButtonindex1]); Serial.println("  code here");
            j = 7;
            ButtonOn(j);
            CreateFFTAxis();
            displayAudioSpectrum();
            break;
        }
      }
    }


  }
  buttonPushFlag = 0;
}   //void Read Buttons
