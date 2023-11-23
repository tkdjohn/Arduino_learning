
//#include "SPI.h"
//#include <OpenAudio_ArduinoLibrary.h> // http://hamradiodesigns.com/index.php/content/ 
#include <Adafruit_GFX.h>  //(https://github.com/adafruit/Adafruit-GFX-Library)
//#include "Adafruit_ILI9341.h"
#include <ILI9488_t3.h>         // https://github.com/jaretburkett/ILI9488
//#include <URTouch.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
//#include <SD.h>
#include <SerialFlash.h>
#include <Rotary.h>           // https://github.com/brianlow/Rotary
#include <XPT2046_Touchscreen.h>

#define CS_PIN  14
#define TIRQ_PIN  2
#define TFT_RST 23
#define TFT_DC 9
#define TFT_CS 10
#define TFT_MOSI        11
#define TFT_CLK        13
#define TFT_MISO        12

/******************* UI details */
#define DISPLAYWIDTH            480     // For our display 
#define DISPLAYHEIGHT           320

#define BUTTONTOP_X 30
#define BUTTONTOP_Y 100
#define BUTTONMAIN_X 48
#define BUTTONMAIN_Y 15
#define BUTTONSET_X 280
#define BUTTONSET_Y 55

#define BUTTON_W 85
#define BUTTON_W2 60
#define BUTTON_H 30
#define BUTTON_SPACING_X 20
#define BUTTON_SPACING_Y 20
#define BUTTON_TEXTSIZE 2

#define CWFILTERFREQUENCY  750
#define NOTCHQ  20

#define FREQENCODERPINB         3      // Frequency encoder pin B
#define FREQENCODERPINA         4      // Frequency encoder pin A
#define FREQENCODERSWITCH       5      // Frequency encoder switch

#define LPFILTERPIN            24      // 1 LP Filter on/off
#define NOTCHFILTERPIN         25      // 2 Notch Filter on/off
#define AUTONOTCHFILTERPIN     26      // 3 Auto Notch
#define CWFILTERPIN            27      // 4 CW Filter on/off
#define EQFILTERPIN            28      // 5 EQ
#define ALCPIN                 29      // 6 ALC
#define NRPIN                  30      // 7 NR
#define FFTPIN                 31      // 8 FFT on/off


#define SECONDENCODERSWITCH      15     // Filter encoder switch
#define SECONDENCODERPINB        16     // Filter encoder pin A
#define SECONDENCODERPINA        17     // Filter encoder pin A
//---------------------------------------------------------------  ILI9488 colors
#define ILI9488_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9488_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9488_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9488_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9488_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9488_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9488_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9488_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9488_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9488_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9488_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9488_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9488_RED         0xF800      /* 255,   0,   0 */
#define ILI9488_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9488_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9488_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9488_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9488_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9488_PINK        0xF81F

extern ILI9488_t3 tft;
//extern URTouch  myTouch; //
extern XPT2046_Touchscreen myTouch;
extern Adafruit_GFX_Button ButtonV[8];
extern Adafruit_GFX_Button ButtonH[3];
extern Adafruit_GFX_Button ButtonSet[6];
extern Adafruit_GFX_Button NotchHold;
extern Adafruit_GFX_Button Exit;
extern const char *ButtonNamesV[];
extern const char *ButtonNamesH[];
extern uint16_t  *ButtonColorsOff[];
extern uint16_t  *ButtonColorsTextOff[];
extern uint16_t  *ButtonColorsOn[];
extern uint16_t  ButtonColorsTextOn;


//----------------------
extern AudioInputI2S            i2s1; 
extern AudioAnalyzeNoteFrequency notefreq;          
extern AudioAnalyzeFFT1024      fft1024_1;      
extern AudioAnalyzePeak         peak1;          
extern AudioRecordQueue         queue1;         
extern AudioFilterBiquad        CW_1;       
extern AudioFilterBiquad        LP1;        
extern AudioFilterBiquad        EQ_1;       
extern AudioFilterBiquad        EQ_3;       
extern AudioFilterBiquad        EQ_2;       
extern AudioFilterBiquad        EQ_4;       
extern AudioFilterBiquad        EQ_5;      
extern AudioFilterBiquad        EQ_6;       
extern AudioFilterBiquad        EQ_7;       
extern AudioFilterBiquad        EQ_8; 
extern AudioFilterBiquad        HP_1;
extern AudioFilterBiquad        HP_2;
extern AudioFilterBiquad        HP_3;
extern AudioFilterBiquad        HP_4;      
extern AudioFilterBiquad        LP5;        
extern AudioFilterBiquad        CW_2;       
extern AudioMixer4              M1;         
extern AudioFilterBiquad        LP2;        
extern AudioFilterBiquad        LP6;        
extern AudioFilterBiquad        CW_3;       
extern AudioFilterBiquad        Notch;        
extern AudioMixer4              EQ_Mix2;        
extern AudioMixer4              EQ_Mix1;         
extern AudioFilterBiquad        LP3;        
extern AudioFilterBiquad        LP7;        
extern AudioFilterBiquad        CW_4;       
extern AudioMixer4              M2;         
extern AudioMixer4              EQ_Mix3;        
extern AudioFilterBiquad        LP4;        
extern AudioFilterBiquad        LP8;       
extern AudioMixer4              M3;         
extern AudioMixer4              M4;        
extern AudioMixer4              M5; 
//extern AudioControlSGTL5000_Extended    sgtl5000_1; 
//extern AudioConvert_I16toF32     int2Float_L, int2Float_R;    //Converts Int16 to Float.  See class in AudioStream_F32.h
//extern AudioEffectCompressor_F32 comp_L, comp_R;      // compressors
//extern AudioConvert_F32toI16     float2Int_L, float2Int_R;    //Converts Float to Int16.  See class in AudioStream_F32.h
//------------------------------

