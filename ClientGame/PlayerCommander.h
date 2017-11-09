#pragma once

#include "stdafx.h"

#include "Tank.h"
#include "BasicCommander.h"
#include "GamepadStoreInput.h"

class CPlayerCommander :
    public CBasicCommander
{
public:
    CPlayerCommander();
    virtual void ReceiveMessage(Message* m) override;
    virtual void SetTank(std::weak_ptr<CTank>);
    void SetSubscriptions();

protected:
    void UpdateWeapon();
    void UpdateHP();
    void UpdateSpeed();
    void UpdateBasicDamage();

protected:
    std::weak_ptr<CTank> m_player;
    ESideIdentificator m_side;
};

class CPlayerKeyboardCommander :
    public CPlayerCommander,
    public MouseListener
{
public:
    CPlayerKeyboardCommander();
    ~CPlayerKeyboardCommander() = default;
    virtual void ReceiveMessage(Message* m) override;
    virtual void MouseMotionEvent(Vec2i screenCoordinates) override;
    virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button) override;
    virtual void Update(std::list<std::shared_ptr<CBasicUnit>>&) override;
    virtual void Command(CBasicUnit&) override {};
    virtual void AddCommandable(std::weak_ptr<CBasicUnit>) override {};
    virtual bool HasCommandable() override;

private:
    Vec2i m_mouseCoords = Vec2i(1000, 0);
    Vector2 m_playerMoveDirection;
};

class CPlayerControllerCommander :
    public CPlayerCommander
{
public:
    CPlayerControllerCommander();
    ~CPlayerControllerCommander() = default;
    virtual void ReceiveMessage(Message* m) override;
    virtual void Update(std::list<std::shared_ptr<CBasicUnit>>&) override;
    virtual void Command(CBasicUnit&) override {};
    virtual void AddCommandable(std::weak_ptr<CBasicUnit>) override {};
    virtual bool HasCommandable() override;

private:
    Vector2 CorrectDirectionOfTower(std::list<std::shared_ptr<CBasicUnit>>& gameUnits, Vector2& leftStick);

private:
    Vector2 m_prevDirrection;
};

