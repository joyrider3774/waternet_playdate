#include <stdint.h>
#include <string.h>
#include "pd_api.h"
#include "commonvars.h"
#include "sound.h"


//I (joyrider3774) created the music in this tool : https://onlinesequencer.net
//levels cleared: https://onlinesequencer.net/2498607
//level done:     https://onlinesequencer.net/2484974
//game music:     https://onlinesequencer.net/2485064
//title music:    https://onlinesequencer.net/2484977

int prev_music = -1, music_on = 0, sound_on = 0, force = 0;

FilePlayer* musicPlayer;
FilePlayer* gameMoveSound;
FilePlayer* errorSound;
FilePlayer* menuSelectSound;
FilePlayer* menuBackSound;
FilePlayer* gameAction;
FilePlayer* menuAcknowledge;


void stopMusic(void)
{
    if (pd->sound->fileplayer->isPlaying(musicPlayer))
    {
        pd->sound->fileplayer->stop(musicPlayer);
    }
}

void setMusicOn(int value)
{
    music_on = value;
    if(music_on)
    {
        if (prev_music != -1)
        {
            force = 1;
            SelectMusic(prev_music);
        }
        else if (gameState == gsTitle)
        {
            force = 1;
            SelectMusic(musTitle);
        }
    }
    else
    {
        stopMusic();
    }
}

void setSoundOn(int value)
{
    sound_on = value;
}

int isMusicOn(void)
{
    return music_on;
}

int isSoundOn(void)
{
    return sound_on;
}

FilePlayer* loadSoundFile(const char* path)
{
    FilePlayer* soundPlayer = pd->sound->fileplayer->newPlayer();
    pd->sound->fileplayer->setStopOnUnderrun(soundPlayer, 1);
    pd->sound->fileplayer->setVolume(soundPlayer, 0.7f, 0.7f);
    pd->sound->fileplayer->setRate(soundPlayer, 1.0f);
    pd->sound->fileplayer->loadIntoPlayer(soundPlayer, path);
    return soundPlayer;
}

void initSound(void)
{
    gameMoveSound = loadSoundFile("sound/gamemove");
    errorSound = loadSoundFile("sound/error");
    menuSelectSound = loadSoundFile("sound/menuselect");
    menuBackSound = loadSoundFile("sound/menuback");
    gameAction = loadSoundFile("sound/gameaction");
    menuAcknowledge = loadSoundFile("sound/menuacknowledge");
}

void playMusicFile(const char* path, int repeat)
{
    if(pd->sound->fileplayer->isPlaying(musicPlayer))
    {
        pd->sound->fileplayer->stop(musicPlayer);
    }

    if (pd->sound->fileplayer->loadIntoPlayer(musicPlayer, path))
    {
        pd->sound->fileplayer->play(musicPlayer, repeat);
    }
}

void SelectMusic(int musicFile)
{
    if (((prev_music != musicFile) || force) && music_on)
    {
        force = 0;
        prev_music = musicFile;
        switch (musicFile) 
        {
            case musTitle:
                playMusicFile("music/title", 0);
                break;
            case musLevelClear:
                playMusicFile("music/leveldone", 1);
                break;
            case musAllLevelsClear:
                playMusicFile("music/levelscleared", 0);
                break;
            case musGame:
                playMusicFile("music/game", 0);
                break;
        }
    }
    else
    {
        //still need to remember last music we tried to play in case music was off & we reenable
        if (!music_on)
        {
            prev_music = musicFile;
        }
    }
}


void initMusic(void)
{
    prev_music = -1;
    //titleMusic = loadMidi("music/title.mid", 0);
    musicPlayer = pd->sound->fileplayer->newPlayer();
    pd->sound->fileplayer->setStopOnUnderrun(musicPlayer, 1);
    pd->sound->fileplayer->setVolume(musicPlayer, 1.0f, 1.0f);
    pd->sound->fileplayer->setRate(musicPlayer, 1.0f);
}

void playSound(FilePlayer* soundPlayer)
{
    if (pd->sound->fileplayer->isPlaying(soundPlayer))
    {
        pd->sound->fileplayer->stop(soundPlayer);
    }
    pd->sound->fileplayer->play(soundPlayer, 1);   
}

void playGameMoveSound(void)
{
    if(!sound_on)
    {
        return;
    }
    playSound(gameMoveSound);
}

void playErrorSound(void)
{
    if(!sound_on)
    {
        return;
    }
    playSound(errorSound);
}

void playMenuSelectSound(void)
{
    if(!sound_on)
    {
        return;
    }
    playSound(menuSelectSound);
}

void playMenuBackSound(void)
{
    if(!sound_on)
    {
        return;
    }
    playSound(menuBackSound);
}

void playMenuAcknowlege(void)
{
    if(!sound_on)
    {
        return;
    }
    playSound(menuAcknowledge);
}

void playGameAction(void)
{
    if(!sound_on)
    {
        return;
    }
    playSound(gameAction);
}
