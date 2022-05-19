#pragma once
#include "Obj.h"
#include "UINum.h"

class CUIScore
	: public CObj
{
public:
	CUIScore();
	virtual ~CUIScore();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Add_Score() { m_iScore += 10; }
	void Add_Ring() { m_iRing++; }
	void Rest_Ring() { m_iRing = 0; }
	void Update_ScoreVector();
	void Update_RingVector();

private:
	int m_iScore;
	int m_iRing;
	vector<CUINum*> m_vecScoreNumber;
	vector<CUINum*> m_vecRingNumber;


};

