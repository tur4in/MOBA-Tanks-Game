#pragma once
#include "BasicCommander.h"
#include "Mob.h"

class CMobCommander :
    public CBasicCommander
{
public:
    CMobCommander();
    virtual ~CMobCommander();

    virtual void Update(std::list<std::shared_ptr<CBasicUnit>>&) override;
    virtual void Command(CBasicUnit&) override;
    virtual void ReceiveMessage(Message* m) override;

    virtual void AddCommandable(std::weak_ptr<CBasicUnit>);
    virtual bool HasCommandable();

private:
    std::list<std::weak_ptr<CMob>> m_handledMobs;
    bool m_basesFound = false;
    Vector2 m_base1Pos;
    Vector2 m_base2Pos;
};

