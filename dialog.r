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
 	"About PetProject-m68k",
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
		StaticText {enabled, "PetProject-m68k 0.0.0\rBy Zac Silverman (macosten)"};
		
		{ 25, 10, 95, 105 },
		Picture {enabled, 128};

	}
};

resource 'ALRT' (alrtUnimplemented, purgeable) {
	{ 0, 0, 90, 400 },
	ditlUnimplemented,
	{
		OK, visible, sound1,
		OK, visible, sound1,
		OK, visible, sound1,
		OK, visible, sound1
	},
	alertPositionMainScreen
};

resource 'DITL' (ditlUnimplemented, purgeable){
	{
		{56, 300, 56+20, 380},
		Button {enabled, "OK"};

		{8, 72, 38, 380},
		StaticText { disabled, "This functionality has not yet been implemented."};
	}
};

resource 'DLOG' (dlogMain){ //Purgeable?
	{0, 0, 400, 600},
	movableDBoxProc,
	visible,
	goAway, //Revisit this
	0,
	ditlMain,
	"PetProject-m68k",
	centerMainScreen
};

resource 'DITL' (ditlMain, purgeable){
	{
		{10, 10, 40, 300},
		StaticText {disabled, "PetProject Main Window."};
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
#ifdef TARGET_API_MAC_CARBON
	500 * 1024,	// Carbon apparently needs additional memory.
	500 * 1024
#else
	100 * 1024,
	100 * 1024
#endif
};
