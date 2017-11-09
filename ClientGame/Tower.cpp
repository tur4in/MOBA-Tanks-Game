#include "stdafx.h"
#include "Tower.h"


CTower::CTower() :
    CWeaponHolder(this)
{
}

CTower::~CTower()
{
    theSwitchboard.Broadcast(new TypedMessage<std::pair<Vector2, Vector2>>("Explosion", std::make_pair(this->GetPosition(), this->GetSize())));
}

void CTower::Update(float dt)
{
    CBasicUnit::Update(dt);
    CWeaponHolder::Update(dt);
}

void CTower::Render()
{
    CBasicUnit::Render();
    CWeaponHolder::Render();
}

void CTower::Attack()
{
    if (theWorld.IsPhysicsRunning() && AttackAvailiable())
    {
        m_gun->PlaySpriteAnimation(0.04f, SAT_OneShot, 0, 5);
        CBasicUnit::Attack();
        CWeaponHolder::Attack();
    }
}

void CTower::SetSideOfConflict(ESideIdentificator id)
{
    CWeaponHolder::SetSideOfConflict(id);
    CBasicUnit::SetSideOfConflict(id);
}
