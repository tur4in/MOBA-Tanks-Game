#include "MobSpawnManager.h"

class CRangeMobSpawnPoint :
    public CMobSpawnPoint
{
public:
    CRangeMobSpawnPoint(Vector2 pos, ESideIdentificator side);
    ~CRangeMobSpawnPoint() = default;
    virtual void Spawn(std::list<std::shared_ptr<CBasicUnit>>& list, std::unique_ptr<CBasicCommander>& commander) override;
};
