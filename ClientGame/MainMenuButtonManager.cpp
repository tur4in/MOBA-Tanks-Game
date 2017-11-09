#include "stdafx.h"
#include "MainMenuButtonManager.h"

CMainMenuButtonManager::CMainMenuButtonManager()
{
    SubscrscribeToMsg();

    int xWidth = theCamera.GetWindowWidth();
    int yHeight = theCamera.GetWindowHeight();

    SetButtonText();
    SetButtonPosition(xWidth, yHeight);
    SetButtonSizes(Vector2(4, 2));
    SetButtonHighlightColor(Color(0.4f, 0.2f, 0.0f));
    SetButtonBackGroundColor(Color(1.0f, 0.7f, 0.0f));
    SetButtonBodyColor(Color(0.9f, 0.6f, 0.0f));
    SetFont();

    m_pos = 0;
    m_isActive = true;
}

CMainMenuButtonManager::~CMainMenuButtonManager()
{
}

void CMainMenuButtonManager::ReceiveMessage(Message* m)
{
    if (m_isActive)
    {
        if (m->GetMessageName() == "KeyBoardUp" ||
            m->GetMessageName() == "PadUp")
        {
            if (m_pos == 0)
            {
                m_pos = 2;
            }
            else
            {
                --m_pos;
            }
        }
        else if (m->GetMessageName() == "KeyBoardDown" ||
            m->GetMessageName() == "PadDown")
        {
            if (m_pos == 2)
            {
                m_pos = 0;
            }
            else
            {
                ++m_pos;
            }
        }
        else if (m->GetMessageName() == "BuyKeyBoard" ||
            m->GetMessageName() == "BuyPad")
        {
            switch (m_pos)
            {
            case 0:
            {
                m_isActive = false;
                theSwitchboard.Broadcast(new Message("OpenMapChoice"));
            }
            break;
            case 1:
            {
                m_isActive = false;
                theSwitchboard.Broadcast(new Message("OpenOptionsScreen"));
            }
            break;
            case 2:
            {
                m_isActive = false;
                theSwitchboard.Broadcast(new Message("ReturnBack"));
            }
            break;
            }
        }
    }
}

void CMainMenuButtonManager::SetActive()
{
    m_isActive = true;
}

void CMainMenuButtonManager::Update()
{
    switch (m_pos)
    {
    case 0:
    {
        m_play.HighLight();
        m_options.UnHighLight();
        m_exit.UnHighLight();
    }
    break;
    case 1:
    {
        m_play.UnHighLight();
        m_options.HighLight();
        m_exit.UnHighLight();
    }
    break;
    case 2:
    {
        m_play.UnHighLight();
        m_options.UnHighLight();
        m_exit.HighLight();
    }
    break;
    }
}

void CMainMenuButtonManager::Render()
{
    if (m_isActive)
    {
        m_play.Render();
        m_options.Render();
        m_exit.Render();
        m_title.Render();
    }
}

void CMainMenuButtonManager::SetButtonPosition(int xWidth, int yHeight)
{
    m_play.SetButtonPosition(MathUtil::ScreenToWorld(xWidth / 2, yHeight / 2));
    m_options.SetButtonPosition(MathUtil::ScreenToWorld(xWidth / 2, yHeight / 2 + yHeight / 8));
    m_exit.SetButtonPosition(MathUtil::ScreenToWorld(xWidth / 2, yHeight / 2 + (yHeight / 8) * 2));
    m_title.SetPosition(MathUtil::ScreenToWorld(xWidth / 2, yHeight * 0.35f));
}

void CMainMenuButtonManager::SetButtonSizes(Vector2 sizeRegularButton)
{
    m_play.SetButtonSize(sizeRegularButton);
    m_options.SetButtonSize(sizeRegularButton);
    m_exit.SetButtonSize(sizeRegularButton);
}

void CMainMenuButtonManager::SetButtonHighlightColor(Color color)
{
    m_play.SetHilightColor(color);
    m_options.SetHilightColor(color);
    m_exit.SetHilightColor(color);
}

void CMainMenuButtonManager::SetButtonBackGroundColor(Color colorBack)
{
    m_play.SetButtonBackgroundColor(colorBack);
    m_options.SetButtonBackgroundColor(colorBack);
    m_exit.SetButtonBackgroundColor(colorBack);
}

void CMainMenuButtonManager::SetButtonText()
{
    m_play.SetButtonText("Play");
    m_options.SetButtonText("Options");
    m_exit.SetButtonText("Quit");
    m_title.SetDisplayString("GAME NAME");
}

void CMainMenuButtonManager::SetButtonBodyColor(Color colorBody)
{
    m_play.SetButtonColor(colorBody);
    m_options.SetButtonColor(colorBody);
    m_exit.SetButtonColor(colorBody);
}

void CMainMenuButtonManager::SetFont()
{
    RegisterFont("Resources\\Fonts\\28DaysLater.ttf", 50, "MainMenuButtonName");
    m_play.SetButtonTextFont("MainMenuButtonName");
    m_options.SetButtonTextFont("MainMenuButtonName");
    m_exit.SetButtonTextFont("MainMenuButtonName");
    RegisterFont("Resources\\Fonts\\28DaysLater.ttf", 300, "MainMenuTitle");
    m_title.SetFont("MainMenuTitle");
    m_title.SetAlignment(TXT_Center);
}

void CMainMenuButtonManager::SubscrscribeToMsg()
{
    theSwitchboard.SubscribeTo(this, "KeyBoardUp");
    theSwitchboard.SubscribeTo(this, "KeyBoardDown");
    theSwitchboard.SubscribeTo(this, "PadUp");
    theSwitchboard.SubscribeTo(this, "PadDown");
    theSwitchboard.SubscribeTo(this, "BuyKeyBoard");
    theSwitchboard.SubscribeTo(this, "BuyPad");
}
