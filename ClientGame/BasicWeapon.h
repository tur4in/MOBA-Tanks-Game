#pragma once

#include "stdafx.h"
#include "Bullet.h"

class CBasicWeapon :
    public Actor
{
public:
    CBasicWeapon(ESideIdentificator side = ESideIdentificator::Neutrals, bool ownedByPlayer = false);
    CBasicWeapon(size_t poolSize, ESideIdentificator side = ESideIdentificator::Neutrals, bool ownedByPlayer = false);
    virtual void Attack();
    virtual void Render() override;
    virtual void Update(float dt) override;
    void SetDamage(size_t damage);
    size_t GetDamage();
    void SetSideOfConflict(ESideIdentificator side);
    ESideIdentificator GetSideOfConflict() const;
    void SetPoolSize(size_t size);
    void SetOwnedByPlayer(bool flag);

public:
    static std::shared_ptr<CBasicWeapon> Create(std::string const& type, ESideIdentificator side);

protected:
    std::list<std::shared_ptr<CBullet>> m_bulletPool;
    bool m_ownedByPlayer;
    ESideIdentificator m_side;
    size_t m_damage;
};