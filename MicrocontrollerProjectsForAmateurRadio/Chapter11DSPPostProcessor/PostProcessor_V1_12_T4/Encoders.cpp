#ifndef BEENHERE
//#include <SPI.h>
#include "Post.h"
#endif



/*****
  Purpose: To read the rotary encoder that controls frequency tuning

  Parameter list:
    void

  Return value:
    int           the direction of the rotation,
                  0 = no rotation
                  1 = CW
                 -1 = CCW
*****/
/*void ReadTuningEncoder()
{
  unsigned char result = rotaryFreq.process();
  encoderDirection = 0;
    if (result == DIR_CW) {
      encoderDirection = 1;
    } else {
      if (result == DIR_CCW) {
        encoderDirection = -1;
      }
    }
  encoderDirection = 0;
}*/
