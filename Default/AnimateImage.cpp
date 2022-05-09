#include "stdafx.h"
#include "BmpMgr.h"
#include "AnimateImage.h"


CAnimateImage::CAnimateImage()
{
}


CAnimateImage::~CAnimateImage()
{
	Release();
}

void CAnimateImage::Initialize(void)
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_iMaxFrameY = 0;
	m_tFrame.dwTime = GetTickCount();
	m_fTargetX = 0;
	m_fTargetY = 0;
}

int CAnimateImage::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_iMaxFrameY == m_tFrame.iMotion)
	{
		m_tFrame.iMotion = 0;
	}


	Move_Frame();


	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_tFrame.iFrameEnd)
	{
		if (m_iMaxFrameY)
		{
			m_tFrame.iMotion++;
		}
	}

	MoveToTarget();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CAnimateImage::Late_Update(void)
{
}

void CAnimateImage::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		int(m_tInfo.fCX) * m_tFrame.iFrameStart,	// 비트맵 출력 시작 좌표, X,Y
		int(m_tInfo.fCY) * m_tFrame.iMotion,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));			// 제거하고자 하는 색상

}

void CAnimateImage::Release(void)
{
}

void CAnimateImage::MoveToTarget()
{
	if (m_fTargetX == m_tInfo.fX || m_fTargetY == m_tInfo.fY)
	{
		return;
	}


	if (m_eDir == DIR_LEFT)
	{
		m_tInfo.fX--;
	}
	else if(m_eDir == DIR_RIGHT)
	{
		m_tInfo.fX++;
	}
	else if (m_eDir == DIR_UP)
	{
		m_tInfo.fY--;
	}
	else if (m_eDir == DIR_DOWN)
	{
		m_tInfo.fY++;
	}
	else
	{
		return;
	}
}
