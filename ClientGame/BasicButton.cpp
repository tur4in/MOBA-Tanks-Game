#include "stdafx.h"
#include "BasicButton.h"

CBasicButton::CBasicButton()
{
}

CBasicButton::CBasicButton(const CBasicButton& copy)
{
    m_highLight = copy.m_highLight;
    m_body = copy.m_body;
    m_background = copy.m_background;
    m_buttonName = copy.m_buttonName;
    m_msgText = copy.m_msgText;
}

void CBasicButton::Show()
{
    m_body.SetAlpha(1.0f);
    m_background.SetAlpha(1.0f);
}

void CBasicButton::Hide()
{
    m_buttonName.SetAlpha(0.0f);
    m_body.SetAlpha(0.0f);
    m_highLight.SetAlpha(0.0f);
}

void CBasicButton::SetSprite(std::string texture)
{
    m_body.SetSprite(texture);
}

std::string CBasicButton::GetDisplayString()
{
    return m_buttonName.GetDisplayString();
}

void CBasicButton::ResetDisplayString()
{
    m_buttonName.SetDisplayString("");
}

void CBasicButton::SetButtonSize(Vector2 size)
{
    m_body.SetSize(size);
    m_highLight.SetSize(size * 1.1f);
    m_background.SetSize(size * 1.2f);
}

void CBasicButton::SetMsgText(std::string text)
{
    m_msgText = text;
}

std::string CBasicButton::GetMsgText()
{
    return m_msgText;
}

void CBasicButton::SetHilightColor(Color color)
{
    m_highLight.SetColor(color);
}

void CBasicButton::SetButtonColor(Color color)
{
    m_body.SetColor(color);
}

void CBasicButton::SetButtonBackgroundColor(Color color)
{
    m_background.SetColor(color);
}

void CBasicButton::HighLight()
{
    m_highLight.SetAlpha(1.0f);
}

void CBasicButton::UnHighLight()
{
    m_highLight.SetAlpha(0.0f);
}

void CBasicButton::Render()
{
    m_background.Render();
    m_highLight.Render();
    m_body.Render();
    m_buttonName.Render();
}

bool CBasicButton::IsChoosen()
{
    return m_highLight.GetAlpha() > 0.0f;
}

void CBasicButton::SetButtonPosition(Vector2 x)
{
    m_body.SetPosition(x);
    m_highLight.SetPosition(x);
    m_background.SetPosition(x);
}

void CBasicButton::SetButtonText(std::string text)
{
    m_buttonName.SetDisplayString(text);
}

void CBasicButton::SetButtonTextFont(std::string font)
{
    m_buttonName.SetFont(font);
}
