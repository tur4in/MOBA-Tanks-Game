#include "stdafx.h"
#include "WeaponHolder.h"
#include "RayCastCallbackClosest.h"

CWeaponHolder::CWeaponHolder(const CBasicUnit* unitPtr) :
    m_unitPtr(unitPtr),
    m_gun(std::make_shared<CBasicWeapon>()),
    m_beemDraw(false)
{
}

CWeaponHolder::~CWeaponHolder()
{

}

void CWeaponHolder::RotateTower(float direction)
{
    m_towerTargetDirection = direction;
}

void CWeaponHolder::Update(float dt)
{
    m_gun->Update(dt);
    float towerRotation = MathUtil::ToRadians(m_gun->GetRotation()) + MathUtil::PiOver2;
    Vector2 towerOffset(cos(towerRotation) * m_gun->GetSize().Y * 0.25, sin(towerRotation) * m_gun->GetSize().Y * 0.25);
    m_gun->SetPosition(m_unitPtr->GetPosition() + towerOffset);
    float degreeDiff = MathUtil::DeltaAngle(m_towerTargetDirection, towerRotation);
    if (degreeDiff < -0.05)
    {
        m_gun->SetRotation(m_gun->GetRotation() + m_towerRotationSpeed * dt);
    }
    else if (degreeDiff > 0.05)
    {
        m_gun->SetRotation(m_gun->GetRotation() - m_towerRotationSpeed * dt);
    }
    else
    {
        m_gun->SetRotation(MathUtil::ToDegrees(m_towerTargetDirection - MathUtil::PiOver2));
    }
    while (m_gun->GetRotation() > 360)
    {
        m_gun->SetRotation(m_gun->GetRotation() - 360);
    }
    while (m_gun->GetRotation() < -360)
    {
        m_gun->SetRotation(m_gun->GetRotation() + 360);
    }
}

void CWeaponHolder::Render()
{
    if (m_beemDraw)
    {
        RenderBeem();
    }
    m_gun->Render();
}

const float CWeaponHolder::GetTowerRotation() const
{
    return m_gun->GetRotation() + 90;
}

void CWeaponHolder::Attack()
{
    m_gun->Attack();
}

void CWeaponHolder::SetWeapon(std::shared_ptr<CBasicWeapon> weapon)
{
    m_gun = weapon;
    m_gun->SetSideOfConflict(m_unitPtr->GetSideOfConflict());
}

std::shared_ptr<CBasicWeapon> CWeaponHolder::GetWeapon()
{
    return m_gun;
}

void CWeaponHolder::SetSideOfConflict(ESideIdentificator side)
{
    m_gun->SetSideOfConflict(side);
}

void CWeaponHolder::SetTowerRotation(float towerRotationSpeed)
{
    m_towerRotationSpeed = towerRotationSpeed;
}

void CWeaponHolder::RenderBeem()
{
    auto rccallback = std::make_unique<CRayCastCallbackClosest>();
    float towerRotation = MathUtil::ToRadians(m_gun->GetRotation()) + MathUtil::PiOver2;
    Vector2 beemOffset(cos(towerRotation) * theTuning.GetFloat("AttackRange"), sin(towerRotation) * theTuning.GetFloat("AttackRange"));
    Vector2 towerOffset(cos(towerRotation) * m_gun->GetSize().Y * 0.25, sin(towerRotation) * m_gun->GetSize().Y * 0.25);
    Vector2 m_beemEnd = beemOffset + towerOffset + m_gun->GetPosition();
    theWorld.GetPhysicsWorld().RayCast(rccallback.get(), m_unitPtr->GetBody()->GetPosition(), b2Vec2(m_beemEnd.X, m_beemEnd.Y));
    if (rccallback->m_fixture && rccallback->m_fixture->GetBody())
    {
        m_beemEnd = Vector2(rccallback->m_point.x, rccallback->m_point.y);
    }
    m_beemStart = (m_gun->GetPosition());
    m_beem.SetRotation(m_gun->GetRotation() + 90);
    float rayLength = (m_beemStart - m_beemEnd).Length();
    m_beem.SetSize(Vector2(rayLength, 0.03f));
    m_beem.SetPosition(m_beemStart + Vector2(cos(MathUtil::ToRadians(m_beem.GetRotation())), sin(MathUtil::ToRadians(m_beem.GetRotation()))) * rayLength / 2);
    m_beem.SetColor(0.0f, 1.0f, 0.0f, 0.3f);
    m_beem.Render();
}

void CWeaponHolder::SetBeem(bool flag)
{
    m_beemDraw = flag;
}

