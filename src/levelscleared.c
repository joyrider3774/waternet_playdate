#include <stdint.h>

#include "pd_api.h"
#include "helperfuncs.h"
#include "commonvars.h"
#include "printfuncs.h"
#include "sound.h"
#include "level.h"

void initLevelsCleared(void)
{
    set_bkg_data(congratsScreenTiles);
    pd->graphics->clear(kColorBlack);
    set_bkg_tiles(0, 0, congratsMap);
    SelectMusic(musAllLevelsClear);
}

void levelsCleared(void) 
{
    if (gameState == gsInitLevelsCleared)
    {
        initLevelsCleared();
        gameState -= gsInitDiff;
    }
    
    if (difficulty == diffVeryEasy)
    {
        printCongratsScreen(0, 3, "VERY EASY LEVELS");
    }
    if (difficulty == diffEasy)
    {
        printCongratsScreen(3, 3, "EASY LEVELS");
    }
    if (difficulty == diffNormal)
    {
        printCongratsScreen(2, 3, "NORMAL LEVELS");
    }
    if (difficulty == diffHard)
    {
        printCongratsScreen(3, 3, "HARD LEVELS");
    }
    if (difficulty == diffVeryHard)
    {
        printCongratsScreen(0, 3, "VERY HARD LEVELS");
    }


     if (((currButtons & kButtonA) && (!(prevButtons & kButtonA))) ||
         ((currButtons & kButtonB) && (!(prevButtons & kButtonB))))
     {
         playMenuAcknowlege();
         titleStep = tsMainMenu;
         gameState = gsInitTitle;
     }
}