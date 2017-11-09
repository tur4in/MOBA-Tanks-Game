#pragma once

#include "stdafx.h"
#include "BasicWeapon.h"
#include "BasicUnit.h"
#include "PlaySides.h"

class CWeaponHolder
{
public:
    CWeaponHolder(const CBasicUnit* unitPtr);
    virtual ~CWeaponHolder();
    void RotateTower(float direction);
    virtual void Update(float dt);
    virtual void Render();
    const float GetTowerRotation() const;
    virtual void Attack();
    void SetWeapon(std::shared_ptr<CBasicWeapon> weapon);
    std::shared_ptr<CBasicWeapon> GetWeapon();
    virtual void SetSideOfConflict(ESideIdentificator side);
    virtual void SetTowerRotation(float towerRotationSpeed);
    void RenderBeem();
    void SetBeem(bool flag);


protected:
    float m_towerRotationSpeed;
    float m_towerTargetDirection;

    bool m_beemDraw;
    Actor m_beem;
    Vector2 m_beemStart;
    Vector2 m_beemEnd;

    std::shared_ptr<CBasicWeapon> m_gun;
    CBasicUnit const* m_unitPtr;
};