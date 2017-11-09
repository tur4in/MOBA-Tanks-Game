#include "stdafx.h"
#include "HealthBar.h"

CHealthBar::CHealthBar() : m_maxHp(0),
m_currentHp(0)
{
    m_blue.SetColor(0.0, 0.0, 1.0);
    m_red.SetColor(1.0, 0.0, 0.0);
}

CHealthBar::~CHealthBar()
{
}

void CHealthBar::Update(Vector2 parentPosition)
{
    m_red.SetSize(m_blue.GetSize().X * ((float)m_currentHp / (float)m_maxHp), m_red.GetSize().Y);
    m_blue.SetPosition(parentPosition.X, parentPosition.Y + (m_sizeOfParent.Y / 1.5));
    m_red.SetPosition(m_blue.GetPosition().X - ((m_blue.GetSize().X - m_red.GetSize().X) / 2), parentPosition.Y + (m_sizeOfParent.Y / 1.5));
}

size_t CHealthBar::GetMaxHP() const
{
    return m_maxHp;
}

size_t CHealthBar::GetCurrentHP() const
{
    return m_currentHp;
}

void CHealthBar::SetMaxHP(size_t hp)
{
    m_maxHp = hp;
    m_currentHp = m_maxHp;
}

void CHealthBar::SetCurrentHP(size_t hp)
{
    m_currentHp = hp;
}

void CHealthBar::TakeDamage(size_t damage)
{
    m_currentHp = m_currentHp > damage ? m_currentHp - damage : 0;
}

void CHealthBar::Heal(size_t heal)
{
    m_currentHp = m_currentHp + heal > m_maxHp ? m_maxHp : m_currentHp + heal;
}

bool CHealthBar::IsAlive() const
{
    return m_currentHp > 0;
}

void CHealthBar::Render()
{
    m_blue.Render();
    m_red.Render();
}

void CHealthBar::SetSize(Vector2 x)
{
    m_sizeOfParent = x;
    m_blue.SetSize(m_sizeOfParent.X * 2, 0.1f);
    m_red.SetSize(m_sizeOfParent.X * 2, 0.1f);
}
