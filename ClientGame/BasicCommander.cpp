#include "stdafx.h"
#include "BasicCommander.h"
#include "RayCastCallbackClosest.h"

CBasicCommander::CBasicCommander()
{
}

CBasicCommander::~CBasicCommander()
{
}

bool CBasicCommander::CanSee(std::shared_ptr<CBasicUnit> commandable, std::shared_ptr<CBasicUnit> unit) const
{
    float curDistanceToMob = Vector2::Distance(commandable->GetPosition(), unit->GetPosition());
    if (curDistanceToMob < commandable->GetDetectDist())
    {
        auto rccallback = std::make_unique<CRayCastCallbackClosest>();
        theWorld.GetPhysicsWorld().RayCast(rccallback.get(), commandable->GetBody()->GetPosition(), unit->GetBody()->GetPosition());
        return rccallback->m_fixture && rccallback->m_fixture->GetBody() == unit->GetBody();
    }
    return false;
}

std::shared_ptr<CBasicUnit> CBasicCommander::FindClosest(std::list<std::shared_ptr<CBasicUnit>>& monitoredUnits, std::shared_ptr<CBasicUnit> mobPtr)
{
	std::shared_ptr<CBasicUnit> target(nullptr);
	std::vector<std::shared_ptr<CBasicUnit>> attackQueue;
	for (auto & unit : monitoredUnits)
	{
		if (mobPtr->GetSideOfConflict() != unit->GetSideOfConflict() && CanSee(mobPtr, unit))
		{
			attackQueue.push_back(unit);
		}
	}
	auto comp = [&mobPtr](decltype(mobPtr) const& a, decltype(mobPtr) const& b) 
	{
		return mobPtr->GetPriority()(a, b);
	};
	std::sort(attackQueue.begin(), attackQueue.end(), comp);
	if (attackQueue.size())
	{
		target = attackQueue.front();
	}
	return target;
}
