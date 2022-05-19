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


	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		m_tInfo.fX,	// 2,3 인자 :  복사받을 위치 X, Y
		m_tInfo.fY,
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		(int)m_tInfo.fCX,
		0,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

}

void CUILife::Release(void)
{
}
