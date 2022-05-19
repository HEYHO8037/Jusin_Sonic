#include "stdafx.h"
#include "MyEdit.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Ring.h"
#include "Spike.h"
#include "Spring.h"
#include "Goal.h"
#include "Mushroom.h"
#include "SoundMgr.h"
#include "BGMushroom_1.h"
#include "BGMushroom_2.h"
#include "BGMushroom_3.h"


CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TileMap/MushroomBack.bmp", L"Ground");
	CTileMgr::Get_Instance()->Initialize();
	CObjMgr::Get_Instance();
	CSoundMgr::Get_Instance()->PlayBGM(L"MushRoomBGM.mp3", 1.f);
	m_fX = 0;
	m_fY = 0;

}

void CMyEdit::Update(void)
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	Key_Input();
}

void CMyEdit::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC hDC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC backHdc = CBmpMgr::Get_Instance()->Find_Image(L"Ground");
	BitBlt(hDC, ScrollX, ScrollY, BACKGROUNDX, BACKGROUNDY, backHdc, 0, 0, SRCCOPY);

	
	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyEdit::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
}

void CMyEdit::Move_Frame(void)
{
}

void CMyEdit::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 0, 0);
		
		int		x = pt.x / TILECX;
		int		y = pt.y / TILECY;

		int	iIndex = y * TILEX + x;

		CObj* pTile = CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex);
		dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_NORMAL);
		dynamic_cast<CTile*>(pTile)->Set_Mask(true);

	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 0);

		int		x = pt.x / TILECX;
		int		y = pt.y / TILECY;

		int	iIndex = y * TILEX + x;

		CObj* pTile = CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex);
		dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_NORMAL);
		dynamic_cast<CTile*>(pTile)->Set_Mask(true);

	}

	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{

		m_fX++;
		if (m_fX > 7)
		{
			m_fX = 0;
		}


		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, m_fX, m_fY);

		int		x = pt.x / TILECX;
		int		y = pt.y / TILECY;

		int	iIndex = y * TILEX + x;

		CObj* pTile = CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex);
		
		if(m_fY == 10)
		{ 
			dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_CIRCLE);
		}
		else if(m_fX == 6 && m_fY == 1)
		{
			dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_SLIDE);
		}
		else if (m_fY == 4)
		{
			dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_SLIDEUP);
		}
		else
		{
			dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_NORMAL);
		}


		if (m_fY == 10 && m_fX == 6)
		{
			dynamic_cast<CTile*>(pTile)->Set_Mask(false);
		}
		else
		{
			dynamic_cast<CTile*>(pTile)->Set_Mask(true);
		}


	}

	if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{

		m_fY++;

		if (m_fY > 11)
		{
			m_fY = 0;
		}

		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, m_fX, m_fY);

		int		x = pt.x / TILECX;
		int		y = pt.y / TILECY;

		int	iIndex = y * TILEX + x;

		CObj* pTile = CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex);

		if (m_fY == 10)
		{
			dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_CIRCLE);
		}
		else if (m_fX == 6 && m_fY == 1)
		{
			dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_SLIDE);
		}
		else if (m_fY == 4)
		{
			dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_SLIDEUP);
		}
		else
		{
			dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_NORMAL);
		}
		

		if (m_fY == 10 && m_fX == 6)
		{
			dynamic_cast<CTile*>(pTile)->Set_Mask(false);
		}
		else
		{
			dynamic_cast<CTile*>(pTile)->Set_Mask(true);
		}

	}






	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CObj* pObj = CAbstractFactory<CRing>::Create((float)pt.x, (float)pt.y);
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);

	}

	if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CObj* pObj = CAbstractFactory<CSpike>::Create((float)pt.x, (float)pt.y);
		CObjMgr::Get_Instance()->Add_Object(OBJ_SPIKE, pObj);

	}

	if (CKeyMgr::Get_Instance()->Key_Down('3'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CObj* pObj = CAbstractFactory<CSpring>::Create((float)pt.x, (float)pt.y);
		CObjMgr::Get_Instance()->Add_Object(OBJ_SPRING, pObj);

	}

	if (CKeyMgr::Get_Instance()->Key_Down('4'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CObj* pObj = CAbstractFactory<CGoal>::Create((float)pt.x, (float)pt.y);
		CObjMgr::Get_Instance()->Add_Object(OBJ_POINT, pObj);

	}

	if (CKeyMgr::Get_Instance()->Key_Down('5'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CObj* pObj = CAbstractFactory<CMushroom>::Create((float)pt.x, (float)pt.y);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MUSHROOM, pObj);

	}

	if (CKeyMgr::Get_Instance()->Key_Down('6'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CObj* pObj = CAbstractFactory<CBGMushroom_1>::Create((float)pt.x, (float)pt.y);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BG1, pObj);

	}

	if (CKeyMgr::Get_Instance()->Key_Down('7'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CObj* pObj = CAbstractFactory<CBGMushroom_2>::Create((float)pt.x, (float)pt.y);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BG2, pObj);

	}

	if (CKeyMgr::Get_Instance()->Key_Down('8'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CObj* pObj = CAbstractFactory<CBGMushroom_3>::Create((float)pt.x, (float)pt.y);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BG3, pObj);

	}




	if (CKeyMgr::Get_Instance()->Key_Down(VK_TAB))
	{
		CTileMgr::Get_Instance()->Save_Tile();
		CObjMgr::Get_Instance()->Save_Ring();
		CObjMgr::Get_Instance()->Save_Spring();
		CObjMgr::Get_Instance()->Save_Spike();
		CObjMgr::Get_Instance()->Save_Point();
		CObjMgr::Get_Instance()->Save_MushRoom();
		CObjMgr::Get_Instance()->Save_BackGroundObj_1();
		CObjMgr::Get_Instance()->Save_BackGroundObj_2();
		CObjMgr::Get_Instance()->Save_BackGroundObj_3();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LSHIFT))
	{
		CTileMgr::Get_Instance()->Load_Tile();
		CObjMgr::Get_Instance()->Load_Ring();
		CObjMgr::Get_Instance()->Load_Spring();
		CObjMgr::Get_Instance()->Load_Spike();
		CObjMgr::Get_Instance()->Load_Point();
		CObjMgr::Get_Instance()->Load_MushRoom();
		CObjMgr::Get_Instance()->Load_BackGroundObj_1();
		CObjMgr::Get_Instance()->Load_BackGroundObj_2();
		CObjMgr::Get_Instance()->Load_BackGroundObj_3();
	}

}
