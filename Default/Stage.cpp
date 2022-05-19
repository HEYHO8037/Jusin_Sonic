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
#include "Ring.h"
#include "Spike.h"
#include "Goal.h"
#include "Spring.h"
#include "SoundMgr.h"
#include "InGameStart.h"
#include "UIScore.h"
#include "UILife.h"
#include "UINum.h"

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
	CSoundMgr::Get_Instance()->PlayBGM(L"MushRoomBGM.mp3", 1.f);

	CCamera::Get_Instance()->SetClientResolution(WINCX, WINCY);
	CCamera::Get_Instance()->SetWorldResolution(BACKGROUNDX, BACKGROUNDY);

	CTileMgr::Get_Instance()->Load_Tile();

	CObjMgr::Get_Instance()->Load_Ring();
	CObjMgr::Get_Instance()->Load_Spring();
	CObjMgr::Get_Instance()->Load_Spike();
	CObjMgr::Get_Instance()->Load_Point();
	CObjMgr::Get_Instance()->Load_MushRoom();
	CObjMgr::Get_Instance()->Load_BackGroundObj_1();
	CObjMgr::Get_Instance()->Load_BackGroundObj_2();
	CObjMgr::Get_Instance()->Load_BackGroundObj_3();

	
	CObj* pPlayer = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
	
	CCamera::Get_Instance()->SetTarget(pPlayer);
	CCamera::Get_Instance()->SetPivot(0.8f, 0.3f);


	CObj* pUI = CAbstractFactory<InGameStart>::Create();
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pUI);

	pUI = CAbstractFactory<CUILife>::Create();
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pUI);


	pUI = CAbstractFactory<CUIScore>::Create();
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pUI);





}	


void CStage::Update(void)
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CCollisionMgr::Collision_Tile(CObjMgr::Get_Instance()->Get_Player());
	CCollisionMgr::Collision_Pixel(CObjMgr::Get_Instance()->Get_Player());
	CCollisionMgr::Collision_Player_Ring(CObjMgr::Get_Instance()->Get_Player(), CObjMgr::Get_Instance()->Get_OBJType(OBJ_ITEM));
	CCollisionMgr::Collision_Player_Spike(CObjMgr::Get_Instance()->Get_Player(), CObjMgr::Get_Instance()->Get_OBJType(OBJ_SPIKE));
	CCollisionMgr::Collision_Player_Spring(CObjMgr::Get_Instance()->Get_Player(), CObjMgr::Get_Instance()->Get_OBJType(OBJ_SPRING));
	CCollisionMgr::Collision_Player_Point(CObjMgr::Get_Instance()->Get_Player(), CObjMgr::Get_Instance()->Get_OBJType(OBJ_POINT));
	CCollisionMgr::Collision_Player_MushRoom(CObjMgr::Get_Instance()->Get_Player(), CObjMgr::Get_Instance()->Get_OBJType(OBJ_MUSHROOM));
	
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
	
	BitBlt(hDC, (int)tPos.x, (int)tPos.y,
		WINCX, WINCY, hGroundMemDC,
		(int)tCamPos.x, (int)tCamPos.y, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CStage::Release(void)
{
	CCamera::Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(OBJ_ITEM);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_SPIKE);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_POINT);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_SPRING);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MUSHROOM);
}

void CStage::Move_Frame(void)
{
}
