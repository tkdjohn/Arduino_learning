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
  Release 2.01  April 27, 2019, Jack Purdum, W8TEE, adjusted constants for power calculation
      and modified test routine.
  Release 2.00  April 24, 2019, Jack Purdum, W8TEE, Al Peter, AC8GY Project start from 
    original DL
*/
//                                Compiled with Arduino Nano
//   NOTE: Some clones require using old bootloader option for upload (Tools --> Processor --> ATMega328P (Old Bootloader))
#define VERSION "v0.2s"   // 's' appended to version means Split Dummy Load (ie the diode pulls voltage from 
                          // the center of a 2 banks of resistors that provide the 50 Ohm load. 
#include <Wire.h>
#include <Adafruit_GFX.h>       // https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_SSD1306.h>   // https://github.com/adafruit/Adafruit_SSD1306

// #define DEBUG_SENSOR                 // Uncomment to calibrate and debug
// #define DEBUG_CALC 
// #define DEBUG_DISPLAY
// #define DEBUG_TIMER
/*
  The following symbolic constants will vary somewhat depending upon how you build
  your version of the MDL. 
 */
#define DIODE_VOLTAGE_DROP      0.289      // Voltage drop from diode you selected.
#define R1_OHMS                29.510      // Resistor R1 in voltage divider circuit
#define R2_OHMS                 3.175      //     "    R2               "
#define Vp_CALIBRATION_CONST    0.989      // This, too.
#define P_CALIBRATION_CONST     1.000      // 
/* 
  If your circuit measures the voltage between the resistors in a split load, and those loads have equal resistance:
    1) DUMMY_LOAD_OHMS should be set to the value of the load you're measuring the voltage aross (ie half the total load). 
    2) RMS_CONSTANT should be set to 1.0 insteald of SQRT(2)/2
  This is necessary because you're actually measuring half the power through half the load. We could just multiply
  the calculated power by two, except the calculated power depends on adding in the voltage lost in the diode and that 
  voltage doesn't change based on where the diode is connected. Thereofre, we must adjust the measured voltage BEFORE
  adding in the diode voltage. Which means at the same point where we convert the measured (peak) voltage to an RMS voltage.
  Since P = V^2/R  doubling the power means multiplying the voltage by the square root of 2, but to convert to RMS, we 
  multiply by the square root of 2 divided by 2.  so sqrt(2) * sqrt(2) / 2 = 2/2 = 1.
  But we're not done. We also have to double R because math.
  The math works out such that if you use twice the load value
  If the two loads are not nearly equal in resistance, more math will be necessary than is provided in this code.
*/
#define DUMMY_LOAD_OHMS         24.5       // Measure your RF power resistor resistance and place its value here.
#define WARNING_POWER_THRESHOLD 20.0       // Set this to a value at which you want the screen to warn the user.
#define RMS_CONSTANT             1.0       // 0.70711 - for non split mode. 1.0 for split mode. See above.          
#define VOLTS_PER_UNIT   (5.0/1024.0)      // 10-bit ADC is 1024 units with a max of 5V on the pin

#define DISPLAY_INTERVAL 500

#define RX_DETECT_WARNING_THRESHOL  9999
#define POWER_WARNING_THRESHOLD    19.95

#define SENSOR_PIN               A2        // Analog pin that samples the voltage
#define READS_PER_AVG            50        // We use a sample average for display
#define SENSOR_READ_INTERVAL     10        // ms to wait between reads to allow pin to 'settle'
#define REFRESH_DELAY            50        // Additional time to wait before starting the next cycle of reading/updating 
#define DISPLAY_WIDTH           128
#define DISPLAY_HEIGHT           64
#define X_CENTER            (DISPLAY_WIDTH/2) 
#define Y_CENTER            (DISPLAY_HEIGHT/2)
Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
#define sensorAverage ((float)sensorSum/(float)READS_PER_AVG)

unsigned long rxStartMills = 0;

short sensorData[READS_PER_AVG];
int sensorIndex = 0;
int sensorSum = 0;
unsigned long lastSensorReadMills = 0;
unsigned long lastReportMills = 0;
bool displayInvert = false; 
/*****
  Let's get things started.
*****/
void setup() 
{
  // Don't need the serial object unless debugging
#if defined(DEBUG_SENSOR) || defined(DEBUG_CALC) || defined(DEBUG_DISPLAY) || defined(DEBUG_TIMER)     
  Serial.begin(115200);                       
#endif

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  Splash();                                   
}

