#include "stdafx.h"
#include "BasicUnit.h"

CBasicUnit::CBasicUnit() :
    m_timeFromLastAttack(0),
    m_bounty(0),
    m_detectDist(0),
    m_attackDist(0),
    m_side(ESideIdentificator::Neutrals),
    m_attackForce(0),
    m_attackDelay(0)
{
    m_highlight.SetColor(0.0, 0.0, 0.0, 0.0);
    m_highlight.SetDrawShape(ADS_Circle);
    m_priority.reset(new CBasicPriority(this));
}

void CBasicUnit::TakeDamage(size_t damage)
{
    m_hp.TakeDamage(damage);
}

void CBasicUnit::Heal(size_t heal)
{
    m_hp.Heal(heal);
}

void CBasicUnit::Attack()
{
    m_timeFromLastAttack = 0;
}

void CBasicUnit::Update(float dt)
{
    m_highlight.SetPosition(this->GetPosition());
    m_timeFromLastAttack += dt;
}

size_t CBasicUnit::GetMaxHP() const
{
    return m_hp.GetMaxHP();
}

float CBasicUnit::GetDetectDist() const
{
    return m_detectDist;
}

float CBasicUnit::GetAttackDist() const
{
    return m_attackDist;
}

size_t CBasicUnit::GetCurrentHP() const
{
    return m_hp.GetCurrentHP();
}

size_t CBasicUnit::GetAttackForce() const
{
    return m_attackForce;
}

float CBasicUnit::GetAttackDelay() const
{
    return m_attackDelay;
}

void CBasicUnit::SetMaxHP(size_t hp)
{
    m_hp.SetSize(this->GetSize());
    m_hp.SetMaxHP(hp);
}

void CBasicUnit::SetDetectDist(float dist)
{
    m_detectDist = dist;
}

void CBasicUnit::SetAttackDist(float dist)
{
    m_attackDist = dist;
}

void CBasicUnit::SetCurrentHP(size_t hp)
{
    m_hp.SetCurrentHP(hp);
}

void CBasicUnit::SetAttackForce(size_t damage)
{
    m_attackForce = damage;
}

void CBasicUnit::SetAttackDelay(float seconds)
{
    m_attackDelay = seconds;
}

bool CBasicUnit::IsAlive() const
{
    return m_hp.IsAlive();
}

bool CBasicUnit::AttackAvailiable() const
{
    return m_timeFromLastAttack > m_attackDelay;
}

ESideIdentificator CBasicUnit::GetSideOfConflict() const
{
    return m_side;
}

void CBasicUnit::SetSideOfConflict(ESideIdentificator id)
{
    if (id != ESideIdentificator::Neutrals)
    {
        m_highlight.SetSize(this->GetSize().Y * 1.2, this->GetSize().Y * 1.2);

        if (id == ESideIdentificator::Side1)
            m_highlight.SetColor(
                theTuning.GetFloat("Team1ColorR"),
                theTuning.GetFloat("Team1ColorG"),
                theTuning.GetFloat("Team1ColorB"),
                theTuning.GetFloat("Team1Alpha"));
        else
            m_highlight.SetColor(
                theTuning.GetFloat("Team2ColorR"),
                theTuning.GetFloat("Team2ColorG"),
                theTuning.GetFloat("Team2ColorB"),
                theTuning.GetFloat("Team2Alpha"));
    }
    m_side = id;
}

CBasicPriority const & CBasicUnit::GetPriority() const
{
    return *m_priority;
}

void CBasicUnit::RenderHighlight()
{
    m_highlight.Render();
}

void CBasicUnit::ResetHighlight()
{
    m_highlight.SetAlpha(0);
}

size_t CBasicUnit::GetBounty() const
{
    return m_bounty;
}

void CBasicUnit::SetBounty(size_t bounty)
{
    m_bounty = bounty;
}

void CBasicUnit::RenderHealthBar()
{
    m_hp.Update(GetPosition());
    m_hp.Render();
}