#pragma once

#include "stdafx.h"
#include "BasicUnit.h"
#include "WeaponHolder.h"

class CTower :
    public CBasicUnit,
    public CWeaponHolder
{
public:
    CTower();
    ~CTower();

    virtual void Update(float dt) override;
    virtual void Render() override;
    virtual void Attack() override;
    virtual void SetSideOfConflict(ESideIdentificator id) override;
};

