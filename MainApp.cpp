#include "MainApp.h"


DialogPtr _mainDialog;
char _run = 1; //Set this to 0 when it's time to quit.
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

void PresentAutojerkResult(){


		
	DialogPtr autojerkResultDialog = GetNewDialog(dlogAutojerkResult, 0, (WindowPtr)-1);
    DialogItemType type;
    Handle itemH;
    Rect box;
	short item;

    GetDialogItem(autojerkResultDialog, 2, &type, &itemH, &box);
    SetDialogItem(autojerkResultDialog, 2, type, (Handle) NewUserItemUPP(&ButtonFrameProc), &box);
 
	MacSetPort(autojerkResultDialog);
	UpdateDialog(autojerkResultDialog, autojerkResultDialog->visRgn);
	
	SelectWindow(autojerkResultDialog);
		
	/*The strings you pass in the parameters to ParamText cannot contain the special strings
	^0 through ^3, or else the procedure will enter an endless loop of substitutions in
	versions of system software earlier than 7.1.*/
	if (!_markov.isInitialized()){
		//Return an error eventually.
		ParamText("\pThe Markov Object has not been initialized yet. Try opening a file.","\p","\p","\p");
		do {
			ModalDialog(NULL, &item);
		} while(item != 1);
		
	} else {
		//ParamText(myString,myString,myString,myString);
		ParamText("\pThe code to actually generate stuff hasn't been written yet...","\p","\p","\p");
		do {
			ModalDialog(NULL, &item);
		} while(item != 1);
    }
	
	FlushEvents(everyEvent, 0);
	DisposeWindow(autojerkResultDialog);
	
	MacSetPort(_mainDialog);
}

void PresentUnimplementedDlog(){
    //CautionAlert(alrtUnimplemented, NULL);
}

void PresentMainDlog(){
    //_mainDialog = GetNewWindow(windMain, 0, (WindowPtr)-1);
    _mainDialog = GetNewDialog(dlogMain, 0, (WindowPtr)-1);
    //SwitchDITL(ditlMain);
    //Do anything else.
}

//Changes the UI of the main dialog.
//This lets us keep one dialog box around and just change its guts.
//The only problem is that I have never gotten this to work, so...
/*
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
*/

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

	//For the "Crash Computer" option: Just try opening a DITL/DLOG that doesn't exist, or something :thonk:

}

//Handle a single event.
void HandleEvent(EventRecord *eventPtr){
	char eventChar;

	switch (eventPtr->what){

		case keyDown:
			//No commands here yet...
			break;
		case autoKey:
			eventChar = eventPtr->message & charCodeMask;
			if ((eventPtr->modifiers & cmdKey) != 0) HandleMenuChoice(MenuKey(eventChar));
			break;
		
		case mouseDown:
			HandleMouseDown(eventPtr);
			break;

		case updateEvt:
			HandleUpdate(eventPtr);
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
			if (window != FrontWindow()) SelectWindow(window);
			HandleInContent(eventPtr);
			break;
		
		case inDrag:
			if (window == FrontWindow()) 
				DragWindow(window, eventPtr->where, &qd.screenBits.bounds);
			break;

		case inGoAway: //with "goAway" being the close box
			if (TrackGoAway(window, eventPtr->where)){
				//We can do other things here, but for now...
				QuitApp();
				
			}
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
			case menuitemQuit:
				QuitApp();
				break;
			default:
				PresentUnimplementedDlog();
				break;
		}
	}
	else if (menuID == menuAutojerk){
		switch (menuItem){
			case menuitemAutojerkGenerate:
				PresentAutojerkResult();
				break;
			case menuitemAutojerkOpenFile:
				Point origin;
				origin.h = 80;
				origin.v = 80;
				OpenAutojerkSourceFile(origin);
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

void HandleInContent(EventRecord *eventPtr){
	//Todo
	WindowPtr window;
	DialogPtr dialog;
	short part, item;

	part = FindWindow(eventPtr->where, &window);
	
	
	
	//SelectWindow(window); //Bring the clicked window to the front.
	
	//Drag the window if CMD is held down.
	if ((eventPtr->modifiers & cmdKey) != 0) DragWindow(window, eventPtr->where, &qd.screenBits.bounds);
	
	if (DialogSelect(eventPtr, &dialog, &item)){
		if (dialog == _mainDialog) DragWindow(window, eventPtr->where, &qd.screenBits.bounds); //We'll do something more here later...
		else {} //Do nothing for now
	}

}

void QuitApp(){
	_run = 0; //Now, the EventLoop will stop.
	//Do any clean-up here.
	//CloseWindow(_mainDialog);
	CloseDialog(_mainDialog);
	//ExitToShell();
	//For now, there isn't much else to do.

}