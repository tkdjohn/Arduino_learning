#ifndef BEENHERE
#include "ProgPS.h"
#endif
#include <Arduino.h>

/*****
  Purpose: Setup encoderRead1

  Parameter list:
    void
  Return value:
    void
*****/
int encoderRead1() 
{
  if (en1State != 0) {
      encoder1Reading10 = setPointCal * eCounter1;
      //Serial.print("encoder1Reading10=  "); //Serial.println(encoder1Reading10);
      
    en1State = 0;
    return encoder1Reading10;
  }
}
//-----------------  end Function -----------


/*****
  Purpose: Setup encoderRead3  "Fine" Encoder

  Parameter list:
    void
  Return value:
    void
*****/
int encoderRead3() 
{
  if (en3State != 0) {
      encoder3Reading = setPointCal * (float) eCounter3 * 0.1;
      //Serial.print("encoder3Reading=  "); Serial.println(encoder3Reading);
      
    en3State = 0;
    return encoder3Reading;
  }
}
//-----------------  end Function -----------
