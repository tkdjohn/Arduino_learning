#ifndef BEENHERE
#include "ProgPS.h"
#endif





/*****
  Purpose: The STM32 does not actually have any EEPROM, so we have to fake it with flash memory. This code defines where the
           page in flash memory resides that will be used as EEPROM

  Parameter list:
    void

  Retrun value:
    void


    startSetpointLevelVolts

  float voltInCal

  float maxVoltageLevel

  int functionDuration

  int numberOfSteps

  int outTimeSec

  int outTimeMin

  int outTimeHour


*****/
void DefineEEPROMPage()
{
  EEPROM.PageBase0 = 0x801f000;     // EEPROM base address. Everything indexed from this address
  EEPROM.PageSize  = 0x400;         // 1024 bytes of EEPROM
}



/*****
  Purpose: Save configuration data to EEPROM
  Parameter list:
    void

  Retrun value:
    void
*****/
void SaveConfigData()
{
  int status;

  status = EEPROM.write(0,   functionDuration);
  if (status) {
    Serial.print("EEPROM functionDuration write bad, Status = ");
    Serial.println(status);
  }
  status = EEPROM.write(4, numberOfSteps);
  if (status) {
    Serial.print("EEPROM numberOfSteps write bad, Status = ");
    Serial.println(status);
  }
  status = EEPROM.write(8, outTimeSec);
  if (status) {
    Serial.print("EEPROM outTimeSec write bad, Status = ");
    Serial.println(status);
  }
  status = EEPROM.write(12,  outTimeMin);
  if (status) {
    Serial.print("EEPROM outTimeMin write bad, Status = ");
    Serial.println(status);
  }
  status = EEPROM.write(16, outTimeHour);
  if (status) {
    Serial.print("EEPROM outTimeHour write bad, Status = ");
    Serial.println(status);
  }

//-------------------
  myUnion.num = maxVoltageLevel;
  status = EEPROM.write( (uint16) 20,   myUnion.myBytes[0]);
  status = EEPROM.write( (uint16) 22,   myUnion.myBytes[1]);
  if (status) {
    Serial.print("EEPROM maxVoltageLevel write bad, Status = ");
    Serial.println(status);
  }

  //---------------------
  myUnion.num = voltInCal;
  status = EEPROM.write( (uint16) 26,   myUnion.myBytes[0]);
  status = EEPROM.write( (uint16) 28,   myUnion.myBytes[1]);
  if (status) {
    Serial.print("EEPROM voltInCal write bad, Status = ");
    Serial.println(status);
  }

//----------------------

  myUnion.num = setPointCal;
  status = EEPROM.write( (uint16) 32,   myUnion.myBytes[0]);
  status = EEPROM.write( (uint16) 34,   myUnion.myBytes[1]);
  if (status) {
    Serial.print("EEPROM setPointCal write bad, Status = ");
    Serial.println(status);
  }

   status = EEPROM.write(38,   pulseTopWidth);
      if (status) {
        Serial.print("EEPROM pulseTopWidth write bad, Status = ");
        Serial.println(status);
      }
      
 status = EEPROM.write(42,   numFunctionCycles);
      if (status) {
        Serial.print("EEPROM numFunctionCycles write bad, Status = ");
        Serial.println(status);
      }
//-------------------
  myUnion.num = startSetpointLevelVolts;
  status = EEPROM.write( (uint16) 46,   myUnion.myBytes[0]);
  status = EEPROM.write( (uint16) 48,   myUnion.myBytes[1]);
  if (status) {
    Serial.print("EEPROM startSetpointLevelVolts write bad, Status = ");
    Serial.println(status);
  }
  
  


  
}

