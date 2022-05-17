#pragma once
#include "Obj.h"
class CGoal :
	public CObj
{
public:
	CGoal();
	virtual ~CGoal();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};

