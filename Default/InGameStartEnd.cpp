#include "stdafx.h"
#include "InGameStartEnd.h"
#include "BmpMgr.h"
#include "Camera.h"


InGameStartEnd::InGameStartEnd()
{
}


InGameStartEnd::~InGameStartEnd()
{
}

void InGameStartEnd::Initialize(void)
{
	m_tInfo.fCX = 16.f;
	m_tInfo.fCY = 16.f;

	m_tPivot = POSITION(0.5, 0.5);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Ring2.bmp", L"Ring");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

}

int InGameStartEnd::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void InGameStartEnd::Late_Update(void)
{
	Move_Frame();
}

void InGameStartEnd::Render(HDC hDC)
{
	POSITION tPos;

	tPos.x = m_tInfo.fX - m_tInfo.fCX * m_tPivot.x;
	tPos.y = m_tInfo.fY - m_tInfo.fCY * m_tPivot.y;
	tPos -= CCamera::Get_Instance()->GetPos();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ring");

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

void InGameStartEnd::Release(void)
{
}
