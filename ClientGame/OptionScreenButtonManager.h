#pragma once

#include "MenuButton.h"

class COptionScreenButtonManager :
    MessageListener
{
public:
    COptionScreenButtonManager();
    ~COptionScreenButtonManager();
    virtual void ReceiveMessage(Message* m) override;
    void Update();
    void Render();

private:
    std::vector<std::shared_ptr<CBasicButton>> m_left;
    std::vector<std::shared_ptr<CBasicButton>> m_right;
    size_t m_posX;
    size_t m_posY;

private:
    void CreateButtons();
    void SetPositions(int xWidth, int yHeight);
    void SetSizes(Vector2 sizeRegularButton);
    void SetButtonColor(Color regular, Color pressed);
    void SetButtonBackGroundColor(Color colorBack);
    void SetText();
    void SetButtonHighlightColor(Color highlight);
    void SubscrscribeToMsg();
};

void ReturnPressed();
void InvertAxisPadLeftTrigged();
void InvertAxisPadRightTrigged();
void MusicVolumePlus();
void MusicVolumeMinus();
void EffectsVolumePlus();
void EffectsVolumeMinus();
void AdvancedKeyboard();