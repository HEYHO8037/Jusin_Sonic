#include "stdafx.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "Player.h"
#include "Spring.h"

TILEID	CCollisionMgr::m_eID = TILE_END;
bool	CCollisionMgr::m_bCircleCircle = false;
CTile*  CCollisionMgr::saveTile = nullptr;

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}


void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				Dest->Set_Dead();
				Sour->Set_Dead();
			}
		}
	}
}
// 고정되어 있는 물체  // 움직이는 물체		
void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				/*	Dest->Set_Dead();
					Sour->Set_Dead();*/

					// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dest->Get_Info().fY > Sour->Get_Info().fY)
						Sour->Set_PosY(-fY);

					else // 하 충돌
						Sour->Set_PosY(fY);

				}
				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dest->Get_Info().fX > Sour->Get_Info().fX)
						Sour->Set_PosX(-fX);

					// 우 충돌
					else
						Sour->Set_PosX(fX);
				}

			}
		}
	}
}

bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSour, float *pX, float* pY)
{
	float		fWidth = abs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float		fHeight = abs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float		fCX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
	float		fCY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f;

	if ((fCX > fWidth) && (fCY > fHeight))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}

	return false;
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
{

	// abs : 절대값을 구해주는 함수
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	// sqrt : 루트를 씌워주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;

	return fRadius > fDiagonal;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->Set_Dead();
				Sour->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Pixel(CObj* _Dest)
{
	bool(*bIsPixel)[TILECX * TILEX] = nullptr;
	bIsPixel = CTileMgr::Get_Instance()->Get_TotalPixel();
	bool bIsGround = false;

	int iBottom = _Dest->Get_Rect().bottom;
	int iTop = _Dest->Get_Rect().top;
	int iRight = _Dest->Get_Rect().right;
	int iLeft = _Dest->Get_Rect().left;
	int iMiddleX = (int)_Dest->Get_Info().fX;



	// 하단 충돌
	if (_Dest->Get_Rect().bottom < BACKGROUNDY)
	{
		if (_Dest->Get_Rect().top > 0)
		{
			for (int i = _Dest->Get_Rect().top + 16; i < iBottom; ++i)
			{
				if (dynamic_cast<CPlayer*>(_Dest)->Get_CirclePosX() != 0)
				{
					return;
				}
				else
				{

					if ((*(bIsPixel[i] + iMiddleX)) == true)
					{
						dynamic_cast<CPlayer*>(_Dest)->Set_Falling(false);
						dynamic_cast<CPlayer*>(_Dest)->Set_Jumping(false);
						float Floor = (float)_Dest->Get_Rect().bottom - i;
						dynamic_cast<CPlayer*>(_Dest)->Set_PosAddY(-Floor);

						return;
					}
				}
			}
		}
	}

	//상단 충돌
	if (_Dest->Get_Rect().bottom < BACKGROUNDY)
	{
		if (_Dest->Get_Rect().top > 64)
		{
			for (int i = _Dest->Get_Rect().left; i < iRight; ++i)
			{
				if (dynamic_cast<CPlayer*>(_Dest)->Get_Gravity() != UP_VERTICAL)
				{
					if ((*(bIsPixel[iTop] + i)) == true)
					{
						dynamic_cast<CPlayer*>(_Dest)->Set_Jumping(false);
						dynamic_cast<CPlayer*>(_Dest)->Set_Falling(true);

						return;
					}
				}

			}
		}
	}
	float fAngle = 0;

	//우측 충돌
	if (_Dest->Get_Rect().bottom < BACKGROUNDY)
	{
		if (_Dest->Get_Rect().top > 0)
		{
			for (int i = _Dest->Get_Rect().bottom - 32; i > iTop; --i)
			{
				if ((*(bIsPixel[i] + (iRight - 13))) == true)
				{
					_Dest->Set_Speed(0.f);
					_Dest->Set_PosX(_Dest->Get_Info().fX - 1);
				}
			}
		}
	}

	//좌측 충돌
	if (_Dest->Get_Rect().bottom < BACKGROUNDY)
	{
		if (_Dest->Get_Rect().top > 0)
		{

			for (int i = _Dest->Get_Rect().bottom - 32; i > iTop; --i)
			{
				if ((*(bIsPixel[i] + (iLeft + 13))) == true)
				{
					_Dest->Set_Speed(0.f);
					_Dest->Set_PosX(_Dest->Get_Info().fX);
				}
			}

		}
	}
}

void CCollisionMgr::Collision_Tile(CObj * _Dest)
{
	int		x = (int)_Dest->Get_Info().fX / TILECX;
	int		y = (int)_Dest->Get_Info().fY / TILECY;

	int	iIndex = y * TILEX + x;

	if (0 > iIndex || CTileMgr::Get_Instance()->Get_VecTile()->size() <= (size_t)iIndex)
		return;

	CTile* GetTile = dynamic_cast<CTile*>(CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex));
	m_eID = dynamic_cast<CTile*>(GetTile)->Get_TileID();

	if (m_eID == TILE_NORMAL)
	{
		dynamic_cast<CPlayer*>(_Dest)->Set_Gravity(DOWN_VERTICAL);
		dynamic_cast<CPlayer*>(_Dest)->Set_Falling(true);

	}
	else if (m_eID == TILE_SLIDE)
	{
		_Dest->Set_Speed(0.f);
		dynamic_cast<CPlayer*>(_Dest)->Set_QuatorCircle(true);
	}
	else if (m_eID == TILE_SLIDEUP)
	{
		dynamic_cast<CPlayer*>(_Dest)->Set_Falling(true);
		dynamic_cast<CPlayer*>(_Dest)->Set_Gravity(UP_VERTICAL);

	}
	else if (m_eID == TILE_CIRCLE)
	{
		iIndex = (y + 1) * TILEX + x;
		CTile* GetDownTile = dynamic_cast<CTile*>(CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex));

		if (saveTile != GetDownTile)
		{
			saveTile = nullptr;

			if (GetDownTile->Get_TileID() == TILE_CIRCLE && saveTile == nullptr)
			{
				bool bMask = GetDownTile->Get_Mask();
				saveTile = GetDownTile;
				GetDownTile->Set_Mask(!bMask);
			}
		}

		if (GetTile->Get_Mask() == false && m_bCircleCircle == false)
		{
			dynamic_cast<CPlayer*>(_Dest)->Set_SaveSpeed();
			_Dest->Set_Speed(0.f);
			dynamic_cast<CPlayer*>(_Dest)->Set_CirclePos(GetTile->Get_Rect().left, GetTile->Get_Rect().top);
			m_bCircleCircle = true;
		}

	}
	else
	{
		iIndex = (y + 1) * TILEX + x;
		CTile* GetDownTile = dynamic_cast<CTile*>(CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex));

		if (GetDownTile->Get_TileID() == TILE_SLIDEUP)
		{
			if (GetTile->Get_Operate() == false)
			{
				dynamic_cast<CPlayer*>(_Dest)->Set_Falling(true);
				dynamic_cast<CPlayer*>(_Dest)->Set_Gravity(UP_VERTICAL);
			}
			else
			{
				dynamic_cast<CPlayer*>(_Dest)->Set_Gravity(DOWN_VERTICAL);
				dynamic_cast<CPlayer*>(_Dest)->Set_Falling(true);

			}
		}
		else
		{
			if (GetDownTile->Get_Operate() == false)
			{
				GetDownTile->Set_Operate(true);
			}

			dynamic_cast<CPlayer*>(_Dest)->Set_Gravity(DOWN_VERTICAL);
			dynamic_cast<CPlayer*>(_Dest)->Set_Falling(true);
		}

	}
}

