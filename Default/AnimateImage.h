#pragma once
#include "Obj.h"
class CAnimateImage :
	public CObj
{
public:
	CAnimateImage();
	virtual ~CAnimateImage();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void SetMaxFrameX(int iFrameX) { m_tFrame.iFrameEnd = iFrameX; }
	void SetMaxFrameY(int iFrameY) { m_iMaxFrameY = iFrameY;  }
	
	void SetTargetX(float X) { m_fTargetX = X; }
	void SetTargetY(float Y) { m_fTargetY = Y; }


private:
	void MoveToTarget();

	float m_fTargetX;
	float m_fTargetY;
	int m_iMaxFrameY;
};

