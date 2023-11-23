#ifndef BEENHERE
#include "AT.h"
#endif
#include <Arduino.h>


/*****
  Purpose: To Fing minimum of array
  Parameter list:
  void
  Return value:
  void
*****/

void FindArrayMaxMin() {

  int arr[100];
  int i, max, min, size;
  size = 100;

  max = arr[0];
  min = arr[0];

  /*
     Find maximum and minimum in all array elements.
  */
  for (i = 1; i < size; i++)
  {
    arr[i] = SWRPosOld[i];
    /* If current element is greater than max */
    if (arr[i] > max)
    {
      max = arr[i];
    }

    /* If current element is smaller than min */
    if (arr[i] < min)
    {
      min = arr[i];
    }
  }

  /* Print maximum and minimum element */
  //Serial.print("Maximum element= "); Serial.println( max);
  //Serial.print("Minimum element= "); Serial.println( min);
}





/*****
  Purpose: To read one bridge measurement

  Parameter list:
  void

  Return value:
  int           the swr * 1000 so it comes back as an int

  CAUTION: Assumes that frequency has already been set
  ALTERNATIVE CALCULATION (Untested ?)
    p = sqrt( ((double)REV) / FWD );   // Calculate reflection coefficient

    VSWR = (1 + p) / (1 - p);         // Calculate VSWR
*****/
double ReadSWRValue()
{

  int i;
  double sum[2] = {0.0, 0.0};

  double FWD = 0.0;
  double REV = 0.0;
  double rawVm;
  double rawVrz;
  double rawVz;
  double VmSum;
  double VrzSum;
  double VzSum;
  double dBValueVm;
  double dBValueVrz;
  double dBValueVz;
  double linFWDSum;
  double linREVSum;
  double aveLinFWD;
  double aveLinREV;
  double dBValueDiff;
  double linValueDiff;
  double VSWR2;
  double rawValueDiff;
  int numSWRSamples = 50;
  double calGain = 1;
  double cosAngle;
  double linVzCorr;
  double  RValueCorr;
  double  XValueCorr;
  double VsLinVoltage;
  double VmLinVoltage;
  double VzLinVoltage;
  double a;
  double b;
  double c;

  for (i = 0; i < numSWRSamples; i++) {
    rawVm = analogRead(VM);
    VmSum  += rawVm;
    rawVrz = analogRead(VRZ);
    VrzSum  += rawVrz;
    rawVz = analogRead(VZ);
    VzSum  += rawVz;
  }
  //aveVm = (VmSum / numSWRSamples) - VmCal;
  //aveVz = (VzSum / numSWRSamples) - VzCal;
  //aveVrz = (VrzSum / numSWRSamples) - VrzCal;
  aveVm = (VmSum / numSWRSamples) - 270;
  aveVz = (VzSum / numSWRSamples) - 390;
  aveVrz = (VrzSum / numSWRSamples) - 230;
#ifdef DEBUG
  Serial.println(" ");
  Serial.print("     aveVrz = "); Serial.println(aveVrz);
  Serial.print("     aveVm = "); Serial.println(aveVm);
  Serial.print("     aveVz = "); Serial.println(aveVz);
  // Serial.println(" ");
  Serial.print("     aveVrz Corrected = "); Serial.println(aveVrz);
  Serial.print("     aveVm Corrected = "); Serial.println(aveVm);
  Serial.print("     aveVz Corrected = "); Serial.println(aveVz);
#endif

  linVm = (aveVm * 3.3 / (4096.*1.8373));
  linVz = (aveVz * 3.3 / (4096.*1.8373));
  //linVz = (aveVz * 3.3 / (4096.*1.8373));
  linVrz = (aveVrz * 3.3 / (4096.*1.8373)) ;

#ifdef DEBUG
  Serial.println(" ");
  Serial.print("     aveVz = "); Serial.print(aveVz);
  Serial.print("     linVz = "); Serial.println(linVz, 3);
  Serial.print("     aveVm = "); Serial.print(aveVm);
  Serial.print("     linVm = "); Serial.println(linVm, 3);
  Serial.print("    aveVrz= "); Serial.print(aveVrz);
  Serial.print("     linVrz = "); Serial.println(linVrz, 3);
  Serial.print("     linVm = "); Serial.println(linVm, 3);
  Serial.print("    2x linVrz = "); Serial.println(linVrz * 2, 3);
#endif

//=====================   Calibrate equation
//  y=a*x*x+b*x+c

yCal25=2.;  //Difference value between actual and readout RValue from Cal routine
yCal50=.2;
yCal200=-30.;
b=(((yCal50-yCal25)/1875.)-(yCal200-yCal25)/39375.)*112.5;
a=(yCal200-yCal25 - 175.*b)/39375;
c=yCal25-625*a-25*b;
Serial.print("a = "); Serial.println(a, 6);
Serial.print("b = "); Serial.println(b, 6);
Serial.print("c = "); Serial.println(c, 6);

//====================
  ZMag = linVz * 50 / linVm;
  //ZMag = ZMag + (.000002 * ZMag * ZMag * ZMag - .001 * ZMag * ZMag - .0055 * ZMag + 2.5667); // 3rd order correction
  // ZMag = ZMag +  a*ZMag*ZMag +b*ZMag + c;  //quadratic correction
  cosAngle = (linVm * linVm + linVz * linVz - 4 * linVrz * linVrz) / (2 * linVm * linVz);

  if (cosAngle > 1.) {
    cosAngle = 1.00;
  }
  angle = acos(cosAngle);
  RValue = ZMag * cosAngle;
  XValue = sqrt(ZMag * ZMag - RValue * RValue);
  reflCoeff = sqrt(((RValue - 50) * (RValue - 50) + XValue * XValue) / ((RValue + 50) * (RValue + 50) + XValue * XValue));
  if (reflCoeff > .99) reflCoeff = .99;
  VSWR = (1 + abs(reflCoeff)) / (1 - abs(reflCoeff));
#ifdef DEBUG
  Serial.print("     ZMag = "); Serial.println(ZMag, 3);
  Serial.print("    cosAngle= "); Serial.print(cosAngle);
  Serial.print("     RValue = "); Serial.println(RValue, 3);
  Serial.print("     XValue = "); Serial.println(XValue, 3);
  Serial.print("    reflCoeff = "); Serial.println(reflCoeff, 3);
  Serial.print("    VSWR = "); Serial.println(VSWR, 3);
  Serial.println("  ");
#endif
  return (VSWR);
}

/*****
  Purpose: Displays the horizontal line for measured SWR
  Paramter list:
    int whichBandOption     // The band being used
    double swr
  Return value:
    void
*****/
void PlotSWRValue(int whichBandOption, double swr)
{
  int yDotSWRPosition;
  double lastSWR;
  int yAxisPixelPerUnit, totalPixels;
  double pixelsPerTenth;
  lastSWR = swr - 1;

  totalPixels = YAXISEND - YAXISSTART;
  pixelsPerTenth = totalPixels / 40.0;      // Highest SWR is 5, so 50 tenths.

  yDotSWRPosition = (int) ((swr - 1) * 10 * pixelsPerTenth);  // Multiply by 10 because it's in tenths
  yDotSWRPosition = YAXISEND - yDotSWRPosition ;

  int swrInt = swr * 100;
  yDotSWRPosition = map(swrInt, 100, 500, YAXISSTART, YAXISEND);

}
