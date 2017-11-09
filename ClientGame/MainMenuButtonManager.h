#pragma once
#include "stdafx.h"
#include "MenuButton.h"

class CMainMenuButtonManager :
    MessageListener
{
public:
    CMainMenuButtonManager();
    ~CMainMenuButtonManager();
    virtual void ReceiveMessage(Message* m) override;
    void SetActive();
    void Update();
    void Render();

private:
    CMenuButton m_play;
    CMenuButton m_options;
    CMenuButton m_exit;
    size_t m_pos;
    TextActor m_title;
    bool m_isActive;

private:
    void SetButtonPosition(int xWidth, int yHeight);
    void SetButtonSizes(Vector2 sizeRegularButton);
    void SetButtonHighlightColor(Color color);
    void SetButtonBackGroundColor(Color colorBack);
    void SetButtonText();
    void SetButtonBodyColor(Color colorBody);
    void SetFont();
    void SubscrscribeToMsg();
};

