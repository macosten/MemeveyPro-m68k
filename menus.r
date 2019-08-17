#include "Menus.r"

#include "constants.h"

resource 'MBAR' (defaultMenubar, preload) {
	{menuApple, menuUser, menuAutojerk, menuHelp, menuFuck};
};

/*See Inside Macintosh: Macintosh Toolbox / More Macintosh Toolbox*/
resource 'MENU' (menuApple, preload) { /*resource ID, preload resource*/
	menuApple, /*menu ID*/
	textMenuProc, /*uses standard menu definition */
					/* procedure*/
	0b1111111111111111111111111111101, /*enable About item, */
					/* disable divider, */
					/* enable all other items*/
					/* Read this word from the LSB to the MSB.*/
	enabled, /*enable menu title*/
	apple, /*menu title*/
	{
		/*first menu item*/
		"About Memevey Pro...", /*text of menu item*/
		noicon, nokey, nomark, plain; /*item characteristics*/
		/*second menu item*/
		"-",
		noicon, nokey, nomark, plain
	}

}; 

resource 'MENU' (menuUser, preload) {
	menuUser,
	textMenuProc,
	0b1111111111111111111111111111111,
	enabled,
	"User",
	{
		"Quit",
		noicon, nokey, nomark, plain
	}
};

resource 'MENU' (menuAutojerk, preload) {
	menuAutojerk,
	textMenuProc,
	0b1111111111111111111111111111111,
	enabled,
	"AutoJerk",
	{
		"Open Input File...",
		noicon, nokey, nomark, plain,
		"-", 
		noicon, nokey, nomark, plain,
		"Generate",
		noicon, nokey, nomark, plain
	}
};

resource 'MENU' (menuFuck, preload) {
	menuFuck,
	textMenuProc,
	0b1111111111111111111111111111111, /*I assume this enables all items, dunno though.*/
	enabled,
	"Fuck",
	{
		"Attempt Overwrite of Low Memory...",
		noicon, nokey, nomark, plain
	}
};

resource 'MENU' (menuHelp, preload) {
	menuHelp,
	textMenuProc,
	0b1111111111111111111111111111111,
	enabled,
	"Help",
	{
		"Help...",
		noicon, nokey, nomark, plain;
	}
};