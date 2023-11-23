

//#include <Adafruit_GFX.h>  //(https://github.com/adafruit/Adafruit-GFX-Library)
#include <Audio.h>
#include <SPI.h>
#include <Wire.h>      // this is needed even tho we aren't using it
//#include <ILI9341_t3.h>
#include <ILI9488_t3.h>
//#include <iLI9488_t3_Controls.h> 
#include <XPT2046_Touchscreen.h>
#include <Rotary.h>           // https://github.com/brianlow/Rotary#include <TimerOne.h>

#include <ili9488_t3_font_Arial.h>
#include <ili9488_t3_font_ArialBold.h>

#define T_CS_PIN  14  // The XPT2046 uses hardware SPI on the shield, and pin 14
#define TIRQ_PIN  2
#define TFT_CS 10  // The display also uses hardware SPI, plus #9 & #10
#define TFT_DC  9
#define TFT_RST 23

#define FREQENCODERPINB          3      // Frequency encoder pin B
#define FREQENCODERPINA          4      // Frequency encoder pin A
#define FREQENCODERSWITCH        5      // Frequency encoder switch
#define SECONDENCODERSWITCH     22     // Filter encoder switch
#define SECONDENCODERPINB       16     // Filter encoder pin A
#define SECONDENCODERPINA       17     // Filter encoder pin ASECONDENCODERPINA        17     // Filter encoder pin A
#define VOLUMEPOT               15

#define DISPLAYWIDTH            480     // For our display chocies
#define DISPLAYHEIGHT           320

//---------------------------------------------------------------  iLI9488 colors
#define iLI9488_BLACK       0x0000      /*   0,   0,   0 */
#define iLI9488_NAVY        0x000F      /*   0,   0, 128 */
#define iLI9488_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define iLI9488_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define iLI9488_MAROON      0x7800      /* 128,   0,   0 */
#define iLI9488_PURPLE      0x780F      /* 128,   0, 128 */
#define iLI9488_OLIVE       0x7BE0      /* 128, 128,   0 */
#define iLI9488_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define iLI9488_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define iLI9488_BLUE        0x001F      /*   0,   0, 255 */
#define iLI9488_GREEN       0x07E0      /*   0, 255,   0 */
#define iLI9488_CYAN        0x07FF      /*   0, 255, 255 */
#define iLI9488_RED         0xF800      /* 255,   0,   0 */
#define iLI9488_MAGENTA     0xF81F      /* 255,   0, 255 */
#define iLI9488_YELLOW      0xFFE0      /* 255, 255,   0 */
#define iLI9488_WHITE       0xFFFF      /* 255, 255, 255 */
#define iLI9488_ORANGE      0xFD20      /* 255, 165,   0 */
#define iLI9488_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define iLI9488_PINK        0xF81F

extern AudioInputI2S            audioInput;  // audio shield: mic or line-in
extern AudioAnalyzeFFT1024      fft1024_1; 
extern AudioFilterBiquad        EQ_1;       
extern AudioFilterBiquad        EQ_3;       
extern AudioFilterBiquad        EQ_2;       
extern AudioFilterBiquad        EQ_4;       
extern AudioFilterBiquad        EQ_5;      
extern AudioFilterBiquad        EQ_6;       
extern AudioFilterBiquad        EQ_7;       
extern AudioFilterBiquad        EQ_8; 
extern AudioMixer4              CompMix; 
extern AudioMixer4              M4;  
extern AudioMixer4              EQ_Mix1;
extern AudioMixer4              EQ_Mix2;
extern AudioMixer4              EQ_Mix3; 
extern AudioOutputI2S           audioOutput;

       
extern AudioAnalyzePeak     peak_L;
//extern AudioAnalyzePeak     peak_R;
extern AudioEffectReverb    reverb1;
extern AudioAmplifier       amp1;
//extern AudioAmplifier       amp2;
//extern AudioEffectFade      fade1;
extern AudioMixer4          CompMix;
extern AudioOutputI2S       audioOutput;        // audio shield: headphones & line-out
extern AudioControlSGTL5000 sgtl5000_1;

#define BOXSIZEX 65
#define BOXSIZEY 40
#define BOXSPACEX 70
#define BOXSPACEY 45

