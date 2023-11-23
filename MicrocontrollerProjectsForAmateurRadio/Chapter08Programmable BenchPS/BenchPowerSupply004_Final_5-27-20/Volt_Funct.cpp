#ifndef BEENHERE
#include "ProgPS.h"
#endif
#include <Arduino.h>


/*****
  Purpose: Updates the DAC and diplays the results

  Paramter list:
    long display1UpdateOldTime

  Return value:
    void
*****/
void DoDACOutAndScreenUpdate(long display1UpdateOldTime)
{
  DoDACOut();
  if ((millis() - display1UpdateOldTime) >= 100L) {
    DoScreenPrintVoltage();
    display1UpdateOldTime = millis();
  }
}

//==================================  Output Waveform Functions =============
/*****
   Purpose:Convert Volts to DAC setpoint
   Void
*/
float DACConvert(float voltNumber)
{
  SetpointConv = float(voltNumber * setPointCal);
  return SetpointConv;
}

/*****
   Purpose:setpointCalc()
   Void
*****/
int setpointCalc()
{
  encoderRead1();
  encoderRead3();
  int Setpoint2 = encoder3Reading + encoder1Reading10 + numKeypad2 * setPointCal;
  if (Setpoint2 >= 0 or Setpoint2 <= 4000) {
    // do nothing
  }
  else if (Setpoint2 >= 4000) {
    Setpoint2 = 4000;
  }
  else if (Setpoint2 <= 0) {
    Setpoint2 = 0;
  }

  return Setpoint2;
}


/*****
   Purpose:Calculate Ramp function
   Void
*****/
void DoRampCalc()
{
  //if (on_OffFlag == 1) {
  long runningTime = 0;
  long currentTime;
  long   currentSetpointValue;
  k = 0;
  GraphAxis();
  functionDataPrint ();
  int i;
  delay(100);
  xTime = millis();
  numberCycles = 0;
  //Serial.print("numPlotPoints=  "); Serial.println(numPlotPoints);
  //Serial.print("functionDuration=  "); Serial.println(functionDuration);
  // Serial.print("numFunctionCycles=  "); Serial.println(numFunctionCycles);
  stepTime = functionDuration / numPlotPoints;
  //Serial.print("stepTime=  "); Serial.println(stepTime);
  while (numberCycles < numFunctionCycles) {
    i = 0;
    runningTime = 0;
    SetpointVoltage = startSetpointLevelVolts;
    while (runningTime <= functionDuration and digitalRead(MENUENCODERSWITCH) != LOW) {
      i++;
      currentTime = millis();
      MyDelay(stepTime);

      SetpointVoltage = startSetpointLevelVolts + ((maxVoltageLevel - startSetpointLevelVolts) / numPlotPoints) * i;
      //Serial.print("maxVoltageLevel=  "); Serial.print(maxVoltageLevel);
      //Serial.print("i=  "); Serial.print(i);
      //Serial.print("  SetpointVoltage=  "); Serial.println(SetpointVoltage);
      runningTime = runningTime + stepTime;
      plotTime = runningTime + functionDuration * numberCycles;
      //Serial.print("plotTime=  "); Serial.println(plotTime);
      Setpoint = DACConvert(SetpointVoltage);
      DoDACOut();
      PlotVoltage();
    }
    numberCycles++;
  }
  on_OffFlag = 0;
  //myMenu.eraseDisplay(myDisplay);
  myDisplay.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);
}

/*****
   Purpose:Calculate Sine function
   Void
*****/
void DoSineCalc()
{
  //if (on_OffFlag == 1) {
  long runningTime = 0;
  long currentTime;
  long   currentSetpointValue;
  k = 0;
  GraphAxis();
  functionDataPrint ();
  int i;
  xTime = millis();
  numberCycles = 0;
  stepTime = functionDuration / numPlotPoints;
  while (numberCycles < numFunctionCycles) {
    i = 0;
    runningTime = 0;
    while (runningTime <= functionDuration and digitalRead(MENUENCODERSWITCH) != LOW) {
      i++;
      MyDelay(stepTime);
      float counter3 = (i * 2 * 3.14159 ) / (numPlotPoints);
      SetpointVoltage = startSetpointLevelVolts + (maxVoltageLevel - startSetpointLevelVolts) / 2 +  ((maxVoltageLevel - startSetpointLevelVolts) * cos(counter3 + 3.14159)) / 2;
      runningTime = runningTime + stepTime;
      plotTime = runningTime + functionDuration * numberCycles;
      Setpoint = DACConvert(SetpointVoltage);
      DoDACOut();
      PlotVoltage();
    }
    numberCycles++;
  }
  on_OffFlag = 0;
  //myMenu.eraseDisplay(myDisplay);
  myDisplay.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);
}

