#include <MacWindows.h>
#include <Quickdraw.h>
#include <Dialogs.h>
#include <Fonts.h>
#include <Events.h>
#include <Devices.h>
#include <Resources.h>

#include "constants.h"

extern DialogPtr _mainDialog;

pascal void ButtonFrameProc(DialogRef dlg, DialogItemIndex itemNo);

//Present Dialog Boxes
void PresentAboutBox();
void PresentUnimplementedDlog();
void PresentMainDlog();

void SwitchDITL(short int toDitlID);

//Event Processing
void EventLoop();

void HandleEvent(EventRecord *eventPtr);

void HandleMouseDown(EventRecord *eventPtr);
void HandleMenuChoice(long menuChoice);
void HandleUpdate(EventRecord *eventPtr);

void QuitApp();