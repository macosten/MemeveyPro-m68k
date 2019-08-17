#include "MainApp.h"
#include "constants.h"

#include <stdlib.h>
#include <time.h>

#ifndef TARGET_API_MAC_CARBON
    /* NOTE: this is checking whether the Dialogs.h we use *knows* about Carbon,
             not whether we are actually compiling for Cabon.
             If Dialogs.h is older, we add a define to be able to use the new name
             for NewUserItemUPP, which used to be NewUserItemProc. */
#define NewUserItemUPP NewUserItemProc
#endif


// Initialize
void Initialize() {

    //Initialize the Toolbox
#if !TARGET_API_MAC_CARBON
    InitGraf(&qd.thePort);
    InitFonts();
    InitWindows();
    InitMenus();
    TEInit();
    InitDialogs(NULL);
#endif
    InitCursor();

    //Initialize the menus

    //Get our menu bar
    Handle menubar = GetNewMBar(defaultMenubar);
    SetMenuBar(menubar);
    
    //Append the user's Apple Menu items to the Apple Menu
    AppendResMenu(GetMenuHandle(defaultMenubar), 'DRVR');

    //Dispose of the handle
    DisposeHandle(menubar);

    //Draw the menu bar
    DrawMenuBar();

	//Seed the random number generator. There's a Macintosh Toolbox call for this, I think, but I forget what it was.
	srand(time(0));
	
    //Do anything else.
	
}



int main(){
    Initialize();

    EventLoop();

    FlushEvents(everyEvent, -1);
    return 0;
}
