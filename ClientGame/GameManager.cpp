#include "stdafx.h"
#include "GameManager.h"


CGameManager::CGameManager()
{
    m_nextLevel = "map.tmx";
    theSwitchboard.SubscribeTo(this, "OpenPlayScreen");
    theSwitchboard.SubscribeTo(this, "OpenMenuScreen");
    theSwitchboard.SubscribeTo(this, "OpenOptionsScreen");
    theSwitchboard.SubscribeTo(this, "ReturnBack");
    PushScreen(EScreenTypes::MenuScreen);
}

void CGameManager::ReceiveMessage(Message * message)
{
    if (message->GetMessageName() == "OpenPlayScreen")
    {
        m_nextLevel = static_cast<TypedMessage<std::string>*>(message)->GetValue();
        PushScreen(EScreenTypes::PlayScreen);
    }
    if (message->GetMessageName() == "OpenMenuScreen")
    {
        PushScreen(EScreenTypes::MenuScreen);
    }
    if (message->GetMessageName() == "OpenOptionsScreen")
    {
        PushScreen(EScreenTypes::OptionsScreen);
    }
    if (message->GetMessageName() == "ReturnBack")
    {
        ReturnBack();
    }
}

void CGameManager::Update(float dt)
{
    GameManager::Update(dt);
    m_pad.Update();
    m_explosive.Update(dt);
}

void CGameManager::Render()
{
    m_explosive.Render();
}

void CGameManager::PushScreen(EScreenTypes screenType)
{
    switch (screenType)
    {
    case EScreenTypes::MenuScreen:
        AddNext(std::make_unique<CMenuScreen>());
        break;
    case EScreenTypes::OptionsScreen:
        AddNext(std::make_unique<COptionsScreen>());
        break;
    case EScreenTypes::PlayScreen:
        AddNext(std::make_unique<CPlayScreen>(m_nextLevel));
        break;
    }
}

void CGameManager::AddNext(std::unique_ptr<CGameScreen>&& screen)
{
    if (!m_screens.empty())
    {
        m_screens.top()->Stop();
        theWorld.Remove(m_screens.top().get());
    }
    m_screens.emplace(std::move(screen));
    m_screens.top()->Start();
    theWorld.Add(m_screens.top().get());
}

void CGameManager::ReturnBack()
{
    m_explosive.Reset();
    if (m_screens.size() >= 2)
    {
        m_screens.top()->Stop();
        theWorld.Remove(m_screens.top().get());
        m_screens.pop();
        m_screens.top()->Start();
        theWorld.Add(m_screens.top().get());
    }
    else
    {
        theWorld.StopGame();
    }
}
