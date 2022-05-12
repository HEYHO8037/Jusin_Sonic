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
	m_BmpRGB = nullptr;
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

	if (!m_bIsCheck)
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

}

void CTile::Release(void)
{
	
}