/*****
  MAIN LOOP
*****/
void loop() {
  unsigned long currentMills;
  currentMills = millis();
  ReadSensor(SENSOR_PIN, currentMills);

  DisplayResults(currentMills);         
}

/*****
  To show sign on at start up
*****/
void Splash()
{
  display.clearDisplay();     // Clear the graphics display buffer.
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(  "Mini Dummy Load ");
  display.println(VERSION);
  display.println("          by         ");
  display.println("     John, KN4YMJ    ");
  display.println();
  display.println();
  display.println(" Original design by: ");
  display.println(" Jack Purdum, W8TEE  ");
  display.println("   Al Peter, AC8GY   ");
  display.display();
  delay(2000);
}

/*****
  Read and average a value from the specified pin.
*****/
void ReadSensor(int pin, unsigned long currentMills) {
  if (currentMills - lastSensorReadMills < SENSOR_READ_INTERVAL)
    return;

  lastSensorReadMills += SENSOR_READ_INTERVAL;

  if (rxStartMills == 0) {
    rxStartMills = currentMills;
  }

  sensorSum -= sensorData[sensorIndex]; // Remove oldest sensor value
  int newValue = analogRead(pin);
  sensorData[sensorIndex] = newValue;
  sensorSum += newValue;
  sensorIndex = (sensorIndex + 1) % READS_PER_AVG;

  if (sensorAverage < 10) {
    rxStartMills = 0;
  } 

#ifdef DEBUG_SENSOR  
  Serial.print("sum = ");Serial.println(sensorSum);
  Serial.print("avg = ");Serial.println(sensorAverage);
#endif //DEBUG_SENSOR
}

/*****
  Display the measurements in a manner that is easy on the eyes.
*****/
void DisplayResults(unsigned long currentMills) {
  if (currentMills - lastReportMills < DISPLAY_INTERVAL) 
     return;
  lastReportMills += DISPLAY_INTERVAL;

  char textLine[(DISPLAY_WIDTH/6)+1];

  display.clearDisplay();
  display.setTextColor(WHITE);

  displayHorizCentered("Power In", 1, 0);

  float Vp = GetPeakVoltage();
  float power = CalculateWatts(Vp);

  getPowerString(power, sizeof(textLine), textLine);
  displayHorizCentered(textLine, 3, 15);

  char volts[8];
  dtostrf(Vp,4,2,volts);
  sprintf(textLine,"Vp: %s", volts);
  displayHorizCentered(textLine, 1, 45);

  // This will display the time (minutes:seconds) since boot, unless an active signal 
  // is present, in which case it will display the time since the signal was first 
  // detected. 
  unsigned long millsSinceRxDetect = currentMills - rxStartMills;
  getTimeStringFromMills(millsSinceRxDetect, sizeof(textLine), textLine);
  
  // Use y offset of 7 bc we don't care about the space at the bottom the chars.
  // We would care if text has a g, j, q, y.
  displayLeftJustified(textLine, 1, DISPLAY_HEIGHT - 7);
  displayRightJustified(VERSION, 1, DISPLAY_HEIGHT - 7);

#ifdef DEBUG_DISPLAY
  drawCrossHairs();
#endif //DEBUG_DISPLAY

  if ((power > POWER_WARNING_THRESHOLD) || (rxStartMills != 0 && millsSinceRxDetect > RX_DETECT_WARNING_THRESHOL)) {
    displayInvert= !displayInvert;
    display.invertDisplay(displayInvert);
  }
  else {
    displayInvert = false;
    display.invertDisplay(false);
  }

  display.display();
}

/*****
  Convert the value read from the MDL/s analog pin and convert it to watts. The
  circuit uses a voltage divider to make sure the Nano's 5V limit is not exceeded.
  This is based on the formula:
    Vpeak = Vmeasured * (1 + (R1/R2))
  
  The sensor reads an integer value between 0 and 1023 (1024 distinct values) for the range of 0-5V.  
  Thus, we can multiply the sesnor reading by 5/1024 to determine volts measured.
    Vmeasured = sensorAverage * VOLTS_PER_UNIT 
  
  Note that this is not the actual peak voltage since it does not yet account for the diode's voltage drop.
  However, this value is easy to measure with a multi meter and so can be used for calibration.
*****/
float GetPeakVoltage()
{
  float voltsPeak = Vp_CALIBRATION_CONST * (sensorAverage * VOLTS_PER_UNIT) * (1.0 + ((float)R1_OHMS / (float)R2_OHMS));
  if (voltsPeak < 0.015) voltsPeak = 0;
#ifdef DEBUG_CALC
  Serial.print("Vp = ");Serial.print(voltsPeak);Serial.println("V");
#endif // DEBUG_CALC
  return voltsPeak;
}

