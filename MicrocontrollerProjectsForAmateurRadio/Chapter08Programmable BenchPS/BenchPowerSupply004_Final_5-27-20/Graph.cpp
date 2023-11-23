#ifndef BEENHERE
#include "ProgPS.h"
#endif
#include <Arduino.h>

/*****
  Purpose: To display the axes for voltage vs time graph
  Paramter list: void
  Return value:  void
*****/
void GraphAxis()
{
  myMenu.eraseDisplay(myDisplay);
  myDisplay.fillRect(DISPLAYWIDTH / 16, DISPLAYHEIGHT / 32, DISPLAYWIDTH / 1.07, DISPLAYHEIGHT -DISPLAYHEIGHT / 11,BLUE); //Fill plot area with BLUE
  myDisplay.drawRect(DISPLAYWIDTH / 16, DISPLAYHEIGHT / 32, DISPLAYWIDTH / 1.07, DISPLAYHEIGHT -DISPLAYHEIGHT / 11,GREEN); // Draw graph area outline
  myDisplay.setFont(&FreeSerif12pt7b);
  myDisplay.setTextColor(YELLOW);
  myDisplay.setCursor(0, DISPLAYHEIGHT / 20);
  myDisplay.print("30");
  myDisplay.setCursor(0, DISPLAYHEIGHT -DISPLAYHEIGHT / 20);
  myDisplay.print("0");
  for(int j=01;j<=9;j++){
  myDisplay.drawLine(DISPLAYWIDTH / 16+j*DISPLAYWIDTH/10.7, DISPLAYHEIGHT / 1.067,DISPLAYWIDTH /16+j*DISPLAYWIDTH/10.7, DISPLAYHEIGHT / 1.0345, GREEN);
  }//myDisplay.drawLine(DISPLAYWIDTH / 1.4545, DISPLAYHEIGHT / 1.067, DISPLAYWIDTH / 1.4545, DISPLAYHEIGHT / 1.0345, GREEN);
  myDisplay.setTextColor(GREEN);
  myDisplay.setCursor(DISPLAYWIDTH / 16, DISPLAYHEIGHT / 1.0042);
  myDisplay.print("0");
  myDisplay.setCursor(DISPLAYWIDTH / 1.06, DISPLAYHEIGHT / 1.0042);
  myDisplay.print(functionDuration*numFunctionCycles);
  for (int i = 0; i <= 6; i++) {
    myDisplay.drawLine(DISPLAYWIDTH / 26.67, (DISPLAYHEIGHT / 32) + (DISPLAYWIDTH / 9.9) * i, DISPLAYWIDTH/16 , (DISPLAYHEIGHT / 32) + (DISPLAYWIDTH / 9.9) * i, GREEN);
  }
}

/*****
  Purpose: To plot voltage for various functions
  Paramter list: void
  Return value:  void
*****/
void PlotVoltage()
{
  k=0;
  long xPosition;
  //if ((millis() - yTime) >= stepTime) {
long maxPlotTime=functionDuration*numFunctionCycles;
    xPosition = map(plotTime,0,maxPlotTime,0,445)+30;
    float voltIn2 = ((float)analogRead(PA3) / 4096) * 30.1;
    long voltIn10 = voltIn2 * 10 ;
    long yPosition = map(voltIn10, 0, 300 , 281, 0);
    myDisplay.fillCircle(xPosition, yPosition+20, 1, YELLOW);
    k++;
    if (k >= 445) {
      k = 0;
myDisplay.fillRect(DISPLAYWIDTH / 16, DISPLAYHEIGHT / 32, DISPLAYWIDTH / 1.07, DISPLAYHEIGHT -DISPLAYHEIGHT / 11,BLUE); //Fill plot area with BLUE
  myDisplay.drawRect(DISPLAYWIDTH / 16, DISPLAYHEIGHT / 32, DISPLAYWIDTH / 1.07, DISPLAYHEIGHT -DISPLAYHEIGHT / 11,GREEN); // Draw graph area outline
    }
    yTime = millis();
    myDisplay.setFont(&FreeSerif12pt7b);
    myDisplay.setTextColor(WHITE);

}
