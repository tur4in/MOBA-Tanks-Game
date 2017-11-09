#pragma once
#include "GameScreen.h"
#include "OptionScreenButtonManager.h"

class COptionsScreen :
    public CGameScreen,
    public MessageListener
{
public:
    COptionsScreen();

    virtual void Start() override;
    virtual void Render() override;
    virtual void Update(float dt) override;
    virtual void ReceiveMessage(Message* m) override;

private:
    COptionScreenButtonManager m_buttonManager;

    TextActor m_options;
    TextActor m_axisPadRight;
    TextActor m_axisPadLeft;
    TextActor m_advancedKeyboard;
    TextActor m_music;
    TextActor m_musicVol;
    TextActor m_effects;
    TextActor m_effectsVol;
};

