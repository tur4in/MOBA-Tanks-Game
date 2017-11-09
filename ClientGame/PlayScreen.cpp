#include "stdafx.h"
#include "PlayScreen.h"
#include "StatManager.h"
#include "SessionInfo.h"

CPlayScreen::CPlayScreen(std::string const& levelName) : m_game(levelName)
{
    theSwitchboard.SubscribeTo(this, "Pause");
    theSwitchboard.SubscribeTo(this, "Resume");
    theSwitchboard.SubscribeTo(this, "BaseDead");
	theSwitchboard.SubscribeTo(this, "OpenTutorial");

    CSessionInfo::Reset();
    CStatManager::Reset();

    m_storeL.SetSide(ESideIdentificator::Side1);
    m_storeR.SetSide(ESideIdentificator::Side2);

    m_background.SetSprite(m_game.GetMap().GetBackground());
	m_tutorial.SetSprite("readytut.png");
	m_tutorial.SetSize(16, 7);
	m_tutorialOn = false;
	ManageTutorial();
}


CPlayScreen::~CPlayScreen()
{
}

void CPlayScreen::Start()
{
    theSwitchboard.Broadcast(new Message("ComeIntoPlayScreen"));
	if (!m_tutorialOn)
	{
		m_isPaused = false;
		m_game.Continue();
	}
}

void CPlayScreen::Update(float dt)
{
    if (!m_isPaused && !m_tutorialOn)
    {
        m_game.Update(dt);
        m_storeL.Update();
        m_storeR.Update();
        m_timer.Update(dt);
    }
	else if (m_isPaused && !m_tutorialOn)
	{
		m_pauseMenu.SetActive();
		m_pauseMenu.Update();
	}
}

void CPlayScreen::Render()
{
    m_background.Render();
    m_game.Render();
    m_storeL.Render();
    m_storeR.Render();
    theStatistic.Render();
    m_timer.Render();
    if (m_isPaused && !m_tutorialOn)
    {
        m_pauseMenu.Render();
    }
	if (m_tutorialOn)
	{
		m_tutorial.Render();
	}
}

void CPlayScreen::ReceiveMessage(Message* m)
{
    if (!m_isPaused)
    {
        if (m->GetMessageName() == "Pause")
        {
            m_isPaused = true;
            m_storeL.PauseSwitcher();
            m_storeR.PauseSwitcher();
            m_game.Pause();
            m_pauseMenu.SetActive();
        }
        if (m->GetMessageName() == "BaseDead")
        {
            m_pauseMenu.EndGameMenu(static_cast<TypedMessage<ESideIdentificator>*>(m)->GetValue());
            m_isPaused = true;
            m_game.Pause();
        }
    }
    else
    {
        if (m->GetMessageName() == "Resume")
        {
            Start();
            if (m_isPaused == false)
            {
                m_storeL.PauseSwitcher();
                m_storeR.PauseSwitcher();
            }
        }
    }
	if (m->GetMessageName() == "OpenTutorial")
	{
		ManageTutorial();
	}
}

void CPlayScreen::ManageTutorial()
{
	if (m_tutorialOn)
	{
		m_tutorialOn = false;
		Start();
	}
	else
	{
		m_tutorialOn = true;
		m_isPaused = true;
		m_game.Pause();
	}
	m_storeL.PauseSwitcher();
	m_storeR.PauseSwitcher();
}



