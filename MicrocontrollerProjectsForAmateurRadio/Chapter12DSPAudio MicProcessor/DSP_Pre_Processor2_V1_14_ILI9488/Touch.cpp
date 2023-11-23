#ifndef BEENHERE
#include "Pre.h"
#endif

/*****
  Purpose: Read Function Screen Buttons
  Parameter list:
    void
  Return value;
    void
*****/
void GetTouchCoord() {
    if (ts.touched()) {
      TS_Point p = ts.getPoint();
      xx = map(p.x, 3457, 250, 0, 320);
      yy = map(p.y, 3396, 360, 0, 240);
      /*Serial.print("p.x ="); Serial.println(p.x);
      Serial.print("p.y ="); Serial.println(p.y);
      Serial.print("xx ="); Serial.println(xx);
      Serial.print("yy ="); Serial.println(yy);*/
    }
  
}
