#include "stdafx.h"
#include "Spike.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "ScrollMgr.h"

CSpike::CSpike()
{

}


CSpike::~CSpike()
{
}

void CSpike::Initialize(void)
{
	if (CCamera::Show_Instance() != nullptr)
	{
		m_tInfo.fY -= 62;
		m_tInfo.fX -= 62;
	}
	
	m_tInfo.fCX = 31.f;
	m_tInfo.fCY = 31.f;


	m_tPivot = POSITION(0.5, 0.5);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Spike.bmp", L"Spike");

	m_iDrawID = 0;
	m_iOption = 0;

}

int CSpike::Update(void)
{

	Update_Rect();
	return 0;
}

void CSpike::Late_Update(void)
{
}

void CSpike::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Spike");

	if (CCamera::Show_Instance() != nullptr)
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
			(int)m_tInfo.fCX * m_iDrawID,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			(int)m_tInfo.fCY * m_iOption,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
	else
	{

		GdiTransparentBlt(hDC,
			int(m_tInfo.fX) + iScrollX,	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tInfo.fY) + iScrollY,
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			(int)m_tInfo.fCX * m_iDrawID,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			(int)m_tInfo.fCY * m_iOption,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}

}

void CSpike::Release(void)
{
}
