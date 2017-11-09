#pragma once
#include "stdafx.h"
#include "GameScreen.h"
#include "MainMenuButtonManager.h"
#include "MapChoiceButtonManager.h"

class CMenuScreen :
    public CGameScreen,
    public MessageListener
{
public:
    CMenuScreen();
    ~CMenuScreen() = default;

    virtual void Start() override;
    virtual void Update(float dt) override;
    virtual void Render() override;
    virtual void ReceiveMessage(Message* m) override;

private:
    CMainMenuButtonManager m_buttonManager;
    CMapChoiceButtonManager m_mapChoice;
};

