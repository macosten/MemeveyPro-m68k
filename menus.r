#include "Menus.r"

#include "constants.h"

resource 'MBAR' (defaultMenubar, preload) {
	{menuApple, menuUser, menuPets, menuHelp};
};

/*See Inside Macintosh: Macintosh Toolbox / More Macintosh Toolbox*/
resource 'MENU' (menuApple, preload) { /*resource ID, preload resource*/
	menuApple, /*menu ID*/
	textMenuProc, /*uses standard menu definition */
					/* procedure*/
	0b1111111111111111111111111111101, /*enable About item, */
					/* disable divider, */
					/* enable all other items*/
	enabled, /*enable menu title*/
	apple, /*menu title*/
	{
		/*first menu item*/
		"About PetProject...", /*text of menu item*/
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
		"Login",
		noicon, nokey, nomark, plain;
		"Logout",
		noicon, nokey, nomark, plain;
		"-",
		noicon, nokey, nomark, plain,
		"Quit",
		noicon, nokey, nomark, plain
	}
};

resource 'MENU' (menuPets, preload) {
	menuPets,
	textMenuProc,
	0b1111111111111111111111111111111, /*I assume this enables all items, dunno though.*/
	enabled,
	"Pets",
	{
		"View Pets",
		noicon, nokey, nomark, plain;
		"Create Pet",
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