/*****
   Purpose:Calculate Step function
   Void
*****/
void DoStepCalc()
{
  on_OffFlag = 1;
  long runningTime = 0;
  long currentTime;
  long   currentSetpointValue;
  GraphAxis();
  int i;
  xTime = millis();
  numberCycles = 0;
  stepTime = functionDuration / numPlotPoints;
  while (numberCycles < numFunctionCycles) {
    i = 0;
    runningTime = 0;
    functionDataPrint ();
    myDisplay.setFont(&FreeSerif9pt7b);
    myDisplay.setTextColor(YELLOW, BLUE);
    myDisplay.setCursor(35, 100);
    myDisplay.print("# Steps");
    myDisplay.setCursor(140, 100);
    myDisplay.print(numberOfSteps);
    //if (on_OffFlag == 1) {
    numberCycles = 0;
    int i;

    while (numberCycles < numFunctionCycles) {
      i = 0;
      runningTime = 0;
      stepTime = functionDuration / (numPlotPoints);
      for (int stepIncrement = 0; stepIncrement <= numberOfSteps - 1; stepIncrement++) {

        runningTime = functionDuration * (stepIncrement) / numberOfSteps;
        while (runningTime <= functionDuration * (stepIncrement + 1) / numberOfSteps  and digitalRead(MENUENCODERSWITCH) != LOW) {
          Setpoint = DACConvert(maxVoltageLevel / numberOfSteps + (maxVoltageLevel / numberOfSteps) * stepIncrement);
          runningTime = runningTime + stepTime;
          plotTime = runningTime + functionDuration * numberCycles;
          DoDACOut();
          PlotVoltage();
          MyDelay(stepTime);
        }
      }
      numberCycles++;
    }
  }
  on_OffFlag = 0;
  //myMenu.eraseDisplay(myDisplay);
  myDisplay.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);
}


/*****
   Purpose:Calculate Half Sine function
   Void
*****/

void DoHalfSineCalc() {
  //if (on_OffFlag == 1) {
  long runningTime = 0;
  long currentTime;
  long   currentSetpointValue;
  k = 0;
  GraphAxis();
  functionDataPrint ();
  int i;
  xTime = millis();
  numberCycles = 0;
  stepTime = functionDuration / numPlotPoints;
  while (numberCycles < numFunctionCycles) {
    i = 0;
    runningTime = 0;
    while (runningTime <= functionDuration and digitalRead(MENUENCODERSWITCH) != LOW) {
      i++;
      currentTime = millis();
      MyDelay(stepTime);
      float counter3 = (((float)i) * 3.14159 ) / (numPlotPoints);
      SetpointVoltage = startSetpointLevelVolts +  (maxVoltageLevel - startSetpointLevelVolts) * abs(sin(counter3));
      runningTime = runningTime + stepTime;
      plotTime = runningTime + functionDuration * numberCycles;
      Setpoint = DACConvert(SetpointVoltage);
      DoDACOut();
      PlotVoltage();
    }
    numberCycles++;
  }
  // numberCycles = 0;
  on_OffFlag = 0;
  //myMenu.eraseDisplay(myDisplay);
  myDisplay.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);
}


/*****
   Purpose:Calculate Triangle function
   Void
*****/
void DoTriangleCalc() {

  //if (on_OffFlag == 1) {
  long runningTime = 0;
  long currentTime;
  long   currentSetpointValue;
  k = 0;
  GraphAxis();
  functionDataPrint ();
  int i;
  xTime = millis();
  numberCycles = 0;
  stepTime = functionDuration / (numPlotPoints);
  while (numberCycles < numFunctionCycles) {
    i = 0;
    runningTime = 0;
    while (runningTime <= (functionDuration) / 2 and digitalRead(MENUENCODERSWITCH) != LOW) {
      i = i + 2;
      currentTime = millis();
      MyDelay(stepTime);

      SetpointVoltage = startSetpointLevelVolts + ((maxVoltageLevel - startSetpointLevelVolts) / numPlotPoints) * i;
      //Serial.print("SetpointVoltage= "); Serial.println(SetpointVoltage);
      runningTime = runningTime + stepTime;
      //Serial.print("runningTime= "); Serial.println(runningTime);
      plotTime = runningTime + functionDuration * numberCycles;
      Setpoint = DACConvert(SetpointVoltage);
      DoDACOut();
      PlotVoltage();
    }
    runningTime = functionDuration / 2;
    i = 0;
    while (runningTime <= functionDuration and digitalRead(MENUENCODERSWITCH) != LOW) {
      i = i + 2;
      currentTime = millis();
      MyDelay(stepTime);

      SetpointVoltage = maxVoltageLevel - ((maxVoltageLevel - startSetpointLevelVolts) / numPlotPoints) * i;

      runningTime = runningTime + stepTime;
      //Serial.print("runningTime2= "); Serial.println(runningTime);
      plotTime = runningTime + functionDuration * numberCycles;
      Setpoint = DACConvert(SetpointVoltage);
      DoDACOut();
      PlotVoltage();
    }
    numberCycles++;
  }
  // numberCycles = 0;
  on_OffFlag = 0;
  //myMenu.eraseDisplay(myDisplay);
  myDisplay.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);
}



