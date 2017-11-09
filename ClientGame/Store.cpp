#include "stdafx.h"
#include "Store.h"
#include "StatManager.h"
#include "CustomButtonLimitted.h"
#include "CustomButtonUnlimitted.h"

CStore::CStore() :
    m_curCol(0),
    m_curRow(0),
    isHidden(true),
    m_id(ESideIdentificator::Neutrals)
{
    m_background.SetAlpha(0);
    onPause = false;
}

CStore::~CStore()
{
}

void CStore::SetSide(ESideIdentificator id)
{
    if (m_id == ESideIdentificator::Neutrals)
    {
        m_id = id;

        size_t xWidth = theCamera.GetWindowWidth();
        size_t yHeight = theCamera.GetWindowHeight();

        SetMessages();
        CreateButtons();
        SetPositionOfStore(yHeight, xWidth);

        m_background.SetColor(0.1f, 0.1f, 0.1f, 0.0f);
        RegisterFont("Resources\\Fonts\\28DaysLater.ttf", 35, "ButtonName");

        SetUpButtons();
    }
}

void CStore::ReceiveMessage(Message* m)
{
    if (!isHidden && !onPause)
    {
        if (m->GetMessageName() == m_mesages[0]) // UP 
        {
            if (m_curRow > 0)
            {
                --m_curRow;
            }
        }
        else if (m->GetMessageName() == m_mesages[1]) // DOWN 
        {
            if (m_curRow < 3)
            {
                ++m_curRow;
            }
        }
        else if (m->GetMessageName() == m_mesages[2]) // LEFT
        {
            if (m_curCol > 0)
            {
                --m_curCol;
            }
        }
        else if (m->GetMessageName() == m_mesages[3]) //RIGHT
        {
            if (m_curCol < 1)
            {
                ++m_curCol;
            }
        }
        else if (m->GetMessageName() == m_storeMessage) // HIDE
        {
            this->Hide();
        }
        else if (m->GetMessageName() == m_buyMessage) // ENTER or X
        {
            for (auto button : m_buttons)
            {
                if (button->IsChoosen() && theStatistic.GetPlayerGold(m_id) >= button->GetPrice())
                {
                    size_t price = button->GetPrice();
                    if (button->Buy())
                    {
                        theStatistic.TakePlayerGold(price, m_id);
                        theSwitchboard.Broadcast(new TypedMessage<ESideIdentificator>(button->GetMsgText(), m_id));
                    }
                    return;
                }
            }
        }
    }
    else if (m->GetMessageName() == m_storeMessage && !onPause)
    {
        this->Show();
    }
    else if (m->GetMessageName() == "ComeIntoPlayScreen" && onPause)
    {
        PauseSwitcher();
    }
}

void CStore::Update()
{
    if (!m_buttons.empty() && !isHidden && !onPause)
    {
        for (size_t i = 0, k = 0; i < m_numberOfLines; ++i)
        {
            for (size_t j = 0; j < m_numberOfColumns; ++j, ++k)
            {
                if (m_curRow == i && m_curCol == j)
                {
                    m_buttons[k]->HighLight();
                }
                else
                {
                    m_buttons[k]->UnHighLight();
                }
            }
        }
    }
}

void CStore::Hide()
{
    m_background.SetAlpha(0.0f);
    for (auto button : m_buttons)
    {
        button->Hide();
        m_curCol = 0;
        m_curRow = 0;
    }
    isHidden = true;
}

void CStore::Show()
{
    for (auto button : m_buttons)
    {
        button->Show();
    }
    m_background.SetAlpha(0.45f);
    isHidden = false;
}

void CStore::Render()
{
    if (!isHidden)
    {
        m_background.Render();
        for (auto button : m_buttons)
        {
            button->Render();
        }
    }
}

void CStore::PauseSwitcher()
{
    onPause = !onPause;
}

