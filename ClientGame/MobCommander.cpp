#include "stdafx.h"
#include "MobCommander.h"
#include "SessionInfo.h"
#include "Base.h"
#include "RayCastCallbackClosest.h"
#include "MapObjectFactory.h"


CMobCommander::CMobCommander()
{
    theSwitchboard.SubscribeTo(this, thePrefs.GetString("StoreMessages", "MobHPUp"));
}


CMobCommander::~CMobCommander()
{
    theSwitchboard.UnsubscribeFrom(this, thePrefs.GetString("StoreMessages", "MobHPUp"));
}

void CMobCommander::Update(std::list<std::shared_ptr<CBasicUnit>>& monitoredUnits)
{
    auto it = m_handledMobs.begin();
    while (it != m_handledMobs.end())
    {
        auto mobPtr = (*it).lock();
        if (!it->expired())
        {
            auto target = FindClosest(monitoredUnits, mobPtr);
            if (target)
            {
                mobPtr->SetTarget(target);
            }
            else
            {
                if (mobPtr->GetState() == EMobState::None)
                {
                    if (mobPtr->GetSideOfConflict() == ESideIdentificator::Side1)
                    {
                        mobPtr->SetDestination(MapObject::basePositions[ESideIdentificator::Side2]);
                    }
                    else if (mobPtr->GetSideOfConflict() == ESideIdentificator::Side2)
                    {
                        mobPtr->SetDestination(MapObject::basePositions[ESideIdentificator::Side1]);
                    }
                }
            }
            ++it;
        }
        else
        {
            it = m_handledMobs.erase(it);
        }
    }
}

void CMobCommander::Command(CBasicUnit&)
{

}

void CMobCommander::ReceiveMessage(Message* m)
{
    if (m->GetMessageName() == thePrefs.GetString("StoreMessages", "MobHPUp"))
    {
        auto side = dynamic_cast<TypedMessage<ESideIdentificator>*>(m)->GetValue();
        int oldBasicHP = theSession[side]->GetBasicMobHP();
        theSession[side]->SetBasicMobHP(theSession[side]->GetBasicMobHP() + theTuning.GetInt("MobHPUpgrade"));
        for (auto & it : m_handledMobs)
        {
            auto mptr = it.lock();
            if (mptr && mptr->GetSideOfConflict() == side)
            {
                int ownhp = mptr->GetMaxHP();
                int bonusHP = ownhp - oldBasicHP;
                mptr->SetMaxHP(theSession[side]->GetBasicMobHP() + bonusHP);
            }
        }
    }
}

void CMobCommander::AddCommandable(std::weak_ptr<CBasicUnit> mob)
{
    m_handledMobs.emplace_back(std::dynamic_pointer_cast<CMob>(mob.lock()));
}

bool CMobCommander::HasCommandable()
{
    return !m_handledMobs.empty();
}