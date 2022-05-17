#include "stdafx.h"
#include "InGameEnd.h"
#include "BmpMgr.h"


InGameEnd::InGameEnd()
{
}


InGameEnd::~InGameEnd()
{
}

void InGameEnd::Initialize(void)
{
	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;

	m_tPivot = POSITION(0.5, 0.5);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/End1.bmp", L"End");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

}

int InGameEnd::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void InGameEnd::Late_Update(void)
{
	Move_Frame();
}

void InGameEnd::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"End");

	GdiTransparentBlt(hDC,
		0,	// 2,3 인자 :  복사받을 위치 X, Y
		0,
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,								// 비트맵 출력 시작 좌표, X,Y
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		m_tFrame.iMotion++;

		if (m_tFrame.iMotion > 4)
		{
			m_bDead = true;
		}
	}


}

void InGameEnd::Release(void)
{

}
