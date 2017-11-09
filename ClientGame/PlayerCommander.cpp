#include "stdafx.h"
#include "PlayerCommander.h"
#include "TunedInfo.h"
#include "SessionInfo.h"
#include "LaserWeapon.h"
#include "BurstWeapon.h"
#include "RayCastCallbackAll.h"



CPlayerKeyboardCommander::CPlayerKeyboardCommander()
{
    theSwitchboard.SubscribeTo(this, "MoveForwardKeyBoard");
    theSwitchboard.SubscribeTo(this, "BackwardKeyBoard");
    theSwitchboard.SubscribeTo(this, "TurnLeftKeyBoard");
    theSwitchboard.SubscribeTo(this, "TurnRightKeyBoard");
    theSwitchboard.SubscribeTo(this, "StopKeyboardForwardMovement");
    theSwitchboard.SubscribeTo(this, "StopKeyboardBackwardMovement");
    theSwitchboard.SubscribeTo(this, "StopKeyboardLeftRotation");
    theSwitchboard.SubscribeTo(this, "StopKeyboardRightRotation");
}

void CPlayerKeyboardCommander::ReceiveMessage(Message* m)
{
    CPlayerCommander::ReceiveMessage(m);
    std::shared_ptr<CTank> player = m_player.lock();
    if (m_player.expired())
    {
        return;
    }
    if (m->GetMessageName() == "MoveForwardKeyBoard")
    {
        player->MoveForward(true);
    }
    else if (m->GetMessageName() == "BackwardKeyBoard")
    {
        player->MoveBackward(true);
    }
    else if (m->GetMessageName() == "TurnLeftKeyBoard")
    {
        player->RotateLeft(true);
    }
    else if (m->GetMessageName() == "TurnRightKeyBoard")
    {
        player->RotateRight(true);
    }
    else if (m->GetMessageName() == "StopKeyboardForwardMovement")
    {
        player->MoveForward(false);
    }
    else if (m->GetMessageName() == "StopKeyboardBackwardMovement")
    {
        player->MoveBackward(false);
    }
    else if (m->GetMessageName() == "StopKeyboardLeftRotation")
    {
        player->RotateLeft(false);
    }
    else if (m->GetMessageName() == "StopKeyboardRightRotation")
    {
        player->RotateRight(false);
    }
}

void CPlayerKeyboardCommander::MouseMotionEvent(Vec2i screenCoordinates)
{
    m_mouseCoords = screenCoordinates;
}

void CPlayerKeyboardCommander::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button)
{
    std::shared_ptr<CTank> player = m_player.lock();
    theSwitchboard.Broadcast(new Message("AttackKeyBoard"));
    if (m_player.expired())
    {
        return;
    }
    player->Attack();
}



void CPlayerKeyboardCommander::Update(std::list<std::shared_ptr<CBasicUnit>>&)
{
    std::shared_ptr<CTank> player = m_player.lock();
    if (m_player.expired())
    {
        return;
    }
    Vector2 playerPosition = player->GetPosition();
    Vector2 viewDirection = MathUtil::ScreenToWorld(m_mouseCoords) - playerPosition;
    float viewRotation = MathUtil::AngleFromVector(viewDirection);
    player->RotateTower(viewRotation);
    if (theInput.IsKeyDown('w') && m_playerMoveDirection.Y < 10)
    {
        m_playerMoveDirection += Vector2(0, 1);
    }
    else if (!theInput.IsKeyDown('w') && m_playerMoveDirection.Y > 0)
    {
        m_playerMoveDirection -= Vector2(0, 1);
    }
    if (theInput.IsKeyDown('s') && m_playerMoveDirection.Y > -10)
    {
        m_playerMoveDirection += Vector2(0, -1);
    }
    else if (!theInput.IsKeyDown('s') && m_playerMoveDirection.Y < 0)
    {
        m_playerMoveDirection -= Vector2(0, -1);
    }
    if (theInput.IsKeyDown('a') && m_playerMoveDirection.X > -10)
    {
        m_playerMoveDirection += Vector2(-1, 0);
    }
    else if (!theInput.IsKeyDown('a') && m_playerMoveDirection.X < 0)
    {
        m_playerMoveDirection -= Vector2(-1, 0);
    }
    if (theInput.IsKeyDown('d') && m_playerMoveDirection.X < 10)
    {
        m_playerMoveDirection += Vector2(1, 0);
    }
    else if (!theInput.IsKeyDown('d') && m_playerMoveDirection.X > 0)
    {
        m_playerMoveDirection -= Vector2(1, 0);
    }
    player->Move(m_playerMoveDirection);
}

