#ifndef commonvars_h
#define commonvars_h

#include <stdlib.h>
#include <stdio.h>
#include "pd_api.h"

#define tileSize 24

#define maxBoardWidth 10
#define maxBoardHeight 8

#define maxBoardBgWidth 10
#define maxBoardBgHeight 8

#define maxBoardSize 80

#define gsGame 0
#define gsTitle 1
#define gsLevelSelect 2
#define gsLevelsCleared 3
#define gsHelpRotate 4
#define gsHelpRotate2 5
#define gsHelpRotate3 6
#define gsHelpRotateSlide 7
#define gsHelpRotateSlide2 8
#define gsHelpRotateSlide3 9
#define gsHelpRotateSlide4 10
#define gsHelpSlide 11
#define gsHelpSlide2 12
#define gsHelpSlide3 13
#define gsIntro 14

#define gsInitDiff 50

#define gsInitGame (gsInitDiff + gsGame)
#define gsInitTitle (gsInitDiff + gsTitle)
#define gsInitLevelSelect (gsInitDiff + gsLevelSelect)
#define gsInitLevelsCleared (gsInitDiff + gsLevelsCleared)
#define gsInitHelpRotate (gsInitDiff + gsHelpRotate)
#define gsInitHelpRotate2 (gsInitDiff + gsHelpRotate2)
#define gsInitHelpRotate3 (gsInitDiff + gsHelpRotate3)
#define gsInitHelpRotateSlide (gsInitDiff + gsHelpRotateSlide)
#define gsInitHelpRotateSlide2 (gsInitDiff + gsHelpRotateSlide2)
#define gsInitHelpRotateSlide3 (gsInitDiff + gsHelpRotateSlide3)
#define gsInitHelpRotateSlide4 (gsInitDiff + gsHelpRotateSlide4)
#define gsInitHelpSlide (gsInitDiff + gsHelpSlide)
#define gsInitHelpSlide2 (gsInitDiff + gsHelpSlide2)
#define gsInitHelpSlide3 (gsInitDiff + gsHelpSlide3)
#define gsInitIntro (gsInitDiff + gsIntro)

#define diffVeryEasy 0
#define diffEasy 1
#define diffNormal 2
#define diffHard 3
#define diffVeryHard 4
#define diffRandom 5
#define diffCount 6

#define gmRotate 0
#define gmSlide 1
#define gmRotateSlide 2
#define gmCount 3

#define mmStartGame 0
#define mmHelp 1
#define mmOptions 2
#define mmCredits 3
#define mmCount 4

#define opMusic 0
#define opSound 1
#define opSkin 2
#define opInverted 3
#define opCount 4

#define tsMainMenu 0
#define tsGameMode 1
#define tsDifficulty 2
#define tsOptions 3
#define tsCredits 4

#define levelCount 25
#define arrowDown 122
#define arrowUp 120
#define arrowLeft 123
#define arrowRight 121
#define leftMenu 118
#define emptyFloor 49

#define maxSkins 24

#define FRAMERATE 15

extern int startPos, menuPos, maxLevel, selectedLevel, boardX, boardY, difficulty,
	gameState, boardWidth, boardHeight, boardSize, levelDone, titleStep, gameMode, posAdd,
	mainMenu, option, debugMode, needRedraw, paused, levelDoneBit, fpsStep;

extern PDMenuItem* SkinOptionMenuItem, * InvertedColorsOptionMenuItem, * musicOptionMenuItem;

extern int selectionX, selectionY;
extern int moves;
extern unsigned int randomSeedGame;
extern unsigned char level[maxBoardSize];
extern PlaydateAPI *pd;
extern PDButtons currButtons, prevButtons;
extern LCDBitmap *titlescreenMap, *congratsMap;
extern LCDBitmapTable* blockTiles, * blockTiles2, * blockTiles3, * blockTiles4, * blockTiles5,
	* blockTiles6, * blockTiles7, * blockTiles8, * blockTiles8, * blockTiles8,
	* blockTiles9, * blockTiles10, * blockTiles11, * blockTiles12, * blockTiles13,
	* blockTiles14, * blockTiles15, * blockTiles16, * blockTiles17, * blockTiles18,
	* blockTiles19, * blockTiles20, * blockTiles21, * blockTiles22, * blockTiles23,
	* blockTiles24, * selectorTiles, * congratsScreenTiles;

void setPDPtr(PlaydateAPI* p);

#endif