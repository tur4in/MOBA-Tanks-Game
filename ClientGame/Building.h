#pragma once

#include "stdafx.h"
#include "BasicUnit.h"

class CBuilding :
    public CBasicUnit
{
public:
    CBuilding(Vector2 pos);
    ~CBuilding();
};

