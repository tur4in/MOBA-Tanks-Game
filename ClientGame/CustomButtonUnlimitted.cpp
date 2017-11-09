#include "stdafx.h"
#include "CustomButtonUnlimitted.h"

bool CCustomButtonUnlimitted::Buy()
{
    if (m_price > 0)
    {
        m_price = 0;
        m_background.SetColor(1.0f, 0.5f, 0.0f);
        SetButtonText(m_msgText);
    }
    return true;
}

void CCustomButtonUnlimitted::SetButtonText(std::string text)
{
    if (m_price > 0)
    {
        m_buttonName.SetDisplayString(text + ": " + std::to_string(m_price) + "G [1]");
    }
    else
    {
        m_buttonName.SetDisplayString(text);
        m_background.SetColor(1.0f, 0.5f, 0.0f);
    }
}
