/*****
  This software is licensed un the GNU General Public License, Version 3, as presetned in
  https://www.gnu.org/licenses/gpl-3.0.txt. You may use this software for non-commercial use. 
  For commercial use, contact the authors:
  Jack Purdum, W8TEE
  Al Peter, AC8GY

  This header file must be copied into all copies and deriviative works of this software
  and remain the very first thing in the primary source code file.
  
*****/
// Note: 8-11-19 Works with alternate pins for Audio Shield & ILI9488

/***************************************************
  This is our GFX example for the Adafruit ILI9488 Breakout and Shield
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
 //                             Compile with Teensy 4.0 or 4.1 board
#ifndef BEENHERE
#include "Post.h"

ILI9488_t3 tft = ILI9488_t3(&SPI, TFT_CS, TFT_DC, TFT_RST);
//URTouch  myTouch( 14, 8, 7, 12, 2); //
XPT2046_Touchscreen myTouch = XPT2046_Touchscreen(CS_PIN, TIRQ_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling
Rotary rotaryFreq   = Rotary( (uint8_t) FREQENCODERPINA, (uint8_t) FREQENCODERPINB);
Rotary rotarySecond = Rotary( (uint8_t) SECONDENCODERPINB, (uint8_t) SECONDENCODERPINA);
Adafruit_GFX_Button ButtonV[8];
Adafruit_GFX_Button ButtonH[3];
Adafruit_GFX_Button ButtonSet[6];
Adafruit_GFX_Button NotchHold;
Adafruit_GFX_Button Exit;

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
long notchFreq = 1000;
long hpFreq = 150;
long lpFreq = 2500;
//long hpFreq = 100;



#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
/*
  AudioMixer4            Notch_Input;         //xy=415,177
  AudioConnection          patchCord6(i2s1, 0, Notch_Input, 0);
  AudioConnection          patchCord12(Notch_Input, Notch);
  AudioConnection          patchCord21(LP8, 0, Notch_Input, 1);*/
// GUItool: end automatically generated code





// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
//#include <OpenAudio_ArduinoLibrary.h> //for AudioConvert_I16toF32, AudioConvert_F32toI16, and AudioEffectGain_F32

// GUItool: begin automatically generated code
//AudioControlSGTL5000_Extended    sgtl5000_1; 
AudioControlSGTL5000   sgtl5000_1; 
//AudioConvert_I16toF32     int2Float_L, int2Float_R;    //Converts Int16 to Float.  See class in AudioStream_F32.h
//AudioEffectCompressor_F32 comp_L, comp_R;      // compressors
//AudioConvert_F32toI16     float2Int_L, float2Int_R;    //Converts Float to Int16.  See class in AudioStream_F32.h

AudioAnalyzeNoteFrequency notefreq;
AudioInputI2S            i2s1;           //
AudioAnalyzeFFT1024      fft1024_1;      //
//AudioAnalyzePeak         peak1;          //
//AudioRecordQueue         queue1;         //
AudioFilterBiquad        CW_1;       //
AudioFilterBiquad        LP1;        //
AudioFilterBiquad        EQ_1;       //
AudioFilterBiquad        EQ_3;       //
AudioFilterBiquad        EQ_2;       //
AudioFilterBiquad        EQ_4;       //
AudioFilterBiquad        EQ_5;       //
AudioFilterBiquad        EQ_6;       //
AudioFilterBiquad        EQ_7;       //
AudioFilterBiquad        EQ_8;
AudioFilterBiquad        HP_1;
AudioFilterBiquad        HP_2;
AudioFilterBiquad        HP_3;
AudioFilterBiquad        HP_4;
AudioFilterBiquad        LP5;        //
AudioFilterBiquad        CW_2;       //
AudioMixer4              M1;         //
AudioFilterBiquad        LP2;        //
AudioFilterBiquad        LP6;        //
AudioFilterBiquad        CW_3;       //
AudioFilterBiquad        Notch;        //
AudioMixer4              EQ_Mix2;         //
AudioMixer4              EQ_Mix1;         //
AudioFilterBiquad        LP3;        //
AudioFilterBiquad        LP7;        //
AudioFilterBiquad        CW_4;       //
AudioMixer4              M2;         //
AudioMixer4              EQ_Mix3;         //
AudioFilterBiquad        LP4;        //
AudioFilterBiquad        LP8;        //
AudioMixer4              M3;         //
AudioMixer4              M4;         //
AudioMixer4              M5;         
AudioOutputI2S           i2s2;           //


