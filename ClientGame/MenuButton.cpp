#include "stdafx.h"
#include "MenuButton.h"


CMenuButton::CMenuButton()
{
}

CMenuButton::~CMenuButton()
{
}

void CMenuButton::SetButtonSize(Vector2 size)
{
    m_body.SetSize(size);
    m_highLight.SetSize(size * 1.2f);
    m_background.SetSize(size * 1.2f);
}

void CMenuButton::SetButtonPosition(Vector2 pos)
{
    CBasicButton::SetButtonPosition(pos);
    m_buttonName.SetPosition(pos.X, pos.Y - (0.2 * m_body.GetSize().Y));
    m_buttonName.SetAlignment(TXT_Center);
}

void CMenuButton::HighLight()
{
    m_highLight.SetAlpha(1.0f);
}

void CMenuButton::UnHighLight()
{
    m_highLight.SetAlpha(0.0f);
}

