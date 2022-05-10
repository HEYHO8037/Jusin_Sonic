#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "LineMgr.h"


CTile::CTile()
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iDrawID = 0;
	m_iOption = 0;
	m_bIsCheck = false;


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TileMap/MushroomTile.bmp", L"Tile");
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

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile");
	
	GdiTransparentBlt(hDC,
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		(int)m_tInfo.fCX * m_iDrawID,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		(int)m_tInfo.fCY * m_iOption,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	if (!m_bIsCheck)
	{
		for (int i = 0; i < TILECY; ++i)
		{
			for (int j = 0; j < TILECX; ++j)
			{
				if (GetPixel(hMemDC, (int)m_tInfo.fCX * m_iDrawID + j,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
					(int)m_tInfo.fCY * m_iOption + i) == RGB(225, 0, 255) || m_iDrawID == 0)
				{
					m_bIsCollider[i][j] = 0;
				}
				else
				{
					m_bIsCollider[i][j] = 1;
				}
			}
		}

		m_bIsCheck = true;
	}



}

void CTile::Release(void)
{
	
}
