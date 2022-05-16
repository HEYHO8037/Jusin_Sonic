#pragma once
#include "Obj.h"
class CRing :
	public CObj
{
public:
	CRing();
	virtual ~CRing();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

