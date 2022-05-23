#pragma once
#include "Obj.h"
class CBossMonster :
	public CObj
{
public:
	CBossMonster();
	virtual ~CBossMonster();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void	Set_Falling(bool bFall) { m_bFalling = bFall; }
	void	Set_Jumping(bool bJump) { m_bJump = bJump; }
	void	Hit();
	bool	Get_KnockDown();

private:
	void		RollingAttack();
	void		BackAttack();
	void		Die();

	void		Falling(void);
	void		Jumping(void);
	void		Motion_Change(void);

private:
	int						m_iHP;
	float					m_fPower;
	float					m_fGroundY;

	bool					m_bJump;		// 점프 상태 확인
	bool					m_bFalling;		// 중력으로 인한 추락
	bool					m_bIsIDLE;

	float					m_fJumpPower;	// 점프 힘
	float					m_fJumpTime;	// 점프 중 진행 시간
	float					m_fFalling;     // 하강 속도
	float					m_fRollSpeed;
	float					m_fMaxMove;
	float					m_fMoveDist;

	bool					m_bIsLR; // 방향
	bool					m_bIsKnockDown;
	bool					m_bDeadSound;

	float					m_fSoundVol;

	BOSSSTATE					m_ePreState;
	BOSSSTATE					m_eCurState;
};

