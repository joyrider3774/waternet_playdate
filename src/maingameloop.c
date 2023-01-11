#include <stdlib.h>
#include <stdio.h>

#include "pd_api.h"
#include "crank.h"
#include "maingameloop.h"
#include "commonvars.h"
#include "titlescreen.h"
#include "game.h"
#include "helpscreens.h"
#include "levelscleared.h"
#include "intro.h"
#include "levelselect.h"
#include "sound.h"
#include "savestate.h"
#include "helperfuncs.h"

LCDBitmap* loadImageAtPath(const char* path)
{
    const char* outErr = NULL;
    LCDBitmap* img = pd->graphics->loadBitmap(path, &outErr);
    if (outErr != NULL) {
        pd->system->error("Error loading image at path '%s': %s", path, outErr);
        pd->system->logToConsole("Error loading image at path '%s': %s", path, outErr);
    }
    return img;
}

LCDBitmapTable* loadBitmapTableAtPath(const char* path)
{
    const char* outErr = NULL;
    LCDBitmapTable* table = pd->graphics->loadBitmapTable(path, &outErr);
    if (outErr != NULL) {
        pd->system->error("Error loading image at path '%s': %s", path, outErr);
        pd->system->logToConsole("Error loading image at path '%s': %s", path, outErr);
    }
    return table;
}

void preloadImages(void)
{
    titlescreenMap = loadImageAtPath("images/titlescreen");
    congratsMap = loadImageAtPath("images/congratsscreen");
    blockTiles = loadBitmapTableAtPath("images/blocktiles");
    blockTiles2 = loadBitmapTableAtPath("images/blocktiles2");
    blockTiles3 = loadBitmapTableAtPath("images/blocktiles3");
    blockTiles4 = loadBitmapTableAtPath("images/blocktiles4");
    blockTiles5 = loadBitmapTableAtPath("images/blocktiles5");
    blockTiles6 = loadBitmapTableAtPath("images/blocktiles6");
    blockTiles7 = loadBitmapTableAtPath("images/blocktiles7");
    blockTiles8 = loadBitmapTableAtPath("images/blocktiles8");
    blockTiles9 = loadBitmapTableAtPath("images/blocktiles9");
    blockTiles10 = loadBitmapTableAtPath("images/blocktiles10");
    blockTiles11 = loadBitmapTableAtPath("images/blocktiles11");
    blockTiles12 = loadBitmapTableAtPath("images/blocktiles12");
    blockTiles13 = loadBitmapTableAtPath("images/blocktiles13");
    blockTiles14 = loadBitmapTableAtPath("images/blocktiles14");
    blockTiles15 = loadBitmapTableAtPath("images/blocktiles15");
    blockTiles16 = loadBitmapTableAtPath("images/blocktiles16");
    blockTiles17 = loadBitmapTableAtPath("images/blocktiles17");
    blockTiles18 = loadBitmapTableAtPath("images/blocktiles18");
    blockTiles19 = loadBitmapTableAtPath("images/blocktiles19");
    blockTiles20 = loadBitmapTableAtPath("images/blocktiles20");
    blockTiles21 = loadBitmapTableAtPath("images/blocktiles21");
    blockTiles22 = loadBitmapTableAtPath("images/blocktiles22");
    blockTiles23 = loadBitmapTableAtPath("images/blocktiles23");
    blockTiles24 = loadBitmapTableAtPath("images/blocktiles24");
    selectorTiles = loadBitmapTableAtPath("images/selectortiles"); 
    congratsScreenTiles = loadBitmapTableAtPath("images/congratstiles");
}

