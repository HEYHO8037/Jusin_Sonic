#pragma once
#include "Obj.h"
class InGameStartEnd :
	public CObj
{
public:
	InGameStartEnd();
	virtual ~InGameStartEnd();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

