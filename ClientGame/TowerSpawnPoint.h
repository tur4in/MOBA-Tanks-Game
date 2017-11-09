#pragma once
#include "BasicSpawnManager.h"
class CTowerSpawnPoint :
    public CBasicSpawnPoint
{
public:
    CTowerSpawnPoint(Vector2 pos, ESideIdentificator side);
    ~CTowerSpawnPoint() = default;
    virtual void Spawn(std::list<std::shared_ptr<CBasicUnit>>& list, std::unique_ptr<CBasicCommander>& commander) override;

protected:
    bool m_spawned = false;
};

