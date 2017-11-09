#include "stdafx.h"
#include "RangedMob.h"
#include "RayCastCallbackClosest.h"


CRangedMob::CRangedMob() :
    CWeaponHolder(this)
{
}


CRangedMob::~CRangedMob()
{
}

void CRangedMob::Update(float dt)
{
    CMob::Update(dt);
    CWeaponHolder::Update(dt);
}

void CRangedMob::Render()
{
    CUnit::Render();
    CWeaponHolder::Render();
}

void CRangedMob::MoveToPoint(Vector2 pos)
{
    if (GetState() != EMobState::Fight)
    {
        CMob::MoveToPoint(pos);
    }
    else
    {
        _physBody->SetLinearVelocity(b2Vec2(0, 0));
        _physBody->SetAngularVelocity(0);
    }
}

void CRangedMob::AttackTarget(std::shared_ptr<CBasicUnit> target)
{
    Vector2 targetDirection = target->GetPosition() - GetPosition();
    RotateTower(MathUtil::AngleFromVector(targetDirection));
    if (abs(MathUtil::DeltaAngle(MathUtil::AngleFromVector(targetDirection), MathUtil::ToRadians(GetTowerRotation()))) < theTuning.GetFloat("AngularError"))
    {
        if (AttackAvailiable())
        {
            CBasicUnit::Attack();
            CWeaponHolder::Attack();
            Reset();
        }
    }
}

void CRangedMob::SetSideOfConflict(ESideIdentificator id)
{
    CWeaponHolder::SetSideOfConflict(id);
    CBasicUnit::SetSideOfConflict(id);
}
