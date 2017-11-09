#pragma once

#include "stdafx.h"

class CSoundSystem :
    GameManager
{
public:
    CSoundSystem();
    ~CSoundSystem();
    void ReceiveMessage(Message* message);

private:
    void Subscribe();
    void SetStartSounds();

private:
    AngelSoundHandle m_optionChanged;
    AngelSoundHandle m_shootStandard;
    AngelSoundHandle m_shootLaser;
    AngelSoundHandle m_boomLaser;
    AngelSoundHandle m_boom;
    AngelSoundHandle m_storeOpened;
    AngelSoundHandle m_itemPayed;
    AngelSoundHandle m_backgroundMusic;
    AngelSoundHandle m_backgroundMusicPlaying;
};

