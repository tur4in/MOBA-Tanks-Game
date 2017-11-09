#include "stdafx.h"
#include "OptionsScreen.h"

COptionsScreen::COptionsScreen()
{
    theSwitchboard.SubscribeTo(this, "MusicTrigged");
    theSwitchboard.SubscribeTo(this, "EffectsTrigged");

    m_background.SetSprite("Resources/Images/menu_backgroud.jpg");

    std::string txt;

    RegisterFont("Resources\\Fonts\\28DaysLater.ttf", 64, "OptionText");
    RegisterFont("Resources\\Fonts\\28DaysLater.ttf", 300, "OptionTitle");

    m_music.SetAlignment(TXT_Right);
    m_music.SetColor(1.0f, 1.0f, 1.0f);
    m_music.SetFont("OptionText");
    m_music.SetDisplayString("Music Volume");

    int x = thePrefs.GetInt("Volume", "Music");
    m_musicVol.SetColor(1.0f, 1.0f, 1.0f);
    m_musicVol.SetAlignment(TXT_Right);
    m_musicVol.SetFont("OptionText");
    if (x > 10 || x < 0)
    {
        x = 10;
    }
    txt = std::to_string(x);
    m_musicVol.SetDisplayString(txt);

    m_effects.SetAlignment(TXT_Right);
    m_effects.SetColor(1.0f, 1.0f, 1.0f);
    m_effects.SetFont("OptionText");
    m_effects.SetDisplayString("Effects Volume");

    m_advancedKeyboard.SetAlignment(TXT_Right);
    m_advancedKeyboard.SetColor(1.0f, 1.0f, 1.0f);
    m_advancedKeyboard.SetFont("OptionText");
    m_advancedKeyboard.SetDisplayString("Advanced Keyboard");

    x = thePrefs.GetInt("Volume", "Effects");
    m_effectsVol.SetAlignment(TXT_Right);
    m_effectsVol.SetColor(1.0f, 1.0f, 1.0f);
    m_effectsVol.SetFont("OptionText");
    if (x > 10 || x < 0)
    {
        x = 10;
    }
    txt = std::to_string(x);
    m_effectsVol.SetDisplayString(txt);

    x = thePrefs.GetInt("InvertAxis", "PadRight");
    m_axisPadRight.SetColor(1.0f, 1.0f, 1.0f);
    m_axisPadRight.SetAlignment(TXT_Right);
    m_axisPadRight.SetFont("OptionText");
    m_axisPadRight.SetDisplayString("Invert Right ThumbStick");

    x = thePrefs.GetInt("InvertAxis", "PadLeft");
    m_axisPadLeft.SetColor(1.0f, 1.0f, 1.0f);
    m_axisPadLeft.SetAlignment(TXT_Right);
    m_axisPadLeft.SetFont("OptionText");
    m_axisPadLeft.SetDisplayString("Invert Left ThumbStick");

    m_options.SetAlignment(TXT_Center);
    m_options.SetFont("OptionTitle");
    m_options.SetDisplayString("Options");
}

void COptionsScreen::Start()
{
    theSwitchboard.Broadcast(new Message("ComeIntoOptions"));
    int x = theCamera.GetWindowWidth();

    m_music.SetPosition(MathUtil::ScreenToWorld(x * 0.43, theCamera.GetWindowHeight() * 0.43));
    m_musicVol.SetPosition(MathUtil::ScreenToWorld(x / 2 + x / 12, theCamera.GetWindowHeight() * 0.43));
    m_effects.SetPosition(MathUtil::ScreenToWorld(x * 0.43, theCamera.GetWindowHeight() * 0.51));
    m_effectsVol.SetPosition(MathUtil::ScreenToWorld(x / 2 + x / 12, theCamera.GetWindowHeight() * 0.51));
    m_axisPadRight.SetPosition(MathUtil::ScreenToWorld(x * 0.43, theCamera.GetWindowHeight() * 0.59));
    m_axisPadLeft.SetPosition(MathUtil::ScreenToWorld(x * 0.43, theCamera.GetWindowHeight() * 0.68));
    m_advancedKeyboard.SetPosition(MathUtil::ScreenToWorld(x * 0.43, theCamera.GetWindowHeight() * 0.77));
    m_options.SetPosition(MathUtil::ScreenToWorld(x / 2, theCamera.GetWindowHeight() * 0.3));
}

void COptionsScreen::Render()
{
    m_background.Render();
    m_options.Render();
    m_buttonManager.Render();

    m_music.Render();
    m_musicVol.Render();
    m_effects.Render();
    m_effectsVol.Render();
    m_axisPadRight.Render();
    m_axisPadLeft.Render();
    m_advancedKeyboard.Render();
}

void COptionsScreen::Update(float dt)
{
    m_buttonManager.Update();
}

void COptionsScreen::ReceiveMessage(Message * m)
{
    if (m->GetMessageName() == "MusicTrigged")
    {
        m_musicVol.SetDisplayString(std::to_string(thePrefs.GetInt("Volume", "Music")));
    }
    else if (m->GetMessageName() == "EffectsTrigged")
    {
        m_effectsVol.SetDisplayString(std::to_string(thePrefs.GetInt("Volume", "Effects")));
    }
}