//AudioConnection          patchCord0100(i2s1,0, notefreq, 0);
AudioConnection          patchCord1(i2s1, 0, LP1, 0);
AudioConnection          patchCord6(i2s1, 0, M1, 1);
AudioConnection          patchCord10(LP1, LP2);
AudioConnection          patchCord23(LP2, LP3);
AudioConnection          patchCord29(LP3, LP4);
AudioConnection          patchCord34(LP4, LP5);
AudioConnection          patchCord19(LP5, LP6);
AudioConnection          patchCord24(LP6, LP7);
AudioConnection          patchCord130(LP7, LP8);
AudioConnection          patchCord131(LP8, HP_1);
AudioConnection          patchCord132(HP_1, HP_2);
AudioConnection          patchCord133(HP_2, HP_3);
AudioConnection          patchCord134(HP_3, HP_4);
AudioConnection          patchCord35(HP_4, 0, M1, 0);

AudioConnection          patchCord22(M1, 0, M2, 0);

AudioConnection          patchCord21(M1, Notch);
AudioConnection          patchCord26(Notch, 0, M2, 1);
AudioConnection          patchCord32(M2, 0, M3, 0);
//AudioConnection          patchCord135(M4, 0, i2s2, 0);

AudioConnection          patchCord5(i2s1, 0, CW_1, 0);
AudioConnection          patchCord9(CW_1, CW_2);
AudioConnection          patchCord20(CW_2, CW_3);
AudioConnection          patchCord25(CW_3, CW_4);
AudioConnection          patchCord31(CW_4, 0, M3, 1);

AudioConnection          patchCord7(i2s1, 0, M4, 2);
AudioConnection          patchCord8(i2s1, 1, i2s2, 1);

AudioConnection          patchCord36(M3, EQ_1);
AudioConnection          patchCord37(M3, EQ_2);
AudioConnection          patchCord38(M3, EQ_3);
AudioConnection          patchCord39(M3, EQ_4);
AudioConnection          patchCord40(M3, EQ_5);
AudioConnection          patchCord41(M3, EQ_6);
AudioConnection          patchCord42(M3, EQ_7);
AudioConnection          patchCord43(M3, EQ_8);
AudioConnection          patchCord11(EQ_1, 0, EQ_Mix1, 0);
AudioConnection          patchCord12(EQ_3, 0, EQ_Mix1, 2);
AudioConnection          patchCord13(EQ_2, 0, EQ_Mix1, 1);
AudioConnection          patchCord14(EQ_4, 0, EQ_Mix1, 3);
AudioConnection          patchCord15(EQ_5, 0, EQ_Mix2, 0);
AudioConnection          patchCord16(EQ_6, 0, EQ_Mix2, 1);
AudioConnection          patchCord17(EQ_7, 0, EQ_Mix2, 2);
AudioConnection          patchCord18(EQ_8, 0, EQ_Mix2, 3);
AudioConnection          patchCord27(EQ_Mix2, 0, EQ_Mix3, 1);
AudioConnection          patchCord28(EQ_Mix1, 0, EQ_Mix3, 0);
AudioConnection          patchCord33(EQ_Mix3, 0, M4, 1);

AudioConnection          patchCord44(M3, 0, M4, 0);
AudioConnection          patchCord50(M4, 0, M5, 1);
//AudioConnection          patchCord45(M4, 0, int2Float_L, 0);   //connect the Left EQ out to the Left Int->Float converter
//AudioConnection_F32      patchCord46(int2Float_L, 0, comp_L, 0); //Left.  makes Float connections between objects
//AudioConnection_F32      patchCord47(comp_L, 0, float2Int_L, 0); //Left.  makes Float connections between objects
//AudioConnection          patchCord48(float2Int_L, 0, i2s2, 0);  //connect the Left float processor to the Left output
//AudioConnection          patchCord49(i2s1, 0, i2s2, 0);  //connect the Left float processor to the Left output
AudioConnection          patchCord49(M5, 0, i2s2, 0); 

//AudioConnection          patchCord2(i2s1, 0, queue1, 0);
AudioConnection          patchCord3(M5, 0, fft1024_1, 0);
//AudioConnection          patchCord4(i2s1, 0, peak1, 0);
//AudioControlSGTL5000     sgtl5000_1;     //xy=81,74
// GUItool: end automatically generated code

int exitFlag = 1;
long xNotch[25];
boolean use_HP_filter = true;
float knee_dBFS_L = -15.0f;  // 
//float comp_ratio_L = 5.0f;
float comp_ratio_L = 10.0f;
//float attack_sec_L = .005f;
float attack_sec_L = 10.f;
//float release_sec_L = .2f;
float release_sec_L = .2f;
float gain_dB_L = -10;

