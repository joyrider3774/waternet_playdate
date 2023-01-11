#include <time.h>

#include "pd_api.h"
#include "helperfuncs.h"
#include "commonvars.h"
#include "printfuncs.h"
#include "savestate.h"
#include "sound.h"
#include "level.h"
#include "crank.h"


void updateBackgroundLevelSelect(void) 
{
    pd->graphics->clear(kColorBlack);
    //LEVEL:
    printMessage(maxBoardBgWidth, 0, "LEVEL:");
    
    //[LEVEL NR] 2 chars
    printNumber(maxBoardBgWidth + 4, 1, selectedLevel, 2);
    
    //B:BACK
    printMessage(maxBoardBgWidth, 6, "b:");
    printMessage(maxBoardBgWidth, 7, "BACK");
    
    //A:PLAY
    printMessage(maxBoardBgWidth, 4, "a:");
    printMessage(maxBoardBgWidth, 5, "PLAY");
    
    //Locked & Unlocked keywoard
    int tmpUnlocked = levelUnlocked(gameMode, difficulty, selectedLevel -1);
    if(!tmpUnlocked)
    {
        printMessage(maxBoardBgWidth, 2, "LOCKED");
    }
    else
    {
        if(tmpUnlocked)
        {
            printMessage(maxBoardBgWidth, 2, "OPEN");
        }
    }
    
    drawLevel();
}

void initLevelSelect(void)
{
    setBlockTilesAsBackground();
    SelectMusic(musTitle);
    updateBackgroundLevelSelect();
    needRedraw = 0;
}

void doLeft(void)
{
    if (difficulty == diffRandom)
    {
        playMenuSelectSound();
        randomSeedGame = pd->system->getCurrentTimeMilliseconds() + pd->system->getSecondsSinceEpoch(NULL);
        initLevel(randomSeedGame);
        needRedraw = 1;
    }
    else
    {
        if (selectedLevel > 1)
        {
            playMenuSelectSound();
            selectedLevel--;
            initLevel(randomSeedGame);
            needRedraw = 1;
        }
    }
}

void doRight(void)
{
    if (difficulty == diffRandom)
    {
        playMenuSelectSound();
        //need new seed based on time
        randomSeedGame = pd->system->getCurrentTimeMilliseconds() + pd->system->getSecondsSinceEpoch(NULL);
        initLevel(randomSeedGame);
        needRedraw = 1;
    }
    else
    {
        if (selectedLevel < maxLevel)
        {
            playMenuSelectSound();
            selectedLevel++;
            initLevel(randomSeedGame);
            needRedraw = 1;
        }
    }
}

void levelSelect(void)
{
    int tmpUnlocked;
    tmpUnlocked = levelUnlocked(gameMode, difficulty, selectedLevel -1);
    
    if (gameState == gsInitLevelSelect)
    {
        initLevelSelect();
        gameState -= gsInitDiff;
    }
       
    if ((currButtons & kButtonB) && (!(prevButtons & kButtonB)))
    {
        playMenuBackSound();
        gameState = gsInitTitle;
    }
    if ((currButtons & kButtonA) && (!(prevButtons & kButtonA)))
    {
        if(tmpUnlocked)
        {
            gameState = gsInitGame;
            playMenuAcknowlege();
        }
        else
        {
            playErrorSound();
        }
    }
    if ((currButtons & kButtonLeft) && (!(prevButtons & kButtonLeft)))
    {
        doLeft();
    }
    if ((currButtons & kButtonRight) && (!(prevButtons & kButtonRight)))
    {
        doRight();
    }
    
    switch (crankUpdate())
    {
        case CRANKMOVELEFT:
            doLeft();
            break;
        case CRANKMOVERIGHT:
            doRight();
            break;
        default:
            break;
    }

    if (needRedraw)
    {
        updateBackgroundLevelSelect();
    }
}
