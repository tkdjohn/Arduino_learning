/*****
  This software is licensed un the GNU General Public License, Version 3, as presetned in
  https://www.gnu.org/licenses/gpl-3.0.txt. You may use this software for non-commercial use. 
  For commercial use, contact the authors:
  Jack Purdum, W8TEE
  Al Peter, AC8GY

  This header file must be copied into all copies and deriviative works of this software
  and remain the very first thing in the primary source code file.
  
*****/

//                              Compiloe with Teensy 4.0 or 4.1
/***************************************************
  This is our touchscreen painting example for the Adafruit iLI9488 Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#ifndef BEENHERE
#include "Pre.h"




long unsigned TS_usVal = 50000; // POLL rate from the timer interrupt on Touch Detect

XPT2046_Touchscreen ts(T_CS_PIN, TIRQ_PIN);
//iLI9488_t3 tft = iLI9488_t3(TFT_CS, TFT_DC);
ILI9488_t3 tft = ILI9488_t3(&SPI, TFT_CS, TFT_DC, TFT_RST);
Rotary rotaryFreq   = Rotary( (uint8_t) FREQENCODERPINA, (uint8_t) FREQENCODERPINB);
Rotary rotarySecond = Rotary( (uint8_t) SECONDENCODERPINB, (uint8_t) SECONDENCODERPINA);

AudioControlSGTL5000     sgtl5000_1;
AudioInputI2S            audioInput;
AudioAnalyzePeak         peak_L;
AudioEffectReverb        reverb1;

AudioAnalyzeFFT1024      fft1024_1;
AudioFilterBiquad        EQ_1;       //
AudioFilterBiquad        EQ_3;       //
AudioFilterBiquad        EQ_2;       //
AudioFilterBiquad        EQ_4;       //
AudioFilterBiquad        EQ_5;       //
AudioFilterBiquad        EQ_6;       //
AudioFilterBiquad        EQ_7;       //
AudioFilterBiquad        EQ_8;
AudioMixer4              CompMix;
//AudioMixer4              M1;
AudioMixer4              M4;
AudioMixer4              EQ_Mix1;
AudioMixer4              EQ_Mix2;
AudioMixer4              EQ_Mix3;
AudioOutputI2S           audioOutput;  // audio shield: headphones & line-out

AudioConnection          patchCordc1(audioInput, 0, peak_L, 0);
AudioConnection          patchCordc2(audioInput, 0, CompMix, 0);
AudioConnection          patchCord1(CompMix, 0, EQ_1, 0);
AudioConnection          patchCord2(CompMix, 0, EQ_2, 0);
AudioConnection          patchCord3(CompMix, 0, EQ_3, 0);
AudioConnection          patchCord4(CompMix, 0, EQ_4, 0);
AudioConnection          patchCord5(CompMix, 0, EQ_5, 0);
AudioConnection          patchCord6(CompMix, 0, EQ_6, 0);
AudioConnection          patchCord7(CompMix, 0, EQ_7, 0);
AudioConnection          patchCord8(CompMix, 0, EQ_8, 0);
AudioConnection          patchCord9(EQ_1, 0, EQ_Mix1, 0);
AudioConnection          patchCord10(EQ_3, 0, EQ_Mix1, 2);
AudioConnection          patchCord11(EQ_2, 0, EQ_Mix1, 1);
AudioConnection          patchCord12(EQ_4, 0, EQ_Mix1, 3);
AudioConnection          patchCord13(EQ_5, 0, EQ_Mix2, 0);
AudioConnection          patchCord14(EQ_6, 0, EQ_Mix2, 1);
AudioConnection          patchCord15(EQ_7, 0, EQ_Mix2, 2);
AudioConnection          patchCord16(EQ_8, 0, EQ_Mix2, 3);
AudioConnection          patchCord17(EQ_Mix2, 0, EQ_Mix3, 1);
AudioConnection          patchCord18(EQ_Mix1, 0, EQ_Mix3, 0);
AudioConnection          patchCord19(EQ_Mix3, 0, M4, 0);
//AudioConnection          patchCord20(M4, 0, audioOutput, 0);
AudioConnection          patchCord30(M4, 0, fft1024_1, 0);
AudioConnection          patchCordc100(audioInput, 0, audioOutput, 0);

/*SliderV sBand1(&tft, BAND1, 45, 160, iLI9488_WHITE, iLI9488_BLACK, iLI9488_ORANGE);
  SliderV sBand2(&tft, BAND2, 45, 160, iLI9488_WHITE, iLI9488_BLACK, iLI9488_ORANGE);
  SliderV sBand3(&tft, BAND3, 45, 160, iLI9488_WHITE, iLI9488_BLACK, iLI9488_ORANGE);
  SliderV sBand4(&tft, BAND4, 45, 160, iLI9488_WHITE, iLI9488_BLACK, iLI9488_ORANGE);
  SliderV sBand5(&tft, BAND5, 45, 160, iLI9488_WHITE, iLI9488_BLACK, iLI9488_ORANGE);
  SliderV sBand6(&tft, BAND6, 45, 160, iLI9488_WHITE, iLI9488_BLACK, iLI9488_ORANGE);
  SliderV sBand7(&tft, BAND7, 45, 160, iLI9488_WHITE, iLI9488_BLACK, iLI9488_ORANGE);
  SliderV sBand8(&tft, BAND8, 45, 160, iLI9488_WHITE, iLI9488_BLACK, iLI9488_ORANGE);*/
