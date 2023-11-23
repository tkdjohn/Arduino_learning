#ifndef BEENHERE
//#include <SPI.h>
#include "Post.h"
#endif


int doneFlag = false;

int   iCount = 1;
int   iSq;

//===================================================================================



int screenPosition = 1;

//float caltx, calty;
float aveX[100];
float aveY[100];

float xFinal;
float yFinal;


float xMapLowRange1 = 671;
float xMapLowRange2 = 689;
float xMapLowRange3 = 689;
float xMapLowRange4 = 716;

float xMapHigh = 327;
float yMapLow = 834;
float yMapHigh = 190;
float xMapLowTotal = 0;
float xMapHighTotal = 0;
float yMapLowTotal = 0;
float yMapHighTotal = 0;
float xLowVarTot1 = 0;
float xLowVar = 0;
float stdDeviation = 0;
float xLowVarDiff = 0;
float yLowVarDiff = 0;
float xHighVarDiff = 0;
float yHighVarDiff = 0;
float xLowVarDiffSq = 0;
float xLowVarSqTot;
float yLowVarSqTot;
float xHighVarSqTot;
float yHighVarSqTot;

float xLowSquareDiff[25];
float yLowSquareDiff[25];
float xHighSquareDiff[25];
float yHighSquareDiff[25];

float xLowValue[25];
float xLowValue2[25];
float xLowValue3[25];
float xLowValue4[25];

float yLowValue[25];
float xHighValue[25];
float yHighValue[25];

float xLowVariance;
float xHighVariance;
float yLowVariance;
float yHighVariance;

float stdDeviation1;
float stdDeviation2;
float stdDeviation3;
float stdDeviation4;


int xLowCount = 1;


//float tiny = .2; // tiny=(1-1/N) where N is the window sample used to average data
long range;

/*****
  Purpose:Get raw screen coordinate data, then calibrate to screen coordinates
  Paramter list:
    void
  Return value:  xFinal,yFinal  - final screen coordinates
*****/
/*void GetTouchCoordinates()
{
  int i = 1;
  int j = 0;
  int k = 0;
  myTouch.dataAvailable();
  do {                                  // using Do While to capture the first ADC value
    myTouch.read();         //read directly from ADC - raw values
    int    tx = myTouch.TP_X; //raw touch values
    int      ty = myTouch.TP_Y;
#ifdef DEBUG
    Serial.print("RAW in displayCal:  tx = ");
    Serial.print(tx);
    Serial.print("   ty = ");
    Serial.print(ty);
    Serial.print("  ID = ");
    //Serial.println(myButton.buttons[i].text);

#endif
    MyDelay(15);
    aveX[i] = tx;  // Calculate an array of x and y valuesfrom raw values
    aveY[i] = ty;
    i++;
  } while (myTouch.dataAvailable() and i <= 100);  // Do this up to 100 times as long as button pushed

  if (i > 5) {  //Check to see that there are at least 5 values
    for ( j = 10; j <= i - 5 ; j++) { //Average values, throwing away first 9 and last 5 values
      xFinal += aveX[j];
      yFinal += aveY[j];
      k++;
    }
    if (k == 0) {
      k = 1;
    }
    xFinal = xFinal / k;
    yFinal = yFinal / k;
    k = 0;
    //tft.touchEnable(false); // Turn off touch to prevent additional touches for 100ms
    //delay(100);
    //tft.touchEnable(true);  //Turn touch back on
  }
  calty = map( (long) yFinal, (long) yMapLowAve, (long) yMapHighAve, (long) 20, (long) 300);       //
  caltx = map((long) xFinal, (long) xMapLowAve, (long) xMapHighAve, (long) 20, (long) 460); // Map from ADC values to Screen     // Jack
  //  whichButton = myButton.WhichButton(caltx, calty);
}*/