/****
  Calculate RMS Power.

  Given Vin we need to convert to Vrms, so we can apply the power equation.
  We also need to add the diode's voltage drop after converting to RMS.

  Knowing the input voltage allows us to determine the power: Pw =  Vin * Vin / R
****/
float CalculateWatts(float voltsIn)
{
  float voltsRMS = 0;
  float dummyLoadOhms = DUMMY_LOAD_OHMS;
  
  if (voltsIn > DIODE_VOLTAGE_DROP) {
    voltsRMS = (RMS_CONSTANT * voltsIn) + DIODE_VOLTAGE_DROP;   // Convert Vpeak to RMS and add diode D1 voltage drop
  }
  float powerRMS = P_CALIBRATION_CONST * (voltsRMS * voltsRMS ) / DUMMY_LOAD_OHMS;         
#ifdef DEBUG_CALC
  Serial.print("P = ");Serial.print(powerRMS);Serial.println("W");
#endif //DEBUG_CALC
  return powerRMS;                            // Apply your factor
}

/*****
  Format the power into a pretty string so we can inform the user.
*****/
void getPowerString(float power, int strsize, char *powerStr) {
  char out[6];
  if (power < 0.9995) {
    dtostrf(power, -4, 3, out); 
  } else if (power < 9.995) {
    dtostrf(power, -3, 2, out); 
  } else if (power < 99.95) {
    dtostrf(power, -3, 1, out); 
  } else { 
    dtostrf(power, -3, 0, out);
  }
  
  int minsize = min(strlen(out), strsize);
  strncpy(powerStr, out, minsize);
  powerStr[minsize] = '\0';
}

/*****
  Generate a string of running time m:ss so we can inform the user.
*****/
void getTimeStringFromMills(long mills, int strsize, char *timeStr) {
  char out[6];

  int secs = mills/1000 % 60;
  int mins = mills/60000;
  sprintf(out, "%02d:%02d", mins, secs);

  int minsize = min(strlen(out), strsize);
  strncpy(timeStr, out, minsize);
  timeStr[minsize] = '\0';
}

/*****
  Get text width in pixels based on textSize
*****/
int getTextWidthinPx(int textSize) {
  // from: https://forum.arduino.cc/t/how-many-pixel-width-for-one-char-in-tft-screen/464907
  // The space occupied by a character using the standard font is 6 pixels wide by 8 pixels high.
  // A two characters string sent with this command occup a space that is 12 pixels wide by 8 pixels
  switch (textSize) {
      default:
      case (1): return 6; 
      case (2): return 12;  // untested
      case (3): return 17;  // 17 and not 18 b/c space between chars isnt' scaled the same as the characters.
    }
}

/*****
  Center text on the screen. NOTE: Does not call display.display. 
*****/
void displayHorizCentered(const char *text, int textSize, int y) {
  int textScale = getTextWidthinPx(textSize);
 
  int x = X_CENTER - textScale*strlen(text)/2;
  display.setTextSize(textSize);
  display.setCursor(x, y);
  display.print(text);
}

/*****
  Right justify text on the screen. NOTE: Does not call display.display. 
*****/
void displayRightJustified(const char *text, int textSize, int y) {
  int textScale = getTextWidthinPx(textSize);
  display.setTextSize(textSize);
  display.setCursor(DISPLAY_WIDTH - (6 * strlen(text)),y);
  display.print(text);
}

/*****
  Left justify text on the screen. NOTE: Does not call display.display. 
*****/
void displayLeftJustified(const char *text, int textSize, int y) {
  display.setTextSize(textSize);
  display.setCursor(0,y);
  display.print(text);
}
#ifdef DEBUG_DISPLAY
/*****
  Draw some crosshairs to make centering things easy.
*****/
void drawCrossHairs() {
  display.drawLine(X_CENTER,0,X_CENTER, DISPLAY_HEIGHT, WHITE);
  display.drawLine(0,Y_CENTER,DISPLAY_WIDTH, Y_CENTER, WHITE);
  //display.drawRect(0, 0, 128, 64, WHITE);
}
#endif //DEBUG_DISPLAY