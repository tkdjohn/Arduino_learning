#ifndef BEENHERE
#include "MorseTutor.h"
#endif

#ifndef MENU
#define MENU

#define HORIZONTAL       1    // Menu orientation
#define DROPDOWN         2

#define MAXMENUDEPTH    10
#define MENURANK        10     // The max level of menus


class Menuing
{
  public:
    int itemCount;              // options in a menu
    int defaultOption;          // which is highlighted when shown. Taken from defaultsList[] array
    int width;                  // width of display  (480)
    int height;                 // height of display (320)
    int spacing;                // pixel count available for each main menu option
    int activeColumn;           // Which column is active
    int activeRow;              // Which row is active
    int fontSize;               // Default text size
    int foregroundColor;        // Color of normal text
    int backgroundColor;        // Background color
    int selectForegroundColor;  // Color for active menu option
    int selectBackgroundColor;  // Background color for all menus
  
    void deselectMenuItem(ILI9488 myDisplay, char *menu[]);
    void eraseDisplay(ILI9488 myDisplay);
    void eraseMenus(ILI9488 myDisplay);
    Menuing(int displayWidth, int displayHeight, int foreColor, int backColor, int activeFore, int activeBack, int font);
    void scrollTopMenu(ILI9488 myDisplay, char *menu[], int encoder2, int defaults[]);
    int  selectFromMenu(ILI9488 myDisplay, char *menu[]);
    void showMenu(ILI9488 myDisplay, char *whichMenu[]);
    void showNewMenu(ILI9488 myDisplay, char *menu[], int encoder2, int defaults[]);
    int  updateMenu(ILI9488 myDisplay, char *menu[], int encoder2);
    
  private:
  
};

#endif
