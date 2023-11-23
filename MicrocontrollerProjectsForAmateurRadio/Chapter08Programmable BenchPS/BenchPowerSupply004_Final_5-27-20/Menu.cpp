#ifndef BEENHERE
#include "ProgPS.h"
#endif


/*****
  Purpose: This is the constructor for the menuing system.

  Parameter list:
    int displayWidth     the max width for this menu
    int menuLevels       what it the depth of the menus
    unit16 foreColor        display menu item in this fore color...
    unit16 backColor        ...using this background color
    unit16 activeFore       Highlight active menu choice with this fore color...
    unit16 activeBack       ...and this back color
    int font             using this font size

  Return value:
    void
*****/
Menuing::Menuing(int displayWidth, int displayHeight, int foreColor, int backColor, int activeFore, int activeBack, int font)
{
  width                 = displayWidth;
  height                = displayHeight;
  foregroundColor       = foreColor;        // Unselected
  backgroundColor       = backColor;
  selectForegroundColor = activeFore;       // Selected
  selectBackgroundColor = activeBack;
  fontSize              = font;
}


/*****
  Purpose: To show a menu option - Draws initial instance of top menu

  Paramter list:
    const char *whichMenu[]     // Array of pointers to the menu option
    int len;                    // The number of menus

  Return value:
    void
*****/
void Menuing::showMenu(ILI9488 myDisplay, char *whichMenu[])
{
  int i;
  myDisplay.setTextColor(foregroundColor, backgroundColor);
  activeRow = FONTROWOFFSET;
  for (i = 0; i < itemCount; i++) {
    myDisplay.setCursor(i * spacing, activeRow);
    myDisplay.print(whichMenu[i]);

  }
  activeColumn = activeMenuIndex * spacing;
  myDisplay.setFont(&FreeSerif12pt7b);
  myDisplay.setCursor(activeColumn, activeRow);
  myDisplay.setTextColor(selectForegroundColor, selectBackgroundColor);
  myDisplay.print(whichMenu[activeMenuIndex]);
  myDisplay.setTextColor(WHITE, backgroundColor);
  myDisplay.setCursor(0, activeRow+7);
  myDisplay.print(" _____");
}


/*****
  Purpose: To erase all sub menus while leaving the top-most menu unchanged

  Parameter list:

  Return value:
    void
*****/
void Menuing::eraseMenus(ILI9488 myDisplay)
{
  myDisplay.fillRect(0, MARGINROWOFFSET, DISPLAYWIDTH, BELOWMENUS, BLACK); // Erase old speed line
}

/*****
  Purpose: To erase display

  Parameter list:

  Return value:
    void
*****/
void Menuing::eraseDisplay(ILI9488 myDisplay)
{
   myDisplay.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);   // Erase old speed line
}


/*****
  Purpose: TDeselects a menu item

  Parameter list:
    int activeMenuLevel     the current menu level
    char *menu[]            the menu choices
    int orientation         horizontal or dropdown

  Return value:
    int                     the choice selected
*****/
void Menuing::deselectMenuItem(ILI9488 myDisplay, char *menu[])
{
  int col, row;
  col = activeMenuIndex * spacing;

  if (activeMenuLevel == 0) {
    row = FONTROWOFFSET;                                  // Start below top menu and work down
    activeRow = row;
    activeColumn = col;                                // Where is top-most column?
  } else {
    col = spacing * activeMenuIndex;
    row = ROWSPACING * activeMenuIndex;
  }

  myDisplay.setFont(&FreeSerif12pt7b);

  myDisplay.setTextColor(foregroundColor, backgroundColor);
  myDisplay.setCursor(col, row);              // Put on old choice...
  myDisplay.print(menu[activeMenuIndex]);       // ...and de-select it.
  myDisplay.setTextColor(BLACK, backgroundColor);
  myDisplay.setCursor(col, row+7);
  myDisplay.print(" _____");

}

/*****
  Purpose: This moves to the next menu item - updates a menu item

  Parameter list:
    char *menu[]         pointer to the current menu list
    int encoder2          direction of rotation

  Return value:
    int                 currently active index
*****/
int Menuing::updateMenu(ILI9488 myDisplay, char *menu[], int encoder2)

{
  //Serial.print("encoder2=  ");Serial.println(encoder2);
  int col, row;

  if (encoder2 == 1)             // Based on encoder2 movement...
    activeMenuIndex++;          // ...advance to next item, or...
  else
    activeMenuIndex--;          // ...backup to previous item

  if (activeMenuIndex > itemCount - 1) // Advanced too far, set to first item
    activeMenuIndex = 0;
  if (activeMenuIndex < 0)                                    // Backed up too far, set to end item
    activeMenuIndex = itemCount - 1;

  col = activeMenuIndex * spacing;
  activeColumn = col;
  if (activeMenuLevel == 0) {  //activeMenuLevel == 0 means top horizontal menu
    row = FONTROWOFFSET;       // Upper most menu always goes on first line
  } else {
    row = TOPDEADSPACE + FONTROWOFFSET + ROWSPACING * activeMenuIndex;  // Sub-menu
  }
  activeRow = row;

  myDisplay.setFont(&FreeSerif12pt7b);

  myDisplay.setTextColor(selectForegroundColor, selectBackgroundColor);
  myDisplay.setCursor(col, row);
  
  myDisplay.print(menu[activeMenuIndex]);


  return activeMenuIndex;

}


