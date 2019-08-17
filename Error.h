#include <MacWindows.h>
#include <Quickdraw.h>
#include <Dialogs.h>
#include <Fonts.h>
#include <Events.h>
#include <Devices.h>
#include <Resources.h>
#include <Types.h>


#include "constants.h"

//Convenient ways to call errors with custom text, when combined with the appropriate ditl and alrt in dialog.r



void NoteAlertWithText(ConstStr255Param inString);
void CautionAlertWithText(ConstStr255Param inString);
void StopAlertWithText(ConstStr255Param inString);

void PikaAlertWithText(ConstStr255Param inString);