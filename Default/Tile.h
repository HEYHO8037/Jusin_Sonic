#pragma once

#include "Obj.h"
#include "MyBmp.h"

class CTile :	public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	const int& Get_DrawID(void) { return m_iDrawID; }
	const int& Get_Option(void) { return m_iOption; }
	const void Set_bCollider(bool (*bIsCollider)[TILECX * TILEX]) { m_bIsCollider = bIsCollider; }

public:
	void		Set_TileID(TILEID eID) { m_eTileID = eID; }
	void		Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void		Set_Option(int _iOption) { m_iOption = _iOption; }
	void		Set_IsCheck(bool bCheck) { m_bIsCheck = bCheck;  }
	void		Set_BmpRGB(CMyBmp* pBmp) { m_BmpRGB = pBmp; }

public:
	const TILEID		Get_TileID() { return m_eTileID; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool		m_bIsCheck;
	bool		(*m_bIsCollider)[TILECX * TILEX];
	int			m_iDrawID;
	int			m_iOption;

	CMyBmp*		m_BmpRGB;
	TILEID		m_eTileID;
};

