#ifndef BEENHERE
#define BEENHERE

#define VERSION   3.12
typedef unsigned int uint16;

//#define DEBUG 
#define DEBUG1 // Comment this out when done testing
//#define DEBUG2   // Uncomment tosave default parrameter values to EEProm
#define ELEMENTS(x) (sizeof(x) / sizeof(x[0]))


//#include <Adafruit_SPIDevice.h>
#include <Adafruit_GFX.h>           // https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_MCP4725.h>       // https://github.com/adafruit/Adafruit_MCP4725
#include <Fonts/FreeSerif9pt7b.h>   // In Adafruit_GFX
#include <Fonts/FreeSerif12pt7b.h>  //       "
#include <ILI9488.h>                // https://github.com/jaretburkett/ILI9488
#include <Rotary.h>                 // https://github.com/brianlow/Rotary
#include <Time.h>                   // https://github.com/PaulStoffregen/Time/blob/master/TimeLib.h
#include <TimeLib.h>                // https://github.com/PaulStoffregen/Time/blob/master/TimeLib.h
#include <EEPROM.h>                 // Standard with IDE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <SD.h>
//#include <SPI.h>
#include <Wire.h>
#include "Menu.h"                   // Jack's Menu Library

//=================================================== Symbolic Constants ==============================================
//                              For the Adafruit display shield, these are the default pins.
#define TFT_CS                  PA1
#define TFT_DC                  PA0
#define TFT_LED                 PB0
#define TFT_RST                 PB4

#define PIN_INPUT               PA5     // Read Voltage Pin
#define PIN_OUTPUT              PB0     // Output to DAC Pin
#define CURR_INPUT              PB1     // Read Current Sensor Pin
#define PIN_INPUT               PA3     // Read Voltage Pin
#define PIN_OUTPUT              PB0     // Output to DAC Pin

#define ROTARYDELAY             150     // Milliseconds for display delay

#define COARSEENCODERSWITCH     PA8     // Encoder1   "Coarse"
#define COARSEENCODERPINA       PA10    // Encoder1
#define COARSEENCODERPINB       PA9     // Encoder1
 
#define MENUENCODERSWITCH       PB14    // Encoder2   "Menu"
#define MENUENCODERPINA         PB12    // Encoder2
#define MENUENCODERPINB         PB13    // Encoder2

#define FINEENCODERSWITCH       PB3     // Encoder2   "Fine"
#define FINEENCODERPINA         PB4     // Encoder2
#define FINEENCODERPINB         PB5     // Encoder2

#define ON_OFFPIN               PB15    // Push Button SW to turn output on and off
#define DISPLAYDELAY            500     // Delay between voltage display updates

#define DISPLAYWIDTH            480
#define DISPLAYHEIGHT           320
#define DEFAULTFONTSIZE           1
#define TOPDEADSPACE             35     // All dropdown submenus appear below top line which never disappears
#define ROWSPACING               28     // Pixel count between rows
#define FONTROWOFFSET            85
#define MARGINROWOFFSET         (FONTROWOFFSET + 8)
#define BELOWMENUS              (DISPLAYHEIGHT - FONTROWOFFSET)

#define FIRSTOFFSET               0     // Offsets are used to generate a unique menu number by adding the offset to activeMenuIndex
#define SECONDOFFSET            100
#define THIRDOFFSET             200
#define FORTHOFFSET             300
#define FIFTHOFFSET             400
//                                        Color definitions
#define BLACK                   0x0000
#define BLUE                    0x001F
#define RED                     0xF800
#define GREEN                   0x07E0
#define CYAN                    0x07FF
#define MAGENTA                 0xF81F
#define YELLOW                  0xFFE0
#define WHITE                   0xFFFF
#define DKGREEN                 0x03E0
#define DARKVIOLET              0x00D3

#define CW                      1
#define CCW                     -1

#define DISPLAYOFFSET           (WPMOFFSET + 1) // Is display ON or OFF?

#define SCREENWIDTH             16              // Chars on one line of LCD

#define OFF                     0               // Used for display state
#define ON                      1
#define MAXFILES                20              // Number of SD files that can be opened
#define NAMELENGTH              5 
#define TOPMARGIN               60

#define LEFTMARGIN              170

#define MAXFILES                20              // Number of SD files that can be opened
#define NAMELENGTH              13

//======================================== Global declarartions ==================================
extern char *CalibrationChar[];
extern char *GeneralChar[];
extern char *keyPadChar[];
extern char *menuConfig[];
extern char *menuFunction[];
extern char *menuLevel1[];
extern char *menuPreset[];
extern char mySDFiles[MAXFILES][NAMELENGTH];
extern char *StepChar[];
extern char *TimeChar[];
extern char *TimeSet[];

extern uint8_t rotation;
extern uint8_t tNow;
extern uint8_t t;

extern uint16   functionDuration;
extern uint16   numberOfSteps;
extern uint16   outTimeSec;
extern uint16   outTimeMin;
extern uint16   outTimeHour;

extern int   activeColumn;
extern int   activeMenuIndex;                       // Which menu item is currently selected
extern int   activeMenuLevel;
extern int   activeRow;

