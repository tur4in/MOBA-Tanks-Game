#include "stdafx.h"
#include "LaserWeapon.h"
#include "RayCastCallbackAll.h"
#include "ParticleSystem.h"
#include "BasicUnit.h"
#include "StatManager.h"

CLaserWeapon::CLaserWeapon(ESideIdentificator side, bool ownedByPlayer) : CBasicWeapon(side, ownedByPlayer)
{
    m_redraw = false;
    m_laserRayLength = theTuning.GetFloat("AttackRange");
    m_ray.SetColor(1, 0, 0);
    m_ray.SetSize(m_laserRayLength, 0.05f);
    m_rayRenderTime = 0;
}

void CLaserWeapon::Attack()
{
    m_rayBegin = GetPosition() + Vector2(cos(MathUtil::ToRadians(GetRotation() + 90)) * GetSize().Y,
        sin(MathUtil::ToRadians(GetRotation() + 90)) * GetSize().Y) / 2;
    m_rayEnd = m_rayBegin + Vector2(cos(MathUtil::ToRadians(GetRotation() + 90)), sin(MathUtil::ToRadians(GetRotation() + 90))) * m_laserRayLength;
    auto rcallback = std::make_unique<CRayCastCallbackAll>();
    theWorld.GetPhysicsWorld().RayCast(rcallback.get(), b2Vec2(m_rayBegin.X, m_rayBegin.Y), b2Vec2(m_rayEnd.X, m_rayEnd.Y));
    std::sort(rcallback->m_intersections.begin(), rcallback->m_intersections.end());
    for (auto rit = rcallback->m_intersections.rbegin(); rit != rcallback->m_intersections.rend(); rit++)
    {
        auto uptr = dynamic_cast<CBasicUnit*>(((PhysicsActor*)rit->m_fixture->GetBody()->GetUserData()));
        if (uptr && uptr->GetSideOfConflict() != m_side)
        {
            theSwitchboard.Broadcast(new Message("BoomLaser"));
            uptr->TakeDamage(m_damage);
            ParticleSystem::CreateExplosion(uptr->GetPosition());
            if (m_ownedByPlayer && !uptr->IsAlive())
            {
                theStatistic.ReceiveInfo(m_side, uptr->GetBounty());
                auto killMessage = new TypedMessage<std::pair<ESideIdentificator, size_t>>("PlayerKilledUnit", std::make_pair(m_side, uptr->GetBounty()), this);
                theSwitchboard.Broadcast(killMessage);
            }
        }
        else if (!uptr)
        {
            m_rayEnd.X = rit->m_point.x;
            m_rayEnd.Y = rit->m_point.y;
            break;
        }
    }
    theSwitchboard.Broadcast(new Message("LaserSound"));
    DrawRay();
}

void CLaserWeapon::Render()
{
    Actor::Render();
    if (m_redraw)
    {
        m_ray.Render();
    }
}

void CLaserWeapon::Update(float dt)
{
    m_ray.Update(dt);
    if (m_redraw)
    {
        if (m_rayRenderTime < 0.5)
        {
            m_rayRenderTime += dt;
        }
        else
        {
            m_rayRenderTime = 0;
            m_redraw = true;
        }
    }
}

void CLaserWeapon::SetRayLength(float length)
{
    m_laserRayLength = length;
}

void CLaserWeapon::DrawRay()
{
    m_ray.SetRotation(GetRotation() + 90);
    float rayLength = (m_rayBegin - m_rayEnd).Length();
    m_ray.SetSize(Vector2(rayLength, 0.05f));
    m_ray.SetPosition(m_rayBegin + Vector2(cos(MathUtil::ToRadians(m_ray.GetRotation())), sin(MathUtil::ToRadians(m_ray.GetRotation()))) * rayLength / 2);
    m_ray.SetColor(1.0f, 0.0f, 0.0f);
    m_ray.ChangeColorTo(Color(0, 0, 0, 0), 0.5, true);
    m_redraw = true;
}
