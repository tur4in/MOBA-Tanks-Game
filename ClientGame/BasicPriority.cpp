#include "stdafx.h"
#include "BasicPriority.h"
#include "BasicUnit.h"

CBasicPriority::CBasicPriority(CBasicUnit const * const unit) : m_unit(unit)
{
}

bool CBasicPriority::operator()(std::shared_ptr<CBasicUnit> const& u1, std::shared_ptr<CBasicUnit> const& u2) const
{
	float dist1 = (m_unit->GetPosition() - u1->GetPosition()).LengthSquared();
	float dist2 = (m_unit->GetPosition() - u2->GetPosition()).LengthSquared();
	return dist1 < dist2;
}
