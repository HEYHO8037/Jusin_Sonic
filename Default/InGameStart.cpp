#include "stdafx.h"
#include "InGameStart.h"
#include "BmpMgr.h"
#include "Camera.h"


InGameStart::InGameStart()
{
}


InGameStart::~InGameStart()
{
}

void InGameStart::Initialize(void)
{
	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;

	m_tPivot = POSITION(0.5, 0.5);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Start1.bmp", L"Start");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

}

int InGameStart::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void InGameStart::Late_Update(void)
{
	Move_Frame();
}

void InGameStart::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Start");

	GdiTransparentBlt(hDC,
		0,	// 2,3 ���� :  ������� ��ġ X, Y
		0,
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
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

void InGameStart::Release(void)
{

}
