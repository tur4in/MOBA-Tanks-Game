#pragma once
#include "BasicUnit.h"

class CBasicCommander :
    public MessageListener
{
public:
    CBasicCommander();
    virtual ~CBasicCommander();
    virtual void ReceiveMessage(Message* m) override = 0;
    virtual void Update(std::list<std::shared_ptr<CBasicUnit>>&) = 0;
    virtual void Command(CBasicUnit&) = 0;

    virtual void AddCommandable(std::weak_ptr<CBasicUnit>) {};
    virtual bool HasCommandable() = 0;

protected:
    bool CanSee(std::shared_ptr<CBasicUnit> u1, std::shared_ptr<CBasicUnit> u2) const;
    std::shared_ptr<CBasicUnit> FindClosest(std::list<std::shared_ptr<CBasicUnit>>&, std::shared_ptr<CBasicUnit>);
};

