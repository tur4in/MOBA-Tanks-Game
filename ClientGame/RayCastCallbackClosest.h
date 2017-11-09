#pragma once
#include "stdafx.h"
class CRayCastCallbackClosest :
    public b2RayCastCallback
{
public:
    CRayCastCallbackClosest() = default;
    ~CRayCastCallbackClosest() = default;

    virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
        const b2Vec2& normal, float32 fraction) override;
    b2Fixture* m_fixture;
    b2Vec2 m_point;
    b2Vec2 m_normal;
    float32 m_fraction;
};

