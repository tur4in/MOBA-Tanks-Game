#include "stdafx.h"
#include "MeleeMob.h"
#include "RayCastCallbackAll.h"


CMeleeMob::CMeleeMob()
{
}


CMeleeMob::~CMeleeMob()
{
}

void CMeleeMob::AttackTarget(std::shared_ptr<CBasicUnit> target)
{
    if (AttackAvailiable())
    {
        target->TakeDamage(GetAttackForce());
        Attack();
    }
}
