#include "stdafx.h"
#include "BurstWeapon.h"


CBurstWeapon::CBurstWeapon()
{
}


CBurstWeapon::~CBurstWeapon()
{
}

void CBurstWeapon::Update(float dt)
{
    CBasicWeapon::Update(dt);
    if (!m_bulletPool.front()->IsActive() && m_attacksLeft)
    {
        m_bulletPool.front()->SetDamage(m_damage);
        m_bulletPool.front()->SetSideOfConflict(m_side);
        m_bulletPool.front()->SetOwnedByPlayer(m_ownedByPlayer);
        float direction = MathUtil::ToRadians(GetRotation() + 90);
        Vector2 Offset(cos(direction) * GetSize().Y, sin(direction) * GetSize().Y);
        m_bulletPool.front()->Shoot(GetPosition() + Offset, direction);
        auto ptr = m_bulletPool.front();
        m_bulletPool.erase(m_bulletPool.begin());
        m_bulletPool.emplace_back(ptr);
        --m_attacksLeft;
    }
}

void CBurstWeapon::Attack()
{
    if (!m_attacksLeft)
    {
        m_attacksLeft = m_bulletPool.size();
    }
}
