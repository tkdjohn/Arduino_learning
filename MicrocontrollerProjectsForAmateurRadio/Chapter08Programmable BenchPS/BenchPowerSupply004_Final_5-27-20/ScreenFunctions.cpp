
#ifndef BEENHERE
#include "ProgPS.h"
#endif
#include <Arduino.h>


//=======================
/*****
  Purpose: Draw Output parameter labels
  Paramter list: void
  Return value:  void
*****/
void drawVoltDisplay() 
{
  myDisplay.drawRect(2, 5, 475, 55, CYAN); // Draw display area outline
  myDisplay.drawRect(2, 5, 55, 55, CYAN); // Draw display area outline
  myDisplay.setFont(&FreeSerif12pt7b);
  myDisplay.setTextColor(YELLOW, BLACK);
  myDisplay.setCursor(70, 42);
  myDisplay.print("Volts: ");
  myDisplay.setCursor(210, 42);
  myDisplay.print("Amps: ");
  myDisplay.setCursor(355, 42);
  myDisplay.print("Watts: ");
  myDisplay.setFont(&FreeSerif12pt7b);
}

/*****
   Screen print Voltage value
  Paramter list: void
  Return value:  void
*****/
void DoScreenPrintVoltage() 
{
  float tiny = .01;
  float voltIn = 0;
  for (int i = 1; i <= 100; i++) {
    voltIn = voltIn + (((float)analogRead(PA3) / 4096) * voltInCal);
    currentIn = currentIn + ((float)analogRead(PB1)) / 1258;
    MyDelay(1);
  }
  voltIn = voltIn / 100;
  currentIn = currentIn / 100;
  voltInCompare = voltIn * 10;
  voltInCompare = int(voltInCompare);

  currentInCompare = currentIn * 10;
  currentInCompare = int(currentInCompare);

  voltInCompare = voltInCompare * tiny + (1 - tiny) * voltInCompare;
  currentInCompare = currentInCompare * tiny + (1 - tiny) * voltInCompare;


  if (voltInCompare != voltInOldCompare) {
    myDisplay.setFont(&FreeSerif12pt7b);
    myDisplay.setTextColor(BLACK, BLACK);
    myDisplay.setCursor(140, 42);
    myDisplay.print(voltInOld2, 1);
    myDisplay.setTextColor(WHITE, BLACK);
    myDisplay.setCursor(140, 42);
    myDisplay.print(voltIn, 1);
    voltInOld2 = voltIn;
    voltInOldCompare = voltIn;
    voltInOldCompare = voltIn * 10;
    voltInOldCompare = int(voltInOldCompare);
  }

  currentInCompare = int(currentInCompare * 10);
  if (currentInCompare != currentInOldCompare) {
    myDisplay.setCursor(285, 42);
    myDisplay.setTextColor(BLACK, BLACK);
    myDisplay.print(currentInOld2);
    myDisplay.setCursor(285, 42);
    myDisplay.setTextColor(WHITE, BLACK);
    myDisplay.print(currentIn);
    currentInOld2 = currentIn;

    float powerIn = voltIn * currentIn;
    myDisplay.setCursor(428, 42);
    myDisplay.setTextColor(BLACK, BLACK);
    myDisplay.print(powerInOld, 1);
    myDisplay.setCursor(428, 42);
    myDisplay.setTextColor(WHITE, BLACK);
    myDisplay.print(powerIn, 1);
    powerInOld = powerIn;
    currentInOldCompare = int(currentInCompare);
    //displayUpdateOldTime = millis();
  }
  
  myDisplay.setFont(&FreeSerif12pt7b);
}  //-------------------------------------End Function -----------------

/*****
   Display on-screen timer
   Parameters: void
   Return: void
*****/
void displayTimer()
{
  //Serial.print("in dispaly timer "); 
  //myDisplay.setFont(&FreeSerif12pt7b);
  //myDisplay.fillRect(39,108,130,25,BLACK);
  myDisplay.setFont();
  myDisplay.setTextSize(4);
  myDisplay.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
  myDisplay.setCursor(180, 200);
  myDisplay.print(hour(t));
  myDisplay.setCursor(205, 200);
  myDisplay.print(":");


  myDisplay.setTextColor(ILI9488_BLACK, ILI9488_BLACK);
  myDisplay.setCursor(225, 200);
  myDisplay.print(oldTimeMin);
  myDisplay.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
  myDisplay.setCursor(225, 200);
  myDisplay.print(minute(t));
  myDisplay.setCursor(250, 200);
  myDisplay.print(":");

  myDisplay.setTextColor(ILI9488_BLACK, ILI9488_BLACK);
  myDisplay.setCursor(270, 200);
  myDisplay.print(oldTimeSec);

  myDisplay.setTextColor(ILI9488_WHITE, ILI9488_BLACK);
  myDisplay.setCursor(270, 200);
  
  myDisplay.print(second(t));
  //if(second(t)>=59){
   // myDisplay.fillRect(270,190,10,20,BLUE);
 //}

  
  oldTimeSec = second();
  oldTimeMin = minute();
  oldTimeHour = hour();
  //DoScreenPrintVoltage();

  
}
