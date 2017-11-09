#pragma once
class CBasicButton
{
public:
    CBasicButton();
    CBasicButton(const CBasicButton& copy);
    ~CBasicButton() = default;
    virtual void Show();
    virtual void Hide();
    virtual void SetSprite(std::string texture) final;
    virtual std::string GetDisplayString() final;
    virtual void ResetDisplayString() final;
    virtual void SetButtonSize(Vector2 size);
    virtual void SetMsgText(std::string text);
    virtual std::string GetMsgText();
    virtual void SetHilightColor(Color color) final;
    virtual void SetButtonColor(Color color) final;
    virtual void SetButtonBackgroundColor(Color color) final;
    virtual void HighLight();
    virtual void UnHighLight();
    virtual void Render();
    virtual void ChangeStatus() {};
    virtual bool IsChoosen();
    virtual void SetButtonPosition(Vector2 x);
    virtual void SetButtonText(std::string text);
    virtual void SetPressedColor(Color newColor) {};
    virtual void SetUnpressedColor(Color newColor) {};
    virtual void SetButtonTextFont(std::string font) final;

protected:
    Actor m_highLight;
    Actor m_body;
    Actor m_background;
    TextActor m_buttonName;
    std::string m_msgText;
};

