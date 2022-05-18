#pragma once
#include "Obj.h"
class CBackGroundObj :
	public CObj
{
public:
	CBackGroundObj();
	virtual ~CBackGroundObj();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

