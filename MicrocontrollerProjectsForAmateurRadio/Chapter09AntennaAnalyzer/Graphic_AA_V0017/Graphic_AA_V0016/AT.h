#ifndef BEENHERE              // Note the entire file is within #if block is not defined
#define BEENHERE

#include <Arduino.h>
#include "Free_Fonts.h" // Include the header file attached to this sketch
//#include "FS.h"
#include "Adafruit_GFX.h"
#include <ILI9488.h>           //https://github.com/jaretburkett/ILI9488
#include <EEPROM.h>
#include <Rotary.h>            //https://github.com/brianlow/Rotary
#include "SPI.h"
#include <AD9850SPI.h>        // https://github.com/F4GOJ/AD9850SPI
#include <AccelStepper.h>     // http://www.airspayce.com/mikem/arduino/AccelStepper/AccelStepper-1.59.zip
#include <Wire.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <Fonts/FreeSerif18pt7b.h>
#include <Fonts/FreeSerif24pt7b.h>
//=============================== Symbolic Constants ===============================


#define DEBUG                                           // Comment out when not debugging
#define VERSION                     "017"                  // Software version
#define SPLASHDELAY                 2000L               // Normally, 4000L

//  Calibration Constants
#define VMZERO     0
#define VZZERO     0
#define VRZZERO    0

#define VMGAIN     1.0
#define VZGAIN     1.0
#define VRZGAIN    1.0

//end calibration constants
#define LOWEND160M                  1800000L
#define HIGHEND160M                 2000000L

#define LOWEND80M                  3500000L
#define HIGHEND80M                 4000000L

#define LOWEND40M                  7000000L
#define HIGHEND40M                 7300000L           // The 'L' helps document that these are long data types
#define LOWEND30M                  10100000L
#define HIGHEND30M                 10150000L
#define LOWEND20M                  14000000L
#define HIGHEND20M                 14350000L
#define LOWEND17M                  18068000L
#define HIGHEND17M                 18168000L

#define LOWEND15M                  21000000L
#define HIGHEND15M                 21450000L
#define LOWEND12M                  24890000L
#define HIGHEND12M                 24990000L
#define LOWEND10M                  28000000L
#define HIGHEND10M                 28700000L
#define LOWENDFULL                  1800000L
#define HIGHENDFULL                 30000000L

#define MAXPOINTSPERSAMPLE          10
#define MAXMENUES                   4               // Extended ASCII for a block character
#define DIGITINDICATOR              25                 // Extended ASCII for a block character
#define DIGITSPACING4X                21 
#define NUMFREQPOINTSBAND               100
#define NUMFREQPOINTSFULL               430

#define LASTBANDUSED                0                   // This number is the byte-offset into the EEPROM memory space
#define OFFSETTOPOSITIONCOUNTS      sizeof(int)         // The start of the stepper positions for the band edges defined above
#define OFFSETTOPRESETS             sizeof(int) * 6     // There are 8 bands edges

#define PIXELWIDTH                  480                 // Display limits
#define PIXELHEIGHT                 320

#define YAXISSTART                  50                  // For graphing purposes
#define YAXISEND                    290
#define XAXISSTART                  40
#define XAXISEND                    430

#define PRESETSPERBAND              6                   // Allow this many preset frequencies on each band
#define MAXBANDS                    10                   // Can only process this many frequency bands
                 // Used to display increment cursor
   

#define FULLSCAN                    0
#define BANDSCAN                    1                   // Menuing indexes
#define SINGLESWR                   2
#define CAL                         3

#define LASTBANDUSED                0                   // This number is the byte-offset into the EEPROM memory space
#define OFFSETTOPOSITIONCOUNTS      sizeof(int)         // The start of the stepper positions for the band edges defined above
#define OFFSETTOPRESETS             sizeof(int) * 6     // There are 8 bands edges

#define XOFFSETMETER  235
#define YOFFSETMETER  60
#define M_SIZE 1
#define ILI9488_LIGHTGREEN  0x4aff4a      // 173, 255,  47 


//=============================== Pin Assignments ==================================
#define MENUENCODERSWITCH       PB3     //MENUFREQENCODER switch
#define MENUENCODERPINA         PB5     //MENUFREQENCODER
#define MENUENCODERPINB         PB4     //MENUFREQENCODER

