#pragma once
class GamepadStoreInput
{
public:
    GamepadStoreInput();
    ~GamepadStoreInput();
    void Update();

private:
    bool m_upPressed = false;
    bool m_downPressed = false;
    bool m_leftPressed = false;
    bool m_rightPressed = false;
};

