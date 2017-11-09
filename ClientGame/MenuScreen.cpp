#include "stdafx.h"
#include "MenuScreen.h"


CMenuScreen::CMenuScreen()
{
    theSwitchboard.SubscribeTo(this, "OpenMapChoice");
    theSwitchboard.SubscribeTo(this, "OpenMenu");
    m_background.SetSprite("Resources/Images/menu_backgroud.jpg");
}

void CMenuScreen::Start()
{
    theSwitchboard.Broadcast(new Message("ComeIntoMenu"));
    m_buttonManager.SetActive();
}

void CMenuScreen::Update(float dt)
{
    m_buttonManager.Update();
    m_mapChoice.Update();
}

void CMenuScreen::Render()
{
    m_background.Render();
    m_buttonManager.Render();
    m_mapChoice.Render();
}

void CMenuScreen::ReceiveMessage(Message* m)
{
    if (m->GetMessageName() == "OpenMapChoice")
    {
        m_mapChoice.SetActive();
    }
    else if (m->GetMessageName() == "OpenMenu")
    {
        m_buttonManager.SetActive();
    }
}

