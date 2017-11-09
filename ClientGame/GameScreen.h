#pragma once
#include "stdafx.h"
class CGameScreen : public Renderable
{
public:
    CGameScreen() = default;
    virtual ~CGameScreen() = default;

    virtual void Start() = 0;
    virtual void Update(float dt) override {};
    virtual void Render() override {};
    virtual void Stop() {};

protected:
    FullScreenActor m_background;
};

