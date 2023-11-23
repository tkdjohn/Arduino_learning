#ifndef BEENHERE
#include "AT.h"
#endif

/*****
  Purpose: To display current Supply Voltage

  Argument list:
    void

  Return value:
    void
*****/
void DisplaySupplyVoltage() {
  tft.setTextColor(ILI9488_PINK, ILI9488_BLACK);
  supplyVolt = analogRead(PA6);
  supplyVolt = 4.6 * supplyVolt * 3.3 / 4096.;
  tft.setCursor(410, 0);
  tft.print(supplyVolt, 2);
  tft.setCursor(455, 0);
  tft.print(" V");
}

/*****
  Purpose: To erase the display below the top two menu lines
  Argument list:
    void
  Return value:
    void
*****/
void EraseBelowMenu()
{
  tft.fillRect(0, 56, 340, 280, ILI9488_BLACK);
}
/*****
  Purpose: To erase the display page

  Argument list:
    void

  Return value:
    void
*****/
void ErasePage()
{
  tft.fillScreen(ILI9488_BLACK);
}

/*****
  Purpose: To display the main menu page

  Argument list:
    ILI9488 tft      the display object
    int whichMenuPage         the currently displayed menu page
    double SWR                 the current SWR value

  Return value:
    int                       the menu selected
*****/
void ShowMainDisplay()
{

  int i;
  tft.fillScreen(ILI9488_BLACK);
  DisplaySupplyVoltage();
  for (i = 0; i < MAXMENUES; i++) {
    if (i == 0) {
      tft.setTextColor(ILI9488_BLUE, ILI9488_WHITE);
    } else {
      tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
    }
    tft.setCursor(i * (PIXELWIDTH - 40) / (MAXMENUES), 0);
    tft.print(menuOptions[i]);
  }

}

/*****
  Purpose: To display the SWR amd frequency data

  Argument list:
    ILI9488 tft      the display object
    double SWR                 the current SWR value

  Return value:
    void
*****/
void ShowSubmenuData(double SWR, long cursorFrequency )
{
  tft.drawFastHLine(0, 21, 480, ILI9488_RED);
  tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
  tft.setCursor(165, 0);
  tft.print("Cursor:");
  tft.setCursor(250, 0);
  tft.print((double)cursorFrequency / 1000000, 3);
  tft.print(" MHz ");
  tft.setTextColor(ILI9488_YELLOW, ILI9488_BLACK);
  tft.setCursor(XAXISSTART - 20, YAXISSTART - 22);
  tft.print("SWR: ");
  tft.setCursor(XAXISSTART + 30, YAXISSTART - 22);
  tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
  if (SWR > 50) {
    tft.print(">50  ");
  }
  else {
    tft.print(SWR, 1);
  }
  tft.setCursor(XAXISSTART + 110, YAXISSTART - 22);
  tft.setTextColor(ILI9488_MAGENTA, ILI9488_BLACK);
  tft.print("Z: ");
  tft.setCursor(XAXISSTART + 135, YAXISSTART - 22);
  tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
  tft.print(ZMag, 1);
  tft.setCursor(270, YAXISSTART - 22);
  tft.setTextColor(ILI9488_LIGHTGREY, ILI9488_BLACK);
  tft.print("R: ");
  tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
  tft.setCursor(295, YAXISSTART - 22);
  tft.print(RValue, 1);
  tft.setTextColor(ILI9488_ORANGE, ILI9488_BLACK);
  tft.setCursor(375, YAXISSTART - 22);
  tft.print("X: ");
  tft.setCursor(400, YAXISSTART - 22);
  tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
  tft.print(XValue, 1);
  tft.drawFastHLine(0, 47, 480, ILI9488_RED);
}
/*****
  Purpose: To get a main menu choice

  Argument list:
    ILI9488 tft      the display object
    double SWR                 the current SWR value

  Return value:
    int                       the menu selected
*****/
void MakeMenuSelection()
{
  ShowMainDisplay();
  int i, index = 0 ;

  while (digitalRead(MENUENCODERSWITCH) != LOW) {
    delay(100);
    if (menuEncoderMovement) {                             // Must be i (CW) or -1 (CCW)
      if (menuEncoderMovement == 1) {
        index++;
        if (index == MAXMENUES) {        // wrap to first index
          index = 0;
        }
      }
      if (menuEncoderMovement == -1) {
        index--;
        if (index < 0) {        // wrap to first index
          index = MAXMENUES - 1;
        }
      }
      delay(10);
      menuEncoderMovement = 0;
      tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
      for (i = 0; i < MAXMENUES; i++) {
        tft.setCursor(i * (PIXELWIDTH - 40) / MAXMENUES, 0);
        tft.print(menuOptions[i]);
      }
      tft.setTextColor(ILI9488_BLUE, ILI9488_WHITE);
      tft.setCursor(index * (PIXELWIDTH - 40) / MAXMENUES, 0);
      tft.print(menuOptions[index]);
    }
    if (digitalRead(MENUENCODERSWITCH) == LOW) {
      MyDelay(50);

      switch (index) {

        case FULLSCAN:
          currentFrequency = bandCenter[0];
          SendFrequency(currentFrequency);
          PlotFullRealTimeSWR();
          //MakeMenuSelection();
          break;

        case BANDSCAN:
          whichBandOption = SelectBand();
          currentFrequency = bandCenter[whichBandOption];
          SendFrequency(currentFrequency);

          PlotRealTimeSWR(whichBandOption);

          //ShowMainDisplay();
          // loop();
          break;

        case SINGLESWR:
          whichBandOption = SelectBand();
          currentFrequency = bandCenter[whichBandOption];
          SendFrequency(currentFrequency);
          SingleFrequency(whichBandOption);
          GraphAxis(whichBandOption);
          PlotRealTimeSWR(whichBandOption);
          //ShowMainDisplay();
          //loop();
          break;

        case ZERO:
          SendFrequency(0L);
          delay(100);
          Zero();
          //ShowMainDisplay();
          //loop();
          break;
        case CAL:
          SendFrequency(7150000L);
          delay(100);
          Calibrate();
          //ShowMainDisplay();
          //loop();
          break;
      }
      endFlag = 0;

    }
  }
  tft.setTextColor(ILI9488_BLUE, ILI9488_WHITE);
  tft.setCursor(index * (PIXELWIDTH - 40) / MAXMENUES, 0);
  tft.print(menuOptions[index]);
  tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
}

