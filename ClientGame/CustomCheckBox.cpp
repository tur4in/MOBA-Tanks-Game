#include "stdafx.h"
#include "CustomCheckBox.h"

CCustomCheckBox::CCustomCheckBox(bool status)
{
    m_isPressed = status;
    m_pressedColor = Color(1.0, 1.0, 1.0);
    m_unpressedColor = Color(0.0, 0.0, 0.0);

    SetRightColor();
}

void CCustomCheckBox::ChangeStatus()
{
    m_isPressed = !m_isPressed;
    SetRightColor();
}

void CCustomCheckBox::SetPressedColor(Color newColor)
{
    m_pressedColor = newColor;
    SetRightColor();
}

void CCustomCheckBox::SetUnpressedColor(Color newColor)
{
    m_unpressedColor = newColor;
    SetRightColor();
}

CCustomCheckBox::~CCustomCheckBox()
{
}

void CCustomCheckBox::SetButtonSize(Vector2 size)
{
    m_body.SetSize(size);
    m_highLight.SetSize(size * 1.2f);
    m_background.SetSize(size * 1.2f);
}

void CCustomCheckBox::SetRightColor()
{
    if (m_isPressed)
    {
        m_body.SetColor(m_pressedColor);
    }
    else
    {
        m_body.SetColor(m_unpressedColor);
    }
}
