#pragma once
#include "stdafx.h"
#include "MenuButton.h"
#include "PlaySides.h"

class CPauseMenuButtonManager :
    MessageListener
{
public:
    CPauseMenuButtonManager();
    ~CPauseMenuButtonManager();
    virtual void ReceiveMessage(Message* m) override;
    void SetActive();
    void Update();
    void Render();
    void EndGameMenu(ESideIdentificator looser);

private:
    CMenuButton m_resume;
    CMenuButton m_options;
    CMenuButton m_exit;
    CMenuButton m_endButton;

    Actor m_winTextBack;
    TextActor m_winText;

    size_t m_pos;
    Actor m_background;
    bool m_isActive;
    bool m_endGame;

private:
    void SetButtonPosition(int xWidth, int yHeight);
    void SetButtonSizes(Vector2 sizeRegularButton, Vector2 sizeExitButton, int xWidth, int yHeight);
    void SetButtonHighlightColor(Color color);
    void SetButtonBackGroundColor(Color colorBack);
    void SetButtonText();
    void SetButtonBody(Color colorBody);
    void SetFont();
    void SubscrscribeToMsg();
};

