#pragma once
#include "Mob.h"
#include "WeaponHolder.h"
class CRangedMob :
    public CMob,
    public CWeaponHolder
{
public:
    CRangedMob();
    virtual ~CRangedMob();
    virtual void MoveToPoint(Vector2 pos) override;
    virtual void AttackTarget(std::shared_ptr<CBasicUnit>) override;
    virtual void SetSideOfConflict(ESideIdentificator id) override;
    virtual void Render() override;
    virtual void Update(float dt) override;
};

