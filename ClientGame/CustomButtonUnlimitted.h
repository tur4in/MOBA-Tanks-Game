#pragma once
#include "StoreButton.h"

class CCustomButtonUnlimitted :
    public CStoreButton
{
public:
    virtual bool Buy() override;
    virtual void SetButtonText(std::string text) override;
};

