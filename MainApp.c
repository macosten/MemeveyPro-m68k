#include "MainApp.h"

DialogPtr _mainDialog;
char _run = 1; //Set this to 0 when it's time to quit.
int _activeDITL = ditlMain; //This keeps track of the current UI that _mainDialog displays.

pascal void ButtonFrameProc(DialogRef dlg, DialogItemIndex itemNo){
    DialogItemType type;
    Handle itemH;
    Rect box;

    GetDialogItem(dlg, 1, &type, &itemH, &box);
    InsetRect(&box, -4, -4);
    PenSize(3,3);
    FrameRoundRect(&box,16,16);
}

void PresentAboutBox(){

	DialogRef aboutDialog = GetNewDialog(dlogAbout, 0, (WindowPtr)-1);
    DialogItemType type;
    Handle itemH;
    Rect box;

    GetDialogItem(aboutDialog, 2, &type, &itemH, &box);
    SetDialogItem(aboutDialog, 2, type, (Handle) NewUserItemUPP(&ButtonFrameProc), &box);
 
	MacSetPort(aboutDialog);
	UpdateDialog(aboutDialog, aboutDialog->visRgn);

	short item;
    do {
        ModalDialog(NULL, &item);
    } while(item != 1);

	FlushEvents(everyEvent, 0);
	DisposeWindow(aboutDialog);
	MacSetPort(_mainDialog);

}

void PresentUnimplementedDlog(){
    
    CautionAlert(alrtUnimplemented, NULL);

}

void PresentMainDlog(){
    _mainDialog = GetNewDialog(dlogMain, 0, (WindowPtr)-1);
    MacSetPort(_mainDialog);

    SwitchDITL(ditlMain);
    //Do anything else.
}

//Changes the UI of the main dialog.
//This lets us keep one dialog box around and just change its guts.
void SwitchDITL(short int toDitlID){
	_activeDITL = toDitlID;

	MacSetPort(_mainDialog);
	EraseRgn(_mainDialog->visRgn);
	ForeColor(whiteColor);

	ShortenDITL(_mainDialog, CountDITL(_mainDialog));
	Handle newDitl = GetResource('DITL', _activeDITL);
	AppendDITL(_mainDialog, newDitl, overlayDITL);
	ReleaseResource(newDitl);

	UpdateDialog(_mainDialog, _mainDialog->visRgn);
}


//
// Event Processing
//
void EventLoop(){

    EventRecord event;

    //For now, present the main dialog here.
    PresentMainDlog();

    //Essentially, the app's main loop.
    while (_run){
        if (WaitNextEvent(everyEvent, &event, 0, NULL)){
        	//On an event, process it.
            HandleEvent(&event);
        } else {
        	//Background tasks.

        	//Here, we could do something else.
        }
    }


}

//Handle a single event.
void HandleEvent(EventRecord *eventPtr){
	char eventChar;

	switch (eventPtr->what){

		case keyDown:
		case autoKey:
			eventChar = eventPtr->message & charCodeMask;
			if ((eventPtr->modifiers & cmdKey) != 0) HandleMenuChoice(MenuKey(eventChar));
			break;
		
		case mouseDown:
			HandleMouseDown(eventPtr);
			break;

		case updateEvt:
			//HandleUpdate(eventPtr);
			break;
		case kHighLevelEvent:
			AEProcessAppleEvent(eventPtr);
			break;

	}

}

//Handle a mouse click event.
void HandleMouseDown(EventRecord *eventPtr){
	WindowPtr window;
	short int part;
	long menuChoice;

	part = FindWindow(eventPtr->where, &window);

	switch (part){
		case inMenuBar:
			//If it's in the menu bar.
			menuChoice = MenuSelect(eventPtr->where);
			HandleMenuChoice(menuChoice);
			break;

		case inContent:
			//If it's in the content of the window. Todo.
			//HandleInContent(eventPtr)
			break;
		
		case inDrag:
			if (window == FrontWindow()) 
				DragWindow(window, eventPtr->where, &qd.screenBits.bounds);
			break;

		case inGoAway: //with "goAway" being the close box
			if (TrackGoAway(window, eventPtr->where)) QuitApp();
			break;

	}

}

//Handle a menu selection.
void HandleMenuChoice(long menuChoice){
	Str255 str;
	WindowRef w;
	short menuID = menuChoice >> 16;
	short menuItem = menuChoice & 0xFFFF;

	if (menuID == menuApple){ //Handle stuff in the Apple Menu
		if (menuItem == menuitemAbout) PresentAboutBox();
		else { 
			//If it's not the about box, it's another external app that we should let the OS handle.
			GetMenuItemText(MacGetMenu(menuApple), menuItem, str);
			OpenDeskAcc(str);
		}
	}
	else if (menuID == menuUser){
		switch (menuItem){
			case menuItemQuit:
				QuitApp();
				break;
			default:
				PresentUnimplementedDlog();
				break;
		}
	}
	else {
		PresentUnimplementedDlog();
	}

	HiliteMenu(0);
}


void HandleUpdate(EventRecord *eventPtr){
	if (_mainDialog == FrontWindow()){
		BeginUpdate(_mainDialog);

		//Update the content of the window here.

		UpdateDialog(_mainDialog, _mainDialog->visRgn);
		EndUpdate(_mainDialog);
	}
}




void QuitApp(){
	_run = 0; //Now, the EventLoop will stop.
	//Do any clean-up here.
	CloseDialog(_mainDialog);

	//For now, there isn't much else to do.

}