#pragma once
#include "BasicCommander.h"
#include "Tower.h"
#include "BasicUnit.h"

#include <vector>

class CTowerCommander :
    public CBasicCommander
{
public:
    CTowerCommander();
    virtual ~CTowerCommander();

    virtual void ReceiveMessage(Message* m) override;
    virtual void Update(std::list<std::shared_ptr<CBasicUnit>>& monitoredUnits) override;
    virtual void Command(CBasicUnit& monitoredUnit) override;
    virtual void AddCommandable(std::weak_ptr<CBasicUnit> com) override;
    virtual bool HasCommandable() override;
    void AddTowerToHandle(std::weak_ptr<CTower> tower);

private:
    std::list<std::weak_ptr<CTower>> m_handledTowers;
};

