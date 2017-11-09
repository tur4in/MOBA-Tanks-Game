#pragma once

#include "stdafx.h"
#include "PlaySides.h"
#include "StoreButton.h"

class CStore :
    MessageListener
{
public:
    CStore();
    ~CStore();
    void SetSide(ESideIdentificator id);
    virtual void ReceiveMessage(Message* m) override;
    virtual void Update();
    void Hide();
    void Show();
    void Render();
    void PauseSwitcher();

private:
    void SetUpButtons();
    void CreateButtons();
    void SetMessages();
    void SetPositionOfStore(size_t xHeight, size_t yWidth);

private:
    bool isHidden;
    bool onPause;
    ESideIdentificator m_id;

    std::vector<std::shared_ptr<CStoreButton>> m_buttons;
    std::vector<std::string> m_mesages;

    std::string m_storeMessage;
    std::string m_buyMessage;

    Actor m_background;
    size_t m_curCol;
    size_t m_curRow;

    size_t m_numberOfLines = 4;
    size_t m_numberOfColumns = 2;
};

