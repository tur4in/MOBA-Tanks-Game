#pragma once

#include "stdafx.h"
#include "PlaySides.h"

class CBullet :
    public PhysicsActor
{
public:
    CBullet(ESideIdentificator side = ESideIdentificator::Neutrals, bool ownedByPlayer = false);
    ~CBullet();

    void Shoot(Vector2 position, float rotation);
    bool IsActive();
    virtual void Render() override;
    virtual void Update(float dt) override;
    virtual void OnCollisionStart(PhysicsActor* ptr) override;

    void SetDamage(size_t damage);
    size_t GetDamage();
    void SetSideOfConflict(ESideIdentificator side);
    void SetOwnedByPlayer(bool flag);

private:
    void deletePhysicalBody();
    bool m_isActive;
    bool m_ownedByPlayer;
    ESideIdentificator m_side;
    size_t m_damage;
    float m_lifeTime;
    float m_attackRange;
};