
#ifndef BEENHERE
//#include <SPI.h>
#include "Post.h"
#endif

/*****
  Purpose: Display continuous Audio FFT spectrum
           until secondary encoder is pressed
  Parameter list:
    void
  Return value;
    void
*****/
void displayAudioSpectrum() {
  int result;
  int exitFFT = 0;
  int buttonPushFlag = 0;
  tft.fillRect(xOrigin + 1, yOrigin - 230, 209, 209, ILI9488_BLACK); // Clear data area
  long xScreenPos;
  long yPosition;
  long xScreenPosOld;
  while (digitalRead(FREQENCODERSWITCH) != LOW) {
 
  //while (exitFFT != 1) {
   // exitFFT = 0;
    // if (digitalRead(FREQENCODERSWITCH) != HIGH) {
     // exitFFT = 1;
     // }
  // if( myTouch.dataAvailable()){
   // GetTouchCoordinates2();

    //if ((caltx > 0) and (caltx < BUTTONSET_X + BUTTON_W / 2) and (calty > 0) and (calty < 320)) {
    //  exitFFT = 1;
   // }
  // }
    for ( int j = 0; j < 127; j++) {
      xScreenPos = map((long) j, 0L, 255L, (long) (xOrigin - 1 ), (long) (xOrigin + 480) ); // Map to screen coodinates
      xScreenPosOld = xScreenPos;
      tft.drawFastVLine(xScreenPosOld + 5, yOrigin - 229, 230, ILI9488_BLACK);
      tft.drawFastVLine(xScreenPosOld + 6, yOrigin - 229, 230, ILI9488_BLACK);
      tft.fillCircle(xScreenPos + 4, (yOrigin - 1000 * fft1024_1.read(j)), 2, ILI9488_YELLOW); //Plot data points
    }
MyDelay(20);
  }//while(1)
 //int j=7;
 ButtonOff(7);

}

/*****
  Purpose:  Draw the FFT  display axies and tick marks

  Paramter list:
    void

  Return value:  void
*****/
void CreateFFTAxis() {
  //tft.fillScreen(ILI9488_BLACK);
  tft.fillRect(xOrigin - 2, 41, 245, 233, ILI9488_BLACK); // Clear data area
  tft.setTextSize(2);
  tft.setFont();
  tft.setTextColor(ILI9488_WHITE);
  tft.setCursor(0, 0);

  tft.drawFastVLine(xOrigin, yOrigin - 230, 229, ILI9488_WHITE); //Draw Y Axis
  tft.drawLine(xOrigin, yOrigin, xOrigin + 240, yOrigin, ILI9488_WHITE); //Draw X axis

  //tft.setCursor(xOrigin + 124, yOrigin + 5);
  //tft.print("Freq Hz");
  //Draw Major  tick marks
  for (int iFreq = 0; iFreq <= 5; iFreq++) {
    float xFreq = 45 * iFreq;
    tft.drawLine(xFreq + xOrigin, yOrigin, xFreq + xOrigin, yOrigin + 10, ILI9488_WHITE); //Draw  tick lines
  }
  //Print frequency axis Lables

  tft.setCursor(xOrigin , yOrigin + 14);
  tft.print("0");
  tft.setCursor(xOrigin + 38, yOrigin + 14);
  tft.print("1K");
  tft.setCursor(xOrigin + 83, yOrigin + 14);
  tft.print("2K");
  tft.setCursor(xOrigin + 128, yOrigin + 14);
  tft.print("3K");
  tft.setCursor(xOrigin + 163, yOrigin + 14);
  tft.print(" 4K");
  tft.setCursor(xOrigin + 208, yOrigin + 14);
  tft.print(" 5K");
  tft.drawRect(225,  40, 255, 272, ILI9488_BLUE);
  

}
