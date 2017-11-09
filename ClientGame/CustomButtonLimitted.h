#pragma once
#include "StoreButton.h"

class CCustomButtonLimitted :
    public CStoreButton
{
public:
    virtual bool Buy() override;
    virtual void SetButtonText(std::string text) override;
    virtual void SetNumberOfClicks(size_t x);

protected:
    size_t m_clickAvailiable;
};

