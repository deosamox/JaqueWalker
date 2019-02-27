#include <3ds.h>
#include <iostream>
#include "link.h"

int main(int argc, char** argv) {
	gfxInitDefault();
	hidInit();
	consoleInit(GFX_TOP, nullptr);
	std::string text = "(A) to start as main, (B) as slave, (X) to reflect, (SELECT) for test, (START) to quit.";
	std::cout << text << std::endl;

	//copied from keyboard example:
	static SwkbdState swkbd;
	static char mybuf[60];
	static SwkbdStatusData swkbdStatus;
	static SwkbdLearningData swkbdLearning;
	SwkbdButton button = SWKBD_BUTTON_NONE;
	bool didit = false;
	
	while (aptMainLoop()) {
		hidScanInput();
		if (hidKeysDown() & KEY_START)
			break;
		if (hidKeysDown() & KEY_A) {
			FMS::startTransfer(0, false);
            std::cout << text << std::endl;
        }
		if (hidKeysDown() & KEY_B) {
			FMS::startTransfer(1, false);
			std::cout << text << std::endl;
		}
		if (hidKeysDown() & KEY_X) {
			FMS::startTransfer(2, false);
			std::cout << text << std::endl;
		}
		//copied from keyboard example
		if (hidKeysDown() & KEY_SELECT)
		{
			didit = true;
			swkbdInit(&swkbd, SWKBD_TYPE_NORMAL, 3, -1);
			swkbdSetInitialText(&swkbd, mybuf);
			swkbdSetHintText(&swkbd, "Please enter hex values");
			swkbdSetButton(&swkbd, SWKBD_BUTTON_LEFT, "Maybe Not", false);
			swkbdSetButton(&swkbd, SWKBD_BUTTON_MIDDLE, "~Middle~", true);
			swkbdSetButton(&swkbd, SWKBD_BUTTON_RIGHT, "Do It", true);
			swkbdSetFeatures(&swkbd, SWKBD_PREDICTIVE_INPUT);
			static bool reload = false;
			swkbdSetStatusData(&swkbd, &swkbdStatus, reload, true);
			swkbdSetLearningData(&swkbd, &swkbdLearning, reload, true);
			reload = true;
			button = swkbdInputText(&swkbd, mybuf, sizeof(mybuf));
		}


		// Flush and swap framebuffers
        gfxFlushBuffers();
        gfxSwapBuffers();
        //Wait for VBlank
        gspWaitForVBlank();
	}
	gfxExit();
	hidExit();
}
