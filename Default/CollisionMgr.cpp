#include "stdafx.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "Player.h"


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
	int		x = _Dest->Get_Info().fX / TILECX;
	int		y = _Dest->Get_Info().fY / TILECY;

	int	iIndex = y * TILEX + x;

	if (0 > iIndex || CTileMgr::Get_Instance()->Get_VecTile()->size() <= (size_t)iIndex)
		return;

	CTile* GetTile = dynamic_cast<CTile*>(CTileMgr::Get_Instance()->Get_VecTile()->at(iIndex));
	const bool(*bCollider)[TILECX] = nullptr;

	bCollider = GetTile->Get_bIsCollider();

	float	fX = 0.f, fY = 0.f;
	int		iSave = 0;

	if (Check_Rect(_Dest, GetTile, &fX, &fY))
	{
		// 상하 충돌
		if (fX >= fY)
		{
			// 상 충돌
			if (_Dest->Get_Info().fY < GetTile->Get_Info().fY)
			{
				for (int i = 0; i < fY; ++i)
				{
					for (int j = 0; j < fX; ++j)
					{
						if (*(bCollider + i)[j] == true)
						{
							iSave = i;
						}
					}
				}

				if (_Dest->Get_Rect().bottom >= GetTile->Get_Rect().top + iSave && iSave != 0)
				{
					dynamic_cast<CPlayer*>(_Dest)->Set_Falling(false);
				}

			}
			else // 하 충돌
			{
			/*	for (int i = 0; i < fY; ++i)
				{
					for (int j = 0; j < fX; ++j)
					{
						if (*(bCollider + i)[j] == true)
						{
							dynamic_cast<CPlayer*>(_Dest)->Set_Falling(false);
						}
					}
				}*/
			}

		}
		// 좌우 충돌
		else
		{
			// 좌 충돌
			if (_Dest->Get_Info().fX < GetTile->Get_Info().fX)
			{
				for (int i = 0; i < fX; ++i)
				{
					for (int j = 0; j < fY; ++j)
					{
						if (*(bCollider + i)[j] == 1 )
						{
							//dynamic_cast<CPlayer*>(_Dest)->Set_PosY(GetTile->Get_Rect().bottom - j);
						}
					}
				}
			}

			// 우 충돌
			else
			{
				for (int i = 0; i < fX; ++i)
				{
					for (int j = 0; j < fY; ++j)
					{
						if (*(bCollider + i)[j] == 1)
						{
							//dynamic_cast<CPlayer*>(_Dest)->Set_PosX(GetTile->Get_Rect().right - i);
						}
					}
				}
			}
		}
	}

}
