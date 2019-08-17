#include "Error.h"

pascal void ButtonFrameDraw(DialogRef dlg, DialogItemIndex itemNo){
    DialogItemType type;
    Handle itemH;
    Rect box;

    GetDialogItem(dlg, 1, &type, &itemH, &box);
    InsetRect(&box, -4, -4);
    PenSize(3,3);
    FrameRoundRect(&box,16,16);
}


void NoteAlertWithText(ConstStr255Param inString){
	ParamText(inString,"\p","\p","\p");
	NoteAlert(alrtGenericTextless, NULL);
}

void CautionAlertWithText(ConstStr255Param inString){
	ParamText(inString,"\p","\p","\p");
	CautionAlert(alrtGenericTextless, NULL);
}

void StopAlertWithText(ConstStr255Param inString){
	ParamText(inString,"\p","\p","\p");
	StopAlert(alrtGenericTextless, NULL);
}

void PikaAlertWithText(ConstStr255Param inString){
	DialogPtr pikaAlert = GetNewDialog(dlogPikaAlert, 0, (WindowPtr)-1);
    DialogItemType type;
    Handle itemH;
    Rect box;
	short item;

	MacSetPort(pikaAlert);
	UpdateDialog(pikaAlert, pikaAlert->visRgn);
	
	GetDialogItem(pikaAlert, 2, &type, &itemH, &box);
    SetDialogItem(pikaAlert, 2, type, (Handle) NewUserItemUPP(&ButtonFrameDraw), &box);
 
	SelectWindow(pikaAlert);
	
	ParamText(inString,"\p","\p","\p");
	
	do {
		ModalDialog(NULL, &item);
	} while(item != 1);
    
	FlushEvents(everyEvent, 0);
	DisposeWindow(pikaAlert);
	
}