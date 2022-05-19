#pragma once
#include "Obj.h"
class CBGMushroom_3 :
	public CObj
{
public:
	CBGMushroom_3();
	virtual ~CBGMushroom_3();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

