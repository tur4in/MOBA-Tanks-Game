#include "stdafx.h"
#include "StoreButton.h"

CStoreButton::CStoreButton()
{
    m_price = 0;
    m_buttonName.SetColor(1.0, 1.0, 1.0);
    Hide();
}

CStoreButton::~CStoreButton()
{
}

void CStoreButton::SetButtonPosition(Vector2 x)
{
    CBasicButton::SetButtonPosition(x);
    m_buttonName.SetPosition(x.X, x.Y + (m_background.GetSize().Y * 1.75));
    m_buttonName.SetAlignment(TXT_Center);
}

void CStoreButton::SetMsgText(std::string text)
{
    m_msgText = text;
    SetButtonText(text);
}

size_t CStoreButton::GetPrice()
{
    return m_price;
}

void CStoreButton::SetPrice(size_t p)
{
    m_price = p;
}

void CStoreButton::SetNumberOfClicks(size_t x) {}

void CStoreButton::HighLight()
{
    m_buttonName.SetAlpha(1.0f);
    m_highLight.SetAlpha(1.0f);
}

void CStoreButton::UnHighLight()
{
    m_buttonName.SetAlpha(0.0f);
    m_highLight.SetAlpha(0.0f);
}
