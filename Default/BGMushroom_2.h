#pragma once
#include "Obj.h"
class CBGMushroom_2 :
	public CObj
{
public:
	CBGMushroom_2();
	virtual ~CBGMushroom_2();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