// create some band variables
int Band1 = 0;
int Band2 = 0;
int Band3 = 0;
int Band4 = 0;
int Band5 = 0;
int Band6 = 0;
int Band7 = 0;
int Band8 = 0;

int BtnX, BtnY;

//const int myInput = AUDIO_INPUT_LINEIN;
int myInput = AUDIO_INPUT_MIC;
int  myInputOld = AUDIO_INPUT_MIC;

int oldButtonNumber = -1;
int buttonNumber = 0;
int buttonNumber2 = 0;
int oldButton2 = -1;
int currentButton = -1;
int onOffButton = 1;
volatile int encoderDirection;
int freqEncoderMovement;
int secondEncoderMovement;
const char *ButtonNames[] = { " EQ", " Comp", " FFT"};
const char *onOffButtonsNames[] = {"  On", " Off"};
const char *CompButtonNames[] = { "Thresh1", "Thresh2", "Mic Gain", "   Input", "    Set"};
// [Zero] is calibration for mapping to pixal, 1-4 follow screen rotation for mapping math
//TS_MAP tsMap[5] = { {200, 3700, 325, 3670 }, { 0, 319, 0, 239 }, { 319, 0, 0, 239 }, { 319, 0, 239, 0 }, { 0, 319, 239, 0 } };
//int16_t TS_Rotate = 3;
float bandGain[] = {1, 1, 1, 1, 1, 1, 1, 1};
float ydBLevel[] = {0, 0, 0, 0, 0, 0, 0, 0};
int eqFreq[] = {150, 240, 370, 590, 900, 1300, 2000, 3300};
const char *EQTextFreq[] = { "150", "240", "370", "600", "900", "1.3K", " 2K", "3.3K",};

int yLevel[] = {95, 95, 95, 95, 95, 95, 95, 95};
int freqBand;

int on = 1;
int off = 0;
int xOrigin = 0;
int yOrigin = 215;
int positionx;
int positiony;
int touchFlag = 0;
int xx;
int yy;
int pageFlag = 0;
int eqFlag = 0;
int compFlag = 0;

