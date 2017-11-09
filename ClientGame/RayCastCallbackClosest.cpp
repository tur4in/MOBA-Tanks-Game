#include "stdafx.h"
#include "RayCastCallbackClosest.h"

float32 CRayCastCallbackClosest::ReportFixture(b2Fixture * fixture, const b2Vec2 & point, const b2Vec2 & normal, float32 fraction)
{
    if (fixture && !fixture->IsSensor())
    {
        m_fixture = fixture;
        m_point = point;
        m_normal = normal;
        m_fraction = fraction;
        return fraction;
    }
    return 1;
}
