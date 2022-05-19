#include "stdafx.h"
#include "InGameEnd.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

InGameEnd::InGameEnd()
{
}


InGameEnd::~InGameEnd()
{
}

void InGameEnd::Initialize(void)
{
	m_tInfo.fX = 50;
	m_tInfo.fY = 50;

	m_tInfo.fCX = 211.f;
	m_tInfo.fCY = 117.f;

	m_tPivot = POSITION(0.5, 0.5);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/End1.bmp", L"End");



}

int InGameEnd::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}


	Update_Rect();

	

	return OBJ_NOEVENT;
}

void InGameEnd::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		m_bDead = true;
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
	}

}

void InGameEnd::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"End");

	GdiTransparentBlt(hDC,
		m_tInfo.fX,	// 2,3 인자 :  복사받을 위치 X, Y
		m_tInfo.fY,
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));


}

void InGameEnd::Release(void)
{

}
