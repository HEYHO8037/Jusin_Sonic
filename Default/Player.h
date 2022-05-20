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
	
	bool					m_bJump;		// ���� ���� Ȯ��
	bool					m_bFalling; // �߷����� ���� �߶�
	
	bool					m_bIsCircle; // 360�� ȸ���� �����ϴ°�?
	bool					m_bIsQuatorCircle; //90�� ȸ���� �����ϴ°�?

	bool					m_bIsGetPoint; // ���������� �����ߴ°�?
	bool					m_bIsRunStart; // �ٱ� �����ϴ°�?
	bool					m_bIsRollingStart; // �����⸦ �����ϴ°�?

	bool					m_bIsRolling; // �����⸦ �ϴ����ΰ�?
	bool					m_bIsCharging;

	float					m_fJumpPower;	// ���� ��
	float					m_fJumpTime;	// ���� �� ���� �ð�
	float					m_fFalling;     // �ϰ� �ӵ�
	float					m_fPower;
	float					m_fGroundY;

	float					m_fCircleX;
	float					m_fCircleY;

	float					m_fSaveSpeed;

	int						m_iRing; // �� ����

	bool					m_bIsLR; // ����


	float					m_fSoundVol;

	GRAVITY_STATE			m_eGravity;
	PLAYERSTATE					m_ePreState;
	PLAYERSTATE					m_eCurState;

};
