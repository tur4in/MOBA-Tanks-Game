#include "stdafx.h"
#include "Mob.h"
#include "RayCastCallbackClosest.h"
#include "RayCastCallbackAll.h"
#include "PathFinding.h"
#include "ParticleSystem.h"
#include "TakeFlag.h"

CMob::CMob() :
    m_collidedRecently(false),
    m_currentState(EMobState::None),
    m_timeFromLastPathChange(0)
{
}

CMob::~CMob()
{
}

void CMob::Update(float dt)
{
    Actor::Update(dt);
    CBasicUnit::Update(dt);
    GetBody()->SetAngularVelocity(0);
    switch (m_currentState)
    {
    case EMobState::Move:
        MoveAlongPath();
        break;
    case EMobState::Fight:
        FightTarget();
        break;
    default:
        break;
    }
    m_timeFromLastPathChange += dt;
}

void CMob::Render()
{
    Actor::Render();
}

void CMob::SetDestination(Vector2 dest)
{
    Reset();
    m_destination = dest;
    GetReadyToMove();
}

void CMob::SetPath(Vector2List const & path)
{
    Reset();
    m_path = path;
    m_nextPoint = m_path.begin();
    m_collidedRecently = false;
    m_currentState = EMobState::Move;
}

void CMob::SetTarget(std::weak_ptr<CBasicUnit> target)
{
    Reset();
    m_target = target;
    GetReadyToFight();
    m_currentState = EMobState::Fight;
}

void CMob::Reset()
{
    PhysicsActor::GetBody()->SetLinearVelocity(b2Vec2(0, 0));
    m_path.clear();
    m_target.reset();
    m_currentState = EMobState::None;
}

EMobState CMob::GetState() const
{
    return m_currentState;
}

void CMob::MoveToPoint(Vector2 pos)
{
    Vector2 distance = pos - GetPosition();
    Vector2 vel = Vector2::Normalize(distance);
    GetBody()->SetTransform(GetBody()->GetPosition(), atan2(vel.Y, vel.X) - MathUtil::PiOver2);
    vel *= GetMoveSpeed();
    PhysicsActor::GetBody()->SetLinearVelocity(b2Vec2(vel.X, vel.Y));
}

void CMob::AttackTarget(std::shared_ptr<CBasicUnit> target)
{
    target->TakeDamage(GetAttackForce());
    TakeDamage(GetMaxHP());
    ParticleSystem::CreateExplosion(GetPosition(), 0.2f);
}

void CMob::GetReadyToMove()
{
    m_path = thePath.FindPath(GetPosition(), m_destination, true);
    m_nextPoint = m_path.begin();
    m_collidedRecently = false;
    m_currentState = EMobState::Move;
}

void CMob::MoveAlongPath()
{
    if (m_nextPoint != m_path.end() && Vector2::DistanceSquared(*m_nextPoint, GetPosition()) < theTuning.GetFloat("PointChangeDistance"))
    {
        m_nextPoint++;
        if (m_nextPoint != m_path.end())
        {
            MoveToPoint(*m_nextPoint);
        }
        else
        {
            Reset();
        }
    }
    else
    {
        if (m_nextPoint != m_path.end())
        {
            MoveToPoint(*m_nextPoint);
        }
    }
}

void CMob::GetReadyToFight()
{

}

void CMob::FightTarget()
{
    auto target = m_target.lock();
    if (!m_target.expired())
    {
        auto rcallback = std::make_unique<CRayCastCallbackAll>();
        theWorld.GetPhysicsWorld().RayCast(rcallback.get(), b2Vec2(GetPosition().X, GetPosition().Y), b2Vec2(target->GetPosition().X, target->GetPosition().Y));
        std::sort(rcallback->m_intersections.begin(), rcallback->m_intersections.end());
        for (auto rit = rcallback->m_intersections.rbegin(); rit != rcallback->m_intersections.rend(); rit++)
        {
            if (rit->m_fixture->GetBody()->GetUserData() == target.get())
            {
                break;
            }
            else if (!(PhysicsActor*)rit->m_fixture->GetBody()->GetFixtureList()->IsSensor() &&
                !dynamic_cast<CBasicUnit*>((PhysicsActor*)rit->m_fixture->GetBody()->GetUserData())
                && !dynamic_cast<CBullet*>((PhysicsActor*)rit->m_fixture->GetBody()->GetUserData()))
            {
                Reset();
                return;
            }
        }
        Vector2 targetDirection = target->GetPosition() - GetPosition();
        if (targetDirection.Length() < GetAttackDist())
        {
            AttackTarget(target);
        }
        else if (targetDirection.Length() < GetDetectDist())
        {
            MoveToPoint(target->GetPosition());
        }
        else
        {
            Reset();
        }
    }
    else
    {
        Reset();
    }
}

void CMob::UpdatePathOnCollision()
{
    if (m_timeFromLastPathChange > 1)
    {
        Vector2List path;
        path = thePath.FindPath(this, m_destination);
        if (!path.empty())
        {
            m_path = path;
            m_nextPoint = m_path.begin();
            m_collidedRecently = true;
        }
        m_timeFromLastPathChange = 0;
    }
}

void CMob::OnCollisionStart(PhysicsActor* ptr)
{
    if (m_currentState == EMobState::Move)
    {
        UpdatePathOnCollision();
    }
}
