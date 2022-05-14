#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "AnimateImage.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/LogoAndMain/MainBack.bmp", L"MainBack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/LogoAndMain/MainSonic.bmp", L"MainSonic");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/LogoAndMain/MainTitle.bmp", L"MainTitle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/LogoAndMain/Airplane.bmp", L"Airplane");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/LogoAndMain/MainYear.bmp", L"MainYear");


	BackGroundFrame.iFrameStart = 0;
	BackGroundFrame.iFrameEnd = 0;
	BackGroundFrame.iMotion = 0;
	BackGroundFrame.dwSpeed = 1000;
	BackGroundFrame.dwTime = GetTickCount();

	CObj* pAnimateImage = CAbstractFactory<CAnimateImage>::Create(-10.f, 90.f);
	pAnimateImage->Set_FrameKey(L"Airplane");
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pAnimateImage);
	pAnimateImage->Set_Size(54, 24);
	dynamic_cast<CAnimateImage*>(pAnimateImage)->SetMaxFrameX(2);
	pAnimateImage->Set_Dir(DIR_RIGHT);
	dynamic_cast<CAnimateImage*>(pAnimateImage)->SetTargetX(WINCX + 50);


	pAnimateImage = CAbstractFactory<CAnimateImage>::Create(160.f, 110.f);
	pAnimateImage->Set_FrameKey(L"MainSonic");
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pAnimateImage);
	pAnimateImage->Set_Size(240, 170);
	dynamic_cast<CAnimateImage*>(pAnimateImage)->SetMaxFrameX(3);
	dynamic_cast<CAnimateImage*>(pAnimateImage)->SetMaxFrameY(3);
		
	pAnimateImage = CAbstractFactory<CAnimateImage>::Create(160.f, WINCY + 10);
	pAnimateImage->Set_FrameKey(L"MainTitle");
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pAnimateImage);
	pAnimateImage->Set_Size(260, 80);
	pAnimateImage->Set_Dir(DIR_UP);
	dynamic_cast<CAnimateImage*>(pAnimateImage)->SetTargetY(180.f);


}

void CMyMenu::Update(void)
{
	Move_Frame();

	CObjMgr::Get_Instance()->Update();
}

void CMyMenu::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);
		return;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT);
		return;
	}
}

void CMyMenu::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MainBack");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, BackGroundFrame.iFrameStart * WINCX, BackGroundFrame.iMotion * WINCY, SRCCOPY);

	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MainYear");
	GdiTransparentBlt(hDC, 220, 228, 100, 12, hMemDC, 0, 0, 100, 12, RGB(255, 0, 255));

	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyMenu::Move_Frame(void)
{
	if (BackGroundFrame.iMotion > 1)
	{
		BackGroundFrame.iMotion = 0;
	}

	if (BackGroundFrame.dwTime + BackGroundFrame.dwSpeed < GetTickCount())
	{
		BackGroundFrame.iFrameStart++;

		BackGroundFrame.dwTime = GetTickCount();

		if (BackGroundFrame.iFrameStart > BackGroundFrame.iFrameEnd)
		{
			BackGroundFrame.iFrameStart = 0;
			BackGroundFrame.iMotion++;
		}
	}

}

void CMyMenu::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_UI);
}