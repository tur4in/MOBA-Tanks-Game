#include "stdafx.h"
#include "PauseMenuButtonManager.h"

CPauseMenuButtonManager::CPauseMenuButtonManager()
{
    SubscrscribeToMsg();

    int xWidth = theCamera.GetWindowWidth();
    int yHeight = theCamera.GetWindowHeight();

    SetButtonText();
    SetButtonPosition(xWidth, yHeight);
    SetButtonSizes(Vector2(4, 2), Vector2(6, 2), xWidth, yHeight);
    SetButtonHighlightColor(Color(0.4f, 0.2f, 0.0f));
    SetButtonBackGroundColor(Color(1.0f, 0.7f, 0.0f));
    SetButtonBody(Color(0.9f, 0.6f, 0.0f));
    SetFont();

    m_pos = 0;
    m_endGame = false;
    m_isActive = false;
}

CPauseMenuButtonManager::~CPauseMenuButtonManager()
{
}

void CPauseMenuButtonManager::ReceiveMessage(Message* m)
{
    if (m_isActive)
    {
        if (m_endGame)
        {
            if (m->GetMessageName() == "BuyKeyBoard" ||
                m->GetMessageName() == "BuyPad")
            {
                theSwitchboard.Broadcast(new Message("ReturnBack"));
            }
        }
        else
        {
            if (m->GetMessageName() == "KeyBoardUp" ||
                m->GetMessageName() == "PadUp")
            {
                if (m_pos == 0)
                    m_pos = 2;
                else
                    --m_pos;
            }
            else if (m->GetMessageName() == "KeyBoardDown" ||
                m->GetMessageName() == "PadDown")
            {
                if (m_pos == 2)
                    m_pos = 0;
                else
                    ++m_pos;
            }
            else if (m->GetMessageName() == "BuyKeyBoard" ||
                m->GetMessageName() == "BuyPad")
            {
                switch (m_pos)
                {
                case 0:
                {
                    m_isActive = false;
                    theSwitchboard.Broadcast(new Message("Resume"));
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
                m_pos = 0;
            }
        }
    }
}

void CPauseMenuButtonManager::SetActive()
{
    m_isActive = true;
}

void CPauseMenuButtonManager::Update()
{
    if (m_endGame)
    {
        m_endButton.HighLight();
    }
    else
    {
        switch (m_pos)
        {
        case 0:
        {
            m_resume.HighLight();
            m_options.UnHighLight();
            m_exit.UnHighLight();
        }
        break;
        case 1:
        {
            m_resume.UnHighLight();
            m_options.HighLight();
            m_exit.UnHighLight();
        }
        break;
        case 2:
        {
            m_resume.UnHighLight();
            m_options.UnHighLight();
            m_exit.HighLight();
        }
        break;
        }
    }
}

void CPauseMenuButtonManager::Render()
{
    if (m_endGame)
    {
        m_winTextBack.Render();
        m_winText.Render();
        m_endButton.Render();
    }
    else
    {
        m_background.Render();
        m_resume.Render();
        m_options.Render();
        m_exit.Render();
    }
}

void CPauseMenuButtonManager::EndGameMenu(ESideIdentificator looser)
{
    String msg;
    switch (looser)
    {
    case ESideIdentificator::Side1:
        msg = "SIDE 2 WON!";
        break;
    case ESideIdentificator::Side2:
        msg = "SIDE 1 WON!";
        break;
    }
    m_winText.SetDisplayString(msg);
    m_endGame = true;
}

void CPauseMenuButtonManager::SetButtonPosition(int xWidth, int yHeight)
{
    m_resume.SetButtonPosition(MathUtil::ScreenToWorld(xWidth / 2, yHeight / 2 - yHeight / 8));
    m_options.SetButtonPosition(MathUtil::ScreenToWorld(xWidth / 2, yHeight / 2));
    m_exit.SetButtonPosition(MathUtil::ScreenToWorld(xWidth / 2, yHeight / 2 + yHeight / 8));
    m_endButton.SetButtonPosition(MathUtil::ScreenToWorld(xWidth / 2, yHeight / 2 + yHeight / 12));
    m_winText.SetPosition(MathUtil::ScreenToWorld(xWidth / 2, yHeight / 2 - yHeight / 20));
    m_winTextBack.SetPosition(MathUtil::ScreenToWorld(xWidth / 2, yHeight / 2));
}

void CPauseMenuButtonManager::SetButtonSizes(Vector2 sizeRegularButton, Vector2 sizeExitButton, int xWidth, int yHeight)
{
    m_resume.SetButtonSize(sizeRegularButton);
    m_options.SetButtonSize(sizeRegularButton);
    m_exit.SetButtonSize(sizeRegularButton);
    m_endButton.SetButtonSize(sizeExitButton);
    m_background.SetSize(MathUtil::ScreenToWorld(xWidth / 4, yHeight / 4));
    m_winTextBack.SetSize(Vector2(10, 8));
}

void CPauseMenuButtonManager::SetButtonHighlightColor(Color color)
{
    m_resume.SetHilightColor(color);
    m_options.SetHilightColor(color);
    m_endButton.SetHilightColor(color);
    m_exit.SetHilightColor(color);
}

void CPauseMenuButtonManager::SetButtonBackGroundColor(Color colorBack)
{
    m_resume.SetButtonBackgroundColor(colorBack);
    m_options.SetButtonBackgroundColor(colorBack);
    m_exit.SetButtonBackgroundColor(colorBack);
    m_endButton.SetButtonBackgroundColor(colorBack);
    m_winTextBack.SetColor(colorBack);
    m_winTextBack.SetAlpha(0.7f);
}

void CPauseMenuButtonManager::SetButtonText()
{
    m_resume.SetButtonText("Resume");
    m_options.SetButtonText("Options");
    m_exit.SetButtonText("Quit");
    m_endButton.SetButtonText("Back To Menu");
}

void CPauseMenuButtonManager::SetButtonBody(Color colorBody)
{
    m_resume.SetButtonColor(colorBody);
    m_options.SetButtonColor(colorBody);
    m_exit.SetButtonColor(colorBody);
    m_endButton.SetButtonColor(colorBody);
}

void CPauseMenuButtonManager::SetFont()
{
    RegisterFont("Resources\\Fonts\\28DaysLater.ttf", 50, "MainMenuButtonName");
    m_resume.SetButtonTextFont("MainMenuButtonName");
    m_options.SetButtonTextFont("MainMenuButtonName");
    m_exit.SetButtonTextFont("MainMenuButtonName");
    m_endButton.SetButtonTextFont("MainMenuButtonName");
    RegisterFont("Resources\\Fonts\\28DaysLater.ttf", 80, "BigConsole");
    m_winText.SetFont("BigConsole");
    m_winText.SetAlignment(TXT_Center);
}

void CPauseMenuButtonManager::SubscrscribeToMsg()
{
    theSwitchboard.SubscribeTo(this, "KeyBoardUp");
    theSwitchboard.SubscribeTo(this, "KeyBoardDown");
    theSwitchboard.SubscribeTo(this, "PadUp");
    theSwitchboard.SubscribeTo(this, "PadDown");
    theSwitchboard.SubscribeTo(this, "BuyKeyBoard");
    theSwitchboard.SubscribeTo(this, "BuyPad");
}
