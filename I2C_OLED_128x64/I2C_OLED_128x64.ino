#include <Wire.h>

#include <Adafruit_SSD1306.h>
//#include <splash.h>
#include <Adafruit_GFX.h>
//#include <Adafruit_GrayOLED.h>
//#include <Adafruit_SPITFT.h>
//#include <Adafruit_SPITFT_Macros.h>
//#include <gfxfont.h>


Adafruit_SSD1306 display(128, 64);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  while (!Serial.available());
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("1BCDEFGHIJKLMNOPQRSTU");
  display.println("2BCDEFGHIJKLMNOPQRSTU");
  display.println("3BCDEFGHIJKLMNOPQRSTU");
  display.println("4BCDEFGHIJKLMNOPQRSTU");
  display.println("5BCDEFGHIJKLMNOPQRSTU");
  display.println("6BCDEFGHIJKLMNOPQRSTU");
  display.println("7BCDEFGHIJKLMNOPQRSTU");
  display.println("8BCDEFGHIJKLMNOPQRSTU");
  display.println("9 this line is hidden");
  display.display();
  Serial.begin(115200);
  Serial.println("begin");

}

void loop() {
    serialEventRun();
}

void serialEvent() {
  int colsSent = 0;
  int shifts = 0;

  // read all the available characters
  while (Serial.available()) {
    display.setCursor(0,0);
    display.clearDisplay();
  
    char buffer[22];
    size_t size1 = Serial.readBytes(buffer, 21);
    Serial.println(buffer);
    buffer[size1] = '\0';
    display.print(buffer);

    // size_t size2 = 0;
    // if (Serial.available()) {
    //   display.setCursor(0,1);
    //   size2 = Serial.readBytes(buffer, 16);
    //   buffer[size2] = '\0';
    //   display.print(buffer);
    // }

    // colsSent = max(size1, size2);
    // delay(250);
    // display.startscrollleft(0, colsSent);
    // display.stopscroll();
    // delay(1000);
    display.display();
  }
}
