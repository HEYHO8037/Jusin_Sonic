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

public:
	void Set_Ground(float fY) { m_fGroundY = fY; }
	void Set_Losing(bool bIsLosing) { m_bIsLosing = bIsLosing; }
	void MoveRing();
	void ToggleSpeed();
	void SetAngle(float fAngle) { m_fAngle = fAngle; }
	bool Get_Losing() { return m_bIsLosing; }
private:
	void Falling();

private:
	bool m_bIsContact;
	DWORD m_FallingTime;
	float m_fGroundY;
	bool m_bIsLosing;
};

