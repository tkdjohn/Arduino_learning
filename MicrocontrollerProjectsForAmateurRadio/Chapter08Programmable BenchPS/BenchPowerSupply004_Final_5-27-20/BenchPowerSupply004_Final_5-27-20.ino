/*****
  This software is licensed un the GNU General Public License, Version 3, as presetned in
  https://www.gnu.org/licenses/gpl-3.0.txt. You may use this software for non-commercial use. 
  For commercial use, contact the authors:
  Jack Purdum, W8TEE
  Al Peter, AC8GY

  This header file must be copied into all copies and deriviative works of this software
  and remain the very first thing in the primary source code file.
  
*****/
/*
  Ver 3.0, May 22, 2020, Jack Purdum  Activated calls to save variables to EEPROM
  Ver 2.1, May 16, 2020, Jack Purdum  Stareted to save EEPROM variables, ordered variables
*/
//                                  STM32F103, 128K version

#ifndef BEENHERE
#include "ProgPS.h"
#endif

//                                  declare objects
Adafruit_MCP4725 dac;
File myFile;
File root;
ILI9488 myDisplay = ILI9488(TFT_CS, TFT_DC, TFT_RST);
Menuing myMenu(DISPLAYWIDTH, DISPLAYHEIGHT, GREEN, BLACK, WHITE, BLACK, DEFAULTFONTSIZE);
station myUnion;;
Rotary rotary1 = Rotary(COARSEENCODERPINA, COARSEENCODERPINB);   //Coarse Encoder
Rotary rotary2 = Rotary(MENUENCODERPINA, MENUENCODERPINB);   //Menu Encoder
Rotary rotary3 = Rotary(FINEENCODERPINA, FINEENCODERPINB);   //Fine  Encoder
Sd2Card card;
SdVolume volume;
SdFile root2;
//Timer tDisplay;


