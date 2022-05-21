#include "stdafx.h"
#include "InGameEnd.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "AbstractFactory.h"

InGameEnd::InGameEnd()
{
}


InGameEnd::~InGameEnd()
{
}

void InGameEnd::Initialize(void)
{
	m_tInfo.fX = 50;
	m_tInfo.fY = 50;

	m_tInfo.fCX = 211.f;
	m_tInfo.fCY = 117.f;

	m_tPivot = POSITION(0.5, 0.5);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/End1.bmp", L"End");

	m_vecRingBonus.push_back(new CUINum(m_tInfo.fX + 103, m_tInfo.fY + 55));
	m_vecScoreBonus.push_back(new CUINum(m_tInfo.fX + 103, m_tInfo.fY + 75));

}

int InGameEnd::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}


	Update_Rect();
	Update_ScoreVector();
	Update_RingVector();

	for (auto& iter : m_vecRingBonus)
	{
		iter->Update();
	}

	for (auto& iter : m_vecScoreBonus)
	{
		iter->Update();
	}

	

	return OBJ_NOEVENT;
}

void InGameEnd::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		m_bDead = true;
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
	}

}

void InGameEnd::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"End");

	GdiTransparentBlt(hDC,
		m_tInfo.fX,	// 2,3 인자 :  복사받을 위치 X, Y
		m_tInfo.fY,
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	for (auto& iter : m_vecRingBonus)
	{
		iter->Render(hDC);
	}

	for (auto& iter : m_vecScoreBonus)
	{
		iter->Render(hDC);
	}

}

void InGameEnd::Release(void)
{
	for (auto& iter : m_vecRingBonus)
	{
		delete iter;
	}
	m_vecRingBonus.clear();

	for (auto& iter : m_vecScoreBonus)
	{
		delete iter;
	}

	m_vecScoreBonus.clear();
}

void InGameEnd::Update_ScoreVector()
{
	int _iNumLong = 0;
	int saveScore = m_iScore;

	if (m_iScore == 0)
	{
		m_vecScoreBonus.front()->Set_Num(0);
		return;
	}

	while (m_iScore != 0)
	{
		++_iNumLong;
		if (_iNumLong > m_vecScoreBonus.size())
		{
			m_vecScoreBonus.push_back(dynamic_cast<CUINum*>(CAbstractFactory<CUINum>::Create(m_vecScoreBonus[m_vecScoreBonus.size() - 1]->Get_Info().fX - (m_vecScoreBonus[m_vecScoreBonus.size() - 1]->Get_Info().fCX * 0.5f) - 7.f, m_vecScoreBonus[m_vecScoreBonus.size() - 1]->Get_Info().fY)));
			m_vecScoreBonus.back()->Set_Num(m_iScore % 10);
		}
		else
		{
			m_vecScoreBonus[_iNumLong - 1]->Set_Num(m_iScore % 10);
		}

		m_iScore /= 10;
	}

	m_iScore = saveScore;
}

void InGameEnd::Update_RingVector()
{
	int _iNumLong = 0;
	int saveRing = m_iRing;

	if (m_iRing == 0)
	{
		m_vecRingBonus.front()->Set_Num(0);
		return;
	}

	while (m_iRing != 0)
	{
		++_iNumLong;
		if (_iNumLong > m_vecRingBonus.size())
		{
			m_vecRingBonus.push_back(dynamic_cast<CUINum*>(CAbstractFactory<CUINum>::Create(m_vecRingBonus[m_vecRingBonus.size() - 1]->Get_Info().fX - (m_vecRingBonus[m_vecRingBonus.size() - 1]->Get_Info().fCX * 0.5f) - 7.f, m_vecRingBonus[m_vecRingBonus.size() - 1]->Get_Info().fY)));
			m_vecRingBonus.back()->Set_Num(m_iRing % 10);
		}
		else
		{
			m_vecRingBonus[_iNumLong - 1]->Set_Num(m_iRing % 10);
		}
		m_iRing /= 10;
	}

	m_iRing = saveRing;

}
