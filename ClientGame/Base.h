#pragma once

#include "stdafx.h"
#include "Tower.h"

class CBase :
    public CTower
{
public:
    CBase();
    ~CBase();
    virtual void TakeDamage(size_t damage) override;
};

