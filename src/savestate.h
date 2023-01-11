#ifndef SAVESTATE_H
#define SAVESTATE_H

void initSaveState(void);

int lastUnlockedLevel(int mode, int diff);
int levelUnlocked(int mode, int diff, int aLevel);
int isMusicOnSaveState(void);
int isSoundOnSaveState(void);
int isInvertedSaveState(void);
int skinSaveState(void);
void unlockLevel(int mode, int diff, int aLevel);
void setMusicOnSaveState(int value);
void setSoundOnSaveState(int value);
void setSkinSaveState(int value);
void setInvertedSaveState(int value);
#endif