#pragma once
#include "Obj.h"

class CPlayer : public CObj
{
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
	void	Add_Ring() { m_iRing++;  }
	void	Set_IsGetPoint(bool bIsPoint) { m_bIsGetPoint = bIsPoint; }
	void	Set_JumpPower(float fPower) { m_fJumpPower = fPower; }
	void	Set_QuatorCircle(bool bCircle) { m_bIsQuatorCircle = bCircle; }
	void	Set_SaveSpeed() { m_fSaveSpeed = m_fSpeed; }
	void	Set_CurState(PLAYERSTATE eState) { m_eCurState = eState; }

public:
	bool	Get_QuatorCircle() { return m_bIsQuatorCircle; }
	bool	Get_Falling() { return m_bFalling; }
	float	Get_Ground() { return m_fGroundY; }
	bool	Get_Circle() { return m_bIsCircle; }
	GRAVITY_STATE Get_Gravity() { return m_eGravity; }
	PLAYERSTATE Get_Player_State() { return m_eCurState; }
	float	Get_CirclePosX() { return m_fCircleX;  }
	int		Get_Ring() { return m_iRing; }
	void	Get_SaveSpeed() { m_fSpeed = m_fSaveSpeed;  }
	void	Reset_Ring() { m_iRing = 0; }

private:
	void		QuaterCircling(void);
	void		Circling(void);
	void		Falling(void);
	void		Key_Input(void);
	void		Jumping(void);
	void		Motion_Change(void);

private:
	float					m_fDiagonal;
	
	bool					m_bJump;		// 점프 상태 확인
	bool					m_bFalling; // 중력으로 인한 추락
	
	bool					m_bIsCircle; // 360도 회전을 시작하는가?
	bool					m_bIsQuatorCircle; //90도 회전을 시작하는가?

	bool					m_bIsGetPoint; // 골인지점에 도착했는가?
	bool					m_bIsRunStart; // 뛰기 시작하는가?
	bool					m_bIsRollingStart; // 구르기를 시작하는가?

	bool					m_bIsRolling; // 구르기를 하는중인가?
	bool					m_bIsCharging;

	float					m_fJumpPower;	// 점프 힘
	float					m_fJumpTime;	// 점프 중 진행 시간
	float					m_fFalling;     // 하강 속도
	float					m_fPower;
	float					m_fGroundY;

	float					m_fCircleX;
	float					m_fCircleY;

	float					m_fSaveSpeed;

	int						m_iRing; // 링 개수

	bool					m_bIsLR; // 방향


	float					m_fSoundVol;

	GRAVITY_STATE			m_eGravity;
	PLAYERSTATE					m_ePreState;
	PLAYERSTATE					m_eCurState;

};
