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

private:
	void		Falling(void);
	void		Key_Input(void);
	void		Jumping(void);
	void		OffSet(void);
	void		Motion_Change(void);

private:
	float					m_fDiagonal;
	bool					m_bJump;		// ���� ���� Ȯ��
	bool					m_bFalling;
	float					m_fJumpPower;	// ���� ��
	float					m_fJumpTime;	// ���� �� ���� �ð�
	float					m_fFalling;     // �ϰ� �ӵ�
	float					m_fPower;
	float					GroundY;

	STATE					m_ePreState;
	STATE					m_eCurState;

};
