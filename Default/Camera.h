#pragma once

#include "Include.h"
class CCamera
{


private:
	CCamera();
	~CCamera();

private:
	POSITION m_tPos;
	RESOLUTION m_tClientRS;
	RESOLUTION m_tWorldRS;
	POSITION m_tPivot;
	class CObj* m_pTarget;

public:
	void SetTarget(class CObj* pObj);
	void SetPivot(const POSITION& tPivot);
	void SetPivot(float x, float y);
	void SetPos(const POSITION& tPos);
	void SetPos(float x, float y);
	void SetClientResolution(const RESOLUTION& tRS);
	void SetClientResolution(float x, float y);
	void SetWorldResolution(const RESOLUTION& tRS);
	void SetWorldResolution(float x, float y);
	void Scroll(float x, float y);

public:
	POSITION GetPos() const;
	RESOLUTION GetClientRS() const;

public:
	bool Init(const POSITION& tPos, const RESOLUTION& tClientRS, const RESOLUTION& tWorldRS);
	void Update();

private:
	static CCamera* m_pInst;
public:
	static CCamera* Get_Instance()
	{
		if (!m_pInst)
		{
			m_pInst = new CCamera;
		}
		return m_pInst;
	}
	static void Destroy_Instance()
	{
		if (m_pInst)
		{
			delete m_pInst;
		}
	}

	static CCamera*	Show_Instance()
	{
		return m_pInst;
	}
};

