#ifndef BEENHERE
#include "ProgPS.h"
#endif
#include <Arduino.h>
int filePosition;

/*****
  Purpose: To read the most-recent scan data to a CSV data file

  Parameter list:
    long *freqX1      base of array for SWR
    float *valuePoint1     base of array for frequency
  Return value: int  the number of data pairs read
*****/
void ReadDataFile() 
{
  int  edge2 = 0;
  edge2 = filePosition;
  //Serial.print("edge2= "); Serial.println(edge2);
  SD.begin(PA4);
  myFile = SD.open(mySDFiles[edge2]);
  char temp;
  char buff[10];
  int i = 0;
  voltIndex = 0;

  while (myFile.available() ) 
  {
    buff[i] = myFile.read();
    if (buff[i] == '#')
    {
      myFile.close();
    }
    if (buff[i] != ',' && buff[i] != '\n')
    {
      i++;
    }
    else
    {
      if (buff[i] == ',')
      { // Read data
        buff[i] = '\0';
        yVoltValue[voltIndex] = atoi(buff);
        i = 0;
      }
      else
      {
        buff[i] = '\0';
        xTimeValue[voltIndex] = atoi(buff);
        voltIndex++;
        i = 0;
      }
    }
  }
}


/*****
  Purpose: To present a list of the current SD files

  Parameter list:
    void

  Return value:
    int           the number of files on the SD card
*****/
int ShowFiles() 
{
  int sCounter = 0;
  yOffset = TOPMARGIN + 25;
  myDisplay.setFont(&FreeSerif9pt7b);
  myDisplay.setTextColor(GREEN, BLACK);
  root = SD.open("/");
  root.rewindDirectory();        // Begin at the start of the directory

  while (true) {
    File entry =  root.openNextFile();
    if (entry.isDirectory()) {
      sCounter--;
    }
    if (! entry) {
      entry.close();
      break;
    }
    strcpy(mySDFiles[sCounter++],  entry.name());
    entry.close();
  }

  strcpy(mySDFiles[sCounter],  "Exit");
  for (k = 0; k <= sCounter; k++) {
    myDisplay.setCursor(LEFTMARGIN + 80, yOffset + k * 18);
    myDisplay.print(mySDFiles[k]);
  }

  myDisplay.setCursor(160, 80);
  myDisplay.print("SD files:");

  myDisplay.setCursor(160, yOffset + (k - 1) * 18);
  myDisplay.print("List Done!");
  root.close();
  return (sCounter);
}