void CCollisionMgr::Collision_Player_Ring(CObj * _Dest, list<CObj*>* _Sour)
{
	RECT rc{};

	list<CObj*>::iterator iter = _Sour->begin();
	list<CObj*>::iterator iterEnd = _Sour->end();

	for (iter = _Sour->begin(); iter != iterEnd; ++iter)
	{
		if (IntersectRect(&rc, &(_Dest->Get_Rect()), &((*iter)->Get_Rect())))
		{
			dynamic_cast<CPlayer*>(_Dest)->Add_Ring();
			(*iter)->Set_Dead();
		}
	}

}

void CCollisionMgr::Collision_Player_Spike(CObj * _Dest, list<CObj*>* _Sour)
{
	RECT rc{};

	list<CObj*>::iterator iter = _Sour->begin();
	list<CObj*>::iterator iterEnd = _Sour->end();

	for (iter = _Sour->begin(); iter != iterEnd; ++iter)
	{
		if (IntersectRect(&rc, &(_Dest->Get_Rect()), &((*iter)->Get_Rect())))
		{
			float fSpeed = dynamic_cast<CPlayer*>(_Dest)->Get_Speed();
			dynamic_cast<CPlayer*>(_Dest)->Set_Speed(-(fSpeed / 2));
		}
	}

}

void CCollisionMgr::Collision_Player_Spring(CObj * _Dest, list<CObj*>* _Sour)
{
	RECT rc{};

	list<CObj*>::iterator iter = _Sour->begin();
	list<CObj*>::iterator iterEnd = _Sour->end();

	for (iter = _Sour->begin(); iter != iterEnd; ++iter)
	{
		if (IntersectRect(&rc, &(_Dest->Get_Rect()), &((*iter)->Get_Rect())))
		{
			dynamic_cast<CPlayer*>(_Dest)->Set_JumpPower(JUMP + 10);
			dynamic_cast<CPlayer*>(_Dest)->Set_Jumping(true);
			dynamic_cast<CSpring*>(*iter)->Add_iDrawID();

		}
		else
		{
			dynamic_cast<CSpring*>(*iter)->Reset_iDrawID();
		}
	}
}

void CCollisionMgr::Collision_Player_Point(CObj * _Dest, list<CObj*>* _Sour)
{
	RECT rc{};

	list<CObj*>::iterator iter = _Sour->begin();
	list<CObj*>::iterator iterEnd = _Sour->end();

	for (iter = _Sour->begin(); iter != iterEnd; ++iter)
	{
		if (_Dest->Get_Info().fX > (*iter)->Get_Info().fX)
		{
			dynamic_cast<CPlayer*>(_Dest)->Set_Speed(0.f);
			dynamic_cast<CPlayer*>(_Dest)->Set_IsGetPoint(true);
		}
	}

}
