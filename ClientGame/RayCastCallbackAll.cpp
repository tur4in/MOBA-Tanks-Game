#include "stdafx.h"
#include "RayCastCallbackAll.h"

float32 CRayCastCallbackAll::ReportFixture(b2Fixture * fixture, const b2Vec2 & point, const b2Vec2 & normal, float32 fraction)
{
    if (fixture && !fixture->IsSensor())
    {
        SCallbackBody res;
        res.m_fixture = fixture;
        res.m_point = point;
        res.m_fraction = fraction;
        m_intersections.push_back(res);
    }
    return 1;
}
