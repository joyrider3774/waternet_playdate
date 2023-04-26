#include <stdint.h>

#include "pd_api.h"
#include "commonvars.h"
#include "helperfuncs.h"
#include "sound.h"
#include "printfuncs.h"
#include "savestate.h"
#include "level.h"
#include "crank.h"


void updateBackgroundTitleScreen(void)
{
    pd->graphics->clear(kColorBlack);
    set_bkg_tiles(0, 0, titlescreenMap);

    if (titleStep == tsMainMenu)
    {
        printMessage(5, 4, "START");
        printMessage(5, 5, "HELP");
        printMessage(5, 6, "OPTIONS");
        printMessage(5, 7, "CREDITS");
    }
    else
    {
        if (titleStep == tsDifficulty)
        {
            printMessage(3, 3, "VERY EASY");
            printMessage(3, 4, "EASY");
            printMessage(3, 5, "NORMAL");
            printMessage(3, 6, "HARD");
            printMessage(3, 7, "VERY HARD");
            printMessage(3, 8, "RANDOM");
        }
        else
        {
            if (titleStep == tsGameMode)
            {
                printMessage(5, 4, "ROTATE");
                printMessage(5, 5, "SLIDE");
                printMessage(5, 6, "ROSLID");

            }
            else
            {
                if (titleStep == tsCredits)
                {
                    printMessage(3, 5, "CREATED BY");
                    printMessage(2, 6, "WILLEMS DAVY");
                    printMessage(2, 7, "JOYRIDER3774");
                }
                else
                {
                    if(isMusicOn())
                    {
                        printMessage(4, 4, "MUSIC ON");
                    }
                    else
                    {
                        printMessage(4, 4, "MUSIC OFF");
                    }

                    if(isSoundOn())
                    {
                        printMessage(4, 5, "SOUND ON");
                    }
                    else
                    {
                        printMessage(4, 5, "SOUND OFF");
                    }

                    printMessage(4, 6, "SKIN");
                    printNumber(9, 6, skinSaveState() + 1, 2);

                    if (isInvertedSaveState())
                    {
                        printMessage(4, 7, "INVERTED");
                    }
                    else
                    {
                        printMessage(4, 7, "NORMAL");
                    }

                }
            }
        }
    }


    //set menu tile
    if (titleStep == tsMainMenu)
    {
        set_bkg_tile_xy(4, 4 + mainMenu, leftMenu); 
    }
    else
    {
        //set menu tile
        if (titleStep == tsGameMode)
        {
            set_bkg_tile_xy(4, 4 + gameMode, leftMenu); 
        }
        else
        {
            if(titleStep == tsDifficulty)
            {
                set_bkg_tile_xy(2, 3 + difficulty, leftMenu);
            }
            else
            {
                if(titleStep == tsOptions)
                {
                    set_bkg_tile_xy(2, 4 + option, leftMenu);
                }    
            }
        }    
    }

}

void initTitleScreen(void)
{   
    setBlockTilesAsBackground();
    SelectMusic(musTitle);
    updateBackgroundTitleScreen();
    needRedraw = 0;
}

void doUp(void)
{
    if (titleStep == tsMainMenu)
    {
        playMenuSelectSound();
        needRedraw = 1;

        if (mainMenu > mmStartGame)
        {
            mainMenu--;
        }
        else
        {
            mainMenu = mmCount - 1;
        }
    }
    else
    {
        if (titleStep == tsGameMode)
        {
            playMenuSelectSound();
            needRedraw = 1;

            if (gameMode > gmRotate)
            {
                gameMode--;
            }
            else
            {
                gameMode = gmCount - 1;
            }
        }
        else
        {
            if (titleStep == tsDifficulty)
            {
                playMenuSelectSound();
                needRedraw = 1;
                if (difficulty > diffVeryEasy)
                {
                    difficulty--;
                }
                else
                {
                    difficulty = diffCount - 1;
                }
            }
            else
            {
                if (titleStep == tsOptions)
                {
                    playMenuSelectSound();
                    needRedraw = 1;
                    if (option > opMusic)
                    {
                        option--;
                    }
                    else
                    {
                        option = opCount - 1;
                    }
                }
            }
        }
    }
}

