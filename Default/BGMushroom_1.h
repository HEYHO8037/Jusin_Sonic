#pragma once
#include "Obj.h"
class CBGMushroom_1 :
	public CObj
{
public:
	CBGMushroom_1();
	virtual ~CBGMushroom_1();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