int xScreenPos2old=xOrigin+20;
long CWCenterFreq2;
int LPFlag = 0;
int NotchFlag = 0;
int CWFlag = 0;
int EQFlag = 0;
int ALCFlag = 0;
int NRFlag = 0;
int FFTFlag = 0;
float bandGain[] = {1, 1, 1, 1, 1, 1, 1, 1};
float ydBLevel[] = {0, 0, 0, 0, 0, 0, 0, 0};
int secondEncoderMovement;
int freqBand = 0;
int eqFreq[] = {150, 240, 370, 590, 900, 1300, 2000, 3300};
int yLevel[] = {100, 100, 100, 100, 100, 100, 100, 100};
int setButtonOn;
long xScreenPos3 = xOrigin+1;
long yPosition3= yOrigin-1;;
long xScreenPosOld2 = xOrigin+5;
long xScreenPosOld3 = xOrigin+5;
long xScreenPosOld4 = xOrigin+5;
long xScreenPos4= xOrigin+5;
long xScreenPos2 = xOrigin+5;
long yPosition = yOrigin-1;
long xScreenPosOld = xOrigin+1;
volatile int encoderDirection;
int freqEncoderMovement;
int lastButtonindex1;
int lastButtonindex2 = 0;
int lastButtonindex4;
int OnOffFlag = 0;
int firstTimeFlag = 0;
int functionOnFlag = 0;
int functionOffFlag = 0;
int chan1OnFlag = 0;
int chan2OnFlag = 0;
int CWFilter = 1;
float CWFilterQ;
int offSetPositionOld;
const char *ButtonNamesV[] = { "Filters", "Notch", "Auto N","CW", "EQ", "ALC", "NR", "FFT"};
const char *ButtonNamesH[] = { "On", "Off"};
uint16_t  *ButtonColorsOff[] = { ILI9488_BLUE, ILI9488_BLUE, ILI9488_BLUE, ILI9488_BLUE, ILI9488_DARKGREY, ILI9488_DARKGREY, ILI9488_DARKGREY, ILI9488_MAGENTA};
uint16_t  *ButtonColorsTextOff[] = { ILI9488_WHITE, ILI9488_WHITE, ILI9488_WHITE, ILI9488_WHITE, ILI9488_WHITE, ILI9488_WHITE, ILI9488_WHITE, ILI9488_BLACK};
uint16_t  ButtonColorsTextOn = ILI9488_BLACK;
uint16_t  *ButtonColorsOn[] = { ILI9488_GREEN, ILI9488_GREEN, ILI9488_GREEN, ILI9488_GREEN, ILI9488_GREEN, ILI9488_GREEN, ILI9488_GREEN, ILI9488_GREEN};
int dispx;
int dispy;
float caltx;
float calty;
uint16_t tx, ty;
int displayTimeFlag;
float xMapLowAve = 2081;
float yMapLowAve = 2098;
float xMapHighAve = 50000;
float yMapHighAve = 2604;

int on = 1;
int off = 0;
int xOrigin = 235;
int yOrigin = 275;
const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;

int TP_X;
int TP_Y;
const uint16_t bands = 1024;
float tiny;
float fftdata[bands];  // Array of fft data
float fftdataOld[bands];
long xScreenPos[bands];

//============================================
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



