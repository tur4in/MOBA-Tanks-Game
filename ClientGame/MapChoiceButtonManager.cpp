#include "stdafx.h"
#include "MapChoiceButtonManager.h"

CMapChoiceButtonManager::CMapChoiceButtonManager()
{
    SubscrscribeToMsg();

    int xWidth = theCamera.GetWindowWidth();
    int yHeight = theCamera.GetWindowHeight();

    m_isActive = false;

    SetButtonText();
    SetButtonPosition(xWidth, yHeight);
    SetButtonSizes(Vector2(4, 2), Vector2(6, 4), xWidth, yHeight);
    SetButtonHighlightColor(Color(0.4f, 0.2f, 0.0f));
    SetButtonBackGroundColor(Color(1.0f, 0.7f, 0.0f));
    SetButtonBody(Color(0.9f, 0.6f, 0.0f));
    SetFont();
    SetSprites();

    m_pos = 0;
}

CMapChoiceButtonManager::~CMapChoiceButtonManager()
{
}

void CMapChoiceButtonManager::ReceiveMessage(Message* m)
{
    if (m_isActive)
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
                theSwitchboard.Broadcast(new TypedMessage<std::string>("OpenPlayScreen","map.tmx"));
            }
            break;
            case 1:
            {
                m_isActive = false;
                theSwitchboard.Broadcast(new TypedMessage<std::string>("OpenPlayScreen", "snow_map.tmx"));
            }
            break;
            case 2:
            {
                m_isActive = false;
                theSwitchboard.Broadcast(new Message("OpenMenu"));
            }
            break;
            }
            m_pos = 0;
        }
    }
}

void CMapChoiceButtonManager::SetActive()
{
    m_isActive = true;
}

void CMapChoiceButtonManager::Update()
{
    switch (m_pos)
    {
    case 0:
    {
        m_mapDesert.HighLight();
        m_mapWinter.UnHighLight();
        m_exit.UnHighLight();
    }
    break;
    case 1:
    {
        m_mapDesert.UnHighLight();
        m_mapWinter.HighLight();
        m_exit.UnHighLight();
    }
    break;
    case 2:
    {
        m_mapDesert.UnHighLight();
        m_mapWinter.UnHighLight();
        m_exit.HighLight();
    }
    break;
    }
}

void CMapChoiceButtonManager::Render()
{
    if (m_isActive)
    {
        m_mapDesert.Render();
        m_mapWinter.Render();
        m_exit.Render();
    }
}

void CMapChoiceButtonManager::SetButtonPosition(int xWidth, int yHeight)
{
    m_mapDesert.SetButtonPosition(MathUtil::ScreenToWorld(xWidth / 2, yHeight / 2 - yHeight / 4 + yHeight / 16));
    m_mapWinter.SetButtonPosition(MathUtil::ScreenToWorld(xWidth / 2, yHeight / 2 + yHeight / 16));
    m_exit.SetButtonPosition(MathUtil::ScreenToWorld(xWidth / 2, yHeight / 2 + yHeight / 4));
}

void CMapChoiceButtonManager::SetButtonSizes(Vector2 sizeRegularButton, Vector2 sizeExitButton, int xWidth, int yHeight)
{
    m_mapDesert.SetButtonSize(sizeExitButton);
    m_mapWinter.SetButtonSize(sizeExitButton);
    m_exit.SetButtonSize(sizeRegularButton);
}

void CMapChoiceButtonManager::SetButtonHighlightColor(Color color)
{
    m_mapDesert.SetHilightColor(color);
    m_mapWinter.SetHilightColor(color);
    m_exit.SetHilightColor(color);
}

void CMapChoiceButtonManager::SetButtonBackGroundColor(Color colorBack)
{
    m_mapDesert.SetButtonBackgroundColor(colorBack);
    m_mapWinter.SetButtonBackgroundColor(colorBack);
    m_exit.SetButtonBackgroundColor(colorBack);
}

void CMapChoiceButtonManager::SetButtonText()
{
    m_mapDesert.SetButtonText("Desert Map");
    m_mapWinter.SetButtonText("Winter Map");
    m_exit.SetButtonText("Back");
}

void CMapChoiceButtonManager::SetButtonBody(Color colorBody)
{
    /*m_mapDesert.SetButtonColor(colorBody);
    m_mapWinter.SetButtonColor(colorBody);*/
    m_exit.SetButtonColor(colorBody);
}

void CMapChoiceButtonManager::SetFont()
{
    RegisterFont("Resources\\Fonts\\28DaysLater.ttf", 50, "MainMenuButtonName");
    m_mapDesert.SetButtonTextFont("MainMenuButtonName");
    m_mapWinter.SetButtonTextFont("MainMenuButtonName");
    m_exit.SetButtonTextFont("MainMenuButtonName");
}

void CMapChoiceButtonManager::SubscrscribeToMsg()
{
    theSwitchboard.SubscribeTo(this, "KeyBoardUp");
    theSwitchboard.SubscribeTo(this, "KeyBoardDown");
    theSwitchboard.SubscribeTo(this, "PadUp");
    theSwitchboard.SubscribeTo(this, "PadDown");
    theSwitchboard.SubscribeTo(this, "BuyKeyBoard");
    theSwitchboard.SubscribeTo(this, "BuyPad");
}

void CMapChoiceButtonManager::SetSprites()
{
    m_mapDesert.SetSprite("map_mini.png");
    m_mapWinter.SetSprite("Resources/Images/snow_map.png");
}
