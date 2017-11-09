#pragma once
#include "stdafx.h"
class CRayCastCallbackAll :
    public b2RayCastCallback
{
private:
    struct SCallbackBody
    {
        b2Fixture* m_fixture;
        b2Vec2 m_point;
        float32 m_fraction;
        bool operator<(SCallbackBody& other) { return other.m_fraction < m_fraction; }
    };

public:
    CRayCastCallbackAll() = default;
    ~CRayCastCallbackAll() = default;

    virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
        const b2Vec2& normal, float32 fraction) override;
    std::vector<SCallbackBody> m_intersections;
};

