#include "stdafx.h"
#include "RangeMobSpawnPoint.h"
#include "RangedMob.h"
#include "TunedInfo.h"



CRangeMobSpawnPoint::CRangeMobSpawnPoint(Vector2 pos, ESideIdentificator side) : CMobSpawnPoint(pos, side)
{
    SetSpawnDelay(theTuning.GetFloat("RangeMobSpawnDelay"));
}

void CRangeMobSpawnPoint::Spawn(std::list<std::shared_ptr<CBasicUnit>>& list, std::unique_ptr<CBasicCommander>& commander)
{
    if (SpawnTimeIsUp())
    {
        auto mob = std::make_shared<CRangedMob>();
        mob->SetPosition(m_spawnPosition);
        mob->SetSideOfConflict(m_side);
        TunedInfo::SetProps(mob);
        mob->SetDensity(0.5);
        mob->InitPhysics();
        list.emplace_back(mob);
        commander->AddCommandable(mob);
        m_timeTillLastSpawn = 0;
    }
}
