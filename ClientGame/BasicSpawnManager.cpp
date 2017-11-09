#include "stdafx.h"
#include "BasicSpawnManager.h"
#include "SessionInfo.h"

CBasicSpawnPoint::CBasicSpawnPoint(Vector2 pos, ESideIdentificator side, float spawnDelay, bool unique) : m_spawnPosition(pos), m_side(side),
m_spawnDelay(spawnDelay), m_spawnOnlyOnce(unique)
{
}

bool CBasicSpawnPoint::SpawnTimeIsUp()
{
    bool result = (m_spawnDelay + theSession[m_side]->GetBasicSpawnDelay() < m_timeTillLastSpawn) || m_mustSpawnAtStart;
    m_mustSpawnAtStart = false;
    return result;
}

void CBasicSpawnPoint::SetSpawnDelay(float delay)
{
    m_spawnDelay = delay;
}

void CBasicSpawnPoint::SetIfUnique(bool value)
{
    m_spawnOnlyOnce = value;
}

void CBasicSpawnPoint::SetSpawnAtStart(bool val)
{
    m_mustSpawnAtStart = val;
}

void CBasicSpawnPoint::UpdateSpawnTime(float dt)
{
    m_timeTillLastSpawn += dt;
}