/*****
   Purpose:Calculate Trapazoid function
   Void
*****/
void DoTrapazoidCalc() {

  //if (on_OffFlag == 1) {
  long runningTime = 0;
  long currentTime;
  long   currentSetpointValue;
  k = 0;
  GraphAxis();
  functionDataPrint ();
  int i;
  xTime = millis();
  numberCycles = 0;
  stepTime = functionDuration / (numPlotPoints);
  while (numberCycles < numFunctionCycles) {
    i = 0;
    runningTime = 0;

    //Ramp Up
    while (runningTime <= (functionDuration) / 4 and digitalRead(MENUENCODERSWITCH) != LOW) {
      i = i + 4;
      currentTime = millis();
      MyDelay(stepTime);

      SetpointVoltage = startSetpointLevelVolts + ((maxVoltageLevel - startSetpointLevelVolts) / numPlotPoints) * i;
      //Serial.print("SetpointVoltage= "); Serial.println(SetpointVoltage);
      runningTime = runningTime + stepTime;
      //Serial.print("runningTime= "); Serial.println(runningTime);
      plotTime = runningTime + functionDuration * numberCycles;
      Setpoint = DACConvert(SetpointVoltage);
      DoDACOut();
      PlotVoltage();
    }

    //Max Voltage
    runningTime = functionDuration / 4;
    while (runningTime <= functionDuration / 2 and digitalRead(MENUENCODERSWITCH) != LOW) {

      Setpoint = DACConvert(maxVoltageLevel);
      runningTime = runningTime + stepTime;
      plotTime = runningTime + functionDuration * numberCycles;
      DoDACOut();
      PlotVoltage();
      MyDelay(stepTime);
    }

    // Ramp Down
    runningTime = functionDuration / 2;
    i = 0;
    while (runningTime <= functionDuration * 3 / 4 and digitalRead(MENUENCODERSWITCH) != LOW) {
      i = i + 4;
      currentTime = millis();
      MyDelay(stepTime);

      SetpointVoltage = maxVoltageLevel - ((maxVoltageLevel - startSetpointLevelVolts) / numPlotPoints) * i;

      runningTime = runningTime + stepTime;
      //Serial.print("runningTime2= "); Serial.println(runningTime);
      plotTime = runningTime + functionDuration * numberCycles;
      Setpoint = DACConvert(SetpointVoltage);
      DoDACOut();
      PlotVoltage();
    }
    //Min Voltage
    runningTime = functionDuration * 3 / 4;
    while (runningTime <= functionDuration and digitalRead(MENUENCODERSWITCH) != LOW) {

      Setpoint = DACConvert(startSetpointLevelVolts);
      runningTime = runningTime + stepTime;
      plotTime = runningTime + functionDuration * numberCycles;
      DoDACOut();
      PlotVoltage();
      MyDelay(stepTime);
    }
    numberCycles++;
  }
  // numberCycles = 0;
  on_OffFlag = 0;
  //myMenu.eraseDisplay(myDisplay);
  myDisplay.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);

}

