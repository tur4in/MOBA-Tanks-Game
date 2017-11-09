#pragma once
#include "BasicButton.h"
class CMenuButton :
    public CBasicButton
{
public:
    CMenuButton();
    ~CMenuButton();
    virtual void SetButtonSize(Vector2 size) override;
    virtual void SetButtonPosition(Vector2 pos) override;
    virtual void HighLight() override;
    virtual void UnHighLight() override;
};

