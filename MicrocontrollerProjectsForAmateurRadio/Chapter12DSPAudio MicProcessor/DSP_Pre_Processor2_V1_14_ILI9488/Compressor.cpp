#ifndef BEENHERE
#include "Pre.h"
#endif

void SetCompressorPrameters() {
  pageFlag = 2;
  tft.setTextColor(iLI9488_WHITE);
  //int setFlag = 0;
  buttonNumber2 = 10;
  while (digitalRead(FREQENCODERSWITCH) != LOW) {

    freqISR();
    SecondEncoderISR();
    float thresh1Old;
    float thresh2Old;
    float micGainSetOld;
    float compGainOld;
    freqBand = freqBand +  freqEncoderMovement;
    //thresh1 = .4;       // Upper threshold
    //thresh2 = .05;      // Lower threshold
    //compGain = 30;


    boolean istouched = false;
    int j = 0;
    istouched = ts.touched();
    if (istouched) {
      long x1 = 0;
      long y1 = 0;
      for (int k = 1; k < 11; k++) {
        TS_Point p = ts.getPoint();
        delay(5);
        x1 = x1 + p.x;
        y1 = y1 + p.y;
      }
      xx = map(x1, 4000, 39000, 0, 320);
      yy = map(y1, 2800, 38000, 0, 240);
      if (xx < BOXSPACEX) {
        for (j = 0; j < 4; j++) {     //parameter buttons read
          if ((yy > 51 + BOXSPACEY * j) and yy < (51 + BOXSIZEY + BOXSPACEY * j) and pageFlag == 2) {
            istouched = false;
            buttonNumber2 = j;
          }
        }
      }
      //on/off button read
      if ((xx > BOXSPACEX * 3) and xx < (BOXSPACEX * 3 + BOXSIZEX - 6) and yy < BOXSIZEY + 1 and compFlag == 1) {
        buttonNumber2 = 4;
      }
      if ((xx > BOXSPACEX * 4) and xx < (BOXSPACEX * 4 + BOXSIZEX - 6) and yy < BOXSIZEY + 1 and compFlag == 1) {
        buttonNumber2 = 5;
      }

      switch (buttonNumber2) {
        case 0:  //Thresh1
          tft.setCursor(150, 51 + (BOXSPACEY) * buttonNumber2 );
          tft.drawRect(135, 42 + (BOXSPACEY) * buttonNumber2, 50, 28, iLI9488_BLUE);
          while (1) {
            freqISR();
            thresh1 = thresh1 + ((float)freqEncoderMovement) / 20;     // Upper threshold
            if (thresh1 > 1) thresh1 = 1;
            if (thresh1 < .01) thresh1 = .01;
            tft.setCursor(150, 51 + (BOXSPACEY) * buttonNumber2 );
            if (thresh1Old != thresh1) {
              tft.fillRect(136, 43 + (BOXSPACEY) * buttonNumber2, 48, 26, iLI9488_BLACK);

              tft.print(thresh1);
              thresh1Old = thresh1;
            }
            freqEncoderMovement = 0;
//=======================
            boolean istouched = false;
            //int j = 0;
            istouched = ts.touched();  //Set Button
            if (istouched) {
              long x1 = 0;
              long y1 = 0;
              for (int k = 1; k < 11; k++) {
                TS_Point p = ts.getPoint();
                delay(5);
                x1 = x1 + p.x;
                y1 = y1 + p.y;
              }
              xx = map(x1, 4000, 39000, 0, 320);
              yy = map(y1, 2800, 38000, 0, 240);
              if ((yy > 51 + BOXSPACEY * 4) and yy < (51 + BOXSIZEY + BOXSPACEY * 4) ) {
                tft.setTextColor(iLI9488_BLACK);
                tft.fillRoundRect(compButtons[4].tx + 1, compButtons[4].ty + 12, compButtons[4].ww + 20 , compButtons[4].hh, 5, iLI9488_WHITE);
                tft.drawRoundRect(compButtons[4].tx, compButtons[4].ty + 11, compButtons[4].ww + 20, compButtons[4].hh, 5, iLI9488_WHITE);
                tft.setCursor(16, 51 + BOXSPACEY * 4 );
                tft.print(CompButtonNames[4]);
                delay(500);
                tft.fillRoundRect(compButtons[4].tx + 1, compButtons[4].ty + 12, compButtons[4].ww + 20 , compButtons[4].hh, 5, iLI9488_MAROON);
                tft.drawRoundRect(compButtons[4].tx, compButtons[4].ty + 11, compButtons[4].ww + 20, compButtons[4].hh, 5, iLI9488_WHITE);
                tft.setCursor(16, 51 + BOXSPACEY * 4 );
                tft.setTextColor(iLI9488_WHITE);
                tft.print(CompButtonNames[4]);

                istouched = false;
                tft.setCursor(150, 51 + (BOXSPACEY) * 4 );
                tft.print("Set");
                delay(1500);
                tft.fillRect(149, 50 + (BOXSPACEY) * 4, 50, 20, iLI9488_BLACK);
                tft.drawRect(135, 42 + (BOXSPACEY) * buttonNumber2, 50, 28, iLI9488_BLACK);
                buttonNumber2 = 10;
                break;
                break;
              }

            }
          }

          break;
        case 1: // Thresh2
          tft.setCursor(150, 51 + (BOXSPACEY) * buttonNumber2 );
          tft.drawRect(135, 42 + (BOXSPACEY) * buttonNumber2, 50, 28, iLI9488_BLUE);
          while (1) {
            freqISR();
            thresh2 = thresh2 + ((float)freqEncoderMovement) / 50;     // Upper threshold
            if (thresh2 > 1) thresh2 = 1;
            if (thresh2 < .01) thresh2 = .01;
            tft.setCursor(150, 51 + (BOXSPACEY) * buttonNumber2 );
            if (thresh2Old != thresh2) {
              tft.fillRect(136, 43 + (BOXSPACEY) * buttonNumber2, 48, 26, iLI9488_BLACK);

              tft.print(thresh2);
              thresh2Old = thresh2;
            }
            freqEncoderMovement = 0;

            boolean istouched = false;  //Set Button
           // int j = 0;
            istouched = ts.touched();
            if (istouched) {
              long x1 = 0;
              long y1 = 0;
              for (int k = 1; k < 11; k++) {
                TS_Point p = ts.getPoint();
                delay(5);
                x1 = x1 + p.x;
                y1 = y1 + p.y;
              }
              xx = map(x1, 4000, 39000, 0, 320);
              yy = map(y1, 2800, 38000, 0, 240);
              if ((yy > 51 + BOXSPACEY * 4) and yy < (51 + BOXSIZEY + BOXSPACEY * 4) ) {
                tft.setTextColor(iLI9488_BLACK);
                tft.fillRoundRect(compButtons[4].tx + 1, compButtons[4].ty + 12, compButtons[4].ww + 20 , compButtons[4].hh, 5, iLI9488_WHITE);
                tft.drawRoundRect(compButtons[4].tx, compButtons[4].ty + 11, compButtons[4].ww + 20, compButtons[4].hh, 5, iLI9488_WHITE);
                tft.setCursor(16, 51 + BOXSPACEY * 4 );

                tft.print(CompButtonNames[4]);
                delay(500);
                tft.fillRoundRect(compButtons[4].tx + 1, compButtons[4].ty + 12, compButtons[4].ww + 20 , compButtons[4].hh, 5, iLI9488_MAROON);
                tft.drawRoundRect(compButtons[4].tx, compButtons[4].ty + 11, compButtons[4].ww + 20, compButtons[4].hh, 5, iLI9488_WHITE);
                tft.setCursor(16, 51 + BOXSPACEY * 4 );
                tft.setTextColor(iLI9488_WHITE);
                tft.print(CompButtonNames[4]);


                istouched = false;
                tft.setCursor(150, 51 + (BOXSPACEY) * 3 );
                tft.print("Set");
                delay(1500);
                tft.fillRect(149, 50 + (BOXSPACEY) * 3, 50, 20, iLI9488_BLACK);
                tft.drawRect(135, 42 + (BOXSPACEY) * buttonNumber2, 50, 28, iLI9488_BLACK);
                buttonNumber2 = 10;
                break;
                break;
              }

            }
          }

          break;
        case 2: // Mic Gain
          tft.setCursor(150, 51 + (BOXSPACEY) * buttonNumber2 );
          tft.drawRect(135, 42 + (BOXSPACEY) * buttonNumber2, 50, 28, iLI9488_BLUE);
          while (1) {
            freqISR();
            micGainSet = micGainSet + ((float)freqEncoderMovement);     // Upper threshold
            if (micGainSet > 50) micGainSet = 50;
            if (micGainSet < .0) micGainSet = .0;
            tft.setCursor(150, 51 + (BOXSPACEY) * buttonNumber2 );
            if (micGainSetOld != micGainSet) {
              tft.fillRect(136, 43 + (BOXSPACEY) * buttonNumber2, 48, 26, iLI9488_BLACK);

              tft.print(micGainSet);
              micGainSetOld = micGainSet;
            }
            freqEncoderMovement = 0;

            boolean istouched = false;
            //int j = 0;
            istouched = ts.touched();
            if (istouched) {          //SetButton
              long x1 = 0;
              long y1 = 0;
              for (int k = 1; k < 11; k++) {
                TS_Point p = ts.getPoint();
                delay(5);
                x1 = x1 + p.x;
                y1 = y1 + p.y;
              }
              xx = map(x1, 4000, 39000, 0, 320);
              yy = map(y1, 2800, 38000, 0, 240);
              if ((yy > 51 + BOXSPACEY * 4) and yy < (51 + BOXSIZEY + BOXSPACEY * 4) ) {  //Set Button
                tft.setTextColor(iLI9488_BLACK);
                tft.fillRoundRect(compButtons[4].tx + 1, compButtons[4].ty + 12, compButtons[4].ww + 20 , compButtons[4].hh, 5, iLI9488_WHITE);
                tft.drawRoundRect(compButtons[4].tx, compButtons[4].ty + 11, compButtons[4].ww + 20, compButtons[4].hh, 5, iLI9488_WHITE);
                tft.setCursor(16, 51 + BOXSPACEY * 4 );

                tft.print(CompButtonNames[4]);
                delay(500);
                tft.fillRoundRect(compButtons[4].tx + 1, compButtons[4].ty + 12, compButtons[4].ww + 20 , compButtons[4].hh, 5, iLI9488_MAROON);
                tft.drawRoundRect(compButtons[4].tx, compButtons[4].ty + 11, compButtons[4].ww + 20, compButtons[4].hh, 5, iLI9488_WHITE);
                tft.setCursor(16, 51 + BOXSPACEY * 4 );
                tft.setTextColor(iLI9488_WHITE);
                tft.print(CompButtonNames[4]);

                sgtl5000_1.micGain(micGainSet);
                istouched = false;
                tft.setCursor(150, 51 + (BOXSPACEY) * 4 );
                tft.print("Set");
                delay(1500);
                tft.fillRect(149, 50 + (BOXSPACEY) * 4, 50, 20, iLI9488_BLACK);
                tft.drawRect(135, 42 + (BOXSPACEY) * buttonNumber2, 50, 28, iLI9488_BLACK);
                buttonNumber2 = 10;
                break;
                break;
              }

            }
          }

          break;


case 3: // Input Select
          sgtl5000_1.muteHeadphone();
          sgtl5000_1.muteLineout();
          tft.setCursor(150, 51 + (BOXSPACEY) * buttonNumber2 );
          tft.drawRect(135, 42 + (BOXSPACEY) * buttonNumber2, 70, 28, iLI9488_BLUE);
          myInputOld= AUDIO_INPUT_MIC;
          while (1) {

            freqISR();
            compInputSet = compInputSet + freqEncoderMovement;     // Upper threshold
            if (compInputSet > 1) compInputSet = 0;
            if (compInputSet < 0) compInputSet = 1;

            if (compInputSet == 1) {
              myInput = AUDIO_INPUT_LINEIN;
             
              if (myInput != myInputOld) {
                tft.setCursor(150, 51 + (BOXSPACEY) * buttonNumber2 );
                tft.fillRect(136, 43 + (BOXSPACEY) * buttonNumber2, 48, 26, iLI9488_BLACK);
                tft.print("Line");
                tft.setTextColor(iLI9488_YELLOW);
                tft.fillRect(285, 1, 30, 15, iLI9488_BLACK);
                tft.setCursor(286, 4);
                tft.print("Line");
              }
              myInputOld = myInput;
              sgtl5000_1.inputSelect(myInput);
            }
            else {
              myInput = AUDIO_INPUT_MIC;
              
              if (myInput != myInputOld) {
                tft.setCursor(150, 51 + (BOXSPACEY) * buttonNumber2 );
                tft.fillRect(136, 43 + (BOXSPACEY) * buttonNumber2, 48, 26, iLI9488_BLACK);
                tft.print("Mic");
                tft.fillRect(285, 1, 30, 15, iLI9488_BLACK);
                tft.setTextColor(iLI9488_YELLOW);
                tft.setCursor(286, 4);
                tft.print("Mic");
              }
              myInputOld = myInput;
            }


            //const int myInput = AUDIO_INPUT_LINEIN;
            //const int myInput = AUDIO_INPUT_MIC;


            //tft.setCursor(150, 51 + (BOXSPACEY) * buttonNumber2 );

            //  tft.fillRect(136, 43 + (BOXSPACEY) * buttonNumber2, 48, 26, iLI9488_BLACK);

            // tft.print(myInput);


            freqEncoderMovement = 0;
            //===================
            boolean istouched = false;
           // int j = 0;
            istouched = ts.touched();
            if (istouched) {          //SetButton
              long x1 = 0;
              long y1 = 0;
              for (int k = 1; k < 11; k++) {
                TS_Point p = ts.getPoint();
                delay(5);
                x1 = x1 + p.x;
                y1 = y1 + p.y;
              }
              xx = map(x1, 4000, 39000, 0, 320);
              yy = map(y1, 2800, 38000, 0, 240);
              if ((yy > 51 + BOXSPACEY * 4) and yy < (51 + BOXSIZEY + BOXSPACEY * 4) ) {  //Set Button
                tft.setTextColor(iLI9488_BLACK);
                tft.fillRoundRect(compButtons[4].tx + 1, compButtons[4].ty + 12, compButtons[4].ww + 20 , compButtons[4].hh, 5, iLI9488_WHITE);
                tft.drawRoundRect(compButtons[4].tx, compButtons[4].ty + 11, compButtons[4].ww + 20, compButtons[4].hh, 5, iLI9488_WHITE);
                tft.setCursor(16, 51 + BOXSPACEY * 4 );

                tft.print(CompButtonNames[4]);
                delay(500);
                tft.fillRoundRect(compButtons[4].tx + 1, compButtons[4].ty + 12, compButtons[4].ww + 20 , compButtons[4].hh, 5, iLI9488_MAROON);
                tft.drawRoundRect(compButtons[4].tx, compButtons[4].ty + 11, compButtons[4].ww + 20, compButtons[4].hh, 5, iLI9488_WHITE);
                tft.setCursor(16, 51 + BOXSPACEY * 4 );
                tft.setTextColor(iLI9488_WHITE);
                tft.print(CompButtonNames[4]);

                sgtl5000_1.inputSelect(myInput);
                istouched = false;
                tft.setCursor(150, 51 + (BOXSPACEY) * 4 );
                tft.print("Set");
                delay(1500);
                tft.fillRect(149, 50 + (BOXSPACEY) * 4, 50, 20, iLI9488_BLACK);
                tft.drawRect(135, 42 + (BOXSPACEY) * buttonNumber2, 70, 28, iLI9488_BLACK);
                buttonNumber2 = 10;
                break;
                break;
              }

            }

          }
          sgtl5000_1.inputSelect(myInput);
          sgtl5000_1.unmuteHeadphone();
          sgtl5000_1.unmuteLineout();
          
          break;
        case 4: //on
          tft.fillRect(254, 17, 63, 17, iLI9488_BLACK);
          tft.setCursor(255, 18);
          tft.print("Comp");
          compressorFlag = 1;              //Turn on Compressor
          break;
        case 5: //Off
          tft.fillRect(254, 16, 63, 17, iLI9488_BLACK);
          //tft.setCursor(255, 18);
          //tft.print("Comp");
          compressorFlag = 0;              //Turn off Compressor
          break;
      }
    }
  }

}