/*****
  Purpose: To get a band menu choice
  Argument list:
    ILI9488 tft      the display object
  Return value:
    int                       the menu selected
*****/
int SelectBand()
{
  char *bands[] = {" 160 ", " 80M ", " 40M ", " 30M ", " 20M ", " 17M ", " 15M ", " 12M ", " 10M ", "Return to Main Menu"};
  int currBand[] = {160, 80 , 40, 30, 20, 17 , 15 , 12 , 10};
  int i, index, where = 0;
  tft.fillRect(0, 0, PIXELWIDTH, PIXELHEIGHT, ILI9488_BLACK);
  tft.setTextColor(ILI9488_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(5, 0);
  tft.print("Select Band:");
  tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
  for (int i = 0; i < MAXBANDS; i++) {
    tft.setCursor(100, 30 + i * 28);
    tft.print(bands[i]);
  }
  tft.setCursor(100, 30);
  tft.setTextColor(ILI9488_BLUE, ILI9488_WHITE);
  tft.print(bands[0]);
  digitalWrite(MENUENCODERSWITCH, HIGH);
  MyDelay(100L);
  //  Serial.println("In SelectBand, before while");
  index = 0;
  endFlag = 0;
  while (digitalRead(MENUENCODERSWITCH) != LOW) {
    if (menuEncoderMovement) {
      if (menuEncoderMovement == 1) {
        index++;
        if (index == MAXBANDS) {        // wrap to first index
          index = 0;
        }
      }
      if (menuEncoderMovement == -1) {
        index--;
        if (index < 0) {        // wrap to last index
          index = MAXBANDS - 1;
        }
      }
      menuEncoderMovement = 0;
      tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
      for (int i = 0; i < MAXBANDS; i++) {
        tft.setCursor(100, 30 + i * 28);
        tft.print(bands[i]);
      }
      tft.setTextColor(ILI9488_BLUE, ILI9488_WHITE);
      tft.setCursor(100, 30 + index * 28);
      tft.print(bands[index]);
    }

    if (index == MAXBANDS - 1) {


      //SendFrequency(0);
      ShowMainDisplay();
      // MakeMenuSelection();
      loop();
    }
  }
  // MyDelay(500L);
  currentBand = currBand[index];

  return index;
}

/*****
  Purpose: To display the axes for a graph

  Paramter list:
    int whichBandOption     // The band being used

  Return value:
    void
*****/
void GraphAxis(int whichBandOption)
{
  char buff[10];
  int chunks, tickCount;
  int yTick, xTick, yDotSWRPosition, xDotIncrement;
  int tcolor, bcolor;
  int i, k, yIncrement, xIncrement;
  long xPosition1;
  int fullScanFlag = 0;
  double freqStart1;
  double freqEnd1;
  tft.fillRect(0, 52, PIXELWIDTH, PIXELHEIGHT - 54, ILI9488_BLACK);
  int xAxisEnd1 = XAXISEND - 25;
  tft.drawLine(XAXISSTART, YAXISSTART, XAXISSTART, YAXISEND, ILI9488_CYAN);    // Y axis
  tft.drawLine(XAXISSTART, YAXISEND,   XAXISEND,   YAXISEND, ILI9488_CYAN); // X axis
  switch (whichBandOption) {
    case 0:
      freqStart1 = 1.8;
      freqEnd1 = 2.0;
      pip = 0.04;    //
      chunks = 5;  // number of major divisions
      xDotIncrement = 50;  // grey dot increment
      break;
    case 1:
      freqStart1 = 3.5;
      freqEnd1 = 4.0;
      pip = 0.1;    //
      chunks = 5;  // number of major divisions
      xDotIncrement = 50;  // grey dot increment
      break;
    case 2:
      freqStart1 = 7.0;
      freqEnd1 = 7.3;
      pip = 0.1;
      chunks = 3;
      xDotIncrement = 100;
      break;
    case 3:
      freqStart1 = 10.1;
      freqEnd1 = 10.15;
      pip = 0.01;
      chunks = 5;
      xDotIncrement = 20;
      break;
    case 4:
      freqStart1 = 14.0;
      freqEnd1 = 14.35;
      pip = 0.07;
      chunks = 5;
      xDotIncrement = 50;
      break;
    case 5:
      freqStart1 = 18.068;
      freqEnd1 = 18.168;
      pip = 0.025;
      chunks = 4;
      xDotIncrement = 50;
      break;
    case 6:
      freqStart1 = 21.0;
      freqEnd1 = 21.45;
      pip = 0.09;
      chunks = 5;
      xDotIncrement = 50;
      break;
    case 7:
      freqStart1 = 24.89;
      freqEnd1 = 24.990;
      pip = 0.02;
      chunks = 5;
      xDotIncrement = 50;
      break;
    case 8:
      freqStart1 = 28.0;
      freqEnd1 = 29.7;
      pip = 0.34;
      chunks = 5;
      xDotIncrement = 50;
      break;
    case 9:
      freqStart1 = 3.0;
      freqEnd1 = 28;
      pip = 7;
      chunks = 7;
      xDotIncrement = 50;
      break;
  }
  tcolor = ILI9488_YELLOW;
  bcolor = ILI9488_BLACK;
  tickCount = 4;
  tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);              // Lable X axis
  tft.setCursor(XAXISEND + 7 , YAXISEND - 8);
  tft.print("Mhz");
  //int fullYaxisStart = YAXISSTART;
  yIncrement = ((YAXISEND - YAXISSTART) / 4) - 3;                   // Spacing for graph tick marks
  yTick = YAXISSTART + 5;                                       // on Y axis
  xDotIncrement = 10;
  tft.setTextColor(ILI9488_YELLOW, ILI9488_BLACK);
  tft.setCursor(2, 135);
  tft.setTextSize(2);
  tft.print("SWR");
  tft.setTextColor(ILI9488_ORANGE, ILI9488_BLACK);
  // tft.setCursor(445, 85);
  //tft.print("O");
  //tft.setCursor(445, 100);
  //tft.print("h");
  tft.setTextSize(3);
  tft.setCursor(445, 115);
  tft.print((char)233);
  tft.setTextSize(2);
  //tft.print("m");
  //tft.setCursor(445, 130);
  //tft.print("s");
  int gridIncrement = (YAXISEND - YAXISSTART) / 4;
  tft.setTextColor(ILI9488_YELLOW, ILI9488_BLACK);
  for (i = YAXISSTART; i < YAXISEND + 1; i += yIncrement, yTick += yIncrement) {
    tft.setCursor(3, yTick - 4);                     //Y Axis labels
    tft.setTextColor(ILI9488_YELLOW, ILI9488_BLACK);
    tft.print((tickCount--) + 1);
    tft.print(".0");
  }

  tft.setTextColor(ILI9488_ORANGE, ILI9488_BLACK);
  tft.setCursor(XAXISEND + 2, YAXISSTART + 5);
  tft.print("100");
  int fiftyOhmsLine = map(50, 0, 100, YAXISEND, YAXISSTART);
  tft.setCursor(XAXISEND + 5, fiftyOhmsLine - 7);
  tft.print("50");
  tft.setCursor(XAXISEND + 7, YAXISEND - 28);
  tft.print("0");

  tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
  yDotSWRPosition = xIncrement / 2;
  xIncrement = (XAXISEND - XAXISSTART) / chunks;            // Spacing for graph tick marks
  xTick = XAXISSTART;                                       // on X axis
  fullScanFlag == 0;
  for (i = 0; i < chunks + 1; i++, xTick += xIncrement) {
    tft.drawLine(XAXISSTART + i * xIncrement, YAXISEND, XAXISSTART + i * xIncrement, YAXISEND - 10, ILI9488_CYAN);  // X axis tick marks
    tft.setCursor(XAXISSTART - 25 + i * xIncrement, YAXISEND + 12);
    if (freqStart1 > freqEnd1) {
      freqStart1 = freqEnd1;
    }
    tft.drawLine(XAXISEND, YAXISSTART, XAXISEND, YAXISEND, ILI9488_CYAN); // Draw Right impedance  Y axis
    if (freqStart1 > 18.0 and freqStart1 < 18.2) {
      tft.print(freqStart1, 3);
    }
    else {
      tft.print(freqStart1, 2);
    }

    freqStart1 += pip;
  }
  tft.setTextSize(2);
}