//======================== User Parameters to set ============
//These variables should be setable at runtime by user.
int numPlotPoints = 200; // Delay between plot point samples: 100=> 30 sec, 50=> 15 sec
uint16 numFunctionCycles = 10;
uint16 functionDuration = 5000;// milliSeconds
float  startSetpointLevelVolts = 5; // Setpoint in Volts
float maxVoltageLevel = 20;   // Setpoint in Volts
uint16 numberOfSteps = 5;
long stepDuration   = 4000; // millisec.
long outTimeMilli = 0;
uint16 outTimeSec = 10;
uint16 outTimeMin = 1;
uint16 outTimeHour = 0;
long startSetpointLevel = 100; // Setpoint in PID units
long maxSetpointValue = 3000; // Setpoint in PID units
uint16 pulseTopWidth = 500; // pulse width in mS
float setPointCal = 149.62; //Initial voltage out Calibrate - Fine Tune in CalVoltage
float voltInCal = 30.226; //Initial screen display Calibrate - Fine Tune in CalVoltage
//===========================
char *CalibrationChar[]   = {"Voltage", "Current", "Exit   "};
char *GeneralChar[]       = {"Num Cycles", "Start Volts   ", "End Volts     ", "Duration  ", "Num Steps ", "Pulse Width", "Exit      "};
char *keyPadChar[]        = {"B", "0", "C", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
char *menuConfig[]        = {"General", "Time   ",  "Cal    ", "Exit   "};
char *menuFunction[]      = {" Ramp     ", " Step     ", " Sine     ", " Half sine", " Triangle ", " Trapizoid", " Pulse    ", " Timer    "};
char *menuLevel1[]        = {" Preset", " Funct.", " Keypad",  "  User  ", " Config"}; // Top level Menu
char *menuPreset[]        = {" 3.3V ",  " 5V   ", " 9V   ", " 12V  ", " 13.8V", " 15V  ", " 20V  ", " 25V  "};
char *menuUser[]          = {"SD Card", "Exit "};
char mySDFiles[MAXFILES][NAMELENGTH];
char *TimeChar[]          = {"Seconds  ", "Minutes", "Hours  ", "Exit   "};

uint8_t rotation;
uint8_t tNow;
uint8_t t;

int   activeColumn;
int   activeMenuIndex;                       // Which menu item is currently selected
int   activeMenuLevel;
int   activeRow;

int   choice;
int   choiceTime;
int   col;
int   counterReturn;
int   currentCompare;
int   currentInCompare;
int   currentInOldCompare;
int   defaultsList[]          = {0, 0, 0, 0, 0};         // Says: default is 0 for menuPreset, 0 for menuFunction, 0 for menuConfig
int   ditlen;
int   en1State;
int   en2State;
int   en3State;
int   encoderReadingOnOff;
int   encoderSWFlag;
int   eCounter1;
int   eCounter2;
int   eCounter3;
int   elements;                              // Holds menu elements
int   filesSD;
int   itemCount2;
int   k;
int   keypadDigitCounter;
int   keyPadXCoord[]          = {300,  350, 400, 300,  350, 400, 300,  350, 400, 300,  350, 400};
int   keyPadYCoord[]          = {230,  230, 230, 190, 190, 190, 150, 150, 150, 110, 110, 110};
int   lastChoice;
int   lastChoiceTime;
int   menuSelection;                         // Which menu is active
int   newPosition1;
int   numberCycles;
int   on_OffFlag;
int   old_count;
int   oldeCounter2;
int   oldeCounter1Rev;
int   oldIndex;
int   oldIndex2;
int   oldTimeSec;
int   oldTimeMin;
int   oldTimeHour;
int   outputOnOffFlag;                       // 0=off, 1=on
int   outputOnOffFlagOld = 1;
int   onOffFlag;
int   rampStartFlag;
int   row;
int   selectedMenuOption;
int   SetpointConv;
int   spacing;
int   status;
int   voltFlag;
int   voltIndex;
int   voltInCompare;
int   voltInOldCompare;
int   yOffset;
//int   x[]                     = {100, 100, 100, 100, 100, 100, 100};
int   xTimeValue[20];
//int   y[]                     = {150, 178, 206, 234, 262, 290, 318};
int   y[]                     = {130, 155, 180, 205, 230, 255, 280};
int   yVoltValue[20];

volatile int   count, oldCount, encoder2;     // + is CW, - is CCW

uint32_t counter2;
unsigned long xTime;

long display1UpdateOldTime;
long plotTime;
long xPositionOld;
long yPositionOld;
long stepTime;
long yTime;
long rampStart;                                // Setpoint   in PID units
float currentIn;
float currentInRaw;
float currentInOld2;
float numKeypad;
float numKeypad2;
float powerInOld;
float Setpoint;
//float setPointCal;
float SetpointVoltage;
float tiny;
float voltNumber;
float voltIn;
float voltInOld;
float voltInOld2;
float voltInRaw;
float xPosition;
int voltOnOffFlag = 0;
float oldSetPoint;
float PWMSet;
float Input, Output;
float encoder1Reading;
float encoder1Reading10;
float encoder3Reading;




//======================================================= Start of functions ============================
/*****
  Purpose: to cause a delay in program execution without blocking

  Parameter list:
  unsigned long millisWait - the number of millseconds to wait

  Return value:
  void
*****/
void MyDelay(unsigned long millisWait)
{
  unsigned long now = millis();
  while (millis() - now < millisWait)
    ;     // Twiddle thumbs...
}



/*****
  Purpose: Sign-on screen

  Paramter list:
    void

  Return value:
    void
*****/
void Splash()
{
  int row, col;
  myDisplay.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);
  row = 240 / 5;
  col = 320 / 4;
  myDisplay.setFont(&FreeSerif12pt7b);
  myDisplay.setTextColor(MAGENTA, BLACK);
  myDisplay.setCursor(180, 40);
  myDisplay.print(" Programmable");
  myDisplay.setCursor(180, 80);
  myDisplay.print(" Power Supply");
  myDisplay.setFont(&FreeSerif12pt7b);
  myDisplay.setTextColor(WHITE, BLACK);
  col = 480 / 2;
  myDisplay.setCursor(col, 120);
  myDisplay.print("by");
  myDisplay.setTextColor(GREEN, BLACK);
  myDisplay.setCursor(160, 170);
  myDisplay.print("Al Peter, AC8GY");
  myDisplay.setCursor(140, 210);
  myDisplay.print("Jack Purdum, W8TEE");
  myDisplay.setCursor(190, 250);
  myDisplay.setTextColor(MAGENTA, BLACK);
  myDisplay.print("Version  ");
  myDisplay.print(VERSION);
  MyDelay(1000UL);
}


//-------------------------------------------------------------- setup() ---------------------------------------------------------------------------------------------------

