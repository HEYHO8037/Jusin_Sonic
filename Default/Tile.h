#pragma once

#include "Obj.h"

class CTile :	public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	const int& Get_DrawID(void) { return m_iDrawID; }
	const int& Get_Option(void) { return m_iOption; }
	const bool* Get_bIsCollider() { return *m_bIsCollider; }

public:
	void		Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void		Set_Option(int _iOption) { m_iOption = _iOption; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool		m_bIsCheck;
	bool		m_bIsCollider[TILECY][TILECX];
	int			m_iDrawID;
	int			m_iOption;

};

