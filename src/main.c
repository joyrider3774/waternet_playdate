#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"

#include "commonvars.h"
#include "maingameloop.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif

int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg)
{

	if ( event == kEventInit )
	{
		setPDPtr(playdate);
		playdate->system->logToConsole("app.uuid=eabca8a02962448bb4abf53cc07add62");
		playdate->display->setRefreshRate(FRAMERATE);
		//original graphcis were 8x8 for a screen resolution of 128x64 (arduboy) i scaled the graphics by 3
		//so we have some space left and can use a drawoffset to center everything on the screen
		playdate->graphics->setDrawOffset((400 - 384) >> 1, ((240 - 192) >> 1));
		playdate->system->setUpdateCallback(mainLoop, NULL);
		setupGame();
	}
	
	return 0;
}
