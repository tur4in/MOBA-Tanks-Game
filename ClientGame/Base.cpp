#include "stdafx.h"
#include "Base.h"

CBase::CBase()
{
}

CBase::~CBase()
{
}

void CBase::TakeDamage(size_t damage)
{
    CTower::TakeDamage(damage);
    if (!IsAlive())
    {
        theSwitchboard.Broadcast(new TypedMessage<ESideIdentificator>("BaseDead", GetSideOfConflict()));
    }
}