///==================== Setup Left Audio AGC parameters
//To configure Compressor for slow response more like an automatic volume control, use:
//knee_dBFS = -50.0; comp_ratio = 5.0;  attack_sec = 1.0;  release_sec = 2.0;


extern boolean use_HP_filter;
extern float knee_dBFS_L;  // Sets the threshhold
extern float comp_ratio_L;
extern float attack_sec_L;
extern float release_sec_L;
extern float gain_dB_L;
extern long xNotch[];
extern int exitFlag;
extern int xScreenPos2old;
extern long CWCenterFreq2;
extern int LPFlag;
extern int NotchFlag;
extern int CWFlag;
extern int EQFlag;
extern int ALCFlag;
extern int NRFlag;
extern int FFTFlag;
extern float bandGain[];
extern float ydBLevel[];
extern int secondEncoderMovement;
extern int freqBand;
extern int eqFreq[];
extern int yLevel[];
extern int setButtonOn;
extern int CWFilter;
extern int functionOnFlag;
extern int functionOffFlag;
extern float CWFilterQ;
extern int offSetPositionOld;
extern  long xScreenPos3;
extern  long yPosition3;
extern long xScreenPosOld2;
extern  long xScreenPosOld3;
extern long xScreenPosOld4;
extern long xScreenPos4;
extern  long xScreenPos2;
extern  long yPosition;
extern  long xScreenPosOld;
extern Rotary rotaryFreq;
extern Rotary rotarySecond ;
extern volatile int encoderDirection;
extern int freqEncoderMovement;
extern int lastButtonindex1;
extern int lastButtonindex2;
extern int lastButtonindex4;
extern int OnOffFlag;
extern int firstTimeFlag;
extern int chan1OnFlag;
extern int chan2OnFlag;

extern float caltx;
extern float calty;
extern uint16_t tx, ty;
extern int displayTimeFlag;

extern float xMapLowAve;
extern float yMapLowAve;
extern float xMapHighAve;
extern float yMapHighAve;

extern long lpFreq;
extern long hpFreq;
extern float tiny;
extern const uint16_t bands;
extern float fftdata[];  // Array of fft data
extern int on;
extern int off;
extern int xOrigin;
extern int yOrigin;

extern long notchFreq;
extern int freqISR();


void DrawExitButton();
void DoExitButton();

void AutoNotchFilterISR();
int ButtonOn(int j);
int ButtonOff(int j);
void DrawLogo();
void SetAutoNotch();
void SetALC();
void ALCISR();
void ALCOnOff();
void SetupMyCompressors_L(boolean use_HP_filter_L, float knee_dBFS_L, float comp_ratio_L, float attack_sec_L, float release_sec_L);
void DrawButtonswOff();
void EqGainSetL();
int SecondEncoderISR();
void EQFilterISR();
void SetEQFilters();
void CreateEQDisplayAxis();
void SetupFilters();
void DrawSetButtons();
void LPFilterISR();
void notchFilterISR();
void CWFilterISR();
void fftISR();
void ReadTopRowButtons();
void SetNotchFilters();
void displayNotchFilter();
void SetCWFilters();
void displayCWFilter();
void GetTouchCoordinates2();
void displayLPCutoff();
void InitDisplayCalibration();
void MyDelay(unsigned long interval);
void ReadButtons();
void ReadChannelButtons();
void ReadActionButtons();
void DrawLeftButtons();
void DrawTopButtons();
void displayAudioSpectrum();
void CreateFFTAxis();
void Read_Plot_FFT();
void SetLPFilters();
