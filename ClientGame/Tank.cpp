#include "stdafx.h"
#include "Tank.h"

CTank::CTank() :
    CWeaponHolder(this)
{
}

CTank::~CTank()
{
}

void CTank::Update(float dt)
{
    CUnit::Update(dt);
    CWeaponHolder::Update(dt);
}

void CTank::Render()
{
    CUnit::Render();
    CWeaponHolder::Render();
}

void CTank::Attack()
{
    if (theWorld.IsPhysicsRunning() && AttackAvailiable())
    {
        CUnit::Attack();
        CWeaponHolder::Attack();
        theSwitchboard.Broadcast(new Message("AttackFromTank"));
    }
}

void CTank::SetSideOfConflict(ESideIdentificator id)
{
    CWeaponHolder::SetSideOfConflict(id);
    CBasicUnit::SetSideOfConflict(id);
    ResetHighlight();
    std::string idstr = std::to_string((int)id + 1);
    SetColor(
        theTuning.GetFloat("Team" + idstr + "ColorR"),
        theTuning.GetFloat("Team" + idstr + "ColorG"),
        theTuning.GetFloat("Team" + idstr + "ColorB"));
    GetWeapon()->SetColor(
        theTuning.GetFloat("Team" + idstr + "ColorR"),
        theTuning.GetFloat("Team" + idstr + "ColorG"),
        theTuning.GetFloat("Team" + idstr + "ColorB"));
}

void CTank::TakeDamage(size_t damage)
{
    CUnit::TakeDamage(damage);
    if (!IsAlive())
    {
        theSwitchboard.Broadcast(new TypedMessage<std::pair<Vector2, Vector2>>("Explosion", std::make_pair(this->GetPosition(), this->GetSize())));
        theSwitchboard.Broadcast(new TypedMessage<ESideIdentificator>("PlayerDied", GetSideOfConflict()));
    }
}