extern int   choice;
extern int   choiceTime;
extern int   col;
extern int   counterReturn;
extern int   currentCompare;
extern int   currentInCompare;
extern int   currentInOldCompare;
extern int   defaultsList[];
extern int   ditlen;
extern int   en1State;
extern int   en2State;
extern int   en3State;
extern int   encoderReadingOnOff;
extern int   encoderSWFlag;
extern int   eCounter1;
extern int   eCounter2;
extern int   eCounter3;
extern int   eCounter2;

extern int   elements;                              // Holds menu elements
                         // Normal or Farnsowrth
extern int   filesSD;
extern int   *GeneralVariables[];
extern int   itemCount2;
extern int   k;
extern int   keypadDigitCounter;
extern int   keyPadXCoord[];
extern int   keyPadYCoord[];
extern int   lastChoice;
extern int   lastChoiceTime;
extern int   menuSelection;                         // Which menu is active
extern int   newPosition1;
extern int   numberCycles;
extern int   numPlotPoints;                         // # plot point   samples: 
extern uint16    numFunctionCycles;
extern int   on_OffFlag;
extern int   old_count;
extern int   oldeCounter2;
extern int   oldeCounter1Rev;
extern int   oldIndex;
extern int   oldIndex2;
extern int   oldTimeSec;
extern int   oldTimeMin;
extern int   oldTimeHour;
extern int   outputOnOffFlag;                       // 0=off, 1=on
extern int   outputOnOffFlagOld;
extern int   onOffFlag;
extern int   rampStartFlag;
extern int   row;
extern int   SetpointConv;
extern int   selectedMenuOption;
extern int   spacing;
extern int   status;
extern int   voltFlag;
extern int   voltIndex;
extern int   voltInCompare;
extern int   voltInOldCompare;
extern int   yOffset;
//extern int   x[];
extern int   xTimeValue[];
extern int   y[];
extern int   yVoltValue[];

extern volatile int   count, oldCount, encoder2;     // + is CW, - is CCW

extern  uint32_t counter2;
extern unsigned long xTime;
extern long plotTime;
extern long xPositionOld;
extern long yPositionOld;
extern long stepTime;
extern long yTime;
extern long rampStart;                                // Setpoint   in PID units
extern long startSetpointLevel;                       // Setpoint   in PID units
extern long maxSetpointValue;                         // Setpoint   in PID units
extern uint16 pulseTopWidth;
extern long stepDuration;                             // millisec.
extern long outTimeMilli;


extern float currentIn;
extern float currentInRaw;
extern float currentInOld2;
extern float numKeypad;
extern float numKeypad2;
extern float powerInOld;
extern float Setpoint;
extern float setPointCal;
extern float SetpointVoltage;
extern float tiny;
extern float voltNumber;
extern float voltIn;
extern float voltInOld;
extern float voltInOld2;
extern float voltInRaw;
extern float xPosition;
extern float  startSetpointLevelVolts;                  // Setpoint   in Volts
extern float maxVoltageLevel;                           // Setpoint   in Volts
extern float voltInCal;
extern int voltOnOffFlag;
extern float oldSetPoint;
extern float PWMSet;
extern float Input, Output;
extern float encoder1Reading;
extern float encoder1Reading10;
extern float encoder3Reading;


//                                  declare objects
union station{
  uint16 myBytes[2];
  int val;
  float num;
};
extern station myUnion;

extern Adafruit_MCP4725 dac;
extern File myFile;
extern File root;
extern ILI9488 myDisplay;
extern Menuing myMenu;
extern Rotary rotary1;
extern Rotary rotary2;
extern Rotary rotary3;
extern Sd2Card card;
extern SdVolume volume;
extern SdFile root2;
//extern Timer tDisplay;

//=============================================== Function Prototypes ====================================
void  calVoltage();
void  ChangeGeneralSelection();

void  ChangeTimeSelection();
void  DoDACOut();
void  DoDACOutAndScreenUpdate(long display1UpdateOldTime);
float DACConvert(float voltNumber);
void  DefineEEPROMPage();
void  DisplayGeneral();
void  displaySetTime();
void  displayTimeCategories();
void  DisplayStep();
void  displayTimer();
void  DoHalfSineCalc();
void  DoPulseOut();
void  DoRampCalc();
void  DoScreenPrintVoltage();
void  DoSineCalc();
void  DoStepCalc();
void  DoTimerVoltOut();
void digitalClockDisplay();
void printDigits(int digits);
void  DoTrapazoidCalc();
void  DoTriangleCalc();
void  DrawKeyPad();
void  drawVoltDisplay();
void  encoder1ISR();
void  encoder2ISR();
void  encoder3ISR();
int   encoderRead1();
int   encoderRead3();
void formatTime(long startTime1);
void  functionDataPrint();
void  GraphAxis();
void  GraphSDData ();
void  MyDelay(unsigned long millisWait);
void  NumCycles();

void  read_encoder();

void  PlotVoltage();

void  ReadKeypad();
void  SelectStep();
void  ReadDataFile();
void  ReadConfigData();
void  SaveConfigData();
int   SelectFile();
void  SelectGeneral();
void  SelectTime();
int   setpointCalc();
void  ShowConfigData();
int   ShowFiles();
void  ShowString(char s[], int   pass);
void  Splash();
void  voltOnOffISR();


#endif
