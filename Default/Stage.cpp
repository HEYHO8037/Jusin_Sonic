#include "stdafx.h"
#include "Stage.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "CollisionMgr.h"
#include "Camera.h"


CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TileMap/MushroomBack.bmp", L"Ground");
	CTileMgr::Get_Instance()->Load_Tile();
	CObj* pPlayer = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);

	CCamera::Get_Instance()->SetTarget(pPlayer);
	CCamera::Get_Instance()->SetPivot(0.8f, 0.3f);
	CCamera::Get_Instance()->SetClientResolution(WINCX, WINCY);
	CCamera::Get_Instance()->SetWorldResolution(BACKGROUNDX, BACKGROUNDY);
}	


void CStage::Update(void)
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CCollisionMgr::Collision_Tile(CObjMgr::Get_Instance()->Get_Player());
	CCollisionMgr::Collision_Pixel(CObjMgr::Get_Instance()->Get_Player());
	CCamera::Get_Instance()->Update();

}

void CStage::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();

}

void CStage::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");
	
	POSITION tPos;

	tPos.x = 0 - BACKGROUNDX * 0;
	tPos.y = 0 - BACKGROUNDY * 0;

	POSITION tCamPos = CCamera::Get_Instance()->GetPos();

	BitBlt(hDC, tPos.x, tPos.y,
		WINCX, WINCY, hGroundMemDC,
		tCamPos.x, tCamPos.y, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CStage::Release(void)
{
	CCamera::Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
}

void CStage::Move_Frame(void)
{
}
