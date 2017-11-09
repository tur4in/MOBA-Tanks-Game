#pragma once
#include "BasicButton.h"

class CCustomCheckBox :
    public CBasicButton
{
public:
    CCustomCheckBox(bool status = true);
    virtual void ChangeStatus() override;
    virtual void SetPressedColor(Color newColor) override;
    virtual void SetUnpressedColor(Color newColor) override;
    ~CCustomCheckBox();
    virtual void SetButtonSize(Vector2 size) override;

private:
    bool m_isPressed;
    Color m_pressedColor;
    Color m_unpressedColor;

private:
    void SetRightColor();
};

