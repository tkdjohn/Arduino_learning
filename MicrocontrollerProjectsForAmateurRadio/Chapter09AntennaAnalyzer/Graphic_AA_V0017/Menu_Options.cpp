#ifndef BEENHERE
#include "AT.h"
#endif
#include <Arduino.h>

/*****
  Purpose: To show the whole spectrum
  Parameter list:
  void
  Return value:
  void
*****/
void PlotFullRealTimeSWR() {
  long freqIncrementFull;
  long sweepFrequency;
  long xPosition1;
  long xPosition2;
  int yTick1, xTick1, yDotSWRPosition1, xDotIncrement1;
  int tickCount1;
  int i, yIncrement1, xIncrement1;
  int fullYaxisStart = YAXISSTART - 10;
  int fullXaxisEnd =  XAXISEND + 30;
  int lineLength = YAXISEND - fullYaxisStart;
  int yDotSWRPosition;
  int SWRPosition[320] ;
  int xPosition[320] ;
  int SWROld[320] ;
  int SWROld2[320] ;
  double sweepSWRValue;
  int initFlag = 0;
  double maxSWR = 0.;
  double minSWR = 5.;
  int minXPosition;
  int minYPosition;
  int minYPositionOld;
  int minXPositionOld;
  long minFreq;
  int iPosition;
  int    cursorPosition = XAXISSTART;
  int varDelay = 0;
  endFlag = 0;
  SWRPosition[0] = fullYaxisStart;
  xPosition[0] = XAXISSTART;
  SWROld[0] = fullYaxisStart;
  SWROld2[0] = fullYaxisStart;
  yIncrement1 = (YAXISEND - fullYaxisStart) / 4;                     // Spacing for graph tick marks
  yTick1 = fullYaxisStart;                                       // on Y axis
  xDotIncrement1 = 20;
  tickCount1 = 4;
  long freqEndFull = 30000000;
  long freqStartFull = 1800000;
  int dotGrid1;
  tft.fillRect(0, 0, 480, 320, ILI9488_BLACK);   //Erase Screen below Main Menu
  tft.setTextColor(ILI9488_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(20, 0);
  tft.print("All");
  tft.setTextColor(ILI9488_YELLOW);
  tft.setTextSize(1);
  tft.setTextColor(ILI9488_YELLOW, ILI9488_BLACK);              // Lable X axis
  tft.setCursor(XAXISEND - 20, YAXISEND - 20);
  tft.print("Mhz");
  yIncrement1 = (YAXISEND - fullYaxisStart) / 4;                     // Spacing for graph tick marks
  yTick1 = fullYaxisStart + 5;                                       // on Y axis
  xDotIncrement1 = 5;
  tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
  tft.setCursor(0, 125);
  tft.setTextSize(1);
  tft.setFont(&FreeSerif9pt7b);
  tft.print("SWR");
  tft.setFont();
  tft.setTextSize(2);
  dotGrid1 = (YAXISEND - fullYaxisStart) / 4;
  for (int i = fullYaxisStart; i < YAXISEND + 25; i += yIncrement1, yTick1 += yIncrement1) {
    tft.setCursor(3, yTick1 - 10);
    tft.print((tickCount1--) + 1);
    tft.print(".0");
  }
  tft.drawLine(XAXISSTART, fullYaxisStart, XAXISSTART, YAXISEND, ILI9488_CYAN); // Y axis
  tft.drawLine(XAXISSTART, YAXISEND,   fullXaxisEnd,   YAXISEND, ILI9488_CYAN); // X axis
  tft.drawLine(XAXISSTART, fullYaxisStart,   fullXaxisEnd,   fullYaxisStart, ILI9488_CYAN); // Top Line

  tft.setTextSize(2);
  tft.setTextColor(ILI9488_YELLOW, ILI9488_BLACK);
  xPosition1 = map(1800000 , freqStartFull , freqEndFull, XAXISSTART, fullXaxisEnd);
  tft.setCursor(xPosition1 - 35, YAXISEND + 12);
  tft.print("1.8");

  xPosition1 = map(4000000 , freqStartFull , freqEndFull, XAXISSTART, fullXaxisEnd);
  tft.setCursor(xPosition1 - 15, YAXISEND + 12);
  tft.print("3.5");

  xPosition1 = map(7000000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
  tft.setCursor(xPosition1 - 2 , YAXISEND + 12);
  tft.print("7");

  xPosition1 = map(10100000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
  tft.setCursor(xPosition1 - 9, YAXISEND + 12);
  tft.print("10");

  xPosition1 = map(14350000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
  tft.setCursor(xPosition1 - 12, YAXISEND + 12);
  tft.print("14");

  xPosition1 = map(18168000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
  tft.setCursor(xPosition1 - 10, YAXISEND + 12);
  tft.print("18");

  xPosition1 = map(21450000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
  tft.setCursor(xPosition1 - 11, YAXISEND + 12);
  tft.print("21");

  xPosition1 = map(24990000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
  tft.setCursor(xPosition1 - 10, YAXISEND + 12);
  tft.print("24");

  xPosition1 = map(29700000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
  tft.setCursor(xPosition1 - 20, YAXISEND + 12);
  tft.print("28");

  initFlag = 1;
  int iCount = 0;

for (int k = 0; k < 3; k++) {  // Initialize first several elements
      SWRPosition[k] = fullYaxisStart ;
      xPosition[k] = XAXISSTART;
      SWROld[k] = fullYaxisStart ;
      SWROld2[k] = fullYaxisStart;
    }
  
  while (digitalRead(MENUENCODERSWITCH) != LOW)
  {
    DisplaySupplyVoltage();
    tft.setTextColor(ILI9488_YELLOW, ILI9488_BLACK);
    xPosition1 = map(1800000 , freqStartFull , freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition1, fullYaxisStart, lineLength, ILI9488_DARKGREY);
    xPosition2 = map(2000000 , freqStartFull , freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition2, fullYaxisStart, lineLength, ILI9488_DARKGREY);

    xPosition1 = map(4000000 , freqStartFull , freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition1, fullYaxisStart, lineLength, ILI9488_DARKGREY);
    xPosition2 = map(3500000 , freqStartFull , freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition2, fullYaxisStart, lineLength, ILI9488_DARKGREY);

    xPosition1 = map(7000000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition1, fullYaxisStart, lineLength, ILI9488_DARKGREY);
    xPosition2 = map(7300000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition2, fullYaxisStart, lineLength, ILI9488_DARKGREY);

    xPosition1 = map(10100000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition1, fullYaxisStart, lineLength, ILI9488_DARKGREY);

    xPosition1 = map(14350000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition1, fullYaxisStart, lineLength, ILI9488_DARKGREY);
    xPosition2 = map(14000000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition2, fullYaxisStart, lineLength, ILI9488_DARKGREY);

    xPosition1 = map(18168000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition1, fullYaxisStart, lineLength, ILI9488_DARKGREY);
    xPosition2 = map(18068000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition2, fullYaxisStart, lineLength, ILI9488_DARKGREY);

    xPosition1 = map(21450000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition1, fullYaxisStart, lineLength, ILI9488_DARKGREY);
    xPosition2 = map(21000000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition2, fullYaxisStart, lineLength, ILI9488_DARKGREY);

    xPosition1 = map(24990000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition1, fullYaxisStart, lineLength, ILI9488_DARKGREY);
    xPosition2 = map(24890000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition2, fullYaxisStart, lineLength, ILI9488_DARKGREY);

    xPosition1 = map(29700000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition1, fullYaxisStart, lineLength, ILI9488_DARKGREY);
    xPosition2 = map(28000000, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd);
    tft.drawFastVLine(xPosition2, fullYaxisStart, lineLength, ILI9488_DARKGREY);

    for (int k = 0; k <= (fullXaxisEnd - XAXISSTART); k += (fullXaxisEnd - XAXISSTART) / 100) { //  Draw horizontal dotted grid lines
      tft.drawPixel(k + XAXISSTART , yIncrement1 + fullYaxisStart, ILI9488_CYAN); // X and Y dotted axis at minor divisions
      tft.drawPixel(k + XAXISSTART , yIncrement1 * 2 + fullYaxisStart, ILI9488_CYAN); // X and Y dotted axis at minor divisions
      tft.drawPixel(k + XAXISSTART , yIncrement1 * 3 + fullYaxisStart, ILI9488_CYAN); // X and Y dotted axis at minor divisions
    }

    SendFrequency(freqStartFull);
    sweepSWRValue = ReadSWRValue();
    for (int i = 2; i <= 315; i++) {                   //Start @ i=2 to avoid initial condition issues
      if (digitalRead(MENUENCODERSWITCH) == LOW) {
        MakeMenuSelection();
        loop();
        break;
      }
      freqIncrementFull = (freqEndFull - freqStartFull) / 315;
      sweepFrequency = freqStartFull + i * freqIncrementFull;
      xPosition[i] = map(sweepFrequency, freqStartFull, freqEndFull, XAXISSTART, fullXaxisEnd) - 2;
      SendFrequency(sweepFrequency);
      sweepSWRValue = ReadSWRValue();
      if (sweepSWRValue < 4) {                        //Slow down plot around minimums
        int sweepSWRValue2 = sweepSWRValue * 10;
        varDelay = map(sweepSWRValue2 / 10, 4, 1, 2, 15);
        MyDelay(varDelay);
      }
      if (sweepSWRValue > 5.0) sweepSWRValue = 5.0; // keep values in bounds
      if (sweepSWRValue <= 1.0) sweepSWRValue = 1.0;
      if (sweepSWRValue == 0.0) sweepSWRValue = 5.0;
      if (initFlag != 1) {
        tft.drawLine(xPosition[i - 1], SWROld2[i], xPosition[i] , SWROld[i] , ILI9488_BLACK);  //Erase old line segment
      }
      yDotSWRPosition = map(sweepSWRValue * 100, 100, 500, YAXISEND - 1, fullYaxisStart - 1);
      if (yDotSWRPosition < fullYaxisStart)  yDotSWRPosition = fullYaxisStart + 1;
      if (yDotSWRPosition > YAXISEND)  yDotSWRPosition = YAXISEND - 1;
      SWRPosition[i] = yDotSWRPosition;

      if (SWRPosition[i - 1] > (YAXISEND - 1)) SWRPosition[i - 1] = YAXISEND - 1;  //Out of bounds conditions

      tft.drawLine(xPosition[i - 1], SWRPosition[i - 1], xPosition[i] , SWRPosition[i] , ILI9488_YELLOW);   //Draw new line segment

      SWROld[i] = SWRPosition[i];      //Save old positions
      SWROld2[i] = SWRPosition[i - 1];
      //----------------  Minimum SWR cursor - 1/4 of plot at a time

      if (i > cursorPosition - XAXISSTART and i < cursorPosition - XAXISSTART + ((fullXaxisEnd - XAXISSTART) / 4)) {
        if (sweepSWRValue < minSWR)
        {
          minSWR = sweepSWRValue;
          minXPosition = xPosition[i];
          minYPosition = SWRPosition[i];
          minFreq = freqStartFull + i * freqIncrementFull;
          iPosition = i;
        }
      }
      endFlag = 0;
      //-----------------
    }
    endFlag = 0;
    //=====================    Cursor line at bottomfor SWR minimums
    if (digitalRead(FREQUENCYENCODERSWITCH) == LOW) {     //Change cursor position
      tft.drawFastHLine(cursorPosition, YAXISEND + 2, (fullXaxisEnd - XAXISSTART) / 4 , ILI9488_BLACK);
      cursorPosition = cursorPosition + (fullXaxisEnd - XAXISSTART) / 4;

      minSWR = 5;
    }
    if (cursorPosition >= fullXaxisEnd)  cursorPosition = XAXISSTART;
    tft.drawFastHLine(cursorPosition, YAXISEND + 2, (fullXaxisEnd - XAXISSTART) / 4 , ILI9488_YELLOW); //Double lines below axis
    tft.drawFastHLine(cursorPosition, YAXISEND + 3, (fullXaxisEnd - XAXISSTART) / 4 , ILI9488_YELLOW);
    //========================

    tft.fillRect(150, 0, 300, 25, ILI9488_BLACK);
    tft.fillCircle(minXPositionOld, minYPositionOld, 2, ILI9488_BLACK);
    tft.setTextColor(ILI9488_WHITE);

    tft.setCursor(80, 0);
    tft.print("Min SWR ");
    tft.print(minSWR, 1);
    tft.print(" @ ");
    tft.print((float)minFreq/1000000 , 3);
    tft.print(" MHz");

    minXPositionOld = minXPosition;
    tft.fillCircle(minXPosition, minYPosition, 2, ILI9488_CYAN);
    minXPositionOld = minXPosition;
    minYPositionOld = minYPosition;
    initFlag = 0;
    minSWR = 5;
    iCount++;
  }

  SendFrequency(0);


  MakeMenuSelection();
}

/*****
  Purpose: To show the real time SWR plot for one band
  Parameter list:
  void
  Return value:
  void
*****/
void PlotRealTimeSWR(int whichBandOption)
{
  long freqIncrement2;
  long xPositionCurrent;
  int RyDotSWRPosition;
  int XyDotSWRPosition;
  double XRpixelsPerTenth;
  int totalPixels;
  int fullYaxisStart;
  long sweepFrequency2;
  int xPositionBand;
  double sweepSWRValue2;
  double freqStart2, freqEnd2;
  double SWRPosOld[NUMFREQPOINTSBAND];
  double RPosOld[NUMFREQPOINTSBAND];
  double XPosOld[NUMFREQPOINTSBAND];
  int yDotSWRPosition;
  double SWRValue;
  double cursorFrequency;

  endFlag = 0;
  char *bands[] = {" 160M ", " 80M ", " 40M ", " 30M ", " 20M ", " 17M ", " 15M ", " 12M ", " 10M ", "Exit"};
  ErasePage();
  GraphAxis(whichBandOption);

  switch (whichBandOption) {

    case 0:
      freqStart2 = 1800000;
      freqEnd2 = 2000000;
      break;
    case 1:
      freqStart2 = 3500000;
      freqEnd2 = 4000000;
      break;

    case 2:
      freqStart2 = 7000000;
      freqEnd2 = 7300000;
      break;
    case 3:
      freqStart2 = 10100000;
      freqEnd2 = 10150000;
      break;

    case 4:
      freqStart2 = 14000000;
      freqEnd2 = 14350000;

      break;
    case 5:
      freqStart2 = 18068000;
      freqEnd2 = 18168000;
      break;

    case 6:
      freqStart2 = 21000000;
      freqEnd2 = 21450000;
      break;

    case 7:
      freqStart2 = 24890000;
      freqEnd2 = 24990000;
      break;

    case 8:
      freqStart2 = 28000000;
      freqEnd2 = 29700000;
      break;
  }
  cursorFrequency = bandCenter[whichBandOption];
  xPositionCurrent  = map(freqStart2 + (freqEnd2 - freqStart2) / 2 , freqStart2, freqEnd2, XAXISSTART, XAXISEND);
  tft.drawFastVLine(xPositionCurrent,  YAXISSTART, YAXISEND - YAXISSTART, ILI9488_GREEN);
  tft.setTextColor(ILI9488_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(5, 0);
  tft.print(bands[whichBandOption]);
  tft.print(" Scan");

  while (digitalRead(MENUENCODERSWITCH) != LOW)
  {
    DisplaySupplyVoltage();
    tft.drawLine(XAXISSTART, YAXISEND,   XAXISEND,   YAXISEND, ILI9488_CYAN); // X axis
    tft.drawLine(XAXISSTART, YAXISSTART, XAXISSTART, YAXISEND, ILI9488_CYAN);    // Y axis
    freqIncrement2 = freqEnd2 - freqStart2;

    for (int i = 0; i < NUMFREQPOINTSBAND; i++) {
      if (digitalRead(MENUENCODERSWITCH) == LOW) {
        MakeMenuSelection();
        break;
      }

      sweepFrequency2 = freqStart2 + i * freqIncrement2 / NUMFREQPOINTSBAND;
      xPositionBand = map(sweepFrequency2 , freqStart2, freqEnd2 , XAXISSTART, XAXISEND);
      SendFrequency(sweepFrequency2);
      sweepSWRValue2 = ReadSWRValue();

      if (sweepSWRValue2 > 5) sweepSWRValue2 = 5.0;
      if (SWRPosOld[i] > YAXISSTART - 1)  tft.fillCircle(xPositionBand, SWRPosOld[i], 2, ILI9488_BLACK);
      if (RPosOld[i] > YAXISSTART - 1)    tft.fillCircle(xPositionBand, RPosOld[i], 1, ILI9488_BLACK);
      if (XPosOld[i] > YAXISSTART - 1)    tft.fillCircle(xPositionBand, XPosOld[i], 1, ILI9488_BLACK);
      yDotSWRPosition = map(100 * sweepSWRValue2, 100, 500, YAXISEND, YAXISSTART);
      tft.fillCircle(xPositionBand, yDotSWRPosition, 2, ILI9488_YELLOW);
      SWRPosOld[i] = yDotSWRPosition;
      if (XValue < 1) XValue = 1;
      if (RValue < 1) RValue = 1;
      if (XValue > 100) XValue = 100;
      if (RValue > 100) RValue = 100;
      RyDotSWRPosition = map(RValue, 0, 100, YAXISEND, YAXISSTART);
      XyDotSWRPosition = map(XValue, 0, 100, YAXISEND, YAXISSTART);
      RPosOld[i] = RyDotSWRPosition;
      XPosOld[i] = XyDotSWRPosition;
      tft.fillCircle(xPositionBand, RyDotSWRPosition, 1, ILI9488_LIGHTGREY);
      tft.fillCircle(xPositionBand, XyDotSWRPosition, 1, ILI9488_ORANGE);
      if (frequencyEncoderMovement != 0) {     //Change frequency value
        tft.drawFastVLine(xPositionCurrent, YAXISSTART, YAXISEND - YAXISSTART, ILI9488_BLACK);
        cursorFrequency += (long) (frequencyEncoderMovement * 10000);
        frequencyEncoderMovement = 0;
        xPositionCurrent  = map(cursorFrequency , freqStart2, freqEnd2, XAXISSTART, XAXISEND);
        tft.drawFastVLine(xPositionCurrent,  YAXISSTART, YAXISEND - YAXISSTART, ILI9488_GREEN);
      }
    }// for Loop

    int fiftyOhmsLine = map(50, 0, 100, YAXISEND, YAXISSTART);
    tft.drawLine(XAXISSTART, fiftyOhmsLine,   XAXISEND, fiftyOhmsLine, ILI9488_GREEN);
    tft.drawFastVLine(xPositionCurrent,  YAXISSTART, YAXISEND - YAXISSTART, ILI9488_GREEN);
    SendFrequency(cursorFrequency);
    delay(10);
    ReadSWRValue();
    ShowSubmenuData(VSWR, cursorFrequency);
    PlotGrid(whichBandOption);
  } //while loop
  SendFrequency(0);
  MakeMenuSelection();
  MyDelay(100);

}

/*****
  Purpose: To allow variable increments on frequency

  Argument list:
    int bandIndex       // which of the three bands was selected?

  Return value:
    void
*****/
void SingleFrequency(int bandIndex)
{
  int i, changeDigit, digitSpacing, halfScreen,  insetMargin;
  long defaultIncrement;
  int endFlag = 0;
  int plotFlag = 0;
  int insetPad         = 4;                        // Used to align digit indicator
  double SWRValue;
  digitSpacing     = 15;
  insetMargin      = 25;
  defaultIncrement = 1000L;
  halfScreen   = PIXELHEIGHT / 2 - 25;

  int freqYPos = 75;
  int freqIndicatorYPos = 25;
  int SWRYPos = 110;
  double tiny = .3;

  SendFrequency(currentFrequency);
  SWRValue = ReadSWRValue();
  double ZMagAve = ZMag;
  double RValueAve = RValue;
  double XValueAve = XValue;
  double SWRValueAve = SWRValue;
  if (bandIndex > 2) {                 // 40M??
    insetPad = DIGITSPACING4X + 4;
    // smaller number, so less spacing to a given digit
  }
  tft.fillScreen(ILI9488_BLACK);
  tft.setTextColor(ILI9488_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(5, 0);
  tft.print("Select Frequency");
  tft.drawFastHLine(0, 21, 480, ILI9488_RED);
  tft.setTextSize(1);
  tft.setFont(&FreeSerif9pt7b);
  tft.setTextColor(ILI9488_WHITE);                      // Messages
  //tft.setCursor(insetMargin, halfScreen + 155);
  //tft.print("Increment: Menu Encoder      Freq: Freq Encoder");
  tft.setCursor(insetMargin, halfScreen + 175);
  tft.print("Plot: Menu Encoder SW          Exit: Freq Encoder SW");
  //tft.setCursor(insetMargin, halfScreen + 175);
  //tft.print("      Exit: Menu Encoder SW");
  //-----------------
  tft.setFont();
  tft.setTextSize(3);
  tft.setTextColor(ILI9488_WHITE);
  //=======================
  tft.setCursor(insetMargin  + DIGITSPACING4X * 3, freqIndicatorYPos);   // Assume 1KHz increment
  tft.print((char) DIGITINDICATOR);
  tft.setTextSize(1);
  tft.setFont(&FreeMonoBold18pt7b);
  tft.setTextColor(ILI9488_GREEN);
  tft.setCursor(insetMargin, freqYPos);
  tft.print(currentFrequency);
  //==========================

  tft.setFont();
  tft.setTextSize(2);
  analogMeter();

  while (digitalRead(MENUENCODERSWITCH) != LOW)
  {
    //delay(10);
    if (digitalRead(FREQUENCYENCODERSWITCH) == LOW) {
      endFlag = 1;
      delay(100);
    }
    if (endFlag == 1) {
      delay(100);
      endFlag = 0;

      //SendFrequency(0);
      ShowMainDisplay();
      MakeMenuSelection();
      loop();
    }

    if (menuEncoderMovement) {          // Change increment
      tft.fillRect(0, freqIndicatorYPos, 220, 26, ILI9488_BLACK);
      if (menuEncoderMovement == 1) {
        incrementPad += DIGITSPACING4X;
        defaultIncrement /= 10;
        if (incrementPad > DIGITSPACING4X * 4) {             // Don't overshoot or...
          incrementPad -= DIGITSPACING4X;
          defaultIncrement /= 10;                   // ...back off one
        }
        else {
          //defaultIncrement /= 10;                           // Increment is powers of 10
          if (defaultIncrement < 1) {                       // Don't go too far right
            defaultIncrement = 1L;
          }
        }
      }
      else
      {
        if (menuEncoderMovement == -1) {
          incrementPad -= DIGITSPACING4X;
          defaultIncrement *= 10;
          if (incrementPad < -DIGITSPACING4X * 3) {              // Don't undershoot either
            incrementPad += DIGITSPACING4X;
            defaultIncrement *= 10;
          }
          if (defaultIncrement > 1000000L) {
            defaultIncrement = 1000000L;
          }
        }
      } //else

      menuEncoderMovement = 0;

      tft.setTextSize(3);
      tft.setTextColor(ILI9488_WHITE);

      //==========================
      tft.setCursor(insetMargin + insetPad + incrementPad + DIGITSPACING4X * 3 , freqIndicatorYPos);   // Assume 1KHz increment
      tft.print((char) DIGITINDICATOR);

      SWRValue = ReadSWRValue();
      //====================
      tft.setTextColor(ILI9488_GREEN);

#ifdef DEBUG
      Serial.print("In ChangeFreq: defaultIncrement = ");
      Serial.print(defaultIncrement);
      Serial.print("   incrementPad = ");
      Serial.println(incrementPad);
#endif
    }  //  if (menuEncoderMovement)

    if (frequencyEncoderMovement != 0) {     //Change digit value
      currentFrequency += (long) (frequencyEncoderMovement * defaultIncrement);
      SendFrequency(currentFrequency);
      SWRValue = ReadSWRValue();
      //=================
      tft.setTextSize(1);
      tft.setFont(&FreeMonoBold18pt7b);

      //=========================
      tft.fillRect(0, freqYPos - 25 , 200, 30, ILI9488_BLACK);
      tft.setCursor(insetMargin, freqYPos);
      tft.setTextColor(ILI9488_YELLOW, ILI9488_BLACK);
      tft.print(currentFrequency);
      //=========================
      tft.setTextSize(0);
      frequencyEncoderMovement = 0;
    }

    SWRValue = ReadSWRValue();
    delay(10);
    tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);

    //=========================
    ZMagAve = (1 - tiny) * ZMagAve + tiny * ZMag;
    RValueAve = (1 - tiny) * RValueAve + tiny * RValue;
    XValueAve = (1 - tiny) * XValueAve + tiny * XValue;
    SWRValueAve = (1 - tiny) * SWRValueAve + tiny * SWRValue;
    MyDelay(50);
    tft.setTextSize(1);
    tft.setFont(&FreeSerif18pt7b);
    tft.setCursor(insetMargin, SWRYPos);
    tft.print("SWR");
    tft.fillRect(insetMargin + 85, SWRYPos - 26, 90, 30, ILI9488_BLACK);
    tft.setCursor(insetMargin + 90, SWRYPos);
    tft.print(SWRValueAve, 2);
    tft.setFont();
    tft.setTextSize(1);
    //SWRValue=5;
    tft.setFont(&FreeSerif12pt7b);
    tft.setCursor(insetMargin , SWRYPos + 40);
    tft.print("Z: ");
    tft.fillRect(insetMargin + 125, SWRYPos + 15, 70, 30, ILI9488_BLACK);
    tft.setCursor(insetMargin + 130 , SWRYPos + 40);
    tft.print(ZMagAve, 1);
    tft.setCursor(insetMargin , SWRYPos + 70);
    tft.print("R: ");
    tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
    tft.fillRect(insetMargin + 125, SWRYPos + 45, 70, 30, ILI9488_BLACK);
    tft.setCursor(insetMargin + 130, SWRYPos + 70);
    tft.print(RValueAve, 1);

    tft.setTextColor(ILI9488_ORANGE, ILI9488_BLACK);
    tft.setCursor(insetMargin , SWRYPos + 100);
    tft.print("X: ");
    tft.fillRect(insetMargin + 125, SWRYPos + 75, 70, 30, ILI9488_BLACK);
    tft.setCursor(insetMargin + 130 , SWRYPos + 100);
    tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
    tft.print(XValueAve, 1);

    tft.setCursor(insetMargin , SWRYPos + 130);
    tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
    tft.print("Angle:");
    tft.fillRect(insetMargin + 125, SWRYPos + 105, 70, 30, ILI9488_BLACK);
    tft.setCursor(insetMargin + 130 , SWRYPos + 130);
    tft.print(angle, 1);
    tft.setCursor(insetMargin , SWRYPos + 160);
    tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
    tft.print("Refl Coeff:");
    tft.fillRect(insetMargin + 125, SWRYPos + 135, 70, 30, ILI9488_BLACK);
    tft.setCursor(insetMargin + 130 , SWRYPos + 160);
    tft.print(reflCoeff, 1);
    tft.setFont();
    tft.setTextSize(2);

    int plotValue = SWRValue * 10;

    plotNeedle(plotValue, 5);

    if (digitalRead(MENUENCODERSWITCH) == LOW) {
      plotFlag = 1;
      delay(100);
    }
    if (plotFlag == 1) {
      plotFlag = 0;
      PlotRealTimeSWR(bandIndex);
    }

  }

  //SendFrequency(0);
  MyDelay(100);
  MakeMenuSelection();

  tft.setTextSize(2);                         // Back to normal
  tft.setTextColor(ILI9488_WHITE);
}
