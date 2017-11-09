#include "stdafx.h"
#include "CustomButtonLimitted.h"

bool CCustomButtonLimitted::Buy()
{
    if (m_clickAvailiable)
    {
        m_clickAvailiable--;
        if (m_clickAvailiable == 0)
        {
            m_price = 0;
            m_background.SetColor(1.0f, 0.5f, 0.0f);
        }
        else
        {
            m_price *= 2.5f;
        }
        SetButtonText(m_msgText);
        return true;
    }
    return false;
}

void CCustomButtonLimitted::SetButtonText(std::string text)
{
    if (m_clickAvailiable > 0)
    {
        m_buttonName.SetDisplayString(text + ": " + std::to_string(m_price) + "G" + " [" + std::to_string(m_clickAvailiable) + "]");
    }
    else
    {
        m_buttonName.SetDisplayString(text);
        m_background.SetColor(1.0f, 0.5f, 0.0f);
    }
}

void CCustomButtonLimitted::SetNumberOfClicks(size_t x)
{
    m_clickAvailiable = x;
}