#define PENRADIUS 2
#define TSBCOUNT 3 
#define TS_LIMIT 10 // millisecond limit to check touch value
#define TS_MINPRESS 800 // Z Pressure return minimum to use point
#define TS_DEBOUNCE 2 // TX_Map() debounce factor

#define ROW1 70
#define ROW2 110
#define ROW3 150
#define ROW4 190

#define BAND1 20
#define BAND2 60
#define BAND3 100
#define BAND4 140
#define BAND5 180
#define BAND6 220
#define BAND7 260
#define BAND8 300
// create some band variables
extern int Band1;
extern int Band2;
extern int Band3;
extern int Band4;
extern int Band5;
extern int Band6;
extern int Band7;
extern int Band8;

/*extern SliderV sBand1;
extern SliderV sBand2;
extern SliderV sBand3;
extern SliderV sBand4;
extern SliderV sBand5;
extern SliderV sBand6;
extern SliderV sBand7;
extern SliderV sBand8;*/

extern int BtnX, BtnY;


extern XPT2046_Touchscreen ts;
//extern ILI9341_t3 tft;
extern ILI9488_t3 tft;
//extern SliderV sBand4;


//extern const int myInput;
extern int myInput;
extern int  myInputOld;
extern float compInputSet;

volatile static uint16_t inISR = 0;
volatile static boolean inGM = false;
volatile static int16_t iXX = 500;
volatile static int16_t iYY = 500;
struct TS_BUTTON {
  int16_t tx, ty; // Top Left X,Y
  int16_t ww, hh; // Width, Height
  int tsButtonNumber;
  
};
extern int buttonNumber;
extern int buttonNumber2;
extern Rotary rotaryFreq;
extern Rotary rotarySecond ;
extern volatile int encoderDirection;
extern int freqEncoderMovement;
extern int secondEncoderMovement;


extern long unsigned TS_usVal; // POLL rate from the timer interrupt on Touch Detect
extern int oldButtonNumber,oldButton2, currentButton,onOffButton;
extern long unsigned TS_usVal; // POLL rate from the timer interrupt on Touch Detect
extern int16_t TS_Rotate;
extern int TS_bCount;
extern const char *ButtonNames[];
extern const char *onOffButtonsNames[];
extern const char *CompButtonNames[];
extern const char *EQTextFreq[];
extern TS_BUTTON buttons[6];
extern TS_BUTTON onOffButtons[2];
extern TS_BUTTON compButtons[5];
//extern TS_MAP tsMap[5];
extern elapsedMillis tsLimit;
extern float bandGain[];
extern float ydBLevel[];
extern float bandGain[];
extern float ydBLevel[];
extern int on ;
extern int off;
extern int xOrigin;
extern int yOrigin;
extern int freqBand;
extern int eqFreq[];
extern int yLevel[];
extern int positionx;
extern int positiony;
extern int touchFlag;
extern int xx;
extern int yy;
extern int pageFlag;
extern int eqFlag;
extern int compFlag;

extern float thresh1;
extern float thresh2;
extern float compGain;
extern float tiny;          // Running Ave Constant
extern float leftPeak;
extern int attackTime;
extern float compGainFinal;
extern float compGainFinalOld;
extern float b;
extern int range;
extern int timeConstant;
extern float leftPeakOld;
//elapsedMillis fps;
extern float compGain1;
extern int numCount;
extern int compressorFlag;
extern float micGainSet;
extern float vol;



void ButtonInit();
void ButtonDraw();
uint16_t SelectMenuButton( int16_t xx, uint16_t oldButtonNum );
uint16_t SelectOnOffButton( int16_t xx, uint16_t oldButtonNum );
void  ButtonRotate( int setrotate );
boolean TS_GetMap( int xx, int yy );
boolean TS_iGetMap( int xx, int yy );
//oid TS_isr( void );
void DrawEQDisplay();
void EqGainSetL();
void SelectFunction(int currentButton2);
void SetEQ();
void GetTouchCoord();
void ReadButtons();
void RefreshMenuButtons();
void SetEQFilters();
void freqISR();
void SecondEncoderISR();
void MyDelay(unsigned long interval);
void displayAudioSpectrum();
void CreateFFTAxis();
void SetupFilters();
void compressor();
void DrawCompressorButtons();
void SetCompressorPrameters();
void Sliders();
void Splash();