void setup()
{
  char c;
  char temp[10];
  int items;
  rotary1.begin();
  rotary2.begin();
  rotary3.begin();
  Serial.begin(115200);
  MyDelay(1000);

  pinMode(COARSEENCODERPINA,   INPUT_PULLUP);
  pinMode(COARSEENCODERPINB,   INPUT_PULLUP);
  pinMode(COARSEENCODERSWITCH, INPUT_PULLUP);
  pinMode(MENUENCODERPINA,   INPUT_PULLUP);
  pinMode(MENUENCODERPINB,   INPUT_PULLUP);
  pinMode(MENUENCODERSWITCH, INPUT_PULLUP);
  pinMode(FINEENCODERPINA,   INPUT_PULLUP);
  pinMode(FINEENCODERPINB,   INPUT_PULLUP);
  pinMode(FINEENCODERSWITCH, INPUT_PULLUP);

  attachInterrupt(COARSEENCODERPINA, encoder1ISR, CHANGE);
  attachInterrupt(COARSEENCODERPINB, encoder1ISR, CHANGE);

  attachInterrupt(MENUENCODERPINA, encoder2ISR, CHANGE);
  attachInterrupt(MENUENCODERPINB, encoder2ISR, CHANGE);

  attachInterrupt(FINEENCODERPINA, encoder3ISR, CHANGE);
  attachInterrupt(FINEENCODERPINB, encoder3ISR, CHANGE);

  attachInterrupt(FINEENCODERSWITCH, voltOnOffISR, CHANGE);

  myDisplay.begin();
  myDisplay.setRotation(1);
  myDisplay.fillScreen(ILI9488_BLACK);

  DefineEEPROMPage();   //EEPRom initiation
  //#ifdef DEBUG2      //Save default values to EEPRom


  //SaveConfigData();// Just show EEPROM
  delay(100);
  ShowConfigData();
  //#endif
  ReadConfigData();
  Splash();
  myDisplay.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);
  if (!SD.begin(PA4)) {
    Serial.println("SD initialization failed!");
    myDisplay.setFont(&FreeSerif12pt7b);
    myDisplay.setCursor(50, 140);
    myDisplay.print(F("Please insert SD Card"));
    myDisplay.setCursor(50, 170);
    myDisplay.print("and restart!");
    while (1) {
    }
  } else {
    Serial.println("SD initialization done.");
    //myDisplay.setFont(&FreeSerif12pt7b);
    myDisplay.setTextColor(YELLOW, BLACK);
    myDisplay.setCursor(50, 140);
    myDisplay.print(F("SD Card OK"));
    delay(500);
  }
  myDisplay.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);  //Clear entire screen
  myMenu.itemCount = ELEMENTS(menuLevel1);
  myMenu.spacing = myMenu.width / myMenu.itemCount;
  myMenu.showMenu(myDisplay, menuLevel1);
  dac.begin(0x60);  //Start the ouput voltage DAC

  drawVoltDisplay();
  myDisplay.fillRect(4, 6, 50, 50, BLACK);
  myDisplay.setCursor(5, 42);
  myDisplay.setTextColor(GREEN, BLACK);
  myDisplay.print("OFF");
  outputOnOffFlagOld = 0;
  outputOnOffFlag = 1;
}