void CStore::SetUpButtons()
{
    int i = 1;
    for (auto button : m_buttons)
    {
        button->SetNumberOfClicks((size_t)thePrefs.GetInt("MessagesAfterBuy", std::string("Button") + std::to_string(i)));
        button->SetSprite(thePrefs.GetString("StoreButtons", std::string("Button") + std::to_string(i)));
        button->SetPrice(thePrefs.GetInt("StorePrices", std::string("Button") + std::to_string(i)));
        button->SetButtonSize(Vector2(2.0f, 2.0f));
        button->SetHilightColor(Color(1.0f, 0.0f, 0.0f, 0.0f));
        button->SetMsgText(thePrefs.GetString("StoreButtonText", std::string("Button") + std::to_string(i)));
        button->SetButtonTextFont("ButtonName");
        i++;
    }
}

void CStore::CreateButtons()
{
    for (size_t i = 0; i < m_numberOfColumns*m_numberOfLines; i++)
    {
        if ((size_t)thePrefs.GetInt("MessagesAfterBuy", std::string("Button") + std::to_string(i + 1)) > 1)
        {
            m_buttons.push_back(std::make_shared<CCustomButtonLimitted>());
        }
        else
        {
            m_buttons.push_back(std::make_shared<CCustomButtonUnlimitted>());
        }
    }
}

void CStore::SetMessages()
{
    theSwitchboard.SubscribeTo(this, "ComeIntoPlayScreen");
    if (m_id == ESideIdentificator::Side1)
    {
        m_storeMessage = "KeyBoardStore";
        m_buyMessage = "BuyKeyBoard";
        m_mesages.push_back("KeyBoardUp");
        m_mesages.push_back("KeyBoardDown");
        m_mesages.push_back("KeyBoardLeft");
        m_mesages.push_back("KeyBoardRight");

        theSwitchboard.SubscribeTo(this, "BuyKeyBoard");
        theSwitchboard.SubscribeTo(this, "KeyBoardStore");
        for (auto i : m_mesages)
        {
            theSwitchboard.SubscribeTo(this, i);
        }
    }
    else if (m_id == ESideIdentificator::Side2)
    {
        m_storeMessage = "PadStore";
        m_buyMessage = "BuyPad";
        m_mesages.push_back("PadUp");
        m_mesages.push_back("PadDown");
        m_mesages.push_back("PadLeft");
        m_mesages.push_back("PadRight");

        theSwitchboard.SubscribeTo(this, "BuyPad");
        theSwitchboard.SubscribeTo(this, "PadStore");
        for (auto i : m_mesages)
        {
            theSwitchboard.SubscribeTo(this, i);
        }
    }
}

void CStore::SetPositionOfStore(size_t yHeight, size_t xWidth)
{
    size_t x = 0;
    int widthScale = xWidth / (2 * (m_numberOfColumns + 1));
    int heightScale = yHeight / (m_numberOfLines + 1);
    if (m_id == ESideIdentificator::Side2)
    {
        x = (xWidth / 2);
        m_background.SetPosition(MathUtil::ScreenToWorld((xWidth / 2) + (xWidth / 4), yHeight / 2));
    }
    else
    {
        m_background.SetPosition(MathUtil::ScreenToWorld((xWidth / 2) - (xWidth / 4), yHeight / 2));
    }

    m_background.SetSize(
        abs((MathUtil::ScreenToWorld(xWidth, yHeight) - MathUtil::ScreenToWorld(0, 0)).X) * 0.5,
        abs((MathUtil::ScreenToWorld(xWidth, yHeight) - MathUtil::ScreenToWorld(0, 0)).Y));

    for (size_t i = 0, k = 0; i < m_numberOfLines; ++i)
    {
        for (size_t j = 0; j < m_numberOfColumns; ++j, ++k)
        {
            m_buttons[k]->SetButtonPosition(MathUtil::ScreenToWorld(
                x + widthScale * (j + 1),
                heightScale * (i + 1)
            ));
        }
    }
}
