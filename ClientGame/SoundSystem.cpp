#include "stdafx.h"
#include "SoundSystem.h"


CSoundSystem::CSoundSystem()
{
    theSound.SetSoundCallback(this, &GameManager::SoundEnded);
    Subscribe();
    SetStartSounds();
}

CSoundSystem::~CSoundSystem()
{
}

void CSoundSystem::ReceiveMessage(Message* message)
{
    if (message->GetMessageName() == "AttackFromTank")
    {
        if (m_shootStandard)
        {
            theSound.PlaySound(m_shootStandard, thePrefs.GetFloat("Volume", "Effects") / 10.0f, false, 0);
        }
    }
    else if (message->GetMessageName() == "LaserSound")
    {
        if (m_shootStandard)
        {
            theSound.PlaySound(m_shootLaser, thePrefs.GetFloat("Volume", "Effects") / 10.0f, false, 0);
        }
    }
    else if (message->GetMessageName() == "Boom")
    {
        if (m_boom)
        {
            theSound.PlaySound(m_boom, thePrefs.GetFloat("Volume", "Effects") / 200.0f, false, 0);
        }
    }
    else if (message->GetMessageName() == "InvertAxisPadTrigged" ||
        message->GetMessageName() == "InvertAxisMouseTrigged" ||
        message->GetMessageName() == "EffectsTrigged" ||
        message->GetMessageName() == "MusicTrigged" ||
        message->GetMessageName() == "AdvancedKeyboardTrigged")
    {
        if (m_optionChanged)
        {
            theSound.PlaySound(m_optionChanged, thePrefs.GetFloat("Volume", "Effects") / 10.0f, false, 0);
        }
    }
    else if (message->GetMessageName() == "PayForItem")
    {
        if (m_optionChanged)
        {
            theSound.PlaySound(m_optionChanged, thePrefs.GetFloat("Volume", "Effects") / 10.0f, false, 0);
        }
    }
    else if (message->GetMessageName() == "BoomLaser")
    {
        if (m_optionChanged)
        {
            theSound.PlaySound(m_boomLaser, thePrefs.GetFloat("Volume", "Effects") / 10.0f, false, 0);
        }
    }
    else if (message->GetMessageName() == "StorePad" ||
        message->GetMessageName() == "StoreKeyBoard")
    {
        if (m_storeOpened)
        {
            theSound.PlaySound(m_storeOpened, thePrefs.GetFloat("Volume", "Effects") / 10.0f, false, 0);
        }
    }
    else if (message->GetMessageName() == "Pause" ||
        message->GetMessageName() == "Resume")
    {
    }
    //////////////////////BACK GROUND MUSIC CONTROL/////////////////////////////
    if (message->GetMessageName() == "OpenMenuScreen" ||
        message->GetMessageName() == "OpenOptionsScreen" ||
        message->GetMessageName() == "ComeIntoMenu" ||
        message->GetMessageName() == "ComeIntoOptions")
    {
        if (m_backgroundMusicPlaying)
        {
            if (!theSound.IsPlaying(m_backgroundMusicPlaying))
            {
                m_backgroundMusicPlaying = theSound.PlaySound(m_backgroundMusic, thePrefs.GetFloat("Volume", "Music") / 10.0f, true/*yes loop*/, 0);
            }
        }
    }
    else if (message->GetMessageName() == "OpenPlayScreen" ||
        message->GetMessageName() == "ComeIntoPlayScreen")
    {
        if (m_backgroundMusicPlaying)
        {
            theSound.StopSound(m_backgroundMusicPlaying);
            m_backgroundMusicPlaying = m_backgroundMusic;
        }
    }
    if (message->GetMessageName() == "MusicTrigged")
    {
        if (m_backgroundMusicPlaying)
        {
            if (theSound.IsPlaying(m_backgroundMusicPlaying))
            {
                theSound.SetVolume(m_backgroundMusicPlaying, thePrefs.GetFloat("Volume", "Music") / 10.0f);
            }
        }
    }
}

void CSoundSystem::Subscribe()
{
    theSwitchboard.SubscribeTo(this, "AttackFromTank");
    theSwitchboard.SubscribeTo(this, "LaserSound");
    theSwitchboard.SubscribeTo(this, "Boom");
    theSwitchboard.SubscribeTo(this, "InvertAxisPadTrigged");
    theSwitchboard.SubscribeTo(this, "InvertAxisMouseTrigged");
    theSwitchboard.SubscribeTo(this, "EffectsTrigged");
    theSwitchboard.SubscribeTo(this, "MusicTrigged");
    theSwitchboard.SubscribeTo(this, "OpenPlayScreen");
    theSwitchboard.SubscribeTo(this, "OpenMenuScreen");
    theSwitchboard.SubscribeTo(this, "OpenOptionsScreen");
    theSwitchboard.SubscribeTo(this, "Pause");
    theSwitchboard.SubscribeTo(this, "ComeIntoMenu");
    theSwitchboard.SubscribeTo(this, "ComeIntoOptions");
    theSwitchboard.SubscribeTo(this, "ComeIntoPlayScreen");
    theSwitchboard.SubscribeTo(this, "ReturnBack");
    theSwitchboard.SubscribeTo(this, "Resume");
    theSwitchboard.SubscribeTo(this, "BuyPad");
    theSwitchboard.SubscribeTo(this, "BuyKeyBoard");
    theSwitchboard.SubscribeTo(this, "StorePad");
    theSwitchboard.SubscribeTo(this, "StoreKeyBoard");
    theSwitchboard.SubscribeTo(this, "AdvancedKeyboardTrigged");
}

void CSoundSystem::SetStartSounds()
{
    m_boom = theSound.LoadSample("Resources/Sounds/GBoom.mp3", false);
    m_itemPayed = theSound.LoadSample("Resources/Sounds/GItemBuy.mp3", false);
    m_storeOpened = theSound.LoadSample("Resources/Sounds/GOpenStore.mp3", false);
    m_backgroundMusic = theSound.LoadSample("Resources/Sounds/GMainMenu.mp3", true);
    m_shootStandard = theSound.LoadSample("Resources/Sounds/GShootSound.mp3", false);
    m_boomLaser = theSound.LoadSample("Resources/Sounds/GBoomLaserSound.mp3", false);
    m_shootLaser = theSound.LoadSample("Resources/Sounds/GShootLaserSound.mp3", false);
    m_optionChanged = theSound.LoadSample("Resources/Sounds/GOptionsChanged.ogg", false);
    m_backgroundMusicPlaying = theSound.PlaySound(m_backgroundMusic, thePrefs.GetFloat("Volume", "Music") / 10.0f, true, 0);
}
