#pragma once

#include "stdafx.h"
#include "Unit.h"
#include "WeaponHolder.h"

class CTank :
    public CUnit,
    public CWeaponHolder
{
public:
    CTank();
    ~CTank();
    virtual void Update(float dt) override;
    virtual void Render() override;
    virtual void Attack() override;
    virtual void SetSideOfConflict(ESideIdentificator id);
    virtual void TakeDamage(size_t damage) override;
};