#define FREQUENCYENCODERSWITCH      PB7    //Encoder2 switch
#define FREQUENCYENCODERPINA        PB6    //STEPPERENCODER
#define FREQUENCYENCODERPINB        PB8     //STEPPERENCODER

#define ZEROSWITCH                  25
#define MAXSWITCH                   25
#define STEPPERDIR                  25
#define STEPPERPUL                  25


#define VM             PB0       // Sampled without transmitter power
#define VRZ            PB1
#define VZ             PA1
#define VS           PA0

#define OPERFWD        PA2


#define OPERREV        PA3
#define OPERSW         PA4
#define TFT_CS         PC15

#define TFT_DC         PC14
#define TFT_RST        PB10

// following three pin definitions are needed by AD9850
#define W_CLK                       PB15   // connect to AD9850 module word load clock pin (CLK)
#define FQ_UD                       PB14   // connect to freq update pin (FQ)
#define DATA                        PB13   // connect to  data load pin (DATA)
#define RESET                       PB12   // connect to reset pin (RST)


//=============================== Globals ==========================================
extern char *menuOptions[];
extern int currentBand;
extern int plotPoints[][MAXPOINTSPERSAMPLE];
extern long bandEdges[][2];
extern long bandLimitPositionCounts[][2];
extern long currentFrequency;
extern long presetFrequencies[][PRESETSPERBAND];
extern double countPerHertz[];
extern double VSWR;
extern double SWR;
extern volatile int encoder2;     // + is CW, - is CCW
extern volatile long frequencyEncoderMovement;
extern volatile long menuEncoderMovement;
extern double RPosOld[];
extern double XPosOld[];
extern long bandCenter[];
//=============================== Objects ==========================================
extern Rotary menuEncoder;
extern Rotary frequencyEncoder;
extern ILI9488 tft;
extern  double pip;
extern   int zeroIncrement;
extern     float aveVm;
extern     float  aveVrz;
extern     float  aveVz;
extern   double linVm;
extern   double linVrz;
extern   double linVz;
extern    int zeroAveVz;
extern   double RValue;
extern   double XValue;
extern  double voltsConv;
extern double logAmpOut;
extern double logAmpOutOld;
extern uint16_t osx;
extern uint16_t osy; // Saved x & y coords
extern int old_analog;
extern double ltx;
extern double supplyVolt;
extern  double ZMag;
extern   double angle;
extern   double reflCoeff;
extern  int incrementPad;
//extern  int numFreqPoints;
extern double SWRPosOld[];
extern double minFreq;
extern int endFlag;
extern int whichBandOption;

extern float yCal25;  //Difference value between actual and readout RValue from Cal routine
extern float yCal50;
extern float yCal200;
extern int VmCal;
extern int VzCal;
extern int VrzCal;
//=============================== Function Prototypes ==============================
void SingleFrequency(int whichBandIndex);
void DDSWakeUp();
void DefineEEPROMPage();
void DoNewCalibrate();
void EraseBelowMenu();
void ErasePage();
void frequencyISR();
void GraphAxis(int whichBandOption);
void menuISR();
void  MakeMenuSelection();
void MyDelay(unsigned long millisWait);
void outOne();
void outZero();
void PlotGrid(int whichBandOption);
void PlotSWRValue(int whichBandOption, double swr);
void ReadBandPresets();
void ReadCurrentBand();
void ReadEEPROMData();
void ReadPositionCounts();
double ReadSWRValue();
int  SelectBand();
void SendFrequency(long frequency);
void ShowEEPROMValues();
void  ShowMainDisplay();
void ShowPositionCounts();
void ShowSlopeCoefficients();
void ShowSubmenuData(double SWR, long cursorFrequency);
void ShowSWR(double swr, int x, int y);
void Splash();
int  WriteBandPresets();
void WriteCurrentBand();
void WriteDefaultEEPROMValues();
void WritePositionCounts();
void PlotRealTimeSWR(int whichBandOption);
void PlotFullRealTimeSWR();
void Calibrate();
void calSWR();
void analogMeter();
void plotNeedle(int value, byte ms_delay);
void DisplaySupplyVoltage();
void FindArrayMaxMin();
void menuSwitchISR();
void Calibrate();
#endif
