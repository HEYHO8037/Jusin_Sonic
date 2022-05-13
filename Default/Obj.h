#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	} 
	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }
	void		Set_Dead()				{ m_bDead = true; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void		Set_Size(float fCX, float fCY) { m_tInfo.fCX = fCX;  m_tInfo.fCY = fCY; }

	void		Set_PosX(float _fX) { m_tInfo.fX = _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY = _fY; }
	void		Set_PosAddX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosAddY(float _fY) { m_tInfo.fY += _fY; }
	void		Set_Pivot(float x, float y) { m_tPivot.x = x; m_tPivot.y = y; }

	void		Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	void		Set_Speed(float fSpeed) { m_fSpeed = fSpeed; }
	float		Get_Speed() { return m_fSpeed; }

	bool		Get_Dead() { return m_bDead; }
	POSITION	Get_Pivot() { return m_tPivot; }

	const INFO&		Get_Info(void) const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }
	const DIRECTION& Get_Direction() { return m_eDir; }

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

protected:
	void		Update_Rect(void);
	void		Move_Frame(void);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;

	float		m_fSpeed;
	float		m_fAngle;

	DIRECTION	m_eDir;
	bool		m_bDead;

	POSITION	m_tPivot;
	CObj*		m_pTarget;
	TCHAR*		m_pFrameKey;

};