/*****
  Purpose: Displays the Plot grid
  Paramter list:
    int whichBandOption     // The band being used
  Return value:
    void
*****/
void PlotGrid(int whichBandOption)
{
  char limitLo[6];
  char limitHi[6];
  int chunks, tickCount;
  int yTick, xTick, yDotSWRPosition, xDotIncrement;

  int i, k, yIncrement, xIncrement;
  long freqStart, freqEnd, pip;
  int xAxisEnd1 = 25;

  switch (whichBandOption) {
    case 0:                         // 160M
      freqStart = LOWEND160M;
      freqEnd = HIGHEND160M;
      pip = 0.1;
      chunks = 5;
      xDotIncrement = 50;
      break;

    case 1:                          // 80M
      freqStart = LOWEND80M;
      freqEnd = HIGHEND80M;
      pip = 0.1;
      chunks = 5;
      xDotIncrement = 50;
      break;
    case 2:                         // 40M
      freqStart = LOWEND40M;
      freqEnd = HIGHEND40M;
      pip = 0.1;
      chunks = 3;
      xDotIncrement = 50;
      break;

    case 3:                         // 30M
      freqStart = LOWEND30M;
      freqEnd = HIGHEND30M;
      pip = 0.02;
      chunks = 5;
      xDotIncrement = 50;
      break;

    case 4:                         // 20M
      freqStart = LOWEND20M;
      freqEnd = HIGHEND20M;
      pip = 0.10;
      chunks = 5;
      xDotIncrement = 50;
      break;

    case 5:                         // 17M
      freqStart = LOWEND17M;
      freqEnd = HIGHEND17M;
      pip = 0.10;
      chunks = 4;
      xDotIncrement = 50;
      break;
    case 6:                         // 15M
      freqStart = LOWEND15M;
      freqEnd = HIGHEND15M;
      pip = 0.10;
      chunks = 5;
      xDotIncrement = 50;
      break;
    case 7:                         // 12M
      freqStart = LOWEND12M;
      freqEnd = HIGHEND12M;
      pip = 0.10;
      chunks = 5;
      xDotIncrement = 50;
      break;

    case 8:                         // 10M
      freqStart = LOWEND10M;
      freqEnd = HIGHEND10M;
      pip = 0.10;
      chunks = 5;
      xDotIncrement = 50;
      break;
  }
  xIncrement = (XAXISEND - XAXISSTART) / chunks;            // Spacing for graph tick marks
  i = 0;

  int dotGrid1 = (YAXISEND - YAXISSTART) / 4;
  int dotGrid2 = dotGrid1 * 3;

  for (k = 0; k <= (XAXISEND - XAXISSTART); k += (XAXISEND - XAXISSTART) / 50) { //  Draw horizontal dotted grid lines
    tft.drawPixel(k + XAXISSTART , dotGrid1 + YAXISSTART, ILI9488_CYAN); // X and Y dotted axis at minor divisions
    tft.drawPixel(k + XAXISSTART , dotGrid2 + YAXISSTART, ILI9488_CYAN); // X and Y dotted axis at minor divisions
  }
  for (k = XAXISSTART; k < XAXISEND + 1; k += xIncrement) {
    for (i = YAXISSTART; i < YAXISEND + 1; i += 5) {
      tft.drawPixel(k, i, ILI9488_CYAN);    // Y   vertical dotted lines at major division intervals
    }
  }
}
