#ifndef BEENHERE
#include "AT.h"
#endif
#include <Arduino.h>

// #########################################################################
//  Draw the analogue meter on the screen
// #########################################################################
/*****
  Purpose: Draw on-screen analog meter
  Paramter list: void
  Return value:  void
*****/
void analogMeter()
{

  // Meter outline
  tft.fillRect(XOFFSETMETER+0, YOFFSETMETER, M_SIZE * 239, M_SIZE * 126, ILI9488_GREEN);
  tft.fillRect(XOFFSETMETER+5, YOFFSETMETER + 3, M_SIZE * 230, M_SIZE * 119, ILI9488_WHITE);
  tft.drawRect(XOFFSETMETER+5, YOFFSETMETER + 3, M_SIZE * 230, M_SIZE * 119, ILI9488_BLACK); // Draw bezel line
  tft.setTextSize(2);
  tft.setTextColor(ILI9488_BLACK);  // Text colour

  tft.setCursor(XOFFSETMETER+15, YOFFSETMETER + 17);
  tft.print("SWR");

  // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
  for (int i = -50; i < 51; i += 5) {
    // Long scale tick length
    int tl = 15;

    // Coodinates of tick to draw
    double sx = cos((i - 90) * 0.0174532925);
    double sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (M_SIZE * 100 + tl) + XOFFSETMETER+M_SIZE * 120;
    uint16_t y0 = sy * (M_SIZE * 100 + tl) + M_SIZE * 140;
    uint16_t x1 = sx * M_SIZE * 100 + XOFFSETMETER+M_SIZE * 120;
    uint16_t y1 = sy * M_SIZE * 100 + M_SIZE * 140;

    // Coordinates of next tick for zone fill
    double sx2 = cos((i + 5 - 90) * 0.0174532925);
    double sy2 = sin((i + 5 - 90) * 0.0174532925);
    int x2 = sx2 * (M_SIZE * 100 + tl) + XOFFSETMETER+M_SIZE * 120;
    int y2 = sy2 * (M_SIZE * 100 + tl) + M_SIZE * 140;
    int x3 = sx2 * M_SIZE * 100 + XOFFSETMETER+M_SIZE * 120;
    int y3 = sy2 * M_SIZE * 100 + M_SIZE * 140;

    // Yellow zone limits
    if (i >= -50 && i < -25) {
      tft.fillTriangle(x0, YOFFSETMETER+y0, x1, YOFFSETMETER+y1, x2, YOFFSETMETER+y2, ILI9488_LIGHTGREEN);
      tft.fillTriangle(x1, YOFFSETMETER+y1, x2, YOFFSETMETER+y2, x3, YOFFSETMETER+y3, ILI9488_LIGHTGREEN);
    }
    if (i >= -25 && i < 0) {
      tft.fillTriangle(x0, YOFFSETMETER+y0, x1, YOFFSETMETER+y1, x2, YOFFSETMETER+y2, ILI9488_YELLOW);
      tft.fillTriangle(x1, YOFFSETMETER+y1, x2, YOFFSETMETER+y2, x3, YOFFSETMETER+y3, ILI9488_YELLOW);
    }

    // Green zone limits
    if (i >= 0 && i < 25) {
      tft.fillTriangle(x0, YOFFSETMETER + y0, x1, YOFFSETMETER + y1, x2, YOFFSETMETER + y2, ILI9488_ORANGE);
      tft.fillTriangle(x1, YOFFSETMETER + y1, x2, YOFFSETMETER + y2, x3, YOFFSETMETER + y3, ILI9488_ORANGE);
    }

    // Orange zone limits
    if (i >= 25 && i < 50) {
      tft.fillTriangle(x0, YOFFSETMETER + y0, x1, YOFFSETMETER + y1, x2, YOFFSETMETER + y2, ILI9488_RED);
      tft.fillTriangle(x1, YOFFSETMETER + y1, x2, YOFFSETMETER + y2, x3, YOFFSETMETER + y3, ILI9488_RED);
    }

    // Short scale tick length
    if (i % 25 != 0) tl = 8;

    // Recalculate coords incase tick lenght changed
    x0 = sx * (M_SIZE * 100 + tl) + M_SIZE * 120;
    y0 = sy * (M_SIZE * 100 + tl) + M_SIZE * 140;
    x1 = sx * M_SIZE * 100 + M_SIZE * 120;
    y1 = sy * M_SIZE * 100 + M_SIZE * 140;

    // Draw tick
    tft.drawLine(XOFFSETMETER+x0, YOFFSETMETER + y0, XOFFSETMETER+x1, YOFFSETMETER + y1, ILI9488_BLACK); //ok

    // Check if labels should be drawn, with position tweaks

    if (i % 25 == 0) {
      // Calculate label positions
      x0 = sx * (M_SIZE * 100 + tl + 10) + M_SIZE * 120;
      y0 = sy * (M_SIZE * 100 + tl + 10) + M_SIZE * 140;
     switch (i / 25) {
     tft.setCursor(XOFFSETMETER+x0, YOFFSETMETER + y0 - 12);
     //tft.print("0");
        case -2: 
        tft.setCursor(XOFFSETMETER+x0, YOFFSETMETER + y0 - 12);
        tft.print("1"); 
        break;
        
        case -1: 
        tft.setCursor(XOFFSETMETER+x0, YOFFSETMETER + y0 - 12);
        tft.print("2"); break;
        
        case 0: 
        tft.setCursor(XOFFSETMETER+x0, YOFFSETMETER + y0 - 12);
        tft.print("3");
        break;
        case 1: 
        tft.setCursor(XOFFSETMETER+x0, YOFFSETMETER + y0 - 12);
        tft.print("4"); break;
        case 2:
        tft.setCursor(XOFFSETMETER+x0, YOFFSETMETER + y0 - 12);
        tft.print("5"); break;
      }
    }

    // Now draw the arc of the scale
    sx = cos((i + 5 - 90) * 0.0174532925);
    sy = sin((i + 5 - 90) * 0.0174532925);
    x0 = sx * M_SIZE * 100 + M_SIZE * 120;
    y0 = sy * M_SIZE * 100 + M_SIZE * 140;
    // Draw scale arc, don't draw the last part
    if (i < 50) tft.drawLine(XOFFSETMETER+x0, YOFFSETMETER + y0, XOFFSETMETER+x1, YOFFSETMETER + y1, ILI9488_BLACK);
  }

  //tft.drawString("%RH", M_SIZE*(5 + 230 - 40), M_SIZE*(119 - 20), 2); // Units at bottom right
  //tft.drawCentreString("%RH", M_SIZE*120, M_SIZE*70, 4); // Comment out to avoid font 4
  

  plotNeedle(0, 0); // Put meter needle at 0
}

