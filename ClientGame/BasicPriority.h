#pragma once
class CBasicUnit;
class CBasicPriority
{
public:
	CBasicPriority(CBasicUnit const * const unit);
	virtual ~CBasicPriority() = default;
	
	virtual bool operator()(std::shared_ptr<CBasicUnit> const& u1, std::shared_ptr<CBasicUnit> const& u2) const;

protected:
	CBasicUnit const * const m_unit;
};

