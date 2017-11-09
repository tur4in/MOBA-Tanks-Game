#pragma once
#include "MobSpawnManager.h"

class CMeeleeMobSpawnPoint :
    public CMobSpawnPoint
{
public:
    ~CMeeleeMobSpawnPoint() = default;
    CMeeleeMobSpawnPoint(Vector2 pos, ESideIdentificator side);
    virtual void Spawn(std::list<std::shared_ptr<CBasicUnit>>& list, std::unique_ptr<CBasicCommander>& commander) override;
};

