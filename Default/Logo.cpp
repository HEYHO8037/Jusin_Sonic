#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"


CLogo::CLogo()
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/LogoAndMain/Logo.bmp", L"Logo");
	
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	CSoundMgr::Get_Instance()->PlayBGM(L"TitleBGM.mp3", 1.f);

}

void CLogo::Update(void)
{
	if (m_tFrame.iMotion > 3)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}

	Move_Frame();
}

void CLogo::Late_Update(void)
{

}

void CLogo::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");
	
	BitBlt(hDC, 0, 0, WINCX, WINCY,
		hMemDC, 
		m_tFrame.iFrameStart * WINCX,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * WINCY,
		SRCCOPY);
}

void CLogo::Release(void)
{
	
}

void CLogo::Move_Frame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iMotion++;
		}
	}

}