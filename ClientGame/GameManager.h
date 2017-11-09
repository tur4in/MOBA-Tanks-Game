#pragma once
#include "stdafx.h"
#include "GameScreen.h"
#include "PlayScreen.h"
#include "MenuScreen.h"
#include "OptionsScreen.h"
#include "SoundSystem.h"

enum class EScreenTypes
{
    MenuScreen,
    PlayScreen,
    OptionsScreen
};

class CGameManager :
    public GameManager
{
public:
    CGameManager();
    ~CGameManager() = default;

    virtual void ReceiveMessage(Message* message) override;
    virtual void Update(float dt) override;
    virtual void Render() override;

private:
    void PushScreen(EScreenTypes screenType);
    void AddNext(std::unique_ptr<CGameScreen>&& screen);
    void ReturnBack();

private:
    ExplosionSystem m_explosive;
    std::stack<std::unique_ptr<CGameScreen>> m_screens;
    CSoundSystem m_soundSystem;
    GamepadStoreInput m_pad;
	std::string m_nextLevel;
};

