#include "stdafx.h"
#include "Unit.h"

CUnit::CUnit() :
    m_enginePower(1.0f)
{
}

CUnit::~CUnit()
{
}

void CUnit::Move(Vector2 direction)
{
    m_moveDirection = direction;
}

void CUnit::MoveForward(bool set /*= true*/)
{
    m_moveForward = set;
}

void CUnit::MoveBackward(bool set /*= true*/)
{
    m_moveBackward = set;
}

void CUnit::RotateRight(bool set /*= true*/)
{
    m_rotateRigth = set;
}

void CUnit::RotateLeft(bool set /*= true*/)
{
    m_rotateLeft = set;
}

void CUnit::Update(float dt)
{
    CBasicUnit::Update(dt);
    if (GetSideOfConflict() == ESideIdentificator::Side1 && thePrefs.GetInt("Settings", "AdvancedKeyboardMovement"))
    {
        AdvancedMovement(dt);
    }
    else
    {
        SimpleMovement(dt);
    }
}

float CUnit::GetMoveSpeed() const
{
    return m_moveSpeed;
}

void CUnit::SetMoveSpeed(float speed)
{
    m_moveSpeed = speed;
}

void CUnit::SetEnginePower(float percents)
{
    m_enginePower = MathUtil::Clamp(percents, 0.f, 1.f);
}

void CUnit::SetRotationSpeed(float rotSpeed)
{
    m_rotationSpeed = rotSpeed;
}

void CUnit::SimpleMovement(float dt)
{
    float rot = MathUtil::ToRadians(GetRotation()) + MathUtil::PiOver2;
    Vector2 moveDirection = m_moveDirection;
    UpdateMovespeed();
    if (moveDirection.LengthSquared())
    {
        float targetMoveSpeed = m_moveSpeed * m_enginePower;
        float moveRot = MathUtil::AngleFromVector(moveDirection);
        if (abs(MathUtil::DeltaAngle(moveRot, rot)) > MathUtil::PiOver2 + MathUtil::PiOver4 / 2)
        {
            targetMoveSpeed = -targetMoveSpeed;
            moveDirection = -moveDirection;
            moveRot = MathUtil::AngleFromVector(moveDirection);
        }
        if (MathUtil::DeltaAngle(moveRot, rot) > MathUtil::ToRadians(m_rotationSpeed))
        {
            _physBody->SetAngularVelocity(-m_rotationSpeed);
        }
        else if (MathUtil::DeltaAngle(moveRot, rot) < MathUtil::ToRadians(-m_rotationSpeed))
        {
            _physBody->SetAngularVelocity(m_rotationSpeed);
        }
        else
        {
            UpdateMovespeed(targetMoveSpeed, dt);
            GetBody()->SetTransform(GetBody()->GetPosition(), atan2(moveDirection.Y, moveDirection.X) - MathUtil::PiOver2);
        }
    }
    else
    {
        UpdateMovespeed(0, dt);
        _physBody->SetAngularVelocity(0);
    }
    _physBody->SetLinearVelocity(b2Vec2(cos(rot) * m_currentMoveSpeed, sin(rot) * m_currentMoveSpeed));
}

void CUnit::AdvancedMovement(float dt)
{
    float rot = MathUtil::ToRadians(GetRotation()) + MathUtil::PiOver2;
    UpdateMovespeed();
    UpdateMovespeed(GetAdvancedTargetMS(), dt);
    _physBody->SetLinearVelocity(b2Vec2(cos(rot) * m_currentMoveSpeed, sin(rot) * m_currentMoveSpeed));
    UpdateAngularVelocityAdvanced();
}

void CUnit::UpdateAngularVelocityAdvanced()
{
    if (m_rotateLeft && m_rotateRigth)
    {
        _physBody->SetAngularVelocity(0);
    }
    else if (m_rotateLeft)
    {
        if (m_moveBackward && !m_moveForward)
        {
            _physBody->SetAngularVelocity(-m_rotationSpeed);
        }
        else
        {
            _physBody->SetAngularVelocity(m_rotationSpeed);
        }
    }
    else if (m_rotateRigth)
    {
        if (m_moveBackward && !m_moveForward)
        {
            _physBody->SetAngularVelocity(m_rotationSpeed);
        }
        else
        {
            _physBody->SetAngularVelocity(-m_rotationSpeed);
        }
    }
    else
    {
        _physBody->SetAngularVelocity(0);
    }
}

float CUnit::GetAdvancedTargetMS()
{
    if (m_moveForward && m_moveBackward)
    {
        return 0;
    }
    else if (m_moveForward)
    {
        return m_moveSpeed * m_enginePower;
    }
    else if (m_moveBackward)
    {
        return -m_moveSpeed * m_enginePower;
    }
    else
    {
        return 0;
    }
}

void CUnit::UpdateMovespeed()
{
    if (m_currentMoveSpeed >= 0)
    {
        m_currentMoveSpeed = _physBody->GetLinearVelocity().Length();
    }
    else
    {
        m_currentMoveSpeed = -_physBody->GetLinearVelocity().Length();
    }
}

void CUnit::UpdateMovespeed(float ms, float dt)
{
    float acceleration = m_moveSpeed * dt * 3;
    if (m_currentMoveSpeed > ms + acceleration)
    {
        m_currentMoveSpeed -= acceleration;
    }
    else if (m_currentMoveSpeed < ms - acceleration)
    {
        m_currentMoveSpeed += acceleration;
    }
    else
    {
        m_currentMoveSpeed = ms;
    }
    m_currentMoveSpeed = MathUtil::Clamp(m_currentMoveSpeed, -m_moveSpeed, m_moveSpeed);
}
