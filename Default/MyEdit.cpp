#include "stdafx.h"
#include "MyEdit.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Camera.h"


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
}

void CMyEdit::Update(void)
{
	CTileMgr::Get_Instance()->Update();

	Key_Input();
}

void CMyEdit::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC hDC)
{
	int ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC backHdc = CBmpMgr::Get_Instance()->Find_Image(L"Ground");
	BitBlt(hDC, ScrollX, ScrollY, BACKGROUNDX, BACKGROUNDY, backHdc, 0, 0, SRCCOPY);

	
	CTileMgr::Get_Instance()->Render(hDC);
}

void CMyEdit::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
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

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 3, 0);
		
		int		x = pt.x / TILECX;
		int		y = pt.y / TILECY;

		int	iIndex = y * TILEX + x;

		CObj* pTile = CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex);
		dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_NORMAL);

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

	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('R'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 3, 1);

		int		x = pt.x / TILECX;
		int		y = pt.y / TILECY;

		int	iIndex = y * TILEX + x;

		CObj* pTile = CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex);
		dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_NORMAL);

	}


	if (CKeyMgr::Get_Instance()->Key_Pressing('E'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 6, 1);

		int		x = pt.x / TILECX;
		int		y = pt.y / TILECY;

		int	iIndex = y * TILEX + x;

		CObj* pTile = CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex);
		dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_SLIDE);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 3, 4);

		int		x = pt.x / TILECX;
		int		y = pt.y / TILECY;

		int	iIndex = y * TILEX + x;

		CObj* pTile = CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex);
		dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_SLIDE);

	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('Y'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 4, 10);

		int		x = pt.x / TILECX;
		int		y = pt.y / TILECY;

		int	iIndex = y * TILEX + x;

		CObj* pTile = CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex);
		dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_CIRCLE);

	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('U'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 7, 10);

		int		x = pt.x / TILECX;
		int		y = pt.y / TILECY;

		int	iIndex = y * TILEX + x;

		CObj* pTile = CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex);
		dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_CIRCLE);

	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('I'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 0, 10);

		int		x = pt.x / TILECX;
		int		y = pt.y / TILECY;

		int	iIndex = y * TILEX + x;

		CObj* pTile = CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex);
		dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_CIRCLE);

	}


	if (CKeyMgr::Get_Instance()->Key_Pressing('O'))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 10);

		int		x = pt.x / TILECX;
		int		y = pt.y / TILECY;

		int	iIndex = y * TILEX + x;

		CObj* pTile = CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex);
		dynamic_cast<CTile*>(pTile)->Set_TileID(TILE_CIRCLE);

	}




	if (CKeyMgr::Get_Instance()->Key_Down('S'))
		CTileMgr::Get_Instance()->Save_Tile();

	if (CKeyMgr::Get_Instance()->Key_Down('A'))
		CTileMgr::Get_Instance()->Load_Tile();

}
