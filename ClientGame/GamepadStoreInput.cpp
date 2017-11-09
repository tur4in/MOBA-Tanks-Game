#include "stdafx.h"
#include "GamepadStoreInput.h"


GamepadStoreInput::GamepadStoreInput()
{
}


GamepadStoreInput::~GamepadStoreInput()
{
}

void GamepadStoreInput::Update()
{
    if (theController.IsButtonDown(XINPUT_GAMEPAD_DPAD_UP))
    {
        if (!m_upPressed)
        {
            m_upPressed = true;
            theSwitchboard.Broadcast(new Message("PadUp"));
        }
    }
    else
    {
        m_upPressed = false;
    }
    if (theController.IsButtonDown(XINPUT_GAMEPAD_DPAD_DOWN))
    {
        if (!m_downPressed)
        {
            m_downPressed = true;
            theSwitchboard.Broadcast(new Message("PadDown"));
        }
    }
    else
    {
        m_downPressed = false;
    }
    if (theController.IsButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT))
    {
        if (!m_rightPressed)
        {
            m_rightPressed = true;
            theSwitchboard.Broadcast(new Message("PadRight"));
        }
    }
    else
    {
        m_rightPressed = false;
    }
    if (theController.IsButtonDown(XINPUT_GAMEPAD_DPAD_LEFT))
    {
        if (!m_leftPressed)
        {
            m_leftPressed = true;
            theSwitchboard.Broadcast(new Message("PadLeft"));
        }
    }
    else
    {
        m_leftPressed = false;
    }
}
