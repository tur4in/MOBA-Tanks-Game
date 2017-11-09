#pragma once
#include "BasicSpawnManager.h"

class CMobSpawnPoint :
    public CBasicSpawnPoint
{
public:
    ~CMobSpawnPoint() = default;
    void FindDefaultPath();
    CMobSpawnPoint(Vector2 pos, ESideIdentificator side);
    virtual void Spawn(std::list<std::shared_ptr<CBasicUnit>>& list, std::unique_ptr<CBasicCommander>& commander) override;

protected:
    Vector2List m_defaultPath;
};