/*****
  Purpose: To select a file from a list of the current SD files

  Parameter list:
    void

  Return value:
    int           an index into the file name array for the file to be used
*****/
int SelectFile()
{
  filePosition = 0;
  filesSD = ShowFiles();
  myDisplay.setFont(&FreeSerif9pt7b);
  myDisplay.setTextColor(GREEN, WHITE);
  for (int k = 0; k <= filesSD; k++) {
    myDisplay.setCursor(LEFTMARGIN + 80, yOffset + k * 18);
    myDisplay.print(mySDFiles[k]);
  }
  myDisplay.setTextColor(CYAN, WHITE);
  myDisplay.setCursor(LEFTMARGIN + 80, yOffset);
  myDisplay.print(mySDFiles[0]);
  while (digitalRead(MENUENCODERSWITCH) != LOW) {// Wait for encoder switch change
    //Serial.println("in while");

    if (en2State == 1)           // If it has rotated...
    {
      filePosition = encoder2 + filePosition;
      if (mySDFiles[filePosition] == "Exit") {
        Serial.println(mySDFiles[filePosition]);
        myDisplay.fillRect(0, 68, DISPLAYWIDTH, 232, BLACK);
        break;
      }
      if (filePosition > filesSD + 1) filePosition = 0;
      if (filePosition < 0) filePosition = filesSD + 1;
      MyDelay(100);
      myDisplay.setTextColor(GREEN, WHITE);
      for (int k = 0; k <= filesSD; k++) {
        myDisplay.setCursor(LEFTMARGIN + 80, yOffset + k * 18);
        myDisplay.print(mySDFiles[k]);
      }
      //Serial.print("filePosition = ");Serial.println(filePosition);

      myDisplay.setTextColor(CYAN, WHITE);
      myDisplay.setCursor(LEFTMARGIN + 80, yOffset + filePosition * 18);
      myDisplay.print(mySDFiles[filePosition]);
      //en2State = 0;
    }
    en2State = 0;
  }
  return filePosition;    // The index for the file name
}
/*****
  Purpose: Graph

  Parameter list:
    void

  Return value:
    int           an index into the file name array for the file to be used
*****/
void GraphSDData () {
  myDisplay.fillRect(0, 68, DISPLAYWIDTH, 252, BLACK);
  myDisplay.fillRect(30, 70, 450, 230, DARKVIOLET); //Fill plot area with BLUE
  myDisplay.drawRect(30, 70, 450, 230, GREEN); // Draw graph area outline
  myDisplay.setFont(&FreeSerif9pt7b);
  myDisplay.setTextColor(YELLOW);
  myDisplay.setCursor(0, 80);
  myDisplay.print("30");
  myDisplay.setCursor(0, DISPLAYHEIGHT - DISPLAYHEIGHT / 20);
  myDisplay.print("0");
  myDisplay.drawLine(30, DISPLAYHEIGHT / 1.067, 30, DISPLAYHEIGHT / 1.0345, GREEN);
  myDisplay.drawLine(143, DISPLAYHEIGHT / 1.067, 143, DISPLAYHEIGHT / 1.0345, GREEN);
  myDisplay.drawLine(255, DISPLAYHEIGHT / 1.067, 255, DISPLAYHEIGHT / 1.0345, GREEN);
  myDisplay.drawLine(368, DISPLAYHEIGHT / 1.067, 368, DISPLAYHEIGHT / 1.0345, GREEN);
  myDisplay.drawLine(479, DISPLAYHEIGHT / 1.067, 479, DISPLAYHEIGHT / 1.0345, GREEN);
  myDisplay.setTextColor(GREEN);
  myDisplay.setCursor(DISPLAYWIDTH / 16, DISPLAYHEIGHT / 1.0042);
  myDisplay.print("0");
  myDisplay.setCursor(450, DISPLAYHEIGHT / 1.0042);
  myDisplay.print("120");
  for (int i = 0; i <= 6; i++) {
    myDisplay.drawLine(DISPLAYWIDTH / 26.67, 70 + 38 * i, DISPLAYWIDTH / 16 , 70 + 38 * i, GREEN);
  }
  myDisplay.setTextColor(CYAN, WHITE);
  myDisplay.setCursor(60, yOffset + 20);
  myDisplay.print(mySDFiles[filePosition]);
  int yDelay;
  long xTimeValueTotal;
  xTimeValueTotal = 0;
  xPositionOld = 0;
  yPositionOld = 300;
  for (int j = 0; j <= voltIndex - 1; j++) {
    Setpoint = DACConvert(yVoltValue[j]);
    DoDACOut();
    MyDelay(xTimeValue[j] * 1000);
    DoScreenPrintVoltage();
    long xPosition;
    xTimeValueTotal = xTimeValueTotal + xTimeValue[j];
    xPosition = xTimeValueTotal * DISPLAYWIDTH / 120;
    float voltIn2 = ((float)analogRead(PA3) / 4096) * 30.1;
    long voltIn10 = voltIn2 * 10 ;
    long yPosition = map(voltIn10, 0, 280 , 300, 90);

    myDisplay.drawLine(xPositionOld + 30, yPositionOld, xPositionOld + 30, yPosition, WHITE);
    myDisplay.drawLine(xPositionOld + 30, yPosition, xPosition + 30, yPosition, WHITE);
    myDisplay.drawLine(xPositionOld + 31, yPositionOld + 1, xPositionOld + 31, yPosition + 1, WHITE);
    myDisplay.drawLine(xPositionOld + 31, yPosition + 1, xPosition + 31, yPosition + 1, WHITE);

    xPositionOld = xPosition;
    yPositionOld = yPosition;
    k++;
    if (k >= 445) {
      k = 0;
      myDisplay.fillRect(DISPLAYWIDTH / 16, DISPLAYHEIGHT / 32, DISPLAYWIDTH / 1.07, DISPLAYHEIGHT - DISPLAYHEIGHT / 11, BLUE); //Fill plot area with BLUE
      myDisplay.drawRect(DISPLAYWIDTH / 16, DISPLAYHEIGHT / 32, DISPLAYWIDTH / 1.07, DISPLAYHEIGHT - DISPLAYHEIGHT / 11, GREEN); // Draw graph area outline
    }
    yTime = millis();
    myDisplay.setFont(&FreeSerif12pt7b);
    myDisplay.setTextColor(WHITE);

  }
  myDisplay.fillRect(0, 68, DISPLAYWIDTH, 252, BLACK);
}
