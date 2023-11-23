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

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>       // https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_SSD1306.h>   // https://github.com/adafruit/Adafruit_SSD1306

//#define DEBUG                 // Uncomment to calibrate and debug

/*
  The following symbolic constants will vary somewhat depending upon how you build
  your version of the MDL. 
 */
#define MYDUMMYLOADOHMS           51        // Measure your RF power resistor resistance and place its value here
#define MYR1VALUE              56000        // Resistor R1 in voltage divider circuit
#define MYR2VALUE               2000        //     "    R2               "
#define CALIBRATIONOFFSET    1.00408        // This, too.
#define DIODEVOLTAGEDROP       0.608        // Voltage drop from diode you selected.

#define MILLIVOLTSPERUNIT     0.0049        // 10-bit ADC is 1024 units with a max of 5V on the pin
#define OLED_RESET                 4        // Used by the library
#define SENSORPIN                 A1        // Analog pin that samples the voltage
#define ITERATONS                 30        // We use a sample average for display
#define SQRT2DIVIDEDBY2         0.707       // RMS to DC conversion constant 

#define SENSORMAX                1023       // Max-min values for analog pin A1
#define SENSORMIN                   0

Adafruit_SSD1306 display(OLED_RESET);
float CalculateWatts();

int sensorValue = 0;         // the sensor value



/*****
  Purpose: To show sign on at start up

  Parameter list:
    void

  Return value: 
    void 

    CAUTION: 
*****/

void Splash()
{
  display.clearDisplay();     // Clear the graphics display buffer.
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(" Mini DUMMY LOAD");
  display.println("       by");
  display.println("Jack Purdum, W8TEE");
  display.println(" Al Peter, AC8GY");
  display.display();
}

void setup() 
{
#ifdef DEBUG  
  Serial.begin(115200);                       // Don't need the serial object unless debugging
#endif

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

  Splash();                                   // Show start up screen
#ifdef DEBUG                                  // Probably only need to call once to tweak things
  TestSensorRead();                           // Done when first testing
  delay(500);
#endif  
}


void loop() {
  char buff[6];
  char pad[] = "       ";    // 7 spaces
  int where;
  int i;
  float sum;

  sum = 0.0;
  i = 0;
  while (i < ITERATONS) {                   // Do a bunch of reads
    sum += (float)analogRead(SENSORPIN);    // Input from voltage divider
    delay(10);                              // Let pin settle
    i++;
  }
  sum /= ITERATONS;                         // Average reading after ITERATIONS analog reads
#ifdef DEBUG  
  Serial.print("sum=  ");Serial.println(sum);
#endif
  dtostrf(CalculateWatts(sum), 5, 2, buff); // Calculate the power

  where = strlen(buff);         // How big is the result?
  strcpy(&pad[6 - where], buff);        // Update only the new number.
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("      WATTS IN");
  display.setTextSize(3);
  where = (6 - where) * 10;
  display.setCursor(where, 10);
  display.println(buff);
  display.display();
  delay(1000);                              // This is here to lessen display flicker

}

/*****
  Purpose: To convert the value read from the MDL/s analog pin and convert it to watts. The
           circuit uses a voltage divider to make sure the Nano's 5V limit is not exceeded.
           This is based on the formula:

              Vrms = R2 * Vin / (R1 + R2)

           Solving for the input voltage:

              Vin = (Vrmst * (R1 + R2)) /  R2

           Knowing the input voltage allows us to determine the power: Pw =  Vin * Vin / R

  Parameter list:
    float averageValue        the value read on the analog input pin

  Return value:
    float                     the calculated power in watts

    CAUTION: 
*****/
float CalculateWatts(float averageValue)
{
  float powerWatts;
  float voltsRMS;
  float voltsIN;

  voltsRMS = .707 * (averageValue * 5.0 / 1024.0) * (58.0 / 2.0);   // Convert mapped sensor                      // value to RMS volts
  voltsRMS += DIODEVOLTAGEDROP;                                     // Add back diode D1                        // voltage drop
  powerWatts = (voltsRMS * voltsRMS ) / MYDUMMYLOADOHMS;            // Get the power

  return powerWatts * CALIBRATIONOFFSET;                            // Apply your factor
}

/*****
  Purpose: To measure and display min/max readings from A1 voltage divider pin

  Parameter list:
    void

  Return value:
    void

    CAUTION: 
*****/

void TestSensorRead()
{
  int i = ITERATONS;                // We're going to get a series of readings
  int sensorMin = SENSORMAX;        // minimum sensor value
  int sensorMax = SENSORMIN;        // maximum sensor value
  
  while (i--) {
    sensorValue = analogRead(SENSORPIN);
    delay(100);                           // Settle between readings...
    if (sensorValue > sensorMax) {        // record the maximum sensor value
      sensorMax = sensorValue;
    }
    if (sensorValue < sensorMin) {        // record the minimum sensor value
      sensorMin = sensorValue;
    }
  }
 #ifdef DEBUG                             // Only show if DEBUG mode set
    Serial.print("sensorMax = ");
    Serial.print(sensorMax);
    Serial.print("   sensorMin = ");
    Serial.println(sensorMin);
#endif
}
