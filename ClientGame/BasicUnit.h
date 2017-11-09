#pragma once

#include "stdafx.h"
#include "BasicWeapon.h"
#include "Priority.h"
#include "BasicPriority.h"
#include "HealthBar.h"

class CBasicUnit : public PhysicsActor
{
public:
    explicit CBasicUnit();
    virtual ~CBasicUnit() = default;

    virtual void TakeDamage(size_t damage);
    virtual void Heal(size_t heal);
    virtual void Attack();
    virtual void Update(float dt) override;

    size_t GetMaxHP() const;
    float GetDetectDist() const;
    float GetAttackDist() const;
    size_t GetCurrentHP() const;
    size_t GetAttackForce() const;
    float GetAttackDelay() const;

    void SetMaxHP(size_t hp);
    void SetDetectDist(float);
    void SetAttackDist(float);
    void SetCurrentHP(size_t hp);
    void SetAttackForce(size_t damage);
    void SetAttackDelay(float seconds);

    virtual bool IsAlive() const;
    virtual bool AttackAvailiable() const;

    ESideIdentificator GetSideOfConflict() const;
    void SetSideOfConflict(ESideIdentificator id);
    template<typename T>
    void SetPriority()
    {
        m_priority.reset(new CPriority<T>(this));
    }
    CBasicPriority const& GetPriority() const;

    void RenderHighlight();
    void ResetHighlight();
    size_t GetBounty() const;
    void SetBounty(size_t bounty);
    virtual void RenderHealthBar();

private:
    size_t m_attackForce;
    float m_attackDelay;
    float m_timeFromLastAttack;
    size_t m_bounty;
    float m_detectDist;
    float m_attackDist;
    Actor m_highlight;
    CHealthBar m_hp;
    ESideIdentificator m_side;
    std::unique_ptr<CBasicPriority> m_priority;
};