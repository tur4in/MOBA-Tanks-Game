#include "stdafx.h"
#include "Bullet.h"
#include "BasicUnit.h"
#include "ParticleSystem.h"
#include "StatManager.h"
#include "TakeFlag.h"

CBullet::CBullet(ESideIdentificator side, bool ownedByPlayer) :
    m_isActive(false),
    m_side(side),
    m_ownedByPlayer(ownedByPlayer),
    m_attackRange(0),
    m_lifeTime(0),
    m_damage(0)
{
}

CBullet::~CBullet()
{

}

void CBullet::Shoot(Vector2 position, float direction)
{
    SetSize(0.0f, 0.0f);
    SetShapeType(PhysicsActor::SHAPETYPE_CIRCLE);
    SetPosition(position);
    this->SetSprite(theTuning.GetString("BulletSprite"));
    SetRotation(direction);
    InitPhysics();
    SetDrawSize(0.2f, 0.2f);
    GetBody()->SetBullet(true);
    float speed = theTuning.GetFloat("BulletSpeed");
    GetBody()->SetLinearVelocity(b2Vec2(cos(direction) * speed, sin(direction) * speed));
    m_lifeTime = 0;
    m_attackRange = theTuning.GetFloat("AttackRange");
    m_isActive = true;
}

bool CBullet::IsActive()
{
    return GetBody() != nullptr;
}

void CBullet::Render()
{
    if (m_isActive)
    {
        PhysicsActor::Render();
    }
}

void CBullet::Update(float dt)
{
    m_lifeTime += dt;
    if (m_isActive && pow(m_lifeTime, 2) * GetBody()->GetLinearVelocity().LengthSquared() > pow(m_attackRange, 2))
    {
        m_isActive = false;
        deletePhysicalBody();
    }
    else if (!m_isActive)
    {
        deletePhysicalBody();
    }
}

void CBullet::OnCollisionStart(PhysicsActor* ptr)
{
    m_isActive = false;
    ParticleSystem::CreateExplosion(GetPosition());
    auto unit = dynamic_cast<CBasicUnit*>(ptr);
    if (unit && m_side != unit->GetSideOfConflict())
    {
        unit->TakeDamage(GetDamage());
        theSwitchboard.Broadcast(new Message("Boom"));
        if (m_ownedByPlayer && !unit->IsAlive())
        {
            if (m_side == ESideIdentificator::Side1)
            {
                theStatistic.ReceiveInfo(ESideIdentificator::Side1, unit->GetBounty());
            }
            else
            {
                theStatistic.ReceiveInfo(ESideIdentificator::Side2, unit->GetBounty());
            }
            std::string messageText = "PlayerKilledUnit";
            TypedMessage<std::pair<ESideIdentificator, size_t>>* killMessage = new TypedMessage<std::pair<ESideIdentificator, size_t>>(messageText, std::make_pair(m_side, unit->GetBounty()), this);
            theSwitchboard.Broadcast(killMessage);
        }
    }
}

void CBullet::deletePhysicalBody()
{
    if (GetBody())
    {
        GetBody()->SetUserData(NULL);
        theWorld.GetPhysicsWorld().DestroyBody(GetBody());
        ResetBody();
    }
}

void CBullet::SetDamage(size_t damage)
{
    m_damage = damage;
}

size_t CBullet::GetDamage()
{
    return m_damage;
}

void CBullet::SetSideOfConflict(ESideIdentificator side)
{
    m_side = side;
}

void CBullet::SetOwnedByPlayer(bool flag)
{
    m_ownedByPlayer = flag;
}