void doDown(void)
{
    if (titleStep == tsMainMenu)
    {
        needRedraw = 1;
        playMenuSelectSound();
        if (mainMenu < mmCount - 1)
        {
            mainMenu++;
        }
        else
        {
            mainMenu = mmStartGame;
        }
    }
    else
    {
        if (titleStep == tsGameMode)
        {
            playMenuSelectSound();
            needRedraw = 1;
            if (gameMode < gmCount - 1)
            {
                gameMode++;
            }
            else
            {
                gameMode = gmRotate;
            }
        }
        else
        {
            if (titleStep == tsDifficulty)
            {
                playMenuSelectSound();
                needRedraw = 1;
                if (difficulty < diffCount - 1)
                {
                    difficulty++;
                    
                }
                else
                {
                    difficulty = diffVeryEasy;
                }
            }
            else
            {
                if (titleStep == tsOptions)
                {
                    playMenuSelectSound();
                    needRedraw = 1;
                    if (option < opCount - 1)
                    {
                        option++;
                    }
                    else
                    {
                        option = opMusic;
                    }
                }
            }
        }
    }
}

void titleScreen(void)
{
    if (gameState == gsInitTitle)
    {
        initTitleScreen();
        gameState -= gsInitDiff;
    }

    switch (crankUpdate())
    {
        case CRANKMOVERIGHT:
            doUp();
            break;
        case CRANKMOVELEFT:
            doDown();
            break;
    }

    if ((currButtons & kButtonUp) && (!(prevButtons & kButtonUp)))
    {
        doUp();
    }
    if ((currButtons & kButtonDown) && (!(prevButtons & kButtonDown)))
    {
        doDown();
    }
    if ((currButtons & kButtonB) && (!(prevButtons & kButtonB)))
    {
        if ((titleStep == tsOptions) ||
            (titleStep == tsCredits))
        {
            titleStep = tsMainMenu;
            playMenuBackSound();
            needRedraw = 1;
        }
        else
        {
            if (titleStep > tsMainMenu)
            {
                titleStep--;
                playMenuBackSound();
                needRedraw = 1;
            }
        }
    }
    if ((currButtons & kButtonA) && (!(prevButtons & kButtonA)))
    {
        playMenuAcknowlege();
        if (mainMenu == mmOptions)
        {
            if(titleStep != tsOptions)
            {
                titleStep = tsOptions;
                needRedraw = 1;
            }
            else
            {
                switch(option)
                {
                    case opMusic:
					{
                        setMusicOn(!isMusicOn());
                        setMusicOnSaveState(isMusicOn());                       
                        pd->system->setMenuItemValue(musicOptionMenuItem, isMusicOnSaveState());                        
                        needRedraw = 1;
                        break;
					}
                    case opSound:
					{
                        setSoundOn(!isSoundOn());;
                        setSoundOnSaveState(isSoundOn());
                        needRedraw = 1;
                        break;
					}
                    case opSkin:
					{
                        int i = skinSaveState();
                        i++;
                        if (i == maxSkins)
                            i = 0;
                        setSkinSaveState(i);
                        pd->system->setMenuItemValue(SkinOptionMenuItem, skinSaveState());
                        setBlockTilesAsBackground();
                        needRedraw = 1;
                        break;
					}
                    case opInverted:
					{
                        setInvertedSaveState(!isInvertedSaveState());
                        setInverted(isInvertedSaveState());                        
                        needRedraw = 1;
                        break;
					}
                }
            }
        }

        if (mainMenu == mmCredits)
        {
            if(titleStep != tsCredits)
            {
                titleStep = tsCredits;
                needRedraw = 1;
            }
            else
            {
                titleStep = tsMainMenu;
                needRedraw = 1;
            }
        }

        if(mainMenu == mmHelp)
        {
            if (titleStep < tsGameMode)
            {
                titleStep++;
                needRedraw = 1;
            }
            else
            {
                switch (gameMode)
                {
                    case gmRotate:
                        gameState = gsInitHelpRotate;
                        break;
                    case gmSlide:
                        gameState = gsInitHelpSlide;
                        break;
                    case gmRotateSlide:
                        gameState = gsInitHelpRotateSlide;
                        break; 
                }
            }
        }
        if(mainMenu == mmStartGame)
        {
            
            if (titleStep < tsDifficulty)
            {
                titleStep++;
                needRedraw = 1;
            }
            else
            {
                if (difficulty == diffRandom)
                {
                    selectedLevel = 1;
                }
                else
                {
                    selectedLevel = lastUnlockedLevel(gameMode, difficulty);
                }
                gameState = gsInitLevelSelect;
                    
                if (gameMode == gmRotate)
                {
                    posAdd = 0;
                }
                else
                {
                    posAdd = 1;
                }
                //set randomseet to systime here
                //it will be reused all the time
                //with the level generating
                //but not when going back from
                //level playing to level selector
                //when calling init level there
                randomSeedGame = pd->system->getCurrentTimeMilliseconds() + pd->system->getSecondsSinceEpoch(NULL);
                initLevel(randomSeedGame);
            } 
        }  
    }
    if (needRedraw)
    {
        updateBackgroundTitleScreen();
    }
}
