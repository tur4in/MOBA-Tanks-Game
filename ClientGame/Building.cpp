#include "stdafx.h"
#include "Building.h"

CBuilding::CBuilding(Vector2 pos) :
    CBasicUnit(10, 3, 0.5)
{
    SetPosition(pos);
    SetShapeType(eShapeType::SHAPETYPE_BOX);
    SetSize(2, 2);
    SetDensity(0);
}

CBuilding::~CBuilding()
{
}


