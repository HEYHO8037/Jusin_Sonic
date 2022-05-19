#include "stdafx.h"
#include "UILife.h"
#include "BmpMgr.h"


CUILife::CUILife()
{
}


CUILife::~CUILife()
{
}

void CUILife::Initialize(void)
{
	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 25.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/UI.bmp", L"UI");
	m_pFrameKey = L"UI";

	m_tInfo.fX = 10.f;
	m_tInfo.fY = 210.f;
}

int CUILife::Update(void)
{
	Update_Rect();
	return 0;
}

void CUILife::Late_Update(void)
{
}

void CUILife::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		m_tInfo.fX,	// 2,3 ���� :  ������� ��ġ X, Y
		m_tInfo.fY,
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		(int)m_tInfo.fCX,
		0,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

}

void CUILife::Release(void)
{
}
