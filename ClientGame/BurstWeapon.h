#pragma once
#include "BasicWeapon.h"
class CBurstWeapon :
    public CBasicWeapon
{
public:
    CBurstWeapon();
    virtual ~CBurstWeapon();
    virtual void Update(float dt) override;
    virtual void Attack() override;

private:
    size_t m_attacksLeft = 0;
};

