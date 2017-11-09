#pragma once
#include "stdafx.h"
#include "PlaySides.h"

class CCaptureFlag :
    public PhysicsActor
{
public:
    CCaptureFlag();
    virtual ~CCaptureFlag();
    virtual void ReceiveMessage(Message* message) override;
    virtual void Update(float dt) override;
    virtual void Render() override;
    virtual float GetStatus(ESideIdentificator side);
    virtual void Initialize();
    virtual void OnCollisionStart(PhysicsActor* ptr) override;
    virtual void OnCollisionEnd(PhysicsActor* ptr) override;

private:
    void MoveSomeOwnershipTo(float dt, ESideIdentificator to, ESideIdentificator from);
    void RegularUpdate(float dt);
    void UpdateAnimations(float dt);
    void UpdateOwnershipTime(float dt);

    std::map<ESideIdentificator, std::pair<bool, float>> m_status;
    std::map<ESideIdentificator, Actor> m_anims;
    ESideIdentificator m_owner;
    float m_timeFromLastOwnerChange;
};

