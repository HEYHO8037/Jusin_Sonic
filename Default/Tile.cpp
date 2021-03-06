#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "LineMgr.h"
#include "Camera.h"


CTile::CTile()
{
	m_BmpRGB = nullptr;
	m_CollisionBmpRGB = nullptr;
	m_bIsOperate = false;
	m_bIsMask = true;
}


CTile::~CTile()
{
	Release();
	m_BmpRGB = nullptr;
	m_CollisionBmpRGB = nullptr;
}

void CTile::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_tPivot = POSITION(0.5, 0.5);

	m_iDrawID = 0;
	m_iOption = 0;
	m_bIsCheck = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TileMap/MushroomTile.bmp", L"Tile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TileMap/MushroomTileMask.bmp", L"TileMask");
}

int CTile::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	

	Update_Rect();

	return OBJ_NOEVENT;
}

void CTile::Late_Update(void)
{

}

void CTile::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (!m_bIsMask)
	{
		if (!m_bIsCheck && m_BmpRGB != nullptr)
		{
			for (int i = 0; i < TILECY; ++i)
			{
				for (int j = 0; j < TILECX; ++j)
				{
					int x = ((int)m_tInfo.fCX * m_iDrawID) + j;
					int y = ((int)m_tInfo.fCY * m_iOption) + i;

					if ((m_BmpRGB->PosR(x, y) == 255) &&
						(m_BmpRGB->PosG(x, y) == 0) &&
						(m_BmpRGB->PosB(x, y) == 255))
					{
						int Y = m_tRect.top + i;
						int X = m_tRect.left + j;
						*((m_bIsCollider[Y]) + X) = false;
					}
					else
					{
						int Y = m_tRect.top + i;
						int X = m_tRect.left + j;
						*((m_bIsCollider[Y]) + X) = true;
					}
				}
			}

			m_bIsCheck = true;
		}
	}
	else
	{
		if (!m_bIsCheck && m_CollisionBmpRGB != nullptr)
		{
			for (int i = 0; i < TILECY; ++i)
			{
				for (int j = 0; j < TILECX; ++j)
				{
					int x = ((int)m_tInfo.fCX * m_iDrawID) + j;
					int y = ((int)m_tInfo.fCY * m_iOption) + i;

					if ((m_CollisionBmpRGB->PosR(x, y) == 255) &&
						(m_CollisionBmpRGB->PosG(x, y) == 0) &&
						(m_CollisionBmpRGB->PosB(x, y) == 255))
					{
						int Y = m_tRect.top + i;
						int X = m_tRect.left + j;
						*((m_bIsCollider[Y]) + X) = false;
					}
					else
					{
						int Y = m_tRect.top + i;
						int X = m_tRect.left + j;
						*((m_bIsCollider[Y]) + X) = true;
					}
				}
			}

			m_bIsCheck = true;
		}

	}

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile");


	if (CCamera::Show_Instance() != nullptr)
	{
		POSITION tPos;
		tPos.x = m_tInfo.fX - m_tInfo.fCX * m_tPivot.x;
		tPos.y = m_tInfo.fY - m_tInfo.fCY * m_tPivot.y;
		tPos -= CCamera::Get_Instance()->GetPos();

		GdiTransparentBlt(hDC,
			tPos.x,	// 2,3 ???? :  ???????? ???? X, Y
			tPos.y,
			int(m_tInfo.fCX),				// 4,5 ???? : ???????? ????, ???? ????
			int(m_tInfo.fCY),
			hMemDC,							// ???????? ?????? ???? DC
			(int)m_tInfo.fCX * m_iDrawID,								// ?????? ???? ???? ????, X,Y
			(int)m_tInfo.fCY * m_iOption,
			(int)m_tInfo.fCX,				// ?????? ???????? ????, ???? ????
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
	else
	{
		float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
		float ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

		GdiTransparentBlt(hDC,
			int(m_tInfo.fX) + iScrollX,	// 2,3 ???? :  ???????? ???? X, Y
			int(m_tInfo.fY) + iScrollY,
			int(m_tInfo.fCX),				// 4,5 ???? : ???????? ????, ???? ????
			int(m_tInfo.fCY),
			hMemDC,							// ???????? ?????? ???? DC
			(int)m_tInfo.fCX * m_iDrawID,								// ?????? ???? ???? ????, X,Y
			(int)m_tInfo.fCY * m_iOption,
			(int)m_tInfo.fCX,				// ?????? ???????? ????, ???? ????
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));

	}

}

void CTile::Release(void)
{
	
}
