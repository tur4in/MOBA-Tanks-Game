#pragma once

#include "stdafx.h"
#include "BasicUnit.h"

class CUnit :
    public CBasicUnit
{
public:
    CUnit();
    ~CUnit();

    virtual void Move(Vector2 direction);
    virtual void Update(float dt) override;
    virtual void MoveForward(bool set = true);
    virtual void MoveBackward(bool set = true);
    virtual void RotateRight(bool set = true);
    virtual void RotateLeft(bool set = true);

    float GetMoveSpeed() const;
    void SetMoveSpeed(float speed);
    void SetEnginePower(float percents);
    void SetRotationSpeed(float rotSpeed);

private:
    void SimpleMovement(float dt);
    void AdvancedMovement(float dt);

    void UpdateAngularVelocityAdvanced();
    float GetAdvancedTargetMS();

    void UpdateMovespeed(float ms, float dt);
    void UpdateMovespeed();

    float m_rotationSpeed;
    float m_moveSpeed;

    Vector2 m_moveDirection;
    float m_currentMoveSpeed;
    float m_enginePower;

    bool m_moveForward = false;
    bool m_moveBackward = false;
    bool m_rotateRigth = false;
    bool m_rotateLeft = false;
};

