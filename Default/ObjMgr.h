#pragma once

#include "Obj.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	list<CObj*>* Get_OBJType(OBJID eID) { return &m_ObjList[eID]; }
	CObj*		Get_Target(OBJID eID, CObj* pObj);

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Delete_ID(OBJID eID);

public:
	void Save_Ring(void);
	void Save_Spring(void);
	void Save_Spike(void);
	void Save_Point(void);
	void Save_MushRoom(void);
	void Save_BackGroundObj_1(void);
	void Save_BackGroundObj_2(void);
	void Save_BackGroundObj_3(void);

	void Load_Ring(void);
	void Load_Spring(void);
	void Load_Spike(void);
	void Load_Point(void);
	void Load_MushRoom(void);
	void Load_BackGroundObj_1(void);
	void Load_BackGroundObj_2(void);
	void Load_BackGroundObj_3(void);


private:
	list<CObj*>	m_ObjList[OBJ_END];

public:
	static		CObjMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
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
	static CObjMgr*			m_pInstance;

};

