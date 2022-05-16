#include "stdafx.h"
#include "Goal.h"
#include "Camera.h"
#include "BmpMgr.h"


CGoal::CGoal()
{
}

CGoal::~CGoal()
{
}

void CGoal::Initialize(void)
{
	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 47.f;

	m_tInfo.fX = 200;
	m_tInfo.fY = 500;

	m_tPivot = POSITION(0.5, 0.5);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Sign.bmp", L"Sign");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 8;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

}

int CGoal::Update(void)
{
	
	Update_Rect();
	return 0;
}

void CGoal::Late_Update(void)
{
	Move_Frame();
}

void CGoal::Render(HDC hDC)
{
	POSITION tPos;
	tPos.x = m_tInfo.fX - m_tInfo.fCX * m_tPivot.x;
	tPos.y = m_tInfo.fY - m_tInfo.fCY * m_tPivot.y;
	tPos -= CCamera::Get_Instance()->GetPos();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Sign");

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

void CGoal::Release(void)
{
}
