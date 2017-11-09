#pragma once
#include "BasicButton.h"
class CStoreButton :
    public CBasicButton
{
public:
    CStoreButton();
    ~CStoreButton();
    virtual void SetButtonPosition(Vector2 x);
    virtual void SetMsgText(std::string text);
    virtual void SetButtonText(std::string text) = 0;
    virtual bool Buy() = 0;
    virtual size_t GetPrice();
    virtual void SetPrice(size_t p);
    virtual void SetNumberOfClicks(size_t x);
    virtual void HighLight() override;
    virtual void UnHighLight() override;


protected:
    size_t m_price;

};

