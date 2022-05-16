#pragma once
#include "Obj.h"
class CSpring :
	public CObj
{
public:
	CSpring();
	virtual ~CSpring();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Add_iDrawID() { m_iDrawID++; }
	void Reset_iDrawID() { m_iDrawID = 0; }

private:
	int			m_iDrawID;
	int			m_iOption;
};

