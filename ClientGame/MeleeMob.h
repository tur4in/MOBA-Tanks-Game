#pragma once
#include "Mob.h"
class CMeleeMob :
    public CMob
{
public:
    CMeleeMob();
    virtual ~CMeleeMob();
    virtual void AttackTarget(std::shared_ptr<CBasicUnit>) override;
};