// #########################################################################
// Update needle position
// This function is blocking while needle moves, time depends on ms_delay
// 10ms minimises needle flicker if text is drawn within needle sweep area
// Smaller values OK if text not in sweep area, zero for instant movement but
// does not look realistic... (note: 100 increments for full scale deflection)
// #########################################################################
/*****
  Purpose: Plot on-screen analog meter needle
  Paramter list: void
  Return value:  void
*****/
void plotNeedle(int SWRvalue, byte ms_delay)
{
  
  //tft.setFreeFont(FS12);
  tft.setTextSize(2);
  tft.setTextColor(ILI9488_BLACK, ILI9488_WHITE);
  //char buf[8]; dtostrf(SWRvalue, 4, 0, buf);
  //tft.drawRightString(buf, 10 + M_SIZE * 40, 10 + M_SIZE * (119 ), 1);

  if (SWRvalue < 10) SWRvalue = 10; // Limit SWRvalue to emulate needle end stops
  if (SWRvalue > 50) SWRvalue = 50;

  // Move the needle until new SWRvalue reached
  while (!(SWRvalue == old_analog)) {
    if (old_analog < SWRvalue) old_analog++;
    else old_analog--;

    if (ms_delay == 0) old_analog = SWRvalue; // Update immediately if delay is 0

    double sdeg = map(old_analog, 10, 50, -140, -40); // Map SWRvalue to angle
   
    // Calcualte tip of needle coords
    double sx = cos(sdeg * 0.0174532925);
    double sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    double tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    tft.drawLine(XOFFSETMETER+M_SIZE * (120 + 20 * ltx - 1), YOFFSETMETER + M_SIZE * (140 - 20), XOFFSETMETER+osx - 1, YOFFSETMETER + osy, ILI9488_WHITE);
    tft.drawLine(XOFFSETMETER+M_SIZE * (120 + 20 * ltx), YOFFSETMETER + M_SIZE * (140 - 20), XOFFSETMETER+osx, YOFFSETMETER + osy, ILI9488_WHITE);
    tft.drawLine(XOFFSETMETER+M_SIZE * (120 + 20 * ltx + 1), YOFFSETMETER + M_SIZE * (140 - 20), XOFFSETMETER+osx + 1, YOFFSETMETER + osy, ILI9488_WHITE);

    // Re-plot text under needle
    //tft.setTextColor(ILI9488_BLACK);
    //tft.drawCentreString("%RH", M_SIZE*120, M_SIZE*70, 4); // // Comment out to avoid font 4

    // Store new needle end coords for next erase
    ltx = tx;
    osx = M_SIZE * (sx * 98 + 120);
    osy = M_SIZE * (sy * 98 + 140);

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    tft.drawLine(XOFFSETMETER+M_SIZE * (120 + 20 * ltx - 1), YOFFSETMETER + M_SIZE * (140 - 20), XOFFSETMETER+osx - 1, YOFFSETMETER + osy, ILI9488_RED);
    tft.drawLine(XOFFSETMETER+M_SIZE * (120 + 20 * ltx), YOFFSETMETER + M_SIZE * (140 - 20), XOFFSETMETER+osx, YOFFSETMETER + osy, ILI9488_MAGENTA);
    tft.drawLine(XOFFSETMETER+M_SIZE * (120 + 20 * ltx + 1), YOFFSETMETER + M_SIZE * (140 - 20), XOFFSETMETER+osx + 1, YOFFSETMETER + osy, ILI9488_RED);

    // Slow needle down slightly as it approaches new postion
    if (abs(old_analog - SWRvalue) < 10) ms_delay += ms_delay / 5;

    // Wait before next update
    delay(ms_delay);
  }
}
