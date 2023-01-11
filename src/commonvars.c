#include "commonvars.h"
#include "pd_api.h"


int startPos, menuPos, maxLevel, selectedLevel, boardX, boardY, difficulty,
    gameState, boardWidth, boardHeight, boardSize, levelDone, titleStep, gameMode, posAdd,
    mainMenu, option, debugMode, needRedraw, paused, levelDoneBit, fpsStep;

PDMenuItem* SkinOptionMenuItem, * InvertedColorsOptionMenuItem, * musicOptionMenuItem;

int selectionX, selectionY, i16;
int moves;
unsigned int randomSeedGame;
unsigned char level[maxBoardSize];
PlaydateAPI* pd;
PDButtons currButtons, prevButtons;
LCDBitmap* titlescreenMap, * congratsMap;
LCDBitmapTable* blockTiles, * blockTiles2, * blockTiles3, * blockTiles4, * blockTiles5,
    * blockTiles6, * blockTiles7, * blockTiles8, * blockTiles8, * blockTiles8, 
    * blockTiles9, * blockTiles10, * blockTiles11, * blockTiles12, * blockTiles13, 
    * blockTiles14, * blockTiles15, * blockTiles16, * blockTiles17, * blockTiles18, 
    * blockTiles19, * blockTiles20, * blockTiles21, * blockTiles22, * blockTiles23,
    * blockTiles24, * selectorTiles, * congratsScreenTiles;

void setPDPtr(PlaydateAPI* p) {
    pd = p;
}
