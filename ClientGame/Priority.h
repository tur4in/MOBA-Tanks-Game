#pragma once
#include "stdafx.h"
#include <type_traits>
#include "BasicPriority.h"
template <typename T, typename Enable = void>
class CPriority;

template<typename T>
class CPriority<T, typename std::enable_if<std::is_base_of<CBasicUnit, T>::value>::type>
	: public CBasicPriority
{
public:
	CPriority(CBasicUnit const * const unit) : CBasicPriority(unit){}
	~CPriority() = default;

	virtual bool operator()(std::shared_ptr<CBasicUnit> const& u1, std::shared_ptr<CBasicUnit> const& u2) const override
	{
		auto ptr1 = dynamic_cast<T const*>(u1.get());
		auto ptr2 = dynamic_cast<T const*>(u2.get());
		if (!(ptr1 && ptr2) || (!ptr1 && !ptr2))
		{
			return ptr1;
		}
		float dist1 = (m_unit->GetPosition() - u1->GetPosition()).LengthSquared();
		float dist2 = (m_unit->GetPosition() - u2->GetPosition()).LengthSquared();
		return dist1 < dist2;
	}
};

