#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>
#include "pd_api.h"

#define musGame 1
#define musTitle 2
#define musLevelClear 3
#define musAllLevelsClear 4

#define SFX_SUSTAIN 100

void initSound(void);
void SelectMusic(int musicFile);
void initMusic(void);
void playGameAction(void);
void playMenuAcknowlege(void);
void playMenuBackSound(void);
void playMenuSelectSound(void);
void playErrorSound(void);
void playGameMoveSound(void);
void setMusicOn(int value);
void setSoundOn(int value);
int isMusicOn(void);
int isSoundOn(void);
void stopMusic(void);
void deInitSound();
void deInitMusic();
FilePlayer* loadSoundFile(const char* path);

#endif