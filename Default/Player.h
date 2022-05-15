#pragma once
#include "Obj.h"

class CPlayer : public CObj
{
public:
	enum STATE  { IDLE, STARTRUN, RUN, STOPRUN, ROLLSTART, ROLLING, ROLLEND, HIT, DEAD, END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void	Set_Falling(bool bFall) { m_bFalling = bFall; }
	void	Set_Ground(float fY) { m_fGroundY = fY; }
	void	Set_Jumping(bool bJump) { m_bJump = bJump; }
	void	Set_Gravity(GRAVITY_STATE eGravity) { m_eGravity = eGravity; }
	void	Set_Circle(bool bIsCircle) {  m_bIsCircle = bIsCircle; }
	void	Set_CirclePos(float fX, float fY) { m_fCircleX = fX; m_fCircleY = fY; }

public:
	bool	Get_Falling() { return m_bFalling; }
	float	Get_Ground() { return m_fGroundY; }
	bool	Get_Circle() { return m_bIsCircle; }
	GRAVITY_STATE Get_Gravity() { return m_eGravity; }
	float	Get_CirclePosX() { return m_fCircleX;  }

private:
	void		Circling(void);
	void		Falling(void);
	void		Key_Input(void);
	void		Jumping(void);
	void		Motion_Change(void);

private:
	float					m_fDiagonal;
	bool					m_bJump;		// 점프 상태 확인
	bool					m_bFalling;
	bool					m_bIsCircle;
	float					m_fJumpPower;	// 점프 힘
	float					m_fJumpTime;	// 점프 중 진행 시간
	float					m_fFalling;     // 하강 속도
	float					m_fPower;
	float					m_fGroundY;

	float					m_fCircleX;
	float					m_fCircleY;

	GRAVITY_STATE			m_eGravity;
	STATE					m_ePreState;
	STATE					m_eCurState;

};