int TS_bCount = 0;  // Set at run time from sizeof()
TS_BUTTON buttons[] = {
  {0, 0, BOXSIZEX, BOXSIZEY, 0 },   {BOXSPACEX, 0, BOXSIZEX, BOXSIZEY, 1},
  {BOXSPACEX * 2, 0, BOXSIZEX, BOXSIZEY, 2},   {BOXSPACEX * 3, 0, BOXSIZEX, BOXSIZEY, 3},
  {BOXSPACEX * 4, 0, BOXSIZEX, BOXSIZEY, 4},   {BOXSPACEX * 5, 0, BOXSIZEX, BOXSIZEY, 5}
};

TS_BUTTON onOffButtons[] = {
  {BOXSPACEX * 3, 0, BOXSIZEX - 6, BOXSIZEY, 3},
  {(BOXSPACEX * 4) - 6, 0, BOXSIZEX - 6, BOXSIZEY, 4}
};
TS_BUTTON compButtons[] = {
  {10, BOXSIZEY , BOXSIZEX, BOXSIZEY, 0 },   {10, BOXSIZEY + BOXSPACEY, BOXSIZEX, BOXSIZEY, 1},
  {10, BOXSIZEY + BOXSPACEY * 2, BOXSIZEX, BOXSIZEY, 2}, {10, BOXSIZEY + BOXSPACEY * 3, BOXSIZEX, BOXSIZEY, 3},
  {10, BOXSIZEY + BOXSPACEY * 4, BOXSIZEX, BOXSIZEY, 4}
};

float thresh1 = .4;       // Upper threshold
float thresh2 = .05;      // Lower threshold

float compGain = 1;
float tiny = .1;          // Running Ave Constant
float leftPeak = 0.5;
int attackTime;
float compGainFinal = .5;
float compGainFinalOld = .5;
float b;
int range;
int timeConstant = 1;
float leftPeakOld;
elapsedMillis fps;
float compGain1;
int numCount;
int compressorFlag = 0;
float micGainSet = 30;
float vol;
float compInputSet;


/*****
    Purpose: To delay so many milliseconds without blocking interrupts

  Parameter list:
    unsigned long ms      the number of milliseconds to delay

  Return value:
    void

*****/
void MyDelay(unsigned long ms)
{
  unsigned long currentMillis = millis();
  unsigned long previousMillis = millis();

  while (currentMillis - previousMillis < ms) {
    currentMillis = millis();
  }
}

