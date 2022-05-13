#include "stdafx.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "Player.h"

TILEID	CCollisionMgr::m_eID = TILE_END;

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
	float	fWidth  = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
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
			for (int i = _Dest->Get_Rect().top; i < iBottom; ++i)
			{
				if ((*(bIsPixel[i] + iLeft + 9)) == true && 
				    (*(bIsPixel[i] + iMiddleX)) == true )
				{
					dynamic_cast<CPlayer*>(_Dest)->Set_Falling(false);
					dynamic_cast<CPlayer*>(_Dest)->Set_Jumping(false);
					float Floor = (float)_Dest->Get_Rect().bottom - i;
					dynamic_cast<CPlayer*>(_Dest)->Set_PosAddY(-Floor);


					break;
				}
				if ((*(bIsPixel[i] + iRight - 9)) == true &&
					(*(bIsPixel[i] + iMiddleX)) == true)
				{
					dynamic_cast<CPlayer*>(_Dest)->Set_Falling(false);
					dynamic_cast<CPlayer*>(_Dest)->Set_Jumping(false);
					float Floor = (float)_Dest->Get_Rect().bottom - i;
					dynamic_cast<CPlayer*>(_Dest)->Set_PosAddY(-Floor);
					break;
				}
				else
				{
					dynamic_cast<CPlayer*>(_Dest)->Set_Falling(true);
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
				if ((*(bIsPixel[iTop] + i)) == true)
				{
					dynamic_cast<CPlayer*>(_Dest)->Set_Jumping(false);
					dynamic_cast<CPlayer*>(_Dest)->Set_Falling(true);

					break;
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
			int iCount = 0;

			for (int i = _Dest->Get_Rect().bottom; i > iTop - 1; --i)
			{
				if ((*(bIsPixel[i] + iRight)) == true)
				{
					if (iCount > 31 && m_eID == TILE_SLIDE)
					{
						int rX = i - _Dest->Get_Rect().bottom;
						int rY = i - dynamic_cast<CPlayer*>(_Dest)->Get_Ground();

						fAngle = atan(rY / rX) * 180 / PI;
						_Dest->Set_Angle(-fAngle);

						dynamic_cast<CPlayer*>(_Dest)->Set_Gravity(LEFT_HORIZIONAL);

					}
					else
					{
						iCount++;
					}
				}
			}
		}
	}

	//좌측 충돌
	if (_Dest->Get_Rect().bottom < BACKGROUNDY)
	{
		if (_Dest->Get_Rect().top > 0)
		{
			int iCount = 0;

			for (int i = _Dest->Get_Rect().bottom; i < iTop - 1; --i)
			{
				if ((*(bIsPixel[i] + iLeft)) == true)
				{
					iCount++;
				}
			}

			if (iCount > 31)
			{
				if (m_eID == TILE_SLIDE)
				{

				}
				else
				{
					dynamic_cast<CPlayer*>(_Dest)->Set_Speed(0.f);
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
}