/*****
  Purpose: This presents a new menu depending upon the encoder2 direction
  Parameter list:
    char *menu           pointer to the current menu list
    int whichLevel       the setup is for this menu
    int encoder2          direction of rotation
    Menuing mine         the menu being used
    int defaults[]       the array that tells which element of the menu is the default

  Return value:
    int                  the default option being presented
*****/
void Menuing::showNewMenu(ILI9488 myDisplay, char *menu[], int encoder2, int defaults[])
{
  int col, i, row;

  activeColumn = col = spacing * activeMenuIndex;         // Start at main menu column

  for (i = 0; i < itemCount; i++) {
    row = TOPDEADSPACE + FONTROWOFFSET + ROWSPACING * i;            // Start below top menu and work down
    if (i == defaults[activeMenuIndex]) {
      myDisplay.setTextColor(selectForegroundColor, selectBackgroundColor);          // All others are unselected

      defaultOption = defaults[activeMenuIndex];            // This is the currently-active menu selection
      activeRow       = row;
      activeColumn    = col;
    } else {
      myDisplay.setTextColor(foregroundColor, backgroundColor);          // All others are unselected
    }

    myDisplay.setFont(&FreeSerif12pt7b);

    myDisplay.setCursor(col, row);
    myDisplay.print(menu[i]);
  }
  MyDelay(500UL);
  activeMenuIndex = defaultOption;

}

/*****
  Purpose: This scrolls the top-most menu horizontally

  Parameter list:
    ILI9488 myDisplay    display object
    char *menu[]                  pointer to menu options
    int encoder2                   direction of rotation
    int defaults[]       the array that tells which element of the menu is the default

  Return value:
    void
*****/
void Menuing::scrollTopMenu(ILI9488 myDisplay, char *menu[], int encoder2, int defaults[])
{

  if (encoder2 == 1) {            // Based on encoder2 movement...
    //Serial.print("encoder2=  ");Serial.println(encoder2);
    activeMenuIndex++;          // ...advance to next item, or...
  }
  else {
    activeMenuIndex--;          // ...backup to previous item
    //Serial.print("else encoder2=  ");Serial.println(encoder2);
  }
  if (activeMenuIndex > itemCount - 1) // Advanced too far, set to first item
    activeMenuIndex = 0;
  if (activeMenuIndex < 0)                                    // Backed up too far, set to end item
    activeMenuIndex = itemCount - 1;

  activeColumn = col = activeMenuIndex * spacing;
  activeRow    = row = FONTROWOFFSET;           // Upper most menu always goes on first line

  myDisplay.setFont(&FreeSerif12pt7b);

  myDisplay.setTextColor(selectForegroundColor, selectBackgroundColor);
  myDisplay.setCursor(col, row);
  myDisplay.print(menu[activeMenuIndex]);
  myDisplay.setCursor(col, row+7);
  myDisplay.print(" _____");

}

/*****
  Purpose: This scrolls the top-most menu horizontally

  Parameter list:
    ILI9488 myDisplay    the tft display
    char *menu                    pointer to the current menu list
    Menuing mine                  the menu being used

  Return value:
    int                   the submenu choice made
*****/
int Menuing::selectFromMenu(ILI9488 myDisplay, char *menu[])
{
  static int val = 0;
  activeMenuIndex = defaultOption;
  while (digitalRead(MENUENCODERSWITCH) != LOW) {
    if (en2State != 0) {
      MyDelay(200);
      myDisplay.setFont(&FreeSerif12pt7b);
      myDisplay.setTextColor(foregroundColor, backgroundColor);    // Turn off current option
      myDisplay.setCursor(activeColumn, activeRow);
      myDisplay.print(menu[activeMenuIndex]);

      // Find next option...
      if (encoder2 > 0) {                            // CW??
        activeMenuIndex++;
      } else {                                  // Nope, CCW
        activeMenuIndex--;
      }
      if (activeMenuIndex > itemCount - 1) // Advanced too far, set to first item
        activeMenuIndex = 0;
      if (activeMenuIndex < 0)                                  // Backed up too far, set to end item
        activeMenuIndex = itemCount - 1;

      activeRow = TOPDEADSPACE + FONTROWOFFSET + ROWSPACING * activeMenuIndex; // Determine active row

      myDisplay.setFont(&FreeSerif12pt7b);

      myDisplay.setTextColor(selectForegroundColor, selectBackgroundColor);
      myDisplay.setCursor(activeColumn, activeRow);
      myDisplay.print(menu[activeMenuIndex]);


      en2State = 0;
    }

  }

  return activeMenuIndex;
}
