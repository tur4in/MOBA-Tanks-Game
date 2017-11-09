#include "stdafx.h"
#include "TakeFlag.h"
#include "Tank.h"
#include "SessionInfo.h"


CCaptureFlag::CCaptureFlag()
{
}

CCaptureFlag::~CCaptureFlag()
{
}

void CCaptureFlag::ReceiveMessage(Message* message)
{
    if (message->GetMessageName() == "PlayerDied")
    {
        auto typeMsg = dynamic_cast<TypedMessage<ESideIdentificator>*>(message);
        m_status[typeMsg->GetValue()].first = false;
        return;
    }
}

void CCaptureFlag::Update(float dt)
{
    dt = dt / theTuning.GetFloat("FlagCaptureTime");
    if (m_status[ESideIdentificator::Side1].first && m_status[ESideIdentificator::Side2].first)
    {
        return;
    }
    else if (m_status[ESideIdentificator::Side1].first)
    {
        MoveSomeOwnershipTo(dt, ESideIdentificator::Side1, ESideIdentificator::Side2);
    }
    else if (m_status[ESideIdentificator::Side2].first)
    {
        MoveSomeOwnershipTo(dt, ESideIdentificator::Side2, ESideIdentificator::Side1);
    }
    else
    {
        RegularUpdate(dt);
    }
    UpdateOwnershipTime(dt);
    UpdateAnimations(dt);
}

void CCaptureFlag::Render()
{
    PhysicsActor::Render();
    for (auto& it : m_anims)
    {
        it.second.SetPosition(GetPosition());
        it.second.Render();
    }
}

float CCaptureFlag::GetStatus(ESideIdentificator side)
{
    return m_status[side].second;
}

void CCaptureFlag::Initialize()
{
    m_timeFromLastOwnerChange = 0;
    SetIsSensor(true);
    SetDensity(0);
    SetDrawShape(ADS_Circle);
    SetSize(theTuning.GetFloat("FlagSize"));
    SetShapeType(PhysicsActor::SHAPETYPE_CIRCLE);
    //SetAlpha(0.2);
    InitPhysics();
    theSwitchboard.SubscribeTo(this, "PlayerDied");
    m_owner = ESideIdentificator::Neutrals;
    m_anims[ESideIdentificator::Side1].SetColor(0, 0, 1, 0.2f);
    m_anims[ESideIdentificator::Side2].SetColor(1, 1, 0, 0.2f);
    for (auto& it : m_anims)
    {
        it.second.SetDrawShape(ADS_Circle);
        it.second.SetSize(0);
    }
}

void CCaptureFlag::OnCollisionStart(PhysicsActor* ptr)
{
    auto unitPtr = dynamic_cast<CTank*>(ptr);
    if (unitPtr)
    {
        m_status[unitPtr->GetSideOfConflict()].first = true;
    }
}

void CCaptureFlag::OnCollisionEnd(PhysicsActor* ptr)
{
    auto unitPtr = dynamic_cast<CTank*>(ptr);
    if (unitPtr)
    {
        m_status[unitPtr->GetSideOfConflict()].first = false;
    }
}

void CCaptureFlag::MoveSomeOwnershipTo(float dt, ESideIdentificator to, ESideIdentificator from)
{
    if (!(m_status[from].second > 0))
    {
        m_status[to].second = MathUtil::Clamp(m_status[to].second + dt, 0.f, 1.f);
        if (m_status[to].second == 1.f)
        {
            m_owner = to;
            m_timeFromLastOwnerChange = 0;
            theSession[m_owner]->SetBasicSpawnDelay(theTuning.GetFloat("FlagSpawnDelay"));
        }
    }
    else
    {
        m_status[from].second = MathUtil::Clamp(m_status[from].second - dt, 0.f, 1.f);
        if (m_status[from].second == 0.f)
        {
            theSession[from]->ResetBasicSpawnDelay();
            m_owner = ESideIdentificator::Neutrals;
            m_timeFromLastOwnerChange = 0;
        }
    }
}

void CCaptureFlag::RegularUpdate(float dt)
{
    for (auto& it : m_status)
    {
        if (it.first != m_owner)
        {
            it.second.second = MathUtil::Clamp(it.second.second - dt, 0.f, 1.f);
        }
        else if (m_timeFromLastOwnerChange > theTuning.GetFloat("FlagRechargeTime"))
        {
            it.second.second = MathUtil::Clamp(it.second.second - dt, 0.f, 1.f);
            if (it.second.second == 0.f)
            {
                m_owner = ESideIdentificator::Neutrals;
                m_timeFromLastOwnerChange = 0;
                theSession[it.first]->ResetBasicSpawnDelay();
            }
        }
        else
        {
            it.second.second = MathUtil::Clamp(it.second.second + dt, 0.f, 1.f);
        }
    }
}

void CCaptureFlag::UpdateAnimations(float dt)
{
    for (auto& it : m_anims)
    {
        it.second.SetSize(m_status[it.first].second * GetSize().X, m_status[it.first].second * GetSize().Y);
    }
    float blinkingPercent = 0.7f;
    float left = m_timeFromLastOwnerChange - theTuning.GetFloat("FlagRechargeTime") * blinkingPercent;
    for (auto& it : m_anims)
    {
        if (left > 0 && m_owner != ESideIdentificator::Neutrals && m_status[m_owner].second == 1.f)
        {
            it.second.SetAlpha(0.15 + 0.25 * abs(cos(left / (theTuning.GetFloat("FlagRechargeTime") * (1 - blinkingPercent)) * MathUtil::TwoPi * 2)));
        }
        else
        {
            it.second.SetAlpha(0.4f);
        }
    }
}

void CCaptureFlag::UpdateOwnershipTime(float dt)
{
    if (m_owner != ESideIdentificator::Neutrals && !m_status[m_owner].first)
    {
        m_timeFromLastOwnerChange += dt;
    }
    else if (m_timeFromLastOwnerChange > dt)
    {
        m_timeFromLastOwnerChange -= dt;
    }
}
