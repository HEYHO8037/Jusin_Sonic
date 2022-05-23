#pragma once
#include "Obj.h"
#include "UINum.h"
class InGameEnd :
	public CObj
{
public:
	InGameEnd();
	virtual ~InGameEnd();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


public:
	void Set_Score(int iScore)
	{
		m_iScore = iScore; 
		m_iTotal = m_iScore * m_iRing;
	}
	void Set_Ring(int iRing) { m_iRing = iRing; }
private:
	void Update_ScoreVector();
	void Update_RingVector();
	void Update_TotalVector();


private:
	int m_iScore;
	int m_iRing;
	int m_iTotal;

	vector<CUINum*> m_vecRingBonus;
	vector<CUINum*> m_vecScoreBonus;
	vector<CUINum*> m_vecTotal;
};

