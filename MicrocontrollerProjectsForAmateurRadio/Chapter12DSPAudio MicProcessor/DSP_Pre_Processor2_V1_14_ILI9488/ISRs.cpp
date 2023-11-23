#ifndef BEENHERE
#include "Pre.h"
#endif



/*****
  Purpose: The ISR to detect the rotary encoder's direction of movement

  Parameter list:
    void

  Return value:
    void

  CAUTION: This encoder is used for multiple purposes, all sensing direction change
*****/
void freqISR() {
  //Serial.print("freqISR ");
  unsigned char result1 = rotaryFreq.process();

  //freqEncoderMovement = 0;

  if (result1 == DIR_CW) {
    freqEncoderMovement = 1;
    MyDelay(50);
  } else if (result1 == DIR_CCW) {
    freqEncoderMovement = -1;
    MyDelay(50);
  }
  //if (freqEncoderMovement != 0) {
  //Serial.print("freqEncoderMovement= ");Serial.println(freqEncoderMovement);
  //}
}

/*****
  Purpose: The ISR to detect the rotary encoder's direction of movement

  Parameter list:
    void

  Return value:
    void

  CAUTION: This encoder is used for multiple purposes, all sensing direction change
*****/
void SecondEncoderISR() {
  unsigned char result2 = rotarySecond.process();

  //secondEncoderMovement = 0;

  if (result2 == DIR_CW) {
    secondEncoderMovement = 1;
    MyDelay(50);
  } else if (result2 == DIR_CCW) {
    secondEncoderMovement = -1;
    MyDelay(50);
  }
}
