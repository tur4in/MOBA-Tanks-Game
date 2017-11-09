#include "Base.h"
#include "TowerSpawnPoint.h"
class CBaseSpawnPoint :
    public CTowerSpawnPoint
{
public:
    CBaseSpawnPoint(Vector2 pos, ESideIdentificator side);
    ~CBaseSpawnPoint() = default;

    virtual void Spawn(std::list<std::shared_ptr<CBasicUnit>>& list, std::unique_ptr<CBasicCommander>& commander) override;
};