bool CPlayerKeyboardCommander::HasCommandable()
{
    return !m_player.expired();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

CPlayerControllerCommander::CPlayerControllerCommander()
{
    theSwitchboard.SubscribeTo(this, "AttackPad");
}

void CPlayerControllerCommander::ReceiveMessage(Message* m)
{
    CPlayerCommander::ReceiveMessage(m);
    std::shared_ptr<CTank> player = m_player.lock();
    if (m_player.expired())
    {
        return;
    }
    if (m->GetMessageName() == "AttackPad")
    {
        player->Attack();
    }
}

void CPlayerControllerCommander::Update(std::list<std::shared_ptr<CBasicUnit>>& gameUnits)
{
    std::shared_ptr<CTank> player = m_player.lock();
    if (m_player.expired() || !theController.IsConnected())
    {
        return;
    }
    auto leftStick = theController.GetLeftThumbstick();
    auto rightStick = theController.GetRightThumbstick();
    if (thePrefs.GetInt("InvertAxis", "RightPad"))
    {
        rightStick.Y = -rightStick.Y;
    }
    if (thePrefs.GetInt("InvertAxis", "LeftPad"))
    {
        leftStick.Y = -leftStick.Y;
    }
    m_player.lock()->SetTowerRotation(Vector2(rightStick.X, rightStick.Y).Length() / 32768 * 200);
    Vector2 correctedValue = CorrectDirectionOfTower(gameUnits, Vector2(rightStick.X, rightStick.Y));
    player->Move(leftStick);
    if (correctedValue.X != 0)
    {
        float viewRotation = MathUtil::AngleFromVector(correctedValue);
        player->RotateTower(viewRotation);
    }
    player->SetEnginePower(Vector2(leftStick).Length() / Vector2(32768, 32768).Length());
}

bool CPlayerControllerCommander::HasCommandable()
{
    return !m_player.expired();
}

Vector2 CPlayerControllerCommander::CorrectDirectionOfTower(std::list<std::shared_ptr<CBasicUnit>>& gameUnits, Vector2& rightStick)
{
    Vector2 tankPosition;
    Vector2 unitPosition;
    Vector2 resultDirection = rightStick;
    Vector2 relativePositionOfUnit;
    tankPosition = m_player.lock()->GetPosition();
    float minAngleBtwnVectors = 0.07f;
    for (auto it = gameUnits.begin(); it != gameUnits.end(); ++it)
    {
        if ((*it)->GetSideOfConflict() == m_player.lock()->GetSideOfConflict())
        {
            continue;
        }
        unitPosition = it->get()->GetPosition();
        relativePositionOfUnit = unitPosition - tankPosition;
        auto rcallback = std::make_unique<CRayCastCallbackAll>();
        theWorld.GetPhysicsWorld().RayCast(rcallback.get(), b2Vec2(tankPosition.X, tankPosition.Y), b2Vec2(unitPosition.X, unitPosition.Y));
        std::sort(rcallback->m_intersections.begin(), rcallback->m_intersections.end());
        bool shouldBeCorrected = true;
        for (auto rit = rcallback->m_intersections.rbegin(); rit != rcallback->m_intersections.rend(); rit++)
        {
            if (rit->m_fixture->GetBody()->GetUserData() == it->get())
            {
                break;
            }
            else if (!(PhysicsActor*)rit->m_fixture->GetBody()->GetFixtureList()->IsSensor() &&
                !dynamic_cast<CBasicUnit*>((PhysicsActor*)rit->m_fixture->GetBody()->GetUserData()) &&
                !dynamic_cast<CBullet*>((PhysicsActor*)rit->m_fixture->GetBody()->GetUserData()))
            {
                shouldBeCorrected = false;
                break;
            }
        }
        if (shouldBeCorrected && relativePositionOfUnit.Length() < theTuning.GetFloat("AttackRange"))
        {
            float angle = abs(MathUtil::AngleFromVectors(relativePositionOfUnit, rightStick)) / relativePositionOfUnit.Length();
            if (std::dynamic_pointer_cast<CTank>(*it))
            {
                angle /= 2;
            }
            if (angle < minAngleBtwnVectors)
            {
                resultDirection = relativePositionOfUnit;
                minAngleBtwnVectors = MathUtil::AngleFromVectors(relativePositionOfUnit, rightStick) / relativePositionOfUnit.Length();
            }
        }
    }
    m_prevDirrection = resultDirection;
    return resultDirection;
}

CPlayerCommander::CPlayerCommander()
{
    SetSubscriptions();
}

void CPlayerCommander::ReceiveMessage(Message * m)
{
    if (m->GetMessageName() == thePrefs.GetString("StoreMessages", "RegularGun") ||
        m->GetMessageName() == thePrefs.GetString("StoreMessages", "LaserGun") ||
        m->GetMessageName() == thePrefs.GetString("StoreMessages", "MachineGun"))
    {
        auto table = thePrefs.GetTable("StoreMessages");
        decltype(table)::iterator it;
        auto filter = [&](auto p)
        {
            return p.second._string == m->GetMessageName();
        };
        if (static_cast<TypedMessage<ESideIdentificator>*>(m)->GetValue() == m_side &&
            (it = std::find_if(table.begin(), table.end(), filter)) != table.end())
        {
            theSession[m_side]->SetTankWeaponType(it->first);
            UpdateWeapon();
        }
    }
    if (m->GetMessageName() == thePrefs.GetString("StoreMessages", "HealthUp"))
    {
        if (static_cast<TypedMessage<ESideIdentificator>*>(m)->GetValue() == m_side)
        {
            theSession[m_side]->SetTankHP(theSession[m_side]->GetTankHP() + theTuning.GetInt("TankHPUpgrade"));
            UpdateHP();
        }
    }
    if (m->GetMessageName() == thePrefs.GetString("StoreMessages", "SpeedUpTank"))
    {
        if (static_cast<TypedMessage<ESideIdentificator>*>(m)->GetValue() == m_side)
        {
            theSession[m_side]->SetTankSpeed(theSession[m_side]->GetTankSpeed() + theTuning.GetFloat("TankSpeedUpgrade"));
            UpdateSpeed();
        }
    }
    if (m->GetMessageName() == thePrefs.GetString("StoreMessages", "GunPowerUp"))
    {
        if (static_cast<TypedMessage<ESideIdentificator>*>(m)->GetValue() == m_side)
        {
            theSession[m_side]->SetBasicTankDamage(theSession[m_side]->GetBasicTankDamage() + theTuning.GetInt("TankDamageUpgrade"));
            UpdateBasicDamage();
        }
    }
}

void CPlayerCommander::SetTank(std::weak_ptr<CTank> tank)
{
    m_player = tank;
    m_side = m_player.lock()->GetSideOfConflict();
}

void CPlayerCommander::SetSubscriptions()
{
    theSwitchboard.SubscribeTo(this, thePrefs.GetString("StoreMessages", "RegularGun"));
    theSwitchboard.SubscribeTo(this, thePrefs.GetString("StoreMessages", "LaserGun"));
    theSwitchboard.SubscribeTo(this, thePrefs.GetString("StoreMessages", "MachineGun"));
    theSwitchboard.SubscribeTo(this, thePrefs.GetString("StoreMessages", "HealthUp"));
    theSwitchboard.SubscribeTo(this, thePrefs.GetString("StoreMessages", "SpeedUpTank"));
    theSwitchboard.SubscribeTo(this, thePrefs.GetString("StoreMessages", "GunPowerUp"));
}

void CPlayerCommander::UpdateWeapon()
{
    if (auto ptr = m_player.lock())
    {
        auto weapon = CBasicWeapon::Create(theSession[ptr->GetSideOfConflict()]->GetTankWeaponType(), ptr->GetSideOfConflict());
        TunedInfo::SetProps(weapon);
        ptr->SetWeapon(weapon);
        ptr->GetWeapon()->SetOwnedByPlayer(true);
    }
}

void CPlayerCommander::UpdateHP()
{
    if (auto ptr = m_player.lock())
    {
        ptr->SetMaxHP(theSession[m_side]->GetTankHP());
    }
}

void CPlayerCommander::UpdateSpeed()
{
    if (auto ptr = m_player.lock())
    {
        ptr->SetMoveSpeed(theSession[m_side]->GetTankSpeed());
    }
}

void CPlayerCommander::UpdateBasicDamage()
{
    if (auto ptr = m_player.lock())
    {
        ptr->GetWeapon()->SetDamage(theSession[m_side]->GetBasicTankDamage() * theTuning.GetInt(theSession[m_side]->GetTankWeaponType()));
    }
}
