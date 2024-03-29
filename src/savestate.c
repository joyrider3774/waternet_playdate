#include <string.h>
#include <stdbool.h>
#include "commonvars.h"


char header[16];
unsigned int check;
int levelLocks[gmCount][diffCount];
int musicOn;
int soundOn;
int skin;
int inverted;
unsigned int saveTime;
int valid;

unsigned int encrypt(unsigned int filepos, unsigned int time, void* data, unsigned int size, bool returnOriginalPos)
{
    #define keySize 21
    const unsigned char key[keySize] = { 0x58, 0x030, 0x49, 0x53, 0x67, 0x68, 0x68, 0x41, 0x4E, 0x36, 0x78, 0x69, 0x75, 0x33, 0x70, 0x58, 0x42, 0x78, 0x76, 0x46, 0x5C };
    for (unsigned i = 0; i < size; i++)
    {
        *((unsigned char*)(data)+i) ^= key[(filepos + i + time) % keySize];
    }

    if (returnOriginalPos)
    {
        return filepos;
    }
    else
    {
        return filepos + size;
    }
}

void loadSaveState(void)
{
    SDFile* saveStateFile = pd->file->open("savestate.srm", kFileReadData);
    //does not exist
    if (saveStateFile == NULL)
        return;

    int ret = pd->file->read(saveStateFile, &saveTime, sizeof(saveTime));
    if (ret == -1)
    {
        valid = 0;
        pd->system->error("Error reading header from savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    encrypt(0,0, &saveTime, sizeof(saveTime), false);

    ret = pd->file->read(saveStateFile, header, sizeof(header));
    if (ret == -1)
    {
        valid = 0;
        pd->system->error("Error reading header from savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    unsigned int pos = encrypt(0, saveTime, header, sizeof(header), false);
    
    ret = pd->file->read(saveStateFile, &check, sizeof(check));
    if (ret == -1)
    {
        valid = 0;
        pd->system->error("Error reading header from savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    pos = encrypt(pos, saveTime, &check, sizeof(check), false);


    ret = pd->file->read(saveStateFile, levelLocks, sizeof(levelLocks));
    if (ret == -1)
    {
        valid = 0;
        pd->system->error("Error reading levellocks from savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    pos = encrypt(pos, saveTime, levelLocks, sizeof(levelLocks), false);
    
    ret = pd->file->read(saveStateFile, &musicOn, sizeof(musicOn));
    if (ret == -1)
    {
        valid = 0;
        pd->system->error("Error reading music option from savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    pos = encrypt(pos, saveTime, &musicOn, sizeof(musicOn), false);
    
    ret = pd->file->read(saveStateFile, &soundOn, sizeof(soundOn));
    if (ret == -1)
    {
        valid = 0;
        pd->system->error("Error reading sound option from savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    pos = encrypt(pos, saveTime, &soundOn, sizeof(soundOn), false);
    
    ret = pd->file->read(saveStateFile, &skin, sizeof(skin));
    if (ret == -1)
    {
        valid = 0;
        pd->system->error("Error reading skin option from savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    pos = encrypt(pos, saveTime, &skin, sizeof(skin), false);
    
    ret = pd->file->read(saveStateFile, &inverted, sizeof(inverted));
    if (ret == -1)
    {
        valid = 0;
        pd->system->error("Error reading inverted option from savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    pos = encrypt(pos, saveTime, &inverted, sizeof(inverted), false);

    ret = pd->file->close(saveStateFile);
    if (ret == -1)
    {
        valid = 0;
        pd->system->error("Error closing savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }

    unsigned int comparecheck = musicOn + soundOn + inverted + skin;
    for (int j = 0; j < gmCount; j++)
    {
        for (int i = 0; i < diffCount; i++)
        {
            comparecheck += levelLocks[j][i];
        }
    }

    if (comparecheck != check)
    {
        valid = 0;
    }
}

void saveSaveState(void)
{
    check = musicOn + soundOn + inverted + skin;
    for (int j = 0; j < gmCount; j++)
    {
        for (int i = 0; i < diffCount; i++)
        {
            check += levelLocks[j][i];
        }
    }

    valid = 1;

    SDFile* saveStateFile = pd->file->open("savestate.srm", kFileWrite);
    if (saveStateFile == NULL)
    {
        pd->system->error("Couldn�t open savestate file for writing!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    
    saveTime = pd->system->getCurrentTimeMilliseconds();

    encrypt(0, 0, &saveTime, sizeof(saveTime), true);
    int ret = pd->file->write(saveStateFile, &saveTime, sizeof(saveTime));
    if (ret == -1)
    {
        encrypt(0, 0, &saveTime, sizeof(saveTime), true);
        pd->system->error("Error writing header to savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    encrypt(0, 0, &saveTime, sizeof(saveTime), true);

    unsigned int pos = encrypt(0, saveTime, header, sizeof(header), true);
    ret = pd->file->write(saveStateFile, header, sizeof(header));
    if (ret == -1)
    {

        pos = encrypt(0, saveTime, header, sizeof(header), false);
        pd->system->error("Error writing header to savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    pos = encrypt(0, saveTime, header, sizeof(header), false);

    pos = encrypt(pos, saveTime, &check, sizeof(check), true);
    ret = pd->file->write(saveStateFile, &check, sizeof(check));
    if (ret == -1)
    {
        
        pos = encrypt(pos, saveTime, &check, sizeof(check), false);
        pd->system->error("Error writing header to savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    pos = encrypt(pos, saveTime, &check, sizeof(check), false);

    pos = encrypt(pos, saveTime, levelLocks, sizeof(levelLocks), true);
    ret = pd->file->write(saveStateFile, levelLocks, sizeof(levelLocks));
    if (ret == -1)
    {
        pos = encrypt(pos, saveTime, levelLocks, sizeof(levelLocks), false);
        pd->system->error("Error writing levellocks to savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    pos = encrypt(pos, saveTime, levelLocks, sizeof(levelLocks), false);

    pos = encrypt(pos, saveTime, &musicOn, sizeof(musicOn), true);
    ret = pd->file->write(saveStateFile, &musicOn, sizeof(musicOn));
    if (ret == -1)
    {
        pos = encrypt(pos, saveTime, &musicOn, sizeof(musicOn), false);
        pd->system->error("Error writing music option to savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    pos = encrypt(pos, saveTime, &musicOn, sizeof(musicOn), false);
    
    pos = encrypt(pos, saveTime, &soundOn, sizeof(soundOn), true);
    ret = pd->file->write(saveStateFile, &soundOn, sizeof(soundOn));
    if (ret == -1)
    {
        pos = encrypt(pos, saveTime, &soundOn, sizeof(soundOn), false);
        pd->system->error("Error writing sound option to savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    pos = encrypt(pos, saveTime, &soundOn, sizeof(soundOn), false);

    pos = encrypt(pos, saveTime, &skin, sizeof(skin), true);
    ret = pd->file->write(saveStateFile, &skin, sizeof(skin));
    if (ret == -1)
    {
        pos = encrypt(pos, saveTime, &skin, sizeof(skin), false);
        pd->system->error("Error writing skin option to savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    pos = encrypt(pos, saveTime, &skin, sizeof(skin), false);

    pos = encrypt(pos, saveTime, &inverted, sizeof(inverted), true);
    ret = pd->file->write(saveStateFile, &inverted, sizeof(inverted));
    if (ret == -1)
    {
        pos = encrypt(pos, saveTime, &inverted, sizeof(inverted), false);
        pd->system->error("Error writing inverted option to savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
    pos = encrypt(pos, saveTime, &inverted, sizeof(inverted), false);

    //crashes the simulator ???
#ifndef _WIN32
    ret = pd->file->flush(saveStateFile);
    if (ret == -1)
    {
        pd->system->error("Error flushing savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
#endif

    ret = pd->file->close(saveStateFile);
    if (ret == -1)
    {
        pd->system->error("Error closing savesate file!");
        pd->system->logToConsole(pd->file->geterr());
        return;
    }
}

void validateSaveState(void)
{
    if ((strcmp(header, "waternet_001") != 0) || !valid)
    {
        valid = 0;
        strcpy(header, "waternet_001");
    }

    if ((soundOn > 1) || (soundOn < 0) || !valid)
    {
        valid = 0;
        soundOn = 1;
    }

    if ((musicOn > 1) || (musicOn < 0) || !valid)
    {
        valid = 0;
        musicOn = 1;
    }

    if ((skin > maxSkins) || (skin < 0) || !valid)
    {
        valid = 0;
        skin = 0;
    }

    if ((inverted > 1) || (inverted < 0) || !valid)
    {
        valid = 0;
        inverted = 0;
    }

    for (int j = 0; j < gmCount; j++)
    {
        for (int i = 0; i < diffCount; i++)
        {
            if ((levelLocks[j][i] < 1) || (levelLocks[j][i] > levelCount) || !valid)
            {
                levelLocks[j][i] = 1;
                if (valid)
                {
                    j = 0;
                    i = 0;
                    valid = 0;
                }
            }
        }
    }

    if (!valid)
    {
        saveSaveState();
    }
}

void initSaveState(void)
{
    valid = 1;
    loadSaveState();
    validateSaveState();
}

void setSkinSaveState(int value)
{
    skin = value;
    saveSaveState();
}

int skinSaveState(void)
{
    return skin;
}

void setInvertedSaveState(int value)
{
    inverted = value;
    saveSaveState();
}

int isInvertedSaveState(void)
{
    return inverted;
}

void setMusicOnSaveState(int value)
{
    musicOn = value;
    saveSaveState();
}

int isMusicOnSaveState(void)
{
    return musicOn;
}

void setSoundOnSaveState(int value)
{
    soundOn = value;
    saveSaveState();
}

int isSoundOnSaveState(void)
{
    return soundOn;
}

void unlockLevel(int mode, int diff, int aLevel)
{
    levelLocks[mode][diff] = aLevel + 1;
    saveSaveState();
}

int levelUnlocked(int mode, int diff, int aLevel)
{
    return (levelLocks[mode][diff] > aLevel);
}

int lastUnlockedLevel(int mode, int diff)
{
    return levelLocks[mode][diff];
}