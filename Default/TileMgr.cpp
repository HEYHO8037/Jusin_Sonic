#include "stdafx.h"
#include "TileMgr.h"
#include "AbstractFactory.h"

CTileMgr*	CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float		fX = (TILECX >> 1) + float(TILECX * j);
			float		fY = (TILECY >> 1) + float(TILECY * i);

			CObj*	pTile = CAbstractFactory<CTile>::Create(fX, fY);
			m_vecTile.push_back(pTile);
		}
	}

}

void CTileMgr::Update()
{
	for (auto& iter : m_vecTile)
		iter->Update();
}

void CTileMgr::Late_Update()
{
	for (auto& iter : m_vecTile)
		iter->Late_Update();
}

void CTileMgr::Render(HDC hDC)
{
	for (auto& iter : m_vecTile)
		iter->Render(hDC);
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
}