void MenuItemCallback(void* userdata)
{
    int skin = pd->system->getMenuItemValue(SkinOptionMenuItem);
    int invertedColor = pd->system->getMenuItemValue(InvertedColorsOptionMenuItem);
    int musicOn = pd->system->getMenuItemValue(musicOptionMenuItem);
    setSkinSaveState(skin);
    setInvertedSaveState(invertedColor);
    setMusicOnSaveState(musicOn);
    //music is not playing when paused
    if (!paused && !levelDoneBit)
    {
        setMusicOn(musicOn);
    }
    setInverted(invertedColor);
    if (gameState != gsLevelsCleared)
    {
        setBlockTilesAsBackground();
        needRedraw = 1;
    }
}

// game initialization
void setupGame(void)
{  
    setCrankMoveThreshold(30);
    preloadImages();
    option = 0;
    needRedraw = 0;
    levelDoneBit = 0;
    paused = 0;
    difficulty = diffNormal;
    selectedLevel = 1;
    mainMenu = mmStartGame;
    gameState = gsInitIntro;
    titleStep = tsMainMenu;
    gameMode = gmRotate;
    initSaveState();
    initSound();
    initMusic();
    setMusicOn(isMusicOnSaveState());
    setSoundOn(isSoundOnSaveState());
    setBlockTilesAsBackground();
    setInverted(isInvertedSaveState());
    const char* musicOptions[] = { "Off", "On" };
    musicOptionMenuItem = pd->system->addOptionsMenuItem("Music", musicOptions, 2, MenuItemCallback, NULL);
    pd->system->setMenuItemValue(musicOptionMenuItem, isMusicOnSaveState());
    const char* skinOptions[] = {"01", "02", "03","04","05","06","07", "08",
        "09", "10", "11","12","13","14","15", "16",
        "17", "18", "19","20","21","22","23", "24" };
    SkinOptionMenuItem = pd->system->addOptionsMenuItem("Skin", skinOptions, 24, MenuItemCallback, NULL);
    pd->system->setMenuItemValue(SkinOptionMenuItem, skinSaveState());
    const char* InvertedOptions[] = { "Normal", "Inverted" };
    InvertedColorsOptionMenuItem = pd->system->addOptionsMenuItem("Colors", InvertedOptions, 2, MenuItemCallback, NULL);
    pd->system->setMenuItemValue(InvertedColorsOptionMenuItem, isInvertedSaveState());
}

// main update function
int mainLoop(void* ud)
{
    int result = 1;

    prevButtons = currButtons;
    pd->system->getButtonState(&currButtons, NULL, NULL);

    //gamestate handling   
    switch (gameState)
    {
        case gsInitTitle:
        case gsTitle:
            titleScreen();
            break;
        case gsInitLevelSelect:
        case gsLevelSelect:
            levelSelect();
            break;
        case gsInitGame:
        case gsGame:
            game();
            break;
        case gsInitLevelsCleared:
        case gsLevelsCleared:
            levelsCleared();
            break;
        case gsInitHelpSlide:
        case gsHelpSlide:
            helpSlide();
            break;
        case gsInitHelpSlide2:
        case gsHelpSlide2:
            helpSlide2();
            break;
        case gsInitHelpSlide3:
        case gsHelpSlide3:
            helpSlide3();
            break;
        case gsHelpRotateSlide:
        case gsInitHelpRotateSlide:
            helpRotateSlide();
            break;
        case gsInitHelpRotateSlide2:
        case gsHelpRotateSlide2:
            helpRotateSlide2();
            break;
        case gsInitHelpRotateSlide3:
        case gsHelpRotateSlide3:
            helpRotateSlide3();
            break;
        case gsInitHelpRotateSlide4:
        case gsHelpRotateSlide4:
            helpRotateSlide4();
            break;
        case gsInitHelpRotate:
        case gsHelpRotate:
            helpRotate();
            break;
        case gsInitHelpRotate2:
        case gsHelpRotate2:
            helpRotate2();
            break;
        case gsInitHelpRotate3:
        case gsHelpRotate3:
            helpRotate3();
            break;
        case gsInitIntro:
        case gsIntro:
            intro();
            break;
    }
    if (debugMode)
    {
        pd->system->drawFPS(0, 0);
    }
	return result;
}
