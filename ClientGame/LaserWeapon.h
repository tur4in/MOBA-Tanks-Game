#pragma once
#include "BasicWeapon.h"
class CLaserWeapon :
    public CBasicWeapon
{
public:
    CLaserWeapon(ESideIdentificator side = ESideIdentificator::Neutrals, bool ownedByPlayer = true);
    virtual void Attack() override;
    virtual void Render() override;
    virtual void Update(float dt) override;
    void SetRayLength(float length);

private:
    void DrawRay();

    Actor m_ray;
    float m_rayRenderTime;
    float m_laserRayLength;
    Vector2 m_rayBegin;
    Vector2 m_rayEnd;
    bool m_redraw;
};