/*****
   Purpose:Do Timer output function
        First set outout voltage using variabe output,
        then selct time and start with encoder 2 switch
        Time can be set using inputs for Hr, Min, Sec,  Will repeat number of times set for function repeat
   Void
*****/
void DoTimerVoltOut() {
  long timeCounter1 = 0;
  long lastMillis;

  int seconds = 0;
  int minutes = 0;
  int minutesOld = 0;
  int hours = 0;
  int hoursOld = 0;
  myDisplay.fillRect(0, 60, DISPLAYWIDTH, DISPLAYHEIGHT - 60, BLACK);
  int t1 = 0;

  outputOnOffFlag = 1;
  //Serial.print("in DoTimerVoltOut");
  MyDelay(100);
  myDisplay.setCursor(0, 80);
   myDisplay.setFont(&FreeSerif9pt7b);
  myDisplay.setTextColor(MAGENTA, BLACK);
  myDisplay.print("Adjust Voltage");
  myDisplay.setCursor(0, 100);
  myDisplay.print("Press Coarse To Start");
  myDisplay.setCursor(0, 120);
  myDisplay.print("Press Fine To Exit");
myDisplay.setCursor(240, 80);
 myDisplay.println("Time On:");
  myDisplay.setTextColor(YELLOW, BLACK);
 myDisplay.setCursor(260, 100);
  myDisplay.println("Seconds");
  myDisplay.setCursor(260, 120);
  myDisplay.println("Minutes");
    myDisplay.setCursor(260, 140);
  myDisplay.println("Hours");
  

 myDisplay.setCursor(370, 100);
  myDisplay.println(outTimeSec);
  myDisplay.setCursor(370, 120);
  myDisplay.println(outTimeMin);
    myDisplay.setCursor(370, 140);
  myDisplay.println(outTimeHour);

  
  //===============  Adjust Voltage
  while (1)  {
    encoderRead1();
    encoderRead3();
    Setpoint = encoder3Reading + encoder1Reading10 + numKeypad2 * setPointCal;
    DoDACOut();
    DoScreenPrintVoltage();
    if (digitalRead(COARSEENCODERSWITCH) == LOW) {
      break;
    }
  } //While

  lastMillis = millis();  //Set timer start
  long outTime =  1000 * outTimeSec + 60 * 1000 * outTimeMin + 60 * 60 * 1000 * outTimeHour;  //Setpoint for timer end
  long   tNow = millis();
  //Serial.println(outTime , DEC);
  myDisplay.setFont(&FreeSerif12pt7b);
  myDisplay.setTextColor(MAGENTA, BLACK);

  myDisplay.setTextSize(2);
  myDisplay.setCursor(165, 220);
  myDisplay.print("h      m      s");
  myDisplay.setTextColor(WHITE, BLACK);
  myDisplay.drawRect(85,165,320,80, GREEN);
  outputOnOffFlag = 1;
  while ((millis() - tNow ) <= outTime) {  //Timed loop

    //while (millis() - lastMillis != 1000) //1000 ms - 1-sec  //One sec counter
    // ;

    lastMillis = millis();    //shft current time
    seconds++;
    minutes=seconds/60;
    hours=seconds/3600;
    //Serial.print("minutes=  "); Serial.print(minutes); Serial.print("  seconds=  "); Serial.println(seconds % 60);
    //=========== seconds ==========
    myDisplay.fillRect(312, 185, 52, 40, BLACK);
    if (seconds % 60 < 10) {
      myDisplay.setCursor(333, 220);
    }
    else
    {
      if (seconds % 60 >= 10)
      {
        myDisplay.setCursor(313, 220);
      }
    }
    myDisplay.print(seconds % 60);
    //=========== minutes ==========

    if (minutes != minutesOld)
    {
      myDisplay.fillRect(200, 185, 52, 40, BLACK);
      if (minutes % 60 < 10) {
        myDisplay.setCursor(222, 220);
      }
      else
      {
        if (minutes % 60 >= 10)
        {
          myDisplay.setCursor(202, 220);
        }
      }
      myDisplay.print(minutes % 60);
      minutesOld = minutes;
    }
    
    // ========= hours =============
    if (hours != hoursOld)
    {
      myDisplay.fillRect(103, 185, 52, 40, BLACK);

      if (hours%24 < 10) {
        myDisplay.setCursor(125, 220);
      }
      else
      {
        if (hours%24 >= 10)
        {
          myDisplay.setCursor(105, 220);
        }
      }
      myDisplay.print(hours%24);
      hoursOld = hours;
    }
 






    if (outputOnOffFlag == 0) {
      break;
    }

  }  //---while
  outputOnOffFlag = 0;
  Setpoint = 0; // Set the voltage to zeroo
  myDisplay.setTextSize(1);
  myDisplay.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);

}


