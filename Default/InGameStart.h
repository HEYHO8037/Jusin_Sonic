#pragma once
#include "Obj.h"
class InGameStart :
	public CObj
{
public:
	InGameStart();
	virtual ~InGameStart();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

