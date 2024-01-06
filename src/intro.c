 #include <stdint.h>

#include "helperfuncs.h"
#include "commonvars.h"
#include "pd_api.h"
#include "printfuncs.h"
#include "intro.h"

#define FRAMEDELAY 10

int frames = 0;
int ay;

void initIntro(void)
{
	frames = 0;
    setBlockTilesAsBackground();
    ay = pd->display->getHeight();
}

void intro(void)
{
    if (gameState == gsInitIntro)
    {
        initIntro();
        gameState -= gsInitDiff;
    }
    
    frames++;
    pd->graphics->clear(kColorBlack);
    if (frames < FRAMEDELAY)
    {
        printMessage((16-12) >> 1, 4, "WILLEMS DAVY");
    }
    else
    {
        if (frames < FRAMEDELAY *2)
        {
            printMessage((16-8) >> 1, 4, "PRESENTS");
        }
        else
        {
            set_bkg_tiles(0, ay, titlescreenMap);
            if(ay > 0)
            {
                ay -= 10;
            }
            else
            {
                gameState = gsInitTitle;
            }
        }
    }
        
    if (((currButtons & kButtonA) && (!(prevButtons & kButtonA))) ||
        ((currButtons & kButtonB) && (!(prevButtons & kButtonB))))
    {            
        gameState = gsInitTitle;
    }

    if (currButtons & kButtonUp)
    {
        debugMode = 1;
    }
}
