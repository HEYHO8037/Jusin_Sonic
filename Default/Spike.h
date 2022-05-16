#pragma once
#include "Obj.h"
class CSpike :
	public CObj
{
public:
	CSpike();
	virtual ~CSpike();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int			m_iDrawID;
	int			m_iOption;
};

