#include "stdafx.h"
#include "MeeleeMobSpawnPoint.h"
#include "TunedInfo.h"
#include "MeleeMob.h"
#include "Tower.h"
#include "Tank.h"


CMeeleeMobSpawnPoint::CMeeleeMobSpawnPoint(Vector2 pos, ESideIdentificator side) : CMobSpawnPoint(pos, side)
{
    SetSpawnDelay(theTuning.GetFloat("MeeleeMobSpawnDelay"));
}

void CMeeleeMobSpawnPoint::Spawn(std::list<std::shared_ptr<CBasicUnit>>& list, std::unique_ptr<CBasicCommander>& commander)
{
    if (m_defaultPath.empty())
    {
        FindDefaultPath();
    }
    if (SpawnTimeIsUp())
    {
        auto mob = std::make_shared<CMeleeMob>();
        mob->SetPosition(m_spawnPosition);
        mob->SetSideOfConflict(m_side);
        TunedInfo::SetProps(mob);
        mob->SetDensity(0.5);
        mob->InitPhysics();
        mob->SetPriority<CTower>();
        mob->SetPath(m_defaultPath);
        list.emplace_back(mob);
        commander->AddCommandable(mob);
        m_timeTillLastSpawn = 0;
    }
}
