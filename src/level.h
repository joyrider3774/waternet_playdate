#ifndef level_h
#define level_h

void drawLevel(void);
void moveBlockDown(int aTile);
void moveBlockUp(int aTile);
void moveBlockRight(int aTile);
void moveBlockLeft(int aTile);
void rotateBlock(int aTile);
void updateConnected(void);
void initLevel(unsigned long aRandomSeed);
int isLevelDone(void);

#endif