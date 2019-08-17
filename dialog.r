#include "Dialogs.r"
#include "constants.h"

resource 'DLOG' (dlogAbout, purgeable) {
	//Top Left Bottom Right
	{ 0, 0, 145, 350 },
	dBoxProc,
 	visible,
 	noGoAway, //No close box
 	0,
 	ditlAbout,
 	"About MemeveyPro-m68k",
 	centerMainScreen
};

resource 'DITL' (ditlAbout, purgeable) {
	{
		// Top Left Bottom Right 
		{ 110, 200, 130, 320 },
		Button { enabled, "Sure, Whatever" };

		{ 110-5, 200-5, 130+5, 320+5 },
		UserItem {enabled};

		{ 30, 110, 100, 350 },
		StaticText {enabled, "MemeveyPro-m68k 0.0.0\rBy Zac Silverman (macosten)"};
		
		{ 25, 10, 95, 105 },
		Picture {enabled, pictPikawow};

	}
};

resource 'DLOG' (dlogPikaAlert, purgeable) {
	//Top Left Bottom Right
	{ 0, 0, 145, 350 },
	dBoxProc,
 	visible,
 	noGoAway, //No close box
 	0,
 	ditlPikaAlert,
 	"About MemeveyPro-m68k",
 	centerMainScreen
};

resource 'DITL' (ditlPikaAlert, purgeable) {
	{
		// Top Left Bottom Right 
		{ 110, 200, 130, 320 },
		Button { enabled, "OK" };

		{ 110-5, 200-5, 130+5, 320+5 },
		UserItem {enabled};

		{ 30, 110, 100, 350 },
		StaticText {enabled, "^0"};
		
		{ 25, 10, 95, 105 },
		Picture {enabled, pictPikawow};

	}
};

resource 'ALRT' (alrtGenericTextless, purgeable) {
	{ 0, 0, 90, 400 },
	ditlGenericTextless,
	{
		OK, visible, sound1,
		OK, visible, sound1,
		OK, visible, sound1,
		OK, visible, sound1
	},
	alertPositionMainScreen
};

resource 'DITL' (alrtGenericTextless, purgeable){
	{
		{56, 300, 56+20, 380},
		Button {enabled, "OK"};

		{8, 72, 38, 380},
		StaticText { disabled, "^0"}; //There was an error opening that file. Try a different file, or try again later/after a restart.
	}
};

resource 'WIND' (windMain){
	{0, 0, 400, 600},
	zoomDocProc,
	visible,
	goAway,
	0,
	"MemeveyPro-m68k",
	centerMainScreen
};

resource 'DLOG' (dlogMain){ //Purgeable?
	{0, 0, 400, 600},
	zoomDocProc,
	visible,
	goAway, //Revisit this
	0,
	ditlMain,
	"MemeveyPro-m68k",
	centerMainScreen
};

resource 'DITL' (ditlMain, purgeable){
	{
		{10, 10, 40, 300},
		StaticText {disabled, "Memevey Pro Main Window."};
	}
};

#include "Processes.r"

resource 'SIZE' (-1) {
	dontSaveScreen,
	acceptSuspendResumeEvents,
	enableOptionSwitch,
	canBackground,
	multiFinderAware,
	backgroundAndForeground,
	dontGetFrontClicks,
	ignoreChildDiedEvents,
	is32BitCompatible,
	isHighLevelEventAware,
	onlyLocalHLEvents,
	notStationeryAware,
	reserved,
	reserved,
	reserved,
	reserved,
	1000 * 1024,
	1000 * 1024
};
