#pragma once

#include "Include.h"

class CLine
{
public:
	CLine();
	CLine(LINE tLine);
	CLine(LINEPOINT& tLeft, LINEPOINT& tRight);
	~CLine();

public:
	const LINE& Get_Info(void) const { return m_tInfo; }
	void Set_Info(LINEPOINT& tLeft, LINEPOINT& tRight);

public:
	void	Render(HDC hDC);

private:
	LINE		m_tInfo;
};