/*****
  Purpose: Read configuration data from EEPROM

  Parameter list:
    void

  Retrun value:
    void
*****/
void ReadConfigData()
{
  int status;

  status = EEPROM.read( (uint16) 0,   &functionDuration);
  if (status) {
    Serial.print("EEPROM functionDuration write bad, Status = ");
    Serial.println(status);
  }
  status = EEPROM.read( (uint16) 4, &numberOfSteps);
  if (status) {
    Serial.print("EEPROM numberOfSteps write bad, Status = ");
    Serial.println(status);
  }
  status = EEPROM.read( (uint16) 8, &outTimeSec);
  if (status) {
    Serial.print("EEPROM outTimeSec write bad, Status = ");
    Serial.println(status);
  }
  status = EEPROM.read( (uint16) 12,  &outTimeMin);
  if (status) {
    Serial.print("EEPROM outTimeMin write bad, Status = ");
    Serial.println(status);
  }
  status = EEPROM.read( (uint16) 16, &outTimeHour);
  if (status) {
    Serial.print("EEPROM outTimeHour write bad, Status = ");
    Serial.println(status);
  }

 //----------------
  status = EEPROM.read( (uint16) 20,   &myUnion.myBytes[0]);
  status = EEPROM.read( (uint16) 22,   &myUnion.myBytes[1]);
  maxVoltageLevel = myUnion.num;
  if (status) {
    Serial.print("EEPROM maxVoltageLevel write bad, Status = ");
    Serial.println(status);
  }

 //-------------------
  status = EEPROM.read( (uint16) 26,   &myUnion.myBytes[0]);
  status = EEPROM.read( (uint16) 28,   &myUnion.myBytes[1]);
  voltInCal = myUnion.num;
  if (status) {
    Serial.print("EEPROM voltInCal write bad, Status = ");
    Serial.println(status);
  }

  status = EEPROM.read( (uint16) 32,   &myUnion.myBytes[0]);
  status = EEPROM.read( (uint16) 34,   &myUnion.myBytes[1]);
  setPointCal = myUnion.num;
  if (status) {
    Serial.print("EEPROM voltInCal write bad, Status = ");
    Serial.println(status);
  }


status = EEPROM.read(38,   &pulseTopWidth);
      if (status) {
        Serial.print("EEPROM pulseTopWidth write bad, Status = ");
        Serial.println(status);
      }

status = EEPROM.read(42,   &numFunctionCycles);
      if (status) {
        Serial.print("EEPROM numFunctionCycles write bad, Status = ");
        Serial.println(status);
      }

//-------------------

  status = EEPROM.read( (uint16) 46,   &myUnion.myBytes[0]);
  status = EEPROM.read( (uint16) 48,   &myUnion.myBytes[1]);
  startSetpointLevelVolts= myUnion.num;
  if (status) {
    Serial.print("EEPROM startSetpointLevelVolts write bad, Status = ");
    Serial.println(status);
  }

  //-------------------


}


/*****
  Purpose: Debugging read of EEPROM and print to Serial monitor

  Parameter list:
    void

  Retrun value:
    void
*****/
void ShowConfigData()
{
  Serial.print("numFunctionCycles = ");
  Serial.println(numFunctionCycles);

    Serial.print("startSetpointLevelVolts = ");
  Serial.println(startSetpointLevelVolts);
  
 Serial.print("maxVoltageLevel  = ");
  Serial.println(maxVoltageLevel);

   Serial.print("functionDuration  = ");
  Serial.println(functionDuration);

  Serial.print("numberOfSteps    = ");
  Serial.println(numberOfSteps);

    Serial.print("pulseTopWidth    = ");
  Serial.println(pulseTopWidth);

  Serial.print("outTimeSec       = ");
  Serial.println(outTimeSec);

  Serial.print("outTimeMin       = ");
  Serial.println(outTimeMin);

  Serial.print("outTimeHour      = ");
  Serial.println(outTimeHour);

  Serial.print("voltInCal        = ");
  Serial.println(voltInCal);

  Serial.print("setPointCal  = ");
  Serial.println(setPointCal);

  Serial.println(" ");
}

/*****
  Purpose: Write values to EEPROM

  Parameter list:
    void

  Retrun value:
    uint16        0 if okay, non-zero otherwise
*****/
int WriteEEPROMValue(int address, int value)
{
  //  return EEPROM.write(address, value);
  return 1;
}
