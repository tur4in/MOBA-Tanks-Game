#include "stdafx.h"
#include "BaseSpawnPoint.h"
#include "TunedInfo.h"
#include "TowerCommander.h"
CBaseSpawnPoint::CBaseSpawnPoint(Vector2 pos, ESideIdentificator side) : CTowerSpawnPoint(pos, side)
{
}

void CBaseSpawnPoint::Spawn(std::list<std::shared_ptr<CBasicUnit>>& list, std::unique_ptr<CBasicCommander>& commander)
{
    if (!m_spawned)
    {
        auto base = std::make_shared<CBase>();

        base->SetPosition(m_spawnPosition);
        base->SetSideOfConflict(m_side);
        TunedInfo::SetProps(base);
        base->SetDensity(0);
        base->InitPhysics();
        list.emplace_back(base);
        commander->AddCommandable(base);
        m_spawned = true;
    }
}