/*****
  Purpose:Get raw screen coordinate data, then calibrate to screen coordinates
  Paramter list:
    void
  Return value:  xFinal,yFinal  - final screen coordinates
*****/
void GetTouchCoordinates2()
{
  displayTimeFlag = 0;
  int i = 1;
  int j = 0;
  int k = 0;
  /*myTouch.dataAvailable();
  do {                                  // using Do While to capture the first ADC value
    myTouch.read();         //read directly from ADC - raw values
    tx = myTouch.TP_X; //raw touch values
    ty = myTouch.TP_Y;
    MyDelay(15);
    aveX[i] = tx;  // Calculate an array of x and y valuesfrom raw values
    aveY[i] = ty;
    i++;
    if (i >= 100) {
      tft.setTextSize(2);
      tft.setCursor(340, 40);
      tft.print("Release");
      //myTouch.dataAvailable(false);
      MyDelay(100);
      tft.fillRect(339, 39, 90, 20, ILI9488_BLACK);
    }


  } while (myTouch.dataAvailable());*/

  // Do this up to 100 times as long as button pushed
  if (i < 100) {
    tft.setTextSize(2);
    tft.setCursor(100, 240);
    //tft.print("Time too short1");
    displayTimeFlag = 1;
    //MyDelay(1000);
    //tft.setCursor(500, 150);
    //tft.print("                          ");

  }

  if (i > 11) {  //Check to see that there are at least 5 values
    for ( j = 5; j <= i - 5 ; j++) { //Average values, throwing away first 10 and last 5 values
      xFinal += aveX[j];
      yFinal += aveY[j];
      k++;
    }
    if (k == 0) {
      k = 1;
    }
    xFinal = xFinal / k;
    yFinal = yFinal / k;
    k = 0;
    //myTouch.dataAvailable(false); // Turn off touch to prevent additional touches for 100ms
    //delay(100);
    //myTouch.dataAvailable(true);  //Turn touch back on
  }
   calty = map( (long) yFinal, (long) 3500, (long) 400, (long) 20, (long) 300);       //
  caltx = map((long) xFinal, 300, 2000, 20, 240);
    //Serial.print("xFinal=  ");Serial.println(xFinal);
   // Serial.print("yFinal=  ");Serial.println(yFinal);
  //GetTouchCoordinates2();
//Serial.print("caltx  ");Serial.println(caltx);
//Serial.print("calty  ");Serial.println(calty);
//Serial.println(" ");
  //whichButton = myButton.WhichButton(caltx, calty);
}


