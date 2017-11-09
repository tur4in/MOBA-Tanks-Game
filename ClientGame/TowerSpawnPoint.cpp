#include "stdafx.h"
#include "TowerSpawnPoint.h"
#include "TunedInfo.h"
#include "TowerCommander.h"


CTowerSpawnPoint::CTowerSpawnPoint(Vector2 pos, ESideIdentificator side) :
    CBasicSpawnPoint(pos, side, 0, true)
{
}

void CTowerSpawnPoint::Spawn(std::list<std::shared_ptr<CBasicUnit>>& list, std::unique_ptr<CBasicCommander>& commander)
{
    if (!m_spawned)
    {
        auto tower = std::make_shared<CTower>();
        tower->SetPosition(m_spawnPosition);
        tower->SetSideOfConflict(m_side);
        TunedInfo::SetProps(tower);
        tower->SetDensity(0);
        tower->InitPhysics();
        list.emplace_back(tower);
        commander->AddCommandable(tower);

        m_spawned = true;
    }
}
