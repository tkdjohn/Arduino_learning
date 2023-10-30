/****************************************************************
Count up to 9999 using a 5641AH 4-digit 7-segment LED display.
Requres the SevSeg library.
Wiring:
Nano pins:  D7  D8  D9 D10 D11 D12
          --------------------------
          | 12  11  10   9   8   7 |
          |      PN: 564aAH        |
          |  1   2   3   4   5   6 |
          --------------------------
Nano pins:  D2  D3 D13  D4  D5  D6  
*****************************************************************/

#include <SevSeg.h>

int delay_ms = 500;
unsigned long nextUpdate_ms = 0;
int curNumber = 0;
SevSeg sevseg;

// the setup routine  runs once when you press reset:
void setup() {

  while (!Serial)
    ;
  Serial.begin(115200);
  byte digitPins[] = { 7, 10, 11, 6 };
  byte segmentPins[] = { 8, 12, 4, 3, 2, 9, 5, 13 };
  sevseg.begin(COMMON_CATHODE, 4, digitPins, segmentPins, false);
  sevseg.setBrightness(90);
  Serial.println("Setup Complete.");
}

// the loop routine runs over  and over again forever:
void loop() {
  long current_ms = millis();
  if (current_ms >= nextUpdate_ms) {
    sevseg.setNumber(curNumber);
    curNumber = curNumber >= 9999 ? 0 : curNumber + 1;
    nextUpdate_ms = current_ms + delay_ms;
  }
  sevseg.refreshDisplay();
}

void serialEvent() {
  if (Serial.available()) {
    delay_ms = Serial.parseInt();
    Serial.read();
  }
}