/*****
  Purpose:Get raw screen coordinate data, then calibrate to screen coordinates
  Paramter list:
    void
  Return value:  xFinal,yFinal  - final screen coordinates
*****/
void InitDisplayCalibration()
{

  tft.fillCircle(20, 160, 5, ILI9488_YELLOW);
  screenPosition = 1;

  iCount = 1;
  tft.setTextSize(2);
  tft.setCursor(140, 40);
  tft.setTextColor(ILI9488_YELLOW);
  tft.print("Value");
  tft.setCursor(220, 40);
  tft.print("Std Dev");
  tft.setCursor(320, 40);
  tft.print("Count");
  tft.setCursor(400, 40);
  tft.print(iCount);
  tft.setTextColor(ILI9488_CYAN);
  tft.setCursor(50, 70);
  tft.print("X low");

  tft.setCursor(50, 100);
  tft.print("Y low");
  tft.setCursor(50, 130);
  tft.print("X high");
  tft.setCursor(50, 160);
  tft.print("Y high");

  while (iCount < 6) {     // Stay here until they press the secondary encoder switch
    //myTouch.dataAvailable(true);
    tft.setTextColor(ILI9488_CYAN);
    // if (myTouch.dataAvailable()) {
      switch (screenPosition) {
        case 1:
          GetTouchCoordinates2();
          if (displayTimeFlag == 1) {
            tft.setTextSize(2);
            tft.setCursor(100, 240);
            tft.print("Time too short - do again");
            //tft.touchEnable(false);
            delay(1000);
            //tft.setCursor(300,200);
            tft.fillRect(95, 230, 320, 30, ILI9488_BLACK);
            screenPosition = 1;
            displayTimeFlag = 0;
            break;
          }
          if (iCount > 1 && abs(xFinal - xMapLowAve) > 100) { //Check for points too far from dot after first round
            tft.setCursor(100, 240);
            tft.print("Point Ignored - do again");
            delay(1000);
            tft.fillRect(95, 230, 320, 30, ILI9488_BLACK);
            screenPosition = 1;
            break;
          }
          else {
            xLowValue[iCount] = xFinal;                // store current point value
          }

          xMapLowAve = 0;
          for (int iave = 1; iave <= iCount; iave++) {  //Calc running ave
            xMapLowAve =  xLowValue[iave] + xMapLowAve;
          }
          xMapLowAve = xMapLowAve / iCount;

          xLowVarSqTot = 0;
          for (int iSq = 1; iSq <= iCount; iSq++) { // Cal sum of squre of differences
            xLowSquareDiff[iSq] = (xLowValue[iSq] - xMapLowAve) * (xLowValue[iSq] - xMapLowAve);
            xLowVarSqTot = xLowSquareDiff[iSq] + xLowVarSqTot;
          }
          xLowVariance = xLowVarSqTot / (iCount - 1); // Calc Variance
          stdDeviation1 = sqrt(xLowVariance);  //Calc Std Deviation
          screenPosition = 2;
          tft.fillCircle(20, 160, 5, ILI9488_BLACK);
          tft.fillCircle(240, 20, 5, ILI9488_YELLOW);
          tft.fillRect(135, 68, 200, 20, ILI9488_BLACK);
          tft.setTextSize(2);
          tft.setCursor(140, 70);
          //tft.print((int)xFinal);
          tft.print((int)xMapLowAve);
          tft.setCursor(220, 70);
          tft.print(stdDeviation1);
          break;




        case 2:
          GetTouchCoordinates2();
          if (displayTimeFlag == 1) {
            tft.setTextSize(2);
            tft.setCursor(100, 240);
            tft.print("Time too short - do again");
            //myTouch.dataAvailable(false);
            delay(1000);
            tft.fillRect(95, 230, 320, 30, ILI9488_BLACK);
            screenPosition = 2;
            displayTimeFlag = 0;
            break;
          }
          if (iCount > 1 and abs(yFinal - yMapLowAve) > 100) {  //Check for points too far from dot after first round
            tft.setCursor(100, 240);
            tft.print("Point Ignored - do again");
            delay(1000);
            tft.fillRect(95, 230, 320, 30, ILI9488_BLACK);
            screenPosition = 2;
            break;
          }
          else {
            yLowValue[iCount] = yFinal;
          }

          yMapLowAve = 0;
          for (int iave = 1; iave <= iCount; iave++) {  //Calc running ave
            yMapLowAve =  yLowValue[iave] + yMapLowAve;
          }
          yMapLowAve = yMapLowAve / iCount;
          yLowVarSqTot = 0;
          for (int iSq = 1; iSq <= iCount; iSq++) { // Cal sum of squre of differences
            yLowSquareDiff[iSq] = (yLowValue[iSq] - yMapLowAve) * (yLowValue[iSq] - yMapLowAve);
            yLowVarSqTot = yLowSquareDiff[iSq] + yLowVarSqTot;
          }
          yLowVariance = yLowVarSqTot / (iCount - 1); // Calc Variance
          stdDeviation2 = sqrt(yLowVariance);  //Calc Std Deviation
          screenPosition = 3;
          tft.fillCircle(240, 20, 5, ILI9488_BLACK);
          tft.fillCircle(360, 160, 5, ILI9488_YELLOW);
          tft.fillRect(135, 98, 200, 20, ILI9488_BLACK);
          tft.setTextSize(2);
          tft.setCursor(140, 100);
          tft.print((int)yMapLowAve);
          tft.setCursor(220, 100);
          tft.print(stdDeviation2);
          break;

        case 3:
          GetTouchCoordinates2();
          if (displayTimeFlag == 1) {
            tft.setTextSize(2);
            tft.setCursor(100, 240);
            tft.print("Time too short - do again");
            //myTouch.dataAvailable(false);
            delay(1000);
            tft.fillRect(95, 230, 320, 30, ILI9488_BLACK);
            screenPosition = 3;
            displayTimeFlag = 0;
            break;
          }
          if (iCount > 1 and abs(xFinal - xMapHighAve) > 3000) {
            tft.setCursor(100, 240);
            tft.print("Point Ignored - do again");
            delay(1000);
            tft.fillRect(95, 230, 320, 30, ILI9488_BLACK);
            screenPosition = 3;
            break;
          }
          else {
            xHighValue[iCount] = xFinal;
          }

          xMapHighAve = 0;
          for (int iave = 1; iave <= iCount; iave++) {  //Calc running ave
            xMapHighAve =  xHighValue[iave] + xMapHighAve;
          }
          xMapHighAve = xMapHighAve / iCount;
          xHighVarSqTot = 0;
          for (int iSq = 1; iSq <= iCount; iSq++) { // Cal sum of squre of differences
            xHighSquareDiff[iSq] = (xHighValue[iSq] - xMapHighAve) * (xHighValue[iSq] - xMapHighAve);
            xHighVarSqTot = xHighSquareDiff[iSq] + xHighVarSqTot;
          }
          xHighVariance = xHighVarSqTot / (iCount - 1); // Calc Variance
          stdDeviation3 = sqrt(xHighVariance);  //Calc Std Deviation
          screenPosition = 4;
          tft.fillCircle(360, 160, 5, ILI9488_BLACK);
          tft.fillCircle(240, 300, 5, ILI9488_YELLOW);
          tft.fillRect(135, 128, 200, 20, ILI9488_BLACK);
          tft.setTextSize(2);
          tft.setCursor(140, 130);
          tft.print((int)xMapHighAve);
          tft.setCursor(220, 130);
          tft.print(stdDeviation3);
          break;

        case 4:
          GetTouchCoordinates2();
          if (displayTimeFlag == 1) {
            tft.setTextSize(2);
            tft.setCursor(100, 240);
            tft.print("Time too short - do again");
            //myTouch.dataAvailable(false);
            delay(1000);
            tft.fillRect(95, 230, 320, 30, ILI9488_BLACK);
            screenPosition = 4;
            displayTimeFlag = 0;
            break;
          }
          if (iCount > 1 and abs(yFinal - yMapHighAve) > 100) {
            tft.setCursor(100, 240);
            tft.print("Point Ignored - do again");
            delay(1000);
            tft.fillRect(95, 230, 320, 30, ILI9488_BLACK);
            screenPosition = 4;
            break;
          }
          else {
            yHighValue[iCount] = yFinal;
          }

          yMapHighAve = 0;
          for (int iave = 1; iave <= iCount; iave++) {  //Calc running ave
            yMapHighAve =  yHighValue[iave] + yMapHighAve;
          }
          yMapHighAve = yMapHighAve / iCount;
          yHighVarSqTot = 0;
          for (int iSq = 1; iSq <= iCount; iSq++) { // Cal sum of squre of differences
            yHighSquareDiff[iSq] = (yHighValue[iSq] - yMapHighAve) * (yHighValue[iSq] - yMapHighAve);
            yHighVarSqTot = yHighSquareDiff[iSq] + yHighVarSqTot;
          }
          yHighVariance = yHighVarSqTot / (iCount - 1); // Calc Variance
          stdDeviation4 = sqrt(yHighVariance);  //Calc Std Deviation
          screenPosition = 1;
          tft.fillCircle(240, 300, 5, ILI9488_BLACK);
          tft.fillCircle(20, 160, 5, ILI9488_YELLOW);
          tft.fillRect(135, 158, 200, 20, ILI9488_BLACK);
          tft.setTextSize(2);
          tft.setTextColor(ILI9488_WHITE);
          //tft.setFontScale( 1);
          tft.setCursor(140, 160);
          tft.print((int)yMapHighAve);
          tft.setCursor(220, 160);
          tft.print(stdDeviation4);
          //tft.setCursor(520, 300);
          //tft.println(calty );
          iCount++;

          tft.setTextColor(ILI9488_WHITE);
          //tft.setFontScale( 1);
          tft.fillRect(395, 38, 20, 20, ILI9488_BLACK);
          tft.setCursor(400, 40);
          tft.print(iCount);
          break;
      }

    //}

  } // End while (digitalRead(
  /* EEPROM.put(EEPROMUSEROFFSET + CALxMapLowAve,     xMapLowAve);       // Write new calibration data
    EEPROM.put(EEPROMUSEROFFSET + CALXMAPLOWAVE2,     xMapLowAve2);
    EEPROM.put(EEPROMUSEROFFSET + CALXMAPLOWAVE3,     xMapLowAve3);
    EEPROM.put(EEPROMUSEROFFSET + CALXMAPLOWAVE4,     xMapLowAve4);
    EEPROM.put(EEPROMUSEROFFSET + YMAPLOW,            yMapLowAve);
    EEPROM.put(EEPROMUSEROFFSET + XMAPHIGH,           xMapHighAve);
    EEPROM.put(EEPROMUSEROFFSET + YMAPHIGH,           yMapHighAve);*/
  //DisplaySiCalPage();
}
