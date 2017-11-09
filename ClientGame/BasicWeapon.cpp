#include "stdafx.h"
#include "BasicWeapon.h"
#include "LaserWeapon.h"
#include "BurstWeapon.h"

CBasicWeapon::CBasicWeapon(ESideIdentificator side, bool ownedByPlayer) :
    CBasicWeapon(1, side, ownedByPlayer)
{

}

CBasicWeapon::CBasicWeapon(size_t poolSize, ESideIdentificator side, bool ownedByPlayer) :
    m_ownedByPlayer(ownedByPlayer),
    m_side(side),
    m_damage(0)
{
    for (size_t i = 0; i < poolSize; i++)
    {
        m_bulletPool.emplace_back(std::make_shared<CBullet>());
    }
}

void CBasicWeapon::Attack()
{
    if (!m_bulletPool.front()->IsActive())
    {
        m_bulletPool.front()->SetDamage(m_damage);
        m_bulletPool.front()->SetSideOfConflict(m_side);
        m_bulletPool.front()->SetOwnedByPlayer(m_ownedByPlayer);
        float direction = MathUtil::ToRadians(GetRotation() + 90);
        Vector2 Offset(cos(direction) * GetSize().Y * 0.62, sin(direction) * GetSize().Y * 0.62);
        m_bulletPool.front()->Shoot(GetPosition() + Offset, direction);
        auto ptr = m_bulletPool.front();
        m_bulletPool.erase(m_bulletPool.begin());
        m_bulletPool.emplace_back(ptr);
    }
}

void CBasicWeapon::Render()
{
    Actor::Render();
    for (auto bullet : m_bulletPool)
    {
        bullet->Render();
    }
}

void CBasicWeapon::Update(float dt)
{
    for (auto bullet : m_bulletPool)
    {
        Actor::Update(dt);
        bullet->Update(dt);
    }
}

void CBasicWeapon::SetDamage(size_t damage)
{
    m_damage = damage;
}

size_t CBasicWeapon::GetDamage()
{
    return m_damage;
}

void CBasicWeapon::SetSideOfConflict(ESideIdentificator side)
{
    m_side = side;
}

ESideIdentificator CBasicWeapon::GetSideOfConflict() const
{
    return m_side;
}

void CBasicWeapon::SetPoolSize(size_t size)
{
    m_bulletPool.clear();
    for (size_t i = 0; i < size; i++)
    {
        m_bulletPool.emplace_back(std::make_shared<CBullet>());
    }
}

void CBasicWeapon::SetOwnedByPlayer(bool flag)
{
    m_ownedByPlayer = flag;
}

std::shared_ptr<CBasicWeapon> CBasicWeapon::Create(std::string const & type, ESideIdentificator side)
{
    std::shared_ptr<CBasicWeapon> result;
    if (type == "RegularGun")
    {
        result = std::make_shared<CBasicWeapon>();
    }
    else if (type == "LaserGun")
    {
        result = std::make_shared<CLaserWeapon>();
    }
    else if (type == "MachineGun")
    {
        result = std::make_shared<CBurstWeapon>();
    }
    result->SetSideOfConflict(side);
    return result;
}

