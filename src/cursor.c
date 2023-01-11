#include <stdint.h>

#include "pd_api.h"
#include "cursor.h"
#include "commonvars.h"
#include "helperfuncs.h"

#define MAXCURSORFRAMECOUNT (int)(10 * FRAMERATE / 60)
#define CURSORANIMCOUNT 4
#define NUMTILES 32

int cursorFrameCount, cursorFrame;
int spriteTiles[NUMTILES];
int showCursor = 1;
int spritePos[NUMTILES][2];

void set_sprite_tile(int sprite, int tile)
{
    spriteTiles[sprite] = tile;
}

void move_sprite(int sprite, int ax, int ay)
{
    spritePos[sprite][0] = ax * tileSize;
    spritePos[sprite][1] = ay * tileSize;
}

void drawCursors(void)
{
    if(showCursor == 0)
        return;
    for (int i=0; i<NUMTILES; i++)
    {
        if (spritePos[i][1] < pd->display->getHeight())
        {
            LCDBitmap* bitmap = pd->graphics->getTableBitmap(selectorTiles, spriteTiles[i]);
            if (bitmap)
            {
                pd->graphics->setDrawMode(kDrawModeBlackTransparent);
                pd->graphics->drawBitmap(bitmap, spritePos[i][0], spritePos[i][1], kBitmapUnflipped);
                pd->graphics->setDrawMode(kDrawModeCopy);
            }
        }
    }
}

int updateCursorFrame(void)
{
    int tmpFrame, result = 0;    
    if ((cursorFrameCount == 0) || (cursorFrameCount >= MAXCURSORFRAMECOUNT))
    {
        result = 1;
        cursorFrame++;
        cursorFrameCount = 0;
        if (cursorFrame >= CURSORANIMCOUNT)
        {
            cursorFrame = 0;
        }
        tmpFrame = (cursorFrame * 4);
       
        //cursor 0
        set_sprite_tile(0, 8 + tmpFrame);
        set_sprite_tile(1, 9 + tmpFrame);
        set_sprite_tile(2, 10 + tmpFrame);
        set_sprite_tile(3, 11 + tmpFrame);
        set_sprite_tile(4, 25 + tmpFrame);
        set_sprite_tile(5, 26 + tmpFrame);
        set_sprite_tile(6, 27 + tmpFrame);
        set_sprite_tile(7, 28 + tmpFrame);
        
        //cursor 1
        set_sprite_tile(8, 8 + tmpFrame);
        set_sprite_tile(9, 9 + tmpFrame);
        set_sprite_tile(10, 10 + tmpFrame);
        set_sprite_tile(11, 11 + tmpFrame);
        set_sprite_tile(12, 25 + tmpFrame);
        set_sprite_tile(13, 26 + tmpFrame);
        set_sprite_tile(14, 27 + tmpFrame);
        set_sprite_tile(15, 28 + tmpFrame);
       
        //cursor 2
        set_sprite_tile(16, 8 + tmpFrame);
        set_sprite_tile(17, 9 + tmpFrame);
        set_sprite_tile(18, 10 + tmpFrame);
        set_sprite_tile(19, 11 + tmpFrame);
        set_sprite_tile(20, 25 + tmpFrame);
        set_sprite_tile(21, 26 + tmpFrame);
        set_sprite_tile(22, 27 + tmpFrame);
        set_sprite_tile(23, 28 + tmpFrame);
       
        //cursor 3
        set_sprite_tile(24, 8 + tmpFrame);
        set_sprite_tile(25, 9 + tmpFrame);
        set_sprite_tile(26, 10 + tmpFrame);
        set_sprite_tile(27, 11 + tmpFrame);
        set_sprite_tile(28, 25 + tmpFrame);
        set_sprite_tile(29, 26 + tmpFrame);
        set_sprite_tile(30, 27 + tmpFrame);
        set_sprite_tile(31, 28 + tmpFrame);
    }    
    cursorFrameCount++;
    return result;
}

void hideCursors(void)
{
    //HIDE CURSOR SPRITES
    //cursor 0
    setCursorPos(0, 0, (pd->display->getHeight() / tileSize) + 1);
    
    //cursor 1
    setCursorPos(1, 0, (pd->display->getHeight() / tileSize) + 1);
    
    //cursor 2
    setCursorPos(2, 0, (pd->display->getHeight() / tileSize) + 1);
    
    //cursor 3
    setCursorPos(3, 0, (pd->display->getHeight() / tileSize) + 1);

    showCursor = 0;
}

void showCursors(void)
{
    showCursor = 1;
    cursorFrameCount = 0;
}

void setCursorPos(int cursorNr, int xPos, int yPos)
{
    if (cursorNr > 3)
    {
        return;
    }
    move_sprite((cursorNr<<3) + 0, (xPos), (yPos - 1));
    move_sprite((cursorNr<<3) + 1, (xPos + 1), (yPos));
    move_sprite((cursorNr<<3) + 2, (xPos), (yPos + 1));
    move_sprite((cursorNr<<3) + 3, (xPos - 1), (yPos)); 
    //corners
    move_sprite((cursorNr<<3) + 4, (xPos + 1), (yPos - 1));
    move_sprite((cursorNr<<3) + 5, (xPos + 1), (yPos + 1));
    move_sprite((cursorNr<<3) + 6, (xPos - 1), (yPos - 1));
    move_sprite((cursorNr<<3) + 7, (xPos - 1), (yPos + 1)); 
}

int getCursorPosX(int cursorNr)
{
    return spritePos[(cursorNr << 3)][0];
}

int getCursorPosY(int cursorNr)
{
    return spritePos[(cursorNr << 3)][1]+1;
}

void initCursors(void)
{
    //cursor 0
    set_sprite_tile(0, 8);
    set_sprite_tile(1, 9);
    set_sprite_tile(2, 10);
    set_sprite_tile(3, 11);
    set_sprite_tile(4, 25);
    set_sprite_tile(5, 26);
    set_sprite_tile(6, 27);
    set_sprite_tile(7, 28);

    //cursor 1
    set_sprite_tile(8, 8);
    set_sprite_tile(9, 9);
    set_sprite_tile(10, 10);
    set_sprite_tile(11, 11);
    set_sprite_tile(12, 25);
    set_sprite_tile(13, 26);
    set_sprite_tile(14, 27);
    set_sprite_tile(15, 28);

    //cursor 2
    set_sprite_tile(16, 8);
    set_sprite_tile(17, 9);
    set_sprite_tile(18, 10);
    set_sprite_tile(19, 11);
    set_sprite_tile(20, 25);
    set_sprite_tile(21, 26);
    set_sprite_tile(22, 27);
    set_sprite_tile(23, 28);

    //cursor 3
    set_sprite_tile(24, 8);
    set_sprite_tile(25, 9);
    set_sprite_tile(26, 10);
    set_sprite_tile(27, 11);
    set_sprite_tile(28, 25);
    set_sprite_tile(29, 26);
    set_sprite_tile(30, 27);
    set_sprite_tile(31, 28);

    hideCursors();

    cursorFrameCount = 0;
    cursorFrame = 0;
}
