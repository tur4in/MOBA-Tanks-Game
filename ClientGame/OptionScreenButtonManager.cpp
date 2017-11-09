#include "stdafx.h"
#include "OptionScreenButtonManager.h"
#include "CustomCheckBox.h"

COptionScreenButtonManager::COptionScreenButtonManager()
{
    SubscrscribeToMsg();
    CreateButtons();

    int xWidth = theCamera.GetWindowWidth();
    int yHeight = theCamera.GetWindowHeight();

    SetPositions(xWidth, yHeight);
    SetText();
    SetButtonHighlightColor(Color(0.4f, 0.2f, 0.0f));
    SetButtonBackGroundColor(Color(1.0f, 0.7f, 0.0f));
    SetButtonColor(Color(0.9f, 0.6f, 0.0f), Color(0.7f, 0.3f, 0.0f));
    SetSizes(Vector2(1.0, 1.0));

    m_posX = 1;
    m_posY = 0;
}

COptionScreenButtonManager::~COptionScreenButtonManager()
{
}

void COptionScreenButtonManager::ReceiveMessage(Message* m)
{
    if (m->GetMessageName() == "KeyBoardUp" ||
        m->GetMessageName() == "PadUp")
    {
        if (m_posY == 0)
        {
            m_posY = 5;
        }
        else
        {
            --m_posY;
        }
    }
    else if (m->GetMessageName() == "KeyBoardDown" ||
        m->GetMessageName() == "PadDown")
    {
        if (m_posY == 5)
        {
            m_posY = 0;
        }
        else
        {
            ++m_posY;
        }
    }
    else if (m->GetMessageName() == "KeyBoardLeft" ||
        m->GetMessageName() == "PadLeft" ||
        m->GetMessageName() == "KeyBoardRight" ||
        m->GetMessageName() == "PadRight")
    {
        m_posX = m_posX == 0 ? 1 : 0;
    }
    else if (m->GetMessageName() == "BuyKeyBoard" ||
        m->GetMessageName() == "BuyPad")
    {
        switch (m_posY)
        {
        case 0:
        {
            m_posX == 0 ? MusicVolumePlus() : MusicVolumeMinus();
            break;
        }
        case 1:
        {
            m_posX == 0 ? EffectsVolumePlus() : EffectsVolumeMinus();
            break;
        }
        case 2:
        {
            InvertAxisPadLeftTrigged();
            m_left[m_posY]->ChangeStatus();
            break;
        }
        case 3:
        {
            InvertAxisPadRightTrigged();
            m_left[m_posY]->ChangeStatus();
            break;
        }
        case 4:
        {
            AdvancedKeyboard();
            m_left[m_posY]->ChangeStatus();
            break;
        }
        case 5:
            ReturnPressed();
            break;
        }
    }
}

void COptionScreenButtonManager::Update()
{
    for (auto i : m_left)
    {
        i->UnHighLight();
    }
    m_right[0]->UnHighLight();
    m_right[1]->UnHighLight();

    auto vec = m_posX == 0 ? &m_left : &m_right;
    (*vec)[m_posY]->HighLight();
}

void COptionScreenButtonManager::Render()
{
    for (auto i : m_left)
    {
        i->Render();
    }
    m_right[0]->Render();
    m_right[1]->Render();
}

void ReturnPressed()
{
    theSwitchboard.Broadcast(new Message("ReturnBack"));
}

void InvertAxisPadLeftTrigged()
{
    int x = thePrefs.GetInt("InvertAxis", "RightPad");
    x = (x == 0) ? 1 : 0;
    thePrefs.SetInt("InvertAxis", "RightPad", x);
    thePrefs.SavePreferences();

    theSwitchboard.Broadcast(new Message("InvertAxisPadTrigged"));
}

void InvertAxisPadRightTrigged()
{
    int x = thePrefs.GetInt("InvertAxis", "LeftPad");
    x = (x == 0) ? 1 : 0;
    thePrefs.SetInt("InvertAxis", "LeftPad", x);
    thePrefs.SavePreferences();

    theSwitchboard.Broadcast(new Message("InvertAxisMouseTrigged"));
}

void MusicVolumePlus()
{
    int x = thePrefs.GetInt("Volume", "Music");
    if (x < 10)
    {
        ++x;
    }
    thePrefs.SetInt("Volume", "Music", x);
    thePrefs.SavePreferences();

    theSwitchboard.Broadcast(new Message("MusicTrigged"));
}

void MusicVolumeMinus()
{
    int x = thePrefs.GetInt("Volume", "Music");
    if (x > 0)
    {
        --x;
    }
    thePrefs.SetInt("Volume", "Music", x);
    thePrefs.SavePreferences();

    theSwitchboard.Broadcast(new Message("MusicTrigged"));
}

void EffectsVolumePlus()
{
    int x = thePrefs.GetInt("Volume", "Effects");
    if (x < 10)
    {
        ++x;
    }
    thePrefs.SetInt("Volume", "Effects", x);
    thePrefs.SavePreferences();

    theSwitchboard.Broadcast(new Message("EffectsTrigged"));
}

void EffectsVolumeMinus()
{
    int x = thePrefs.GetInt("Volume", "Effects");
    if (x > 0)
    {
        --x;
    }
    thePrefs.SetInt("Volume", "Effects", x);
    thePrefs.SavePreferences();

    theSwitchboard.Broadcast(new Message("EffectsTrigged"));
}