void setup(void) {
  Serial.begin(57600);
  //while ( !Serial && (millis() < 3000)) ;

  pinMode(T_CS_PIN, OUTPUT);

  pinMode(TFT_CS, OUTPUT);
  pinMode(2, INPUT);

  tft.begin();
  ts.begin();

  tft.setRotation(1);
  ts.setRotation(3);
  oldButtonNumber = currentButton = 1;
  //ButtonInit();
  //Serial.println(F("PRe-Processor"));
  //pinMode(TIRQ_PIN, INPUT);
  pinMode(FREQENCODERPINA,      INPUT_PULLUP);
  digitalWrite(FREQENCODERPINA, HIGH);
  pinMode(FREQENCODERPINB,      INPUT_PULLUP);
  digitalWrite(FREQENCODERPINB, HIGH);
  pinMode(FREQENCODERSWITCH,    INPUT_PULLUP);

  pinMode(SECONDENCODERPINA,      INPUT_PULLUP);
  pinMode(SECONDENCODERPINB,      INPUT_PULLUP);
  pinMode(SECONDENCODERSWITCH,    INPUT_PULLUP);
  //attachInterrupt(TIRQ_PIN, TS_isr, FALLING);
  //attachInterrupt(FREQENCODERPINA, freqISR, CHANGE);
  //attachInterrupt(FREQENCODERPINB, freqISR, CHANGE);

  //attachInterrupt(SECONDENCODERPINA,   SecondEncoderISR, CHANGE);
  //attachInterrupt(SECONDENCODERPINB,   SecondEncoderISR, CHANGE);
  AudioMemory(100);
  sgtl5000_1.enable();
  sgtl5000_1.muteHeadphone();
  sgtl5000_1.muteLineout();

  sgtl5000_1.inputSelect(myInput);

  sgtl5000_1.lineInLevel(5);
  sgtl5000_1.lineOutLevel(20);


  sgtl5000_1.micGain(30);
  sgtl5000_1.volume(0.8);
  sgtl5000_1.adcHighPassFilterEnable();
  sgtl5000_1.dacVolume(1);
  sgtl5000_1.dacVolumeRamp();
  CompMix.gain(0, 1);
  reverb1.reverbTime(1);
  Serial.begin(9600);
  b = 0.05 / (1 - thresh1);

  // initialize the sliders
  /*  sBand1.init(-12, 12, 3, 0);
    sBand2.init(-12, 12, 3, 0);
    sBand3.init(-12, 12, 3, 0);
    sBand4.init(-12, 12, 3, 0);
    sBand5.init(-12, 12, 3, 0);
    sBand6.init(-12, 12, 3, 0);
    sBand7.init(-12, 12, 3, 0);
    sBand8.init(-12, 12, 3, 0);

    sBand1.drawSliderColor(true);
    sBand2.drawSliderColor(true);
    sBand3.drawSliderColor(true);
    sBand4.drawSliderColor(true);
    sBand5.drawSliderColor(true);
    sBand6.drawSliderColor(true);
    sBand7.drawSliderColor(true);
    sBand8.drawSliderColor(true);*/
  M4.gain(0, 1);  //
  M4.gain(1, 0);
  M4.gain(2, 0);
  M4.gain(3, 0);
  SetupFilters();
  tft.fillScreen(iLI9488_BLACK);
  //EqGainSetL();
  Splash();
  delay(100);
  tft.fillScreen(iLI9488_BLACK);
  ButtonDraw();
  sgtl5000_1.unmuteHeadphone();
  sgtl5000_1.unmuteLineout();


}

void loop()
{
   if (compressorFlag == 1) {
     compressor();
    }
    else {
     CompMix.gain(0, 1);
    }
  boolean istouched = ts.touched();
  if (istouched and pageFlag == 0) {
    delay(100);
    TS_Point p = ts.getPoint();
    //tft.fillCircle(p.x, p.y, 3, iLI9488_YELLOW);

    xx = map(p.x, 166, 3906, 0, 480);
    yy = map(p.y, 238, 3869, 0, 320);
    tft.fillCircle(xx, yy, 3, iLI9488_YELLOW);
    //tft.print("p.x=  ");tft.print(p.x);tft.print("   p.y=  ");tft.println(p.y);
    //Serial.print("p.x=  ");Serial.print(p.x);Serial.print("   p.y=  ");Serial.println(p.y);
    if (yy < BOXSIZEX + 1 and xx < BOXSPACEX * 3) {
      ReadButtons();
      istouched = false;
    }




  }
  //if (istouched and pageFlag == 0)
  /*if (digitalRead(2) != HIGH) {
      TS_Point p = ts.getPoint();

      tft.fillRect(9,9,130,60,iLI9488_BLUE);

      xx = map(p.x,166, 3906, 0, 480);
      yy = map(p.y, 238, 3869, 0, 320);
      tft.fillCircle(xx,yy,3,iLI9488_YELLOW);
      //tft.print("p.x=  ");tft.print(p.x);tft.print("   p.y=  ");tft.println(p.y);
      //Serial.print("Pressure = ");
      //Serial.print(p.z);
      delay(100);
      tft.setTextColor(iLI9488_WHITE);
      tft.setTextSize(2);
     tft.setCursor(10, 10);
      tft.print("x = ");
      tft.print(p.x);
      tft.setCursor(10, 40);
      tft.print("y = ");
      tft.println(p.y);
      //Serial.println("Touched");


    }*/
  //vol = analogRead(VOLUMEPOT);
  //vol = vol / 1280;
  //sgtl5000_1.volume(vol);
  //sgtl5000_1.dacVolume(vol);
  //Serial.println(vol);
}












#endif
