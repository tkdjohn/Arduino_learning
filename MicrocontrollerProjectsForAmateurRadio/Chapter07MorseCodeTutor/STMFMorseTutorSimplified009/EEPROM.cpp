#ifndef BEENHERE
#include "MorseTutor.h"
#endif 



/*****
  Purpose: The STM32 does not actually have any EEPROM, so we have to fake it with flash memory. This code defines where the 
           page in flash memory resides that will be used as EEPROM

  Parameter list:
    void

  Retrun value:
    void
*****/
void DefineEEPROMPage()
{
  EEPROM.PageBase0 = 0x801f000;     // EEPROM base address. Everything indexed from this address
  EEPROM.PageSize  = 0x400;         // 1024 bytes of EEPROM
}


/*****
  Purpose: Set default configuration data to EEPROM
  
  Parameter list:
    void

  Retrun value:
    void
*****/
void SaveEEPROMDefaults()
{
  int status;
  uint16 temp;

  temp = 18;
  status = EEPROM.write((uint16) WORDSPERMINUTE,   temp);
  if (!status) { 
    Serial.print("EEPROM wpm write sucks, Status = ");
    Serial.println(status);
  }
  temp = 700;  
  status = EEPROM.write((uint16) SIDETONE,         temp);
  if (!status) { 
    Serial.print("EEPROM SIDETONE write sucks, Status = ");
    Serial.println(status);
  }
  temp = PA8;
  status = EEPROM.write((uint16) WHICHISDITPADDLE, temp);
  if (!status) { 
    Serial.print("EEPROM WHICHISDITPADDLE write sucks, Status = ");
    Serial.println(status);
  }
  temp = 10;
  status = EEPROM.write((uint16) FARSWORTHSPEED,   temp);
  if (!status) { 
    Serial.print("EEPROM FARSWORTHSPEED write sucks, Status = ");
    Serial.println(status);
  }
  temp = 25;
  status = EEPROM.write((uint16) KOCHSPEED,        temp);
  if (!status) { 
    Serial.print("EEPROM KOCHSPEED write sucks, Status = ");
    Serial.println(status);
  }
  temp = 1;
  status = EEPROM.write((uint16) ENCODINGACTIVE,   temp);
  if (!status) { 
    Serial.print("EEPROM ENCODINGACTIVE write sucks, Status = ");
    Serial.println(status);
  }
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
  
  status = EEPROM.write((uint16) WORDSPERMINUTE,   wordsPerMinute);
  if (status) { 
    Serial.print("EEPROM wpm write sucks, Status = ");
    Serial.println(status);
  }
  status = EEPROM.write((uint16) SIDETONE,         sidetoneFrequency);
  if (status) { 
    Serial.print("EEPROM sidetoneFrequency write sucks, Status = ");
    Serial.println(status);
  }
  status = EEPROM.write((uint16) WHICHISDITPADDLE, ditPaddle);
  if (status) { 
    Serial.print("EEPROM ditPaddle write sucks, Status = ");
    Serial.println(status);
  }
  status = EEPROM.write((uint16) FARSWORTHSPEED,   farnsworthWPM);
  if (status) { 
    Serial.print("EEPROM farnsworthWPM write sucks, Status = ");
    Serial.println(status);
  }
  status = EEPROM.write((uint16) KOCHSPEED,       kochSpeed);
  if (status) { 
    Serial.print("EEPROM kochSpeed write sucks, Status = ");
    Serial.println(status);
  }
  status = EEPROM.write((uint16) ENCODINGACTIVE,  encodingType);
  if (status) { 
    Serial.print("EEPROM encodingType write sucks, Status = ");
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
  
  status = EEPROM.read((uint16) WORDSPERMINUTE,   &wordsPerMinute);
  if (wordsPerMinute > 90 || wordsPerMinute < 5) {
    wordsPerMinute = 15;
  }
  if (status) Serial.println("EEPROM wpm write sucks");
  status = EEPROM.read((uint16) SIDETONE,         &sidetoneFrequency);
  if (status) Serial.println("EEPROM sidetone write sucks");
  status = EEPROM.read((uint16) WHICHISDITPADDLE, &ditPaddle);
  if (status) Serial.println("EEPROM ditPaddle write sucks");
  status = EEPROM.read((uint16) FARSWORTHSPEED,   &farnsworthWPM);
  if (status) Serial.println("EEPROM farnsworthWPM write sucks");
  status = EEPROM.read((uint16) KOCHSPEED,        &kochSpeed);
  if (status) Serial.println("EEPROM kochSpeed write sucks");
  status = EEPROM.read((uint16) ENCODINGACTIVE,   &encodingType);
  if (status) Serial.println("EEPROM encodingType write sucks");
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
  Serial.print("wordsPerMinute = ");
  Serial.println(wordsPerMinute);
  
  Serial.print("sidetoneFrequency = ");
  Serial.println(sidetoneFrequency);
  
  Serial.print("ditPaddle = ");
  Serial.println(ditPaddle);
  
  Serial.print("farnsworthWPM = ");
  Serial.println(farnsworthWPM);
 
  Serial.print("kochSpeed = ");
  Serial.println(kochSpeed);
  
  Serial.print("encodingType = ");
  Serial.println(encodingType);
 
}

/*****
  Purpose: Write values to EEPROM
  
  Parameter list:
    void

  Retrun value:
    uint16        0 if okay, non-zero otherwise
*****/
//uint16 WriteEEPROMValue(uint16 address, uint16 value)
int WriteEEPROMValue(int address, int value)
{
  return EEPROM.write(address, value);
}
