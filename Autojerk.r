#include "Dialogs.r"
#include "constants.h"


resource 'DLOG' (dlogAutojerkResult){ //Purgeable?
	{0, 0, 280, 480},
	dBoxProc,
	visible,
	goAway, //Revisit this
	0,
	ditlAutojerkResult,
	"AutoJerk Result",
	centerMainScreen
};

resource 'DITL' (ditlAutojerkResult, purgeable){
	{
		{ 240, 150, 260, 290},
		Button {enabled, "Uh..."};
		
		{ 240-5, 150-5, 260+5, 290+5 },
		UserItem {enabled};

		{12, 112, 220, 460},
		StaticText { disabled, "^0^1^2^3"}; //use ^0 as the placeholder when ready to test it
		
		{ 25, 10, 95, 105 },
		Picture {enabled, pictPikawow};
	}
};