/*****
  Purpose:Do Pulse output function
      First set outout voltage using variabe output,
      then selct time and start with encoder 2 switch
      Time can be set using inputs for Hr, Min, Sec,  Will repeat number of times set for function repeat
  Void
*****/
void DoPulseOut ()
{
  //if (on_OffFlag == 1) {
  long runningTime = 0;
  long currentTime;
  long   currentSetpointValue;
  k = 0;
  GraphAxis();
  functionDataPrint ();
  myDisplay.setTextColor(YELLOW, BLUE);
  myDisplay.setCursor(35, 102);
  myDisplay.print("Pulse Width");
  myDisplay.setTextColor(WHITE, BLUE);
  myDisplay.setCursor(160, 102);
  myDisplay.print(pulseTopWidth);
  int i;
  xTime = millis();
  numberCycles = 0;
  stepTime = functionDuration / (numPlotPoints);
  while (numberCycles < numFunctionCycles) {
    i = 0;
    runningTime = 0;
    //Max Voltage
    //runningTime = functionDuration  /(pulseTopWidth*numPlotPoints);
    while (runningTime <= pulseTopWidth and digitalRead(MENUENCODERSWITCH) != LOW) {

      Setpoint = DACConvert(maxVoltageLevel);
      runningTime = runningTime + stepTime;
      plotTime = runningTime + (functionDuration * numberCycles);
      DoDACOut();
      PlotVoltage();
      MyDelay(stepTime);
    }


    //Min Voltage
    runningTime = pulseTopWidth;
    while (runningTime <= functionDuration - pulseTopWidth and digitalRead(MENUENCODERSWITCH) != LOW) {

      Setpoint = DACConvert(startSetpointLevelVolts);
      runningTime = runningTime + stepTime;
      plotTime = runningTime + functionDuration * numberCycles;
      DoDACOut();
      PlotVoltage();
      MyDelay(stepTime);
    }
    numberCycles++;
  }
  // numberCycles = 0;
  on_OffFlag = 0;
  //myMenu.eraseDisplay(myDisplay);
  myDisplay.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);
}



/*****
    Purpose: To Output the Setpoint to the DAC
  Paramter list: void
  Return value:  void
*****/
void DoDACOut() {
  if (outputOnOffFlag == 1)
  {
    PWMSet = Setpoint;
    if (outputOnOffFlagOld != outputOnOffFlag)
    {
      myDisplay.drawRect(2, 5, 55, 55, CYAN); // Draw display area outline
      myDisplay.fillRect(4, 6, 50, 40, BLACK);
      myDisplay.setCursor(5, 42);
      myDisplay.setTextColor(GREEN, BLACK);
      myDisplay.print("ON");
      outputOnOffFlagOld = 1;
    }
  }
  else {
    if (outputOnOffFlag == 0)
    {
      PWMSet = 0;
      if (outputOnOffFlagOld != outputOnOffFlag)
      {
        myDisplay.fillRect(4, 6, 50, 50, BLACK);
        myDisplay.setCursor(5, 42);
        myDisplay.setTextColor(RED, BLACK);
        myDisplay.print("OFF");
        outputOnOffFlagOld = 0;
      }
    }
  }
  // }
  //Serial.print("PWMSet=  "); Serial.println(PWMSet);
  dac.setVoltage(PWMSet, false);
  encoder1Reading = encoder1Reading10 / 10;
  if (encoder1Reading10 >= 40000) {
    encoder1Reading = 4000;
  }
  else
  {
    encoder1Reading = encoder1Reading10 / 10;
  }
  //Serial.print("outputOnOffFlag  "); Serial.println(outputOnOffFlag);
  //Serial.print("outputOnOffFlagOld  "); Serial.println(outputOnOffFlagOld);
  //Serial.print("encoderReading  "); //Serial.println(encoder1Reading);
  int i, flag, len, oldIndex;
  int val;
  float x, y;
}
/*****
   Purpose:Screen Print Function Data

   Void
*****/
void functionDataPrint () {
  myDisplay.setFont(&FreeSerif9pt7b);
  myDisplay.setTextColor(YELLOW, BLUE);
  myDisplay.setCursor(35, 28);
  myDisplay.print("Start V: ");
  myDisplay.setCursor(35, 46);
  myDisplay.print("End V: ");
  myDisplay.setCursor(35, 65);
  myDisplay.print("Time(ms) / cycle: ");
  myDisplay.setCursor(35, 82);
  myDisplay.print("# Cycles");
  myDisplay.setTextColor(WHITE, BLUE);
  myDisplay.setCursor(200, 28);
  myDisplay.print(startSetpointLevelVolts);
  myDisplay.setCursor(200, 46);
  myDisplay.print(maxVoltageLevel);
  myDisplay.setCursor(200, 64);
  myDisplay.print(functionDuration);
  myDisplay.setCursor(200, 82);
  myDisplay.print(numFunctionCycles);
}
//=============================  End of output Waveform Functions ===========
