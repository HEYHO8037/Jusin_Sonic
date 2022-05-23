#include "stdafx.h"
#include "Goal.h"
#include "Camera.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CGoal::CGoal()
{
	m_bIsRender = false;
}

CGoal::~CGoal()
{
}

void CGoal::Initialize(void)
{
	if (CCamera::Show_Instance() != nullptr)
	{
		m_tInfo.fY -= 62;
		m_tInfo.fX -= 62;
	}


	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 47.f;

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
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Sign");

	if (CCamera::Show_Instance() != nullptr)
	{
		if (m_bIsRender)
		{
			POSITION tPos;
			tPos.x = m_tInfo.fX - m_tInfo.fCX * m_tPivot.x;
			tPos.y = m_tInfo.fY - m_tInfo.fCY * m_tPivot.y;
			tPos -= CCamera::Get_Instance()->GetPos();

			GdiTransparentBlt(hDC,
				tPos.x,	// 2,3 ���� :  ������� ��ġ X, Y
				tPos.y,
				int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
				int(m_tInfo.fCY),
				hMemDC,							// ��Ʈ���� ������ �ִ� DC
				(int)m_tInfo.fCX * m_tFrame.iFrameStart,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
				(int)m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
				(int)m_tInfo.fCY,
				RGB(255, 0, 255));
		}
	}
	else
	{

		GdiTransparentBlt(hDC,
			int(m_tInfo.fX) + iScrollX,	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tInfo.fY) + iScrollY,
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}

}

void CGoal::Release(void)
{
}

void CGoal::EnableRender()
{
	m_bIsRender = true;
}
