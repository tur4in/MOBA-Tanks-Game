#pragma once

#include "stdafx.h"
#include "Unit.h"

enum class EMobState {
    None,
    Move,
    Fight
};

class CMob :
    public CUnit
{
public:
    CMob();
    virtual ~CMob();

    virtual void Update(float dt) override;
    virtual void Render() override;

    virtual void SetDestination(Vector2);
    void SetPath(Vector2List const& path);
    void SetTarget(std::weak_ptr<CBasicUnit> target);
    virtual void Reset();
    EMobState GetState() const;

protected:
    virtual void MoveToPoint(Vector2 pos);
    virtual void AttackTarget(std::shared_ptr<CBasicUnit>);
    virtual void GetReadyToMove();
    virtual void MoveAlongPath();
    virtual void GetReadyToFight();
    virtual void FightTarget();
    virtual void UpdatePathOnCollision();
    virtual void OnCollisionStart(PhysicsActor* ptr) override;

protected:
    EMobState m_currentState;
    Vector2 m_destination;
    Vector2List m_path;
    decltype(m_path)::iterator m_nextPoint;
    std::weak_ptr<CBasicUnit> m_target;
    bool m_collidedRecently;
    float m_timeFromLastPathChange = 0;
};

