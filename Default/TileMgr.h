#pragma once

#include "Tile.h"
#include "MyBmp.h"

class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	bool		(*Get_TotalPixel(void))[TILECX * TILEX];
	void		Picking_Tile(POINT _pt, const int& _iDrawID, const int& _iOption);
	void		Save_Tile(void);
	void		Load_Tile(void);
	const vector<CObj*>* Get_VecTile();

public:
	static		CTileMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CTileMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CTileMgr*		m_pInstance;
	vector<CObj*>			m_vecTile;
	bool					m_bTotalPixel[TILECY * TILEY][TILECX * TILEX];
	CMyBmp* m_BmpRGB;
	CMyBmp* m_CollisionBmpRGB;
};

