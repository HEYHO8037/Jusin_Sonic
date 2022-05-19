#include "stdafx.h"
#include "UIScore.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"

CUIScore::CUIScore()
{

}


CUIScore::~CUIScore()
{
	Release();
}


void CUIScore::Initialize(void)
{
	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 25.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/UI.bmp", L"UI");
	m_pFrameKey = L"UI";

	m_tInfo.fX = 10.f;
	m_tInfo.fY = 10.f;
	m_vecScoreNumber.push_back(new CUINum(m_tInfo.fX + 100, m_tInfo.fY));
	m_vecScoreNumber.push_back(new CUINum(m_tInfo.fX + 89, m_tInfo.fY));
	m_vecScoreNumber.push_back(new CUINum(m_tInfo.fX + 78, m_tInfo.fY));
	m_vecScoreNumber.push_back(new CUINum(m_tInfo.fX + 67, m_tInfo.fY));


	m_vecRingNumber.push_back(new CUINum(m_tInfo.fX + 67, m_tInfo.fY + 15));

	m_iScore = 0;
	m_iRing = 0;
}

int CUIScore::Update(void)
{
	Update_Rect();
	Update_ScoreVector();
	Update_RingVector();

	for (auto& iter : m_vecScoreNumber)
	{
		iter->Update();
	}

	for (auto& iter : m_vecRingNumber)
	{
		iter->Update();
	}
	return 0;
}

void CUIScore::Late_Update(void)
{

}

void CUIScore::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		m_tInfo.fX,	// 2,3 ���� :  ������� ��ġ X, Y
		m_tInfo.fY,
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,						// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	for (auto& iter : m_vecScoreNumber)
	{
		iter->Render(hDC);
	}

	for (auto& iter : m_vecRingNumber)
	{
		iter->Render(hDC);
	}
}

void CUIScore::Release()
{
	for (auto& iter : m_vecScoreNumber)
	{
		delete iter;
	}
	m_vecScoreNumber.clear();

	for (auto& iter : m_vecRingNumber)
	{
		delete iter;
	}

	m_vecRingNumber.clear();
}

void CUIScore::Update_ScoreVector()
{
	int _iNumLong = 0;
	int saveScore = m_iScore;

	if (m_iScore == 0)
	{
		m_vecScoreNumber.front()->Set_Num(0);
		return;
	}

	while (m_iScore != 0)
	{
		++_iNumLong;
		if (_iNumLong > m_vecScoreNumber.size())
		{
			m_vecScoreNumber.push_back(dynamic_cast<CUINum*>(CAbstractFactory<CUINum>::Create(m_vecScoreNumber[m_vecScoreNumber.size() - 1]->Get_Info().fX - (m_vecScoreNumber[m_vecScoreNumber.size() - 1]->Get_Info().fCX * 0.5f) - 7.f, m_vecScoreNumber[m_vecScoreNumber.size() - 1]->Get_Info().fY)));
			m_vecScoreNumber.back()->Set_Num(m_iScore % 10);
		}
		else
		{
			m_vecScoreNumber[_iNumLong - 1]->Set_Num(m_iScore % 10);
		}

		m_iScore /= 10;
	}

	m_iScore = saveScore;
}

void CUIScore::Update_RingVector()
{
	int _iNumLong = 0;
	int saveRing = m_iRing;

	if (m_iRing == 0)
	{
		m_vecRingNumber.front()->Set_Num(0);
		return;
	}

	while (m_iRing != 0)
	{
		++_iNumLong;
		if (_iNumLong > m_vecRingNumber.size())
		{
			m_vecRingNumber.push_back(dynamic_cast<CUINum*>(CAbstractFactory<CUINum>::Create(m_vecRingNumber[m_vecRingNumber.size() - 1]->Get_Info().fX - (m_vecRingNumber[m_vecRingNumber.size() - 1]->Get_Info().fCX * 0.5f) - 7.f, m_vecRingNumber[m_vecRingNumber.size() - 1]->Get_Info().fY)));
			m_vecRingNumber.back()->Set_Num(m_iRing % 10);
		}
		else
		{
			m_vecRingNumber[_iNumLong - 1]->Set_Num(m_iRing % 10);
		}
		m_iRing /= 10;
	}

	m_iRing = saveRing;

}