void compressor() {

  if (peak_L.available()) {
    delay(1);
    leftPeak =  peak_L.read();

    //Serial.print("leftPeak= "); Serial.println(leftPeak);

    //-------------------------  Lower Threshold
    if (leftPeak <= thresh1) {
      compGain = 1.;
      range = 0;
      timeConstant = 0;               //Initial fast attack
      tiny = 1;
      numCount = 2;
    }
    //-------------------------   Linear gain region
    if (leftPeak <= thresh1 and leftPeak > thresh2) {
      range = 1;
      timeConstant = 50;
      tiny = .05;

      numCount = 20;
    }
    //-----------------------     Upper Threshold
    if (leftPeak > thresh1) {
      range = 2;
    }
    //-----------------------


    leftPeakOld = leftPeak;                  // Previous measured peak level for attack & decay
    //Serial.print("range= "); Serial.println(range);
    switch (range) {
      case 0:                                // Lower Compressed level - slight slope
        compGain = (thresh2 / leftPeak) * (1 - b) + b;
        if (compGain > 10) {
          compGain = 10;
        }
        break;
      case 1:                                 // Middle linear gain region
        compGain = 1.0;
        break;
      case 2:                                 // Upper hard limiter - flat top
        compGain = (thresh1 / leftPeak);
        delay(2);
        break;
    }
    //Serial.print("compGain= "); Serial.println(compGain);
    for (int i = 0; i < numCount; i++) {
      float ratio = (float)i / numCount;
      compGain1 = compGainFinalOld + (compGain - compGainFinalOld) * ratio;
      //Serial.print("compGain1= "); Serial.println(compGain1);
      //Serial.println(" ");
      // Serial.print("compGainFinalOld= "); Serial.println(compGainFinalOld);
      delay(timeConstant);

      CompMix.gain(0, compGain1);
      compGainFinalOld = compGain1;
    }
    //compGainFinalOld = compGain1;
  }
}
