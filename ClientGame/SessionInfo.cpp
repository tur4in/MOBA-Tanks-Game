#include "stdafx.h"
#include "SessionInfo.h"

std::map<ESideIdentificator, std::unique_ptr<CSessionInfo>> CSessionInfo::s_infoMap;

std::map<ESideIdentificator, std::unique_ptr<CSessionInfo>>& CSessionInfo::GetInfo()
{
    if (!s_infoMap[ESideIdentificator::Side1])
    {
        s_infoMap[ESideIdentificator::Side1].reset(new CSessionInfo());
    }
    if (!s_infoMap[ESideIdentificator::Neutrals])
    {
        s_infoMap[ESideIdentificator::Neutrals].reset(new CSessionInfo());
    }
    if (!s_infoMap[ESideIdentificator::Side2])
    {
        s_infoMap[ESideIdentificator::Side2].reset(new CSessionInfo());
    }
    return s_infoMap;
}

void CSessionInfo::Reset()
{
    for (auto & it : s_infoMap)
    {
        it.second.reset(nullptr);
    }
}

void CSessionInfo::SetTankHP(int hp)
{
    m_tankHP = hp;
}

int CSessionInfo::GetTankHP() const
{
    return m_tankHP;
}

void CSessionInfo::SetTankSpeed(float speed)
{
    m_tankSpeed = speed;
}

float CSessionInfo::GetTankSpeed() const
{
    return m_tankSpeed;
}

void CSessionInfo::SetBasicTankDamage(int damage)
{
    m_basicTankDamage = damage;
}

int CSessionInfo::GetBasicTankDamage() const
{
    return m_basicTankDamage;
}

void CSessionInfo::SetTankWeaponType(std::string const & type)
{
    m_weaponType = type;
}

std::string const & CSessionInfo::GetTankWeaponType() const
{
    return m_weaponType;
}

void CSessionInfo::SetBasicMobHP(int hp)
{
    m_basicMobHP = hp;
}

int CSessionInfo::GetBasicMobHP() const
{
    return m_basicMobHP;
}

void CSessionInfo::SetBaseHP(int hp)
{
    m_baseHP = hp;
}

int CSessionInfo::GetBaseHP() const
{
    return m_baseHP;
}

void CSessionInfo::SetBasicSpawnDelay(float delay)
{
    m_basicSpawnDelay = delay;
}

float CSessionInfo::GetBasicSpawnDelay()
{
    return m_basicSpawnDelay;
}

void CSessionInfo::ResetBasicSpawnDelay()
{
    m_basicSpawnDelay = theTuning.GetFloat("BasicSpawnDelay");
}

CSessionInfo::CSessionInfo()
{
    m_baseHP = theTuning.GetInt("BaseHP");
    m_tankHP = theTuning.GetInt("TankHP");
    m_basicMobHP = theTuning.GetInt("MobHP");
    m_tankSpeed = theTuning.GetFloat("TankSpeed");
    m_weaponType = theTuning.GetString("TankGun");
    m_basicTankDamage = theTuning.GetInt("TankDamage");
    m_basicSpawnDelay = theTuning.GetFloat("BasicSpawnDelay");
}
