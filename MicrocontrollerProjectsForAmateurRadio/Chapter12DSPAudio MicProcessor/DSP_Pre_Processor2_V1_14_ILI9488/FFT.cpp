#ifndef BEENHERE
#include "Pre.h"
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

  float yAmplitude;
 
  long xScreenPos;
  //long yPosition;
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
    long ylogAmplitude;
    for ( int j = 0; j < 127; j++) {
      xScreenPos = map((long) j, 0L, 127L, (long) (xOrigin - 1 ), (long) (xOrigin + 240) ); // Map to screen coodinates
      xScreenPosOld = xScreenPos;
      tft.drawFastVLine(xScreenPosOld + 46, yOrigin - 180, 179, iLI9488_BLACK);
      tft.drawFastVLine(xScreenPosOld + 47, yOrigin - 180, 179, iLI9488_BLACK);
      ylogAmplitude=100000*log10(fft1024_1.read(j));
      //Serial.print("j=  ");Serial.println(j);
      //Serial.print("fft1024_1.read(j)=  ");Serial.println(fft1024_1.read(j));
      //Serial.print("ylogAmplitude=  ");Serial.println(ylogAmplitude);
      yAmplitude=map(ylogAmplitude,-44000,-430,-4.5,-44.5);
      yAmplitude=2*map(yAmplitude,-4.5,-44.5,-13,-125)/12+50;
      //yAmplitude=map(ylogAmplitude,13,125,-44000,-430);
      //Serial.print("yAmplitude=  ");Serial.println(yAmplitude+13);
    if(yAmplitude>=(198)) yAmplitude=198;
      tft.fillCircle(xScreenPos + 44, (yAmplitude+13), 2, iLI9488_YELLOW); //Plot data points
    }
    MyDelay(20);
  }//while(1)
  //int j=7;


}

/*****
  Purpose:  Draw the FFT  display axies and tick marks

  Paramter list:
    void

  Return value:  void
*****/
void CreateFFTAxis() {
  tft.drawRect(0,  34, 310, 205, iLI9488_RED);
  //tft.setFont(ili9488_t3_font_ArialBold);
  tft.setTextColor(iLI9488_WHITE);
  tft.setCursor(0, 0);
  
    tft.drawFastVLine(xOrigin + 41, yOrigin - 175, 179, iLI9488_YELLOW); //Draw Y Axis
    tft.drawLine(xOrigin + 41, yOrigin-1, xOrigin + 280, yOrigin-1, iLI9488_YELLOW); //Draw X axis

tft.drawLine(xOrigin + 33,47,xOrigin + 41,47,iLI9488_YELLOW);
tft.setCursor(xOrigin + 20,42);
tft.print("0");
tft.drawLine(xOrigin + 33,89,xOrigin + 41,89,iLI9488_YELLOW);
tft.setCursor(xOrigin + 12,84);
tft.print("-20");
tft.setCursor(xOrigin + 12,105);
tft.print("dB");
tft.drawLine(xOrigin + 33,131,xOrigin + 41,131,iLI9488_YELLOW);
tft.setCursor(xOrigin + 12,126);
tft.print("-40");
tft.drawLine(xOrigin + 33,173,xOrigin + 41,173,iLI9488_YELLOW);
tft.setCursor(xOrigin + 12,168);
tft.print("-60");
    //tft.setCursor(xOrigin + 124, yOrigin + 5);
    //tft.print("Freq Hz");
    //Draw Major  tick marks
    for (int iFreq = 0; iFreq <= 5; iFreq++) {
      float xFreq = 45 * iFreq;
      tft.drawLine(xFreq + xOrigin+41, yOrigin-1, xFreq + xOrigin+41, yOrigin + 8, iLI9488_WHITE); //Draw  tick lines
    }
    //Print frequency axis Lables

    tft.setCursor(xOrigin+41 , yOrigin + 11);
    tft.print("0");
    tft.setCursor(xOrigin + 80, yOrigin + 11);
    tft.print("1K");
    tft.setCursor(xOrigin + 125, yOrigin + 11);
    tft.print("2K");
    tft.setCursor(xOrigin + 170, yOrigin + 11);
    tft.print("3K");
    tft.setCursor(xOrigin + 210, yOrigin + 11);
    tft.print(" 4K");
    tft.setCursor(xOrigin + 255, yOrigin + 11);
    tft.print(" 5K");
    //tft.drawRect(225,  40, 255, 272, iLI9488_BLUE);
  

}
