#pragma once
#include "stdafx.h"
#include "BasicUnit.h"
#include "SessionInfo.h"
#include "BasicCommander.h"
class CBasicSpawnPoint
{
public:
    CBasicSpawnPoint(Vector2 pos, ESideIdentificator side, float spawnDelay, bool unique = false);
    virtual ~CBasicSpawnPoint() = default;
    virtual void Spawn(std::list<std::shared_ptr<CBasicUnit>>& list, std::unique_ptr<CBasicCommander>& commander) = 0;
    bool SpawnTimeIsUp();
    void SetSpawnDelay(float);
    void SetIfUnique(bool);
    void SetSpawnAtStart(bool);
    virtual void UpdateSpawnTime(float dt);
    virtual void Render() {}
protected:
    Vector2 m_spawnPosition;
    ESideIdentificator m_side;
    float m_spawnDelay;
    float m_timeTillLastSpawn = 0;
    bool m_spawnOnlyOnce;
    bool m_mustSpawnAtStart = false;
};

