#include "stdafx.h"
#include "Spring.h"
#include "BmpMgr.h"
#include "Camera.h"

CSpring::CSpring()
{
}


CSpring::~CSpring()
{
}

void CSpring::Initialize(void)
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_tInfo.fX = 500;
	m_tInfo.fY = 450;

	m_iDrawID = 0;
	m_iOption = 0;

	m_tPivot = POSITION(0.5, 0.5);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Spring.bmp", L"Spring");

}

int CSpring::Update(void)
{

	Update_Rect();
	return 0;
}

void CSpring::Late_Update(void)
{
}

void CSpring::Render(HDC hDC)
{
	POSITION tPos;
	tPos.x = m_tInfo.fX - m_tInfo.fCX * m_tPivot.x;
	tPos.y = m_tInfo.fY - m_tInfo.fCY * m_tPivot.y;
	tPos -= CCamera::Get_Instance()->GetPos();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Spring");

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

void CSpring::Release(void)
{
}
