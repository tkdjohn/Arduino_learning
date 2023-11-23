#ifndef BEENHERE
#include "ProgPS.h"
#endif

/*****
   Purpose: ISR to read rotary encoder1 -  Coarse Voltage Set
  Paramter list: void
  Return value:  void
*****/
void voltOnOffISR() {

  while (digitalRead(FINEENCODERSWITCH) != HIGH) {
    onOffFlag = 1;
  }
  if (onOffFlag == 1) 
  {
    if (outputOnOffFlag == 1) {
      outputOnOffFlag = 0;
      digitalWrite(FINEENCODERSWITCH, HIGH);

    }
    else {
      if (outputOnOffFlag == 0) {
        outputOnOffFlag = 1;
        digitalWrite(FINEENCODERSWITCH, HIGH);
      }
    }
    onOffFlag=0;
  }
}


/*****
   Purpose: ISR to read rotary encoder1 -  Coarse Voltage Set
  Paramter list: void
  Return value:  void
*****/
void encoder1ISR()
{
  unsigned char result1;

  result1 = rotary1.process();
  if (result1 == 0)
    return;

  if (result1 == DIR_CW) {
    eCounter1++;
    en1State = 1;
  } else if (result1 == DIR_CCW) {
    eCounter1--;
    en1State = 1;
    //Serial.print("eCounter1-= ");Serial.println(eCounter1);
  }
}
/*****
   Purpose: ISR to read rotary encoder2   -  Menu Set
  Paramter list: void
  Return value:  void
*****/
void encoder2ISR()
{
  unsigned char result2;

  result2 = rotary2.process();
  if (result2 == 0)
    return;

  if (result2 == DIR_CW) {
    encoder2 = 1;
    eCounter2++;
    en2State = 1;

  } else if (result2 == DIR_CCW) {
    encoder2 = -1;
    eCounter2--;
    en2State = 1;
  }
}

/*****
   Purpose: ISR to read rotary encoder3    -  Fine Voltage Set
  Paramter list: void
  Return value:  void
*****/
void encoder3ISR()
{
  unsigned char result3;
  result3 = rotary3.process();

  if (result3 == 0)
    return;

  if (result3 == DIR_CW) {
    eCounter3++;
    en3State = 1;
  } else if (result3 == DIR_CCW) {
    eCounter3--;
    en3State = 1;
  }
  //Serial.print("eCounter3  "); Serial.println(eCounter3);
}