void AdvancedKeyboard()
{
    int x = thePrefs.GetInt("Settings", "AdvancedKeyboardMovement");
    x = (x == 0) ? 1 : 0;
    thePrefs.SetInt("Settings", "AdvancedKeyboardMovement", x);
    thePrefs.SavePreferences();

    theSwitchboard.Broadcast(new Message("AdvancedKeyboardTrigged"));
}

void COptionScreenButtonManager::CreateButtons()
{
    for (size_t i = 0; i < 2; ++i)
    {
        m_left.push_back(std::make_shared<CMenuButton>());
        m_right.push_back(std::make_shared<CMenuButton>());
    }

    m_left.push_back(std::make_shared<CCustomCheckBox>(thePrefs.GetInt("InvertAxis", "RightPad")));
    m_right.push_back(m_left.back());

    m_left.push_back(std::make_shared<CCustomCheckBox>(thePrefs.GetInt("InvertAxis", "LeftPad")));
    m_right.push_back(m_left.back());

    m_left.push_back(std::make_shared<CCustomCheckBox>(thePrefs.GetInt("Settings", "AdvancedKeyboardMovement")));
    m_right.push_back(m_left.back());

    m_left.push_back(std::make_shared<CMenuButton>());
    m_right.push_back(m_left.back());
}

void COptionScreenButtonManager::SetPositions(int xWidth, int yHeight)
{
    m_right[0]->SetButtonPosition(MathUtil::ScreenToWorld((xWidth / 2) - 50, yHeight * 0.4));
    m_left[0]->SetButtonPosition(MathUtil::ScreenToWorld((xWidth / 2) + 50, yHeight * 0.4));

    m_right[1]->SetButtonPosition(MathUtil::ScreenToWorld((xWidth / 2) - 50, yHeight * 0.48));
    m_left[1]->SetButtonPosition(MathUtil::ScreenToWorld((xWidth / 2) + 50, yHeight * 0.48));

    m_right[2]->SetButtonPosition(MathUtil::ScreenToWorld((xWidth / 2), yHeight * 0.56));
    m_right[3]->SetButtonPosition(MathUtil::ScreenToWorld((xWidth / 2), yHeight * 0.65));
    m_right[4]->SetButtonPosition(MathUtil::ScreenToWorld((xWidth / 2), yHeight * 0.74));
    m_right[5]->SetButtonPosition(MathUtil::ScreenToWorld((xWidth / 2), yHeight * 0.88));
}

void COptionScreenButtonManager::SetSizes(Vector2 sizeRegularButton)
{
    for (auto i : m_left)
    {
        i->SetButtonSize(sizeRegularButton);
    }
    m_right[0]->SetButtonSize(sizeRegularButton);
    m_right[1]->SetButtonSize(sizeRegularButton);
    m_left.back()->SetButtonSize(Vector2(sizeRegularButton.X * 2.5, sizeRegularButton.Y * 1.5));
}

void COptionScreenButtonManager::SetButtonColor(Color regular, Color pressed)
{
    if (!m_left.empty())
    {
        for (auto i : m_left)
        {
            i->SetButtonColor(regular);
        }
        m_right[0]->SetButtonColor(regular);
        m_right[1]->SetButtonColor(regular);

        m_left[2]->SetPressedColor(pressed);
        m_left[3]->SetPressedColor(pressed);
        m_left[4]->SetPressedColor(pressed);
        m_left[2]->SetUnpressedColor(regular);
        m_left[3]->SetUnpressedColor(regular);
        m_left[4]->SetUnpressedColor(regular);
    }
}

void COptionScreenButtonManager::SetButtonBackGroundColor(Color colorBack)
{
    for (auto i : m_left)
    {
        i->SetButtonBackgroundColor(colorBack);
    }
    m_right[0]->SetButtonBackgroundColor(colorBack);
    m_right[1]->SetButtonBackgroundColor(colorBack);
}

void COptionScreenButtonManager::SetText()
{
    m_left[0]->SetButtonText("+");
    m_right[0]->SetButtonText("-");
    m_left[1]->SetButtonText("+");
    m_right[1]->SetButtonText("-");

    m_left[2]->SetButtonText("");
    m_left[3]->SetButtonText("");
    m_left[4]->SetButtonText("");
    m_left[5]->SetButtonText("Exit");
    RegisterFont("Resources\\Fonts\\28DaysLater.ttf", 40, "ButtonOptionMenu");
    m_left[5]->SetButtonTextFont("ButtonOptionMenu");
}

void COptionScreenButtonManager::SetButtonHighlightColor(Color highlight)
{
    for (auto i : m_left)
    {
        i->SetHilightColor(highlight);
    }
    m_right[0]->SetHilightColor(highlight);
    m_right[1]->SetHilightColor(highlight);
}

void COptionScreenButtonManager::SubscrscribeToMsg()
{
    theSwitchboard.SubscribeTo(this, "KeyBoardUp");
    theSwitchboard.SubscribeTo(this, "KeyBoardDown");
    theSwitchboard.SubscribeTo(this, "PadUp");
    theSwitchboard.SubscribeTo(this, "PadDown");
    theSwitchboard.SubscribeTo(this, "KeyBoardLeft");
    theSwitchboard.SubscribeTo(this, "KeyBoardRight");
    theSwitchboard.SubscribeTo(this, "PadLeft");
    theSwitchboard.SubscribeTo(this, "PadRight");
    theSwitchboard.SubscribeTo(this, "BuyKeyBoard");
    theSwitchboard.SubscribeTo(this, "BuyPad");
}
