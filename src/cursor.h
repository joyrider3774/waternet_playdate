#ifndef CURSOR_H
#define CURSOR_H

#include <stdint.h>

int updateCursorFrame(void);
void hideCursors(void);
void showCursors(void);
void setCursorPos(int cursorNr, int xPos, int yPos);
int getCursorPosX(int cursorNr);
int getCursorPosY(int cursorNr);
void initCursors(void);
void drawCursors(void);

#endif