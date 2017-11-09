#include "stdafx.h"
#include "MobSpawnManager.h"
#include "Tank.h"
#include "MapObjectFactory.h"
#include "MobCommander.h"
#include "TunedInfo.h"

CMobSpawnPoint::CMobSpawnPoint(Vector2 pos, ESideIdentificator side) : CBasicSpawnPoint(pos, side, theTuning.GetFloat("MobSpawnDelay"), false)
{
}

void CMobSpawnPoint::Spawn(std::list<std::shared_ptr<CBasicUnit>>& list, std::unique_ptr<CBasicCommander>& commander)
{
    if (m_defaultPath.empty())
    {
        FindDefaultPath();
    }
    if (SpawnTimeIsUp())
    {
        auto mob = std::make_shared<CMob>();
        mob->SetPosition(m_spawnPosition);
        mob->SetSideOfConflict(m_side);
        TunedInfo::SetProps(mob);
        mob->SetDensity(0.5);
        mob->InitPhysics();
        mob->SetPriority<CTank>();
        mob->SetPath(m_defaultPath);
        list.emplace_back(mob);
        commander->AddCommandable(mob);

        m_timeTillLastSpawn = 0;
    }
}

void CMobSpawnPoint::FindDefaultPath()
{
    if (m_side == ESideIdentificator::Side1)
    {
        theSpatialGraph.GetPath(m_spawnPosition, MapObject::basePositions[ESideIdentificator::Side2], m_defaultPath);
    }
    else if (m_side == ESideIdentificator::Side2)
    {
        theSpatialGraph.GetPath(m_spawnPosition, MapObject::basePositions[ESideIdentificator::Side1], m_defaultPath);
    }
    if (m_side == ESideIdentificator::Neutrals)
    {
        theSpatialGraph.GetPath(m_spawnPosition, Vector2(), m_defaultPath);
    }
}
