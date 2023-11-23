/*
                              LICENSE AGREEMENT

  This program source code and its associated hardware design at subject to the GNU General Public License version 2,
  https://opensource.org/licenses/GPL-2.0
  with the following additional conditions:
  1. Any commercial use of the hardware or software is prohibited without express, written, permission of the authors.
  2. This entire comment, unaltered, must appear at the top of the primary source file. In the Arduino IDE environemnt, this comment must
  appear at the top of the INO file that contains setup() and loop(). In any other environmentm, it must appear in the file containing
  main().
  3. This notice must appear in any derivative work, regardless of language used.

*/
#ifndef BEENHERE
#include "AT.h"
#endif



ILI9488 tft = ILI9488(TFT_CS, TFT_DC, TFT_RST);
Rotary menuEncoder      = Rotary(MENUENCODERPINA, MENUENCODERPINB);
Rotary frequencyEncoder = Rotary(FREQUENCYENCODERPINA, FREQUENCYENCODERPINB);

//Rotary menuEncoder = encoder(MENUENCODERPINA, MENUENCODERPINB, MENUENCODERSWITCH);
//Rotary frequencyEncoder = encoder(FREQUENCYENCODERPINA, FREQUENCYENCODERPINB, FREQUENCYENCODERSWITCH);

//========================================================= Global data ===================================
char *menuOptions[]     = {" FullScan", " Bands ", " Freq ", "Cal "}; // Menu text
char *bands[] = {" 160 ", " 80M ", " 40M ", " 30M ", " 20M ", " 17M ", " 15M ", " 12M ", " 10M "};
char *menuOptions2[3][3] = { {"Change Band", "Change Freq"},
  {"Change Band", "Activate", "Set"},
  {"Band Edges"}
};
//int numFreqPoints = 100;
long bandCenter[] = {1900000, 3750000, 7150000, 10125000, 14175000, 18118000, 21225000, 24940000, 28850000};
long presetFrequencies[8][PRESETSPERBAND];
int currentBand;                                //
long currentFrequency = 7000000L;
double VSWR;
double SWR;
float aveVm;
float  aveVrz;
float  aveVz;
double linVm;
double linVrz;
double linVz;
  int VmCal = 0;
  int VzCal = 0;
  int VrzCal = 0;
volatile int encoder2;     // + is CW, - is CCW
volatile long frequencyEncoderMovement;
volatile long menuEncoderMovement;
double  pip;
int zeroIncrement;
int zeroAveVz = 0;
double RValue;
double XValue;
// Meter
double voltsConv;
double logAmpOut;
double logAmpOutOld;
uint16_t osx = M_SIZE * 120, osy = M_SIZE * 120; // Saved x & y coords
int old_analog =  -999; // Value last displayed
double ltx = 0;
double supplyVolt;
double ZMag;
double angle;
double reflCoeff;
int incrementPad     = 0;

int endFlag = 0;
int i, submenuIndex, whichBandOption;
long minCount;
double minSWR;

// Calibration values for reference resistors
float yCal25;  //Difference value between actual and readout RValue from Cal routine
float yCal50;
float yCal200;


/*****
  Purpose: Logon Page

  Argument list:
    void

  Return value:
    void
*****/
void Splash()
{
  ErasePage();
  tft.setFont(&FreeSerif18pt7b);
  tft.setTextColor(ILI9488_MAGENTA, ILI9488_BLACK);
  tft.setCursor(PIXELWIDTH / 2 - 180, PIXELHEIGHT / 4 - 10 );
  tft.print("Graphic Antenna Analyzer");
  tft.setTextColor(ILI9488_RED, ILI9488_BLACK);
  tft.setCursor(PIXELWIDTH / 2 - 20, PIXELHEIGHT / 4 + 40);
  tft.print("by");
  tft.setCursor(PIXELWIDTH / 2 - 130, PIXELHEIGHT / 4 + 90);
  tft.setTextColor(ILI9488_GREEN, ILI9488_BLACK);
  tft.print("Al Peter  AC8GY");
  tft.setCursor(PIXELWIDTH / 2 - 160, PIXELHEIGHT / 4 + 140);
  tft.print("Jack Purdum  W8TEE");
  tft.setCursor(PIXELWIDTH / 2 - 160, PIXELHEIGHT / 4 + 190);
  tft.print("Version ");
  tft.print(VERSION);
  tft.setFont();
  tft.setTextSize(2);
  MyDelay(SPLASHDELAY);
  ErasePage();
}
/*****
  Purpose: to cause a delay in program execution
  Paramter list:
  unsigned long millisWait    // the number of millseconds to wait
  Return value:
  void
*****/
void MyDelay(unsigned long millisWait)
{
  unsigned long now = millis();
  while (millis() - now < millisWait)
    ;     // Twiddle thumbs...
}

void setup()
{
  int status;

  //#ifdef DEBUG
  Serial.begin(57600);
  MyDelay(1000);
  //#endif

  tft.begin();
  tft.setRotation(3);
  Splash();
  pinMode (W_CLK, OUTPUT);
  pinMode (FQ_UD, OUTPUT);
  pinMode (DATA, OUTPUT);
  pinMode (RESET, OUTPUT);

  pinMode(MENUENCODERPINA,   INPUT_PULLUP);
  pinMode(MENUENCODERPINB,   INPUT_PULLUP);
  pinMode(MENUENCODERSWITCH, INPUT_PULLUP);

  pinMode(FREQUENCYENCODERPINA,   INPUT_PULLUP);
  pinMode(FREQUENCYENCODERPINB,   INPUT_PULLUP);
  pinMode(FREQUENCYENCODERSWITCH, INPUT_PULLUP);

  pinMode(VM, INPUT) ;
  pinMode(VRZ, INPUT);
  pinMode(VZ, INPUT);

  pinMode (W_CLK, OUTPUT);
  pinMode (FQ_UD, OUTPUT);
  pinMode (DATA, OUTPUT);
  pinMode (RESET, OUTPUT);
  pinMode(PA6, INPUT);

  attachInterrupt(MENUENCODERPINA,  menuISR,      CHANGE);
  attachInterrupt(MENUENCODERPINB,  menuISR,      CHANGE);
  attachInterrupt(FREQUENCYENCODERPINA, frequencyISR, CHANGE);
  attachInterrupt(FREQUENCYENCODERPINB, frequencyISR, CHANGE);

  SendFrequency(0);    // Send the frequency
  MyDelay(500L);                      // Let DDS stabilize
}

void loop()
{
  DisplaySupplyVoltage();
  MakeMenuSelection();

}
