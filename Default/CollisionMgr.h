#pragma once

#include "Obj.h"
#include "Tile.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static bool		Check_Sphere(CObj* pDest, CObj* pSour);
	static bool		Check_Rect(CObj* pDest, CObj* pSour, float *pX, float* pY);
	static void		Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Pixel(CObj* _Dest);
	
public:
	static void		Collision_Tile(CObj* _Dest);
	static void		Collision_Player_Ring(CObj* _Dest, list<CObj*>* _Sour);
	static void		Collision_Player_Spike(CObj* _Dest, list<CObj*>* _Sour);
	static void		Collision_Player_Spring(CObj* _Dest, list<CObj*>* _Sour);
	static void		Collision_Player_Point(CObj* _Dest, list<CObj*>* _Sour);

private:
	static TILEID	m_eID;
	static bool		m_bCircleCircle;
	static CTile*	saveTile;
};