//==============================================
void setup() {
  Serial.begin(9600);
  Serial.println("ILI9488 Test!2");
  tft.begin();
  tft.setRotation(1);
  //myTouch.begin();
  //myTouch.setRotation(1);
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(100);
//AudioMemory_F32(32); //allocate Float32 audio data blocks
 //notefreq.begin(.15);
  // Enable the audio shield, select input, and enable output
 /* sgtl5000_1.enable();
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(.8);
  sgtl5000_1.lineInLevel(0);
  sgtl5000_1.lineOutLevel(13);

  pinMode(FREQENCODERPINA,      INPUT_PULLUP);
  pinMode(FREQENCODERPINB,      INPUT_PULLUP);
  pinMode(FREQENCODERSWITCH,    INPUT_PULLUP);

  pinMode(SECONDENCODERPINA,      INPUT_PULLUP);
  pinMode(SECONDENCODERPINB,      INPUT_PULLUP);
  pinMode(SECONDENCODERSWITCH,    INPUT_PULLUP);

  pinMode(LPFILTERPIN,          INPUT);
  pinMode(NOTCHFILTERPIN,       INPUT);
   pinMode(AUTONOTCHFILTERPIN,       INPUT);
  pinMode(CWFILTERPIN,          INPUT);
  pinMode(EQFILTERPIN,          INPUT);
  pinMode(ALCPIN,               INPUT);
  //pinMode(FFTPIN,               INPUT_PULLUP);

  attachInterrupt(FREQENCODERPINA,   freqISR, CHANGE);
  attachInterrupt(FREQENCODERPINB,   freqISR, CHANGE);

  attachInterrupt(SECONDENCODERPINA,   SecondEncoderISR, CHANGE);
  attachInterrupt(SECONDENCODERPINB,   SecondEncoderISR, CHANGE);

  attachInterrupt(LPFILTERPIN,      LPFilterISR, CHANGE);
  attachInterrupt(NOTCHFILTERPIN,   notchFilterISR, CHANGE);
    attachInterrupt(AUTONOTCHFILTERPIN,   AutoNotchFilterISR, CHANGE);
  attachInterrupt(CWFILTERPIN,      CWFilterISR, CHANGE);
  attachInterrupt(EQFILTERPIN,      EQFilterISR, CHANGE);
  attachInterrupt(ALCPIN,           ALCISR, CHANGE);
  //attachInterrupt(FFTPIN,           fftISR, CHANGE);



  SetupFilters();

  // Bypass to start


  M1.gain(0, 0);//LP
  M1.gain(1, 1);// ByPass
  M1.gain(2, 0);//
  M1.gain(3, 0);//

  M2.gain(0, 1);//
  M2.gain(1, 0);//
  M2.gain(2, 0);//
  M2.gain(3, 0);//

  M3.gain(0, 1);//
  M3.gain(1, 0);//
  M3.gain(2, 0);//
  M3.gain(3, 0);//

  M4.gain(0, 1);  //
  M4.gain(1, 0);  //
  M4.gain(2, 0);  //
  M4.gain(3, 0);  //

  M5.gain(0, 0);  //
  M5.gain(1, 1);  //
  M5.gain(2, 0);  //
  M5.gain(3, 0);  //*/
  tft.fillRect(0, 0, 480, 320, ILI9488_BLUE);
  delay(30);
 // DrawLeftButtons();
  //DrawTopButtons();
  DrawLogo();
  CreateEQDisplayAxis();
  delay(100);
 // DrawButtonswOff();
  //DrawSetButtons();

  //tft.fillRect(0, 0, 480, 319, ILI9488_BLACK);
  //CreateEQDisplayAxis();
  //sgtl5000_1.audioPostProcessorEnable();
  //sgtl5000_1.autoVolumeControl(1,2,0,-18,.2,.2);
  //sgtl5000_1.autoVolumeEnable();
  //SetupMyCompressors_L(use_HP_filter, knee_dBFS_L, comp_ratio_L, attack_sec_L, release_sec_L);
}



//=============================================  loop() =================================
void loop(void) {

  //InitDisplayCalibration();

  //if (myTouch.dataAvailable()) {

  //ReadButtons();
  
  //Serial.print("After ReadButtons  ");
  //ReadTopRowButtons();
  //Serial.print("After ReadTopRowButtons  ");
  // }
  //GetTouchCoordinates2();


 // tft.fillCircle(caltx, calty, 5, ILI9488_YELLOW);
  //Serial.print("caltx  ");Serial.println(caltx);
  //Serial.print("calty  ");Serial.println(calty);
  //Serial.println(" ");
  //}
  //tft.fillScreen(ILI9488_BLACK); // Clear Screen
  //tft.fillRect(0, 0, 480, 319, ILI9488_BLACK);
  //delay(1000);
  //Serial.println("In loop");
  //InitDisplayCalibration();
  //SetLPFilters();
  //CreateFFTAxis();
  //ReadButtons();
  //displayAudioSpectrum();

  //long x, y;

  /* while (myTouch.dataAvailable() == true)
    {
     myTouch.read();
     x = myTouch.getX();

     y = myTouch.getY();
     int    tx = myTouch.TP_X;
     int      ty = myTouch.TP_Y;
     Serial.print("x=  "); Serial.println(x);
     Serial.print("y=  "); Serial.println(y);
     Serial.print("Raw x=  "); Serial.println(tx);
     Serial.print("Raw y=  "); Serial.println(ty);

     //if ((x!=-1) and (y!=-1))
     //{
     // myGLCD.drawPixel (x, y);
     // }
    }*/
}



/*unsigned long testText() {
  tft.fillScreen(ILI9488_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9488_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9488_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9488_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9488_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;*/

//}

#endif
