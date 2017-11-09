#include "stdafx.h"
#include "TowerCommander.h"
#include "SessionInfo.h"
#include "Base.h"
#include "RayCastCallbackClosest.h"
#include <math.h>


CTowerCommander::CTowerCommander()
{
    theSwitchboard.SubscribeTo(this, thePrefs.GetString("StoreMessages", "BaseHealth"));
}


CTowerCommander::~CTowerCommander()
{
    theSwitchboard.UnsubscribeFrom(this, thePrefs.GetString("StoreMessages", "BaseHealth"));
}

void CTowerCommander::ReceiveMessage(Message* m)
{
    if (m->GetMessageName() == thePrefs.GetString("StoreMessages", "BaseHealth"))
    {
        auto side = static_cast<TypedMessage<ESideIdentificator>*>(m)->GetValue();
        theSession[side]->SetBaseHP(theSession[side]->GetBaseHP() + theTuning.GetInt("BaseHPUpgrade"));
        for (auto & it : m_handledTowers)
        {
            auto tptr = it.lock();
            if (dynamic_cast<CBase*>(tptr.get()) && tptr->GetSideOfConflict() == side)
            {
                tptr->SetMaxHP(theSession[side]->GetBaseHP());
            }
        }
    }
}

void CTowerCommander::Update(std::list<std::shared_ptr<CBasicUnit>>& monitoredUnits)
{
    auto it = m_handledTowers.begin();
    while (it != m_handledTowers.end())
    {
        auto towerPtr = (*it).lock();
        if (!it->expired())
        {
            auto target = FindClosest(monitoredUnits, towerPtr);
            if (!target)
            {
                ++it;
                continue;
            }
            auto targetPosition = target->GetPosition() - towerPtr->GetPosition();
            float viewRotation = MathUtil::AngleFromVector(targetPosition);
            towerPtr->RotateTower(viewRotation);
            if (abs((MathUtil::ToRadians(towerPtr->GetTowerRotation()) - viewRotation)) < theTuning.GetFloat("AngularError"))
            {
                if (targetPosition.Length() < towerPtr->GetAttackDist())
                {
                    towerPtr->Attack();
                }
            }
            ++it;
        }
        else
        {
            it = m_handledTowers.erase(it);
        }
    }
}

void CTowerCommander::Command(CBasicUnit& monitoredTower)
{

}

void CTowerCommander::AddCommandable(std::weak_ptr<CBasicUnit> com)
{
    AddTowerToHandle(std::dynamic_pointer_cast<CTower>(com.lock()));
}

bool CTowerCommander::HasCommandable()
{
    return true;
}

void CTowerCommander::AddTowerToHandle(std::weak_ptr<CTower> tower)
{
    m_handledTowers.emplace_back(tower);
}
