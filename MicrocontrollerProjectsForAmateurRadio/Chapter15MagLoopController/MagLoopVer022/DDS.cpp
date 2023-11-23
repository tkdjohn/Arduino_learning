#ifndef BEENHERE
#include "MagLoop.h"
#endif
#include <Arduino.h>

void DDSWakeUp(){
digitalWrite(W_CLK, HIGH);
  digitalWrite(W_CLK, LOW);
  
  //digitalWrite(DATA, HIGH);
  //digitalWrite(DATA, LOW);
  
  digitalWrite(RESET, HIGH);
  digitalWrite(RESET, LOW);
  
  digitalWrite(FQ_UD, HIGH);
  digitalWrite(FQ_UD, LOW);
}
void outOne() {
  digitalWrite (W_CLK, LOW);
  digitalWrite (DATA, HIGH);
  digitalWrite (W_CLK, HIGH);
  digitalWrite (DATA, LOW);
}
void outZero() {
  digitalWrite (W_CLK, LOW);
  digitalWrite (DATA, LOW);
  digitalWrite (W_CLK, HIGH);
}
void byte_out (unsigned char byte) {
  int i;
  for (i = 0; i < 8; ++i) {
    if ((byte & 1) == 1)
      outOne();
    else
      outZero();
    byte = byte >> 1;
  }
}
void SendFrequency(long frequency) {
   
  long freq = frequency * 4294967295L / 125000000L; // note 125 MHz clock on 9850
  digitalWrite (FQ_UD, LOW);
  for (int b = 0; b < 4; b++, freq >>= 8)
    byte_out (freq & 0xFF);
  byte_out (0x00);   // Final control byte, all 0 for 9850 chip
  digitalWrite (FQ_UD, HIGH);  // Done!  Should see output
}
