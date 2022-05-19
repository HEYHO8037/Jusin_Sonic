#include "stdafx.h"
#include "BGMushroom_2.h"
#include "Camera.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CBGMushroom_2::CBGMushroom_2()
{
}


CBGMushroom_2::~CBGMushroom_2()
{
}

void CBGMushroom_2::Initialize(void)
{
	if (CCamera::Show_Instance() != nullptr)
	{
		m_tInfo.fY -= 45;
		m_tInfo.fX -= 62;
	}

	m_tInfo.fCX = 16.f;
	m_tInfo.fCY = 27.f;


	m_tPivot = POSITION(0.5, 0.5);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/BGMushroom2.bmp", L"BGMushroom2");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 13;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

}

int CBGMushroom_2::Update(void)
{
	Update_Rect();

	return 0;
}

void CBGMushroom_2::Late_Update(void)
{
	Move_Frame();
}

void CBGMushroom_2::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BGMushroom2");

	if (CCamera::Show_Instance() != nullptr)
	{
		POSITION tPos;
		tPos.x = m_tInfo.fX - m_tInfo.fCX * m_tPivot.x;
		tPos.y = m_tInfo.fY - m_tInfo.fCY * m_tPivot.y;
		tPos -= CCamera::Get_Instance()->GetPos();


		GdiTransparentBlt(hDC,
			tPos.x,	// 2,3 인자 :  복사받을 위치 X, Y
			tPos.y,
			int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hMemDC,							// 비트맵을 가지고 있는 DC
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,								// 비트맵 출력 시작 좌표, X,Y
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
	else
	{

		GdiTransparentBlt(hDC,
			int(m_tInfo.fX) + iScrollX,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tInfo.fY) + iScrollY,
			int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hMemDC,							// 비트맵을 가지고 있는 DC
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,								// 비트맵 출력 시작 좌표, X,Y
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
}

void CBGMushroom_2::Release(void)
{
}
