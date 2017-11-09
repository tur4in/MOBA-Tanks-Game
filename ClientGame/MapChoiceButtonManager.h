#pragma once
#include "stdafx.h"
#include "MenuButton.h"
#include "PlaySides.h"

class CMapChoiceButtonManager :
    MessageListener
{
public:
    CMapChoiceButtonManager();
    ~CMapChoiceButtonManager();
    virtual void ReceiveMessage(Message* m) override;
    void SetActive();
    void Update();
    void Render();

private:
    CMenuButton m_mapDesert;
    CMenuButton m_mapWinter;
    CMenuButton m_exit;

    TextActor m_choseMap;
    bool m_isActive;

    size_t m_pos;
    Actor m_background;

private:
    void SetButtonPosition(int xWidth, int yHeight);
    void SetButtonSizes(Vector2 sizeRegularButton, Vector2 sizeExitButton, int xWidth, int yHeight);
    void SetButtonHighlightColor(Color color);
    void SetButtonBackGroundColor(Color colorBack);
    void SetButtonText();
    void SetButtonBody(Color colorBody);
    void SetFont();
    void SubscrscribeToMsg();
    void SetSprites();
};

