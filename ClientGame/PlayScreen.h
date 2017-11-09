#pragma once
#include "GameScreen.h"
#include "Game.h"
#include "Store.h"
#include "PauseMenuButtonManager.h"
#include "Timer.h"

class CPlayScreen :
    public CGameScreen, public MessageListener
{
public:
    CPlayScreen(std::string const& levelName);
    ~CPlayScreen();

    virtual void Start() override;
    virtual void Update(float dt) override;
    virtual void Render() override;
    virtual void ReceiveMessage(Message* m);

private:
	void ManageTutorial();

private:
    CTimer m_timer;
    bool m_isPaused;
    CGame m_game;
	Actor m_tutorial;
	bool m_tutorialOn;
    CPauseMenuButtonManager m_pauseMenu;

    CStore m_storeL;
    CStore m_storeR;
};