void loop()
{
  //ShowConfigData();
  //char c;
  //int index;

  static int val = 0;

  if (en2State != 0) {
    MyDelay(150);
    if (activeMenuLevel == 0) {   // top-most menu, horizontal scroll

      myDisplay.setFont(&FreeSerif12pt7b);
      myDisplay.setTextColor(WHITE, BLACK);
      myMenu.deselectMenuItem(myDisplay, menuLevel1);
      myMenu.itemCount = ELEMENTS(menuLevel1);
      myMenu.scrollTopMenu(myDisplay, menuLevel1, encoder2, defaultsList);
#ifdef DEBUG
      Serial.print("top level  ");
      Serial.print("  activeMenuIndex = ");
      Serial.println(activeMenuIndex);
#endif
    } else {
      switch (activeMenuIndex) {      // The switch/case varies according to your menu levels
        case 0:                       // This is the first submenu, e.g.,
        myMenu.eraseMenus(myDisplay);
          myMenu.deselectMenuItem(myDisplay, menuFunction);
          myMenu.itemCount = ELEMENTS(menuFunction);
          myMenu.updateMenu(myDisplay, menuFunction, encoder2);
          break;

        case 1:                   // This is the second submenu, e.g.,  *menuFunction[]
          myMenu.eraseMenus(myDisplay);
          myMenu.deselectMenuItem(myDisplay, menuFunction);
          myMenu.itemCount = ELEMENTS(menuFunction);
          myMenu.updateMenu(myDisplay, menuFunction, encoder2);
          break;

        case 2:                   // This is the forth submenu, e.g.,  *menuConfig[]
          myMenu.deselectMenuItem(myDisplay, menuFunction);
          myMenu.itemCount = ELEMENTS(menuFunction);
          myMenu.updateMenu(myDisplay, menuFunction, encoder2);
          break;

        case 3:                   // This is the forth submenu, e.g.,  *menuUser[]
          myMenu.deselectMenuItem(myDisplay, menuUser);
          myMenu.itemCount = ELEMENTS(menuUser);
          myMenu.updateMenu(myDisplay, menuUser, encoder2);
          break;

        case 4:                   // This is the fifth submenu, e.g.,  *menuConfig[]
          myMenu.deselectMenuItem(myDisplay, menuConfig);
          myMenu.itemCount = ELEMENTS(menuConfig);
          myMenu.updateMenu(myDisplay, menuConfig, encoder2);
          break;

        default:                  // Something went south...
          break;
      }   // end switch
    }     // end else
#ifdef DEBUG1
    Serial.print("  activeMenuIndex = ");
    Serial.println(activeMenuIndex);
    Serial.print("in if:  encoder2 = ");
    Serial.println(encoder2);
#endif
    en2State = 0;
  }

  if (digitalRead(MENUENCODERSWITCH) == LOW) {               // This causes a menu to be selected
    myMenu.deselectMenuItem(myDisplay, menuLevel1);
    activeMenuLevel++;
    switch (activeMenuIndex) {                            // Only applies to submenus


      case 0:                                             // This is the Preset menu
        myMenu.itemCount = ELEMENTS(menuPreset);
        myMenu.showNewMenu(myDisplay, menuPreset, encoder2, defaultsList);
        selectedMenuOption = myMenu.selectFromMenu(myDisplay, menuPreset) + SECONDOFFSET;
        break;

      case 1:                                             // This is the menuFunction menu
        myMenu.itemCount = ELEMENTS(menuFunction);
        myMenu.showNewMenu(myDisplay, menuFunction, encoder2, defaultsList);
        selectedMenuOption = myMenu.selectFromMenu(myDisplay, menuFunction) + THIRDOFFSET;
        break;

      case 2:                                             // This is the , menukeypad Menu item
        DrawKeyPad();
        keypadDigitCounter = 0;
        MyDelay(200);
        //while (digitalRead(COARSEENCODERSWITCH) != LOW) {
        ReadKeypad();
        DoDACOut();
        if ((millis() - display1UpdateOldTime) >= 100) {
          DoScreenPrintVoltage();
          display1UpdateOldTime = millis();
        }
        // }
        break;

      case 3:                                             // This is the user  menu
        myMenu.itemCount = ELEMENTS(menuUser);
        myMenu.showNewMenu(myDisplay, menuUser, encoder2, defaultsList);
        selectedMenuOption = myMenu.selectFromMenu(myDisplay, menuUser) + FORTHOFFSET;
        break;

      case 4:                                             // This is the menuConfig menu
        myMenu.itemCount = ELEMENTS(menuConfig);
        myMenu.showNewMenu(myDisplay, menuConfig, encoder2, defaultsList);
        selectedMenuOption = myMenu.selectFromMenu(myDisplay, menuConfig) + FIFTHOFFSET;
        break;

      default:
        //Serial.print("I shouldn't be here: activeMenuLevel = ");
        //Serial.println(activeMenuLevel);
        break;
    }                                                     // end switch on activeMenuIndex
    MyDelay(100UL);
#ifdef DEBUG1                                             // Show what was chosen...
    Serial.print("selectedMenuOption = ");
    Serial.println(selectedMenuOption);
    Serial.print("   activeColumn = ");
    Serial.println(activeColumn);
    Serial.print("   activeRow = ");
    Serial.println(activeRow);
#endif
    myDisplay.setCursor(200, 150);
    myDisplay.setTextColor(YELLOW, BLACK);
    switch (selectedMenuOption) {
      case 0:
        break;
      //-------------------------
      case 100:                                                 // 3.3V
        myDisplay.print("Press Coarse to Exit");
        while (digitalRead(COARSEENCODERSWITCH) != LOW) {
          Setpoint = DACConvert(3.3) + 20;
          DoDACOutAndScreenUpdate(display1UpdateOldTime);
        }
        break;

      case 101:
        myDisplay.print("Press Coarse to Exit");// 5V
        while (digitalRead(COARSEENCODERSWITCH) != LOW) {
          Setpoint = DACConvert(5) + 20;
          DoDACOutAndScreenUpdate(display1UpdateOldTime);
        }
        break;

      case 102:
        myDisplay.print("Press Coarse to Exit");// Row 1: 9V
        while (digitalRead(COARSEENCODERSWITCH) != LOW) {
          Setpoint = DACConvert(9) + 10;
          DoDACOutAndScreenUpdate(display1UpdateOldTime);
        }
        break;

      case 103:
        myDisplay.print("Press Coarse to Exit");// Row 1: 12V
        while (digitalRead(COARSEENCODERSWITCH) != LOW) {
          Setpoint = DACConvert(12);
          DoDACOutAndScreenUpdate(display1UpdateOldTime);
        }
        break;

      case 104:                                                 // Row 1: 13.8V
        myDisplay.print("Press Coarse to Exit");
        while (digitalRead(COARSEENCODERSWITCH) != LOW) {
          Setpoint = DACConvert(13.8);
          DoDACOutAndScreenUpdate(display1UpdateOldTime);
        }
        break;

      case 105:
        myDisplay.print("Press Coarse to Exit");// Row 1: 15V
        while (digitalRead(COARSEENCODERSWITCH) != LOW) {
          Setpoint = DACConvert(15);
          DoDACOutAndScreenUpdate(display1UpdateOldTime);
        }
        break;

      case 106:
        myDisplay.print("Press Coarse to Exit");// Row 1: 20V
        while (digitalRead(COARSEENCODERSWITCH) != LOW) {
          Setpoint = DACConvert((float)20.) - 20;
          DoDACOutAndScreenUpdate(display1UpdateOldTime);
        }
        break;

      case 107:
        myDisplay.print("Press Coarse to Exit");// Row 1: 25V
        while (digitalRead(COARSEENCODERSWITCH) != LOW) {
          Setpoint = DACConvert((float)25.) - 20;
          DoDACOutAndScreenUpdate(display1UpdateOldTime);
        }
        break;                                                  //------------------------- Column 2: Function

      case 200:                                                 // Row 1: Ramp
        DoRampCalc();
        break;

      case 201:  // Row 1: Step
        DoStepCalc();
        break;

      case 202:  // Row 1: Sine
        DoSineCalc();
        break;

      case 203:  // Row 1: Half Sine
        DoHalfSineCalc();
        break;

      case 204:  // Row 1: Triangle
        DoTriangleCalc();
        break;

      case 205:  // Row 1: Trapizoid
        DoTrapazoidCalc();
        break;

      case 206:  // Row 1: Pulse
        DoPulseOut();
        break;

      case 207:  // Row 1: Timer
        DoTimerVoltOut();
        break;

      //-------------------------  Column 4: SD Card
      case 300:
        myDisplay.fillRect(0, 70, DISPLAYWIDTH, 230, BLACK);
        ShowFiles();
        SelectFile();
        ReadDataFile();
        GraphSDData ();
        break;

      // case 301:
      //  myDisplay.fillRect(0, 70, DISPLAYWIDTH, 230, BLACK);
      //  ShowFiles();
      //  break;
      //------------------------- Column 5: Settings

      case 400:
        DisplayGeneral();
        SelectGeneral();
        ChangeGeneralSelection();
        break;

      case 401:
        //displayTimeCategories();
        displaySetTime();
        SelectTime();
        ChangeTimeSelection();
        break;

      case 402:
        calVoltage();
        break;
    }
    activeMenuLevel = activeMenuIndex = 0;      // Reset for top-most menu
    myMenu.itemCount = ELEMENTS(menuLevel1);
    myMenu.spacing = myMenu.width / myMenu.itemCount;
    myMenu.eraseMenus(myDisplay);
    drawVoltDisplay();
    myMenu.showMenu(myDisplay, menuLevel1);

  }     // End of switch press

  encoderRead1();
  encoderRead3();
  Setpoint = encoder3Reading + encoder1Reading10 + numKeypad2 * setPointCal;
  DoDACOut();
  DoScreenPrintVoltage();
}
