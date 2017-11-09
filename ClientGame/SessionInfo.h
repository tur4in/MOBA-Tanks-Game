#pragma once
#include "stdafx.h"
#include "BasicUnit.h"

#define theSession CSessionInfo::GetInfo()

class CSessionInfo
{
public:
    static std::map<ESideIdentificator, std::unique_ptr<CSessionInfo>>& GetInfo();
    static void Reset();

    void SetTankHP(int hp);
    int GetTankHP() const;
    void SetTankSpeed(float speed);
    float GetTankSpeed() const;
    void SetBasicTankDamage(int damage);
    int GetBasicTankDamage() const;
    void SetTankWeaponType(std::string const& type);
    std::string const& GetTankWeaponType() const;
    void SetBasicMobHP(int hp);
    int GetBasicMobHP() const;
    void SetBaseHP(int hp);
    int GetBaseHP() const;
    void SetBasicSpawnDelay(float delay);
    float GetBasicSpawnDelay();
    void ResetBasicSpawnDelay();

private:
    CSessionInfo();
    CSessionInfo(CSessionInfo const&) = delete;
    CSessionInfo& operator=(CSessionInfo const&) = delete;

private:
    static std::map<ESideIdentificator, std::unique_ptr<CSessionInfo>> s_infoMap;

private:
    int m_tankHP;
    float m_tankSpeed;
    int m_basicTankDamage;
    std::string m_weaponType;
    int m_basicMobHP;
    int m_baseHP;
    float m_basicSpawnDelay;
};

