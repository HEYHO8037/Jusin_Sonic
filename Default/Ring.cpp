#include "stdafx.h"
#include "Ring.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "ScrollMgr.h"


CRing::CRing()
{
}


CRing::~CRing()
{
}

void CRing::Initialize(void)
{
	if (CCamera::Show_Instance() != nullptr)
	{
		m_tInfo.fY -= 62;
		m_tInfo.fX -= 62;
	}

	m_tInfo.fCX = 16.f;
	m_tInfo.fCY = 16.f;

	m_tPivot = POSITION(0.5, 0.5);
	
	m_fAngle = 101.25f;
	m_fSpeed = 4.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Ring2.bmp", L"Ring");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/ShineEffect.bmp", L"Shine");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_bIsLosing = false;
	m_fGroundY = 0;
	m_bIsContact = false;

}

int CRing::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	if (m_bIsLosing)
	{
		DWORD time = GetTickCount() - m_FallingTime;
		if (time > 500)
		{
			Falling();
		}
		else
		{
			MoveRing();
		}
	}


	Update_Rect();

	return OBJ_NOEVENT;
}

void CRing::Late_Update(void)
{
	Move_Frame();
}

void CRing::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ring");

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

void CRing::Release(void)
{
}

void CRing::MoveRing()
{
	//ring's X Speed = cos(ring_angle) * speed
	//ring's Y Speed = -sin(ring_angle) * speed

	m_tInfo.fX += cos(m_fAngle * RADIAN) * m_fSpeed;
	m_tInfo.fY += -sin(m_fAngle * RADIAN) * m_fSpeed;

	if (!m_bIsContact)
	{
		m_FallingTime = GetTickCount();
		m_bIsContact = true;
	}
}

void CRing::ToggleSpeed()
{
	m_fSpeed = m_fSpeed * -1;
}

void CRing::Falling()
{
	if (m_tInfo.fY >= m_fGroundY)
	{
		m_tInfo.fY = m_fGroundY;
		m_bIsLosing = false;
	}
	else
	{
		m_tInfo.fY += 10.f;
	}
}

