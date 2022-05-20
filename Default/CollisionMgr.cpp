#include "stdafx.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "Player.h"
#include "Spring.h"
#include "SoundMgr.h"
#include "AbstractFactory.h"
#include "Ring.h"
#include "ObjMgr.h"
#include "InGameEnd.h"
#include "UIScore.h"
#include "BossMonster.h"

bool	CCollisionMgr::bIsPoint = false;
float	CCollisionMgr::fRingAngle = 101.25f;
int		CCollisionMgr::iRingCount = 0;
bool	CCollisionMgr::bFlip = false;
DWORD	CCollisionMgr::CollisionTime = 0;
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

void CCollisionMgr::Collision_Pixel_Boss(CObj * _Dest)
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
				if ((*(bIsPixel[i] + iMiddleX)) == true)
				{
					dynamic_cast<CBossMonster*>(_Dest)->Set_Falling(false);
					dynamic_cast<CBossMonster*>(_Dest)->Set_Jumping(false);
					float Floor = (float)_Dest->Get_Rect().bottom - i;
					dynamic_cast<CBossMonster*>(_Dest)->Set_PosAddY(-Floor);
					return;
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
					dynamic_cast<CBossMonster*>(_Dest)->Set_Jumping(false);
					dynamic_cast<CBossMonster*>(_Dest)->Set_Falling(true);

					return;
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
		m_bCircleCircle = false;

	}
	else if (m_eID == TILE_SLIDE)
	{
		_Dest->Set_Speed(0.f);
		dynamic_cast<CPlayer*>(_Dest)->Set_QuatorCircle(true);
		m_bCircleCircle = false;
	}
	else if (m_eID == TILE_SLIDEUP)
	{
		dynamic_cast<CPlayer*>(_Dest)->Set_SaveSpeed();
		dynamic_cast<CPlayer*>(_Dest)->Set_Falling(true);
		dynamic_cast<CPlayer*>(_Dest)->Set_Gravity(UP_VERTICAL);
		m_bCircleCircle = false;

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


		m_bCircleCircle = false;

	}
}

void CCollisionMgr::Collision_Player_Ring(CObj * _Dest, list<CObj*>* _Sour)
{
	RECT rc{};

	list<CObj*>::iterator iter = _Sour->begin();
	list<CObj*>::iterator iterEnd = _Sour->end();

	for (iter = _Sour->begin(); iter != iterEnd; ++iter)
	{
		if (IntersectRect(&rc, &(_Dest->Get_Rect()), &((*iter)->Get_Rect())) && !dynamic_cast<CRing*>(*iter)->Get_Losing())
		{
			dynamic_cast<CPlayer*>(_Dest)->Add_Ring();
			CSoundMgr::Get_Instance()->PlaySound(L"ring.mp3", SOUND_EFFECT, 1.f);
			CObj* pUI = CObjMgr::Get_Instance()->Get_OBJType(OBJ_UI)->back();
			dynamic_cast<CUIScore*>(pUI)->Add_Score();
			dynamic_cast<CUIScore*>(pUI)->Add_Ring();

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
			if (CollisionTime)
			{
				DWORD CheckTime = GetTickCount() - CollisionTime;

				if (CheckTime > 500)
				{
					CollisionTime = GetTickCount();
					float fSpeed = dynamic_cast<CPlayer*>(_Dest)->Get_Speed();
					dynamic_cast<CPlayer*>(_Dest)->Set_Jumping(true);
					dynamic_cast<CPlayer*>(_Dest)->Set_CurState(HIT);
					dynamic_cast<CPlayer*>(_Dest)->Set_Speed(-(fSpeed / 5));
					CSoundMgr::Get_Instance()->PlaySound(L"spiked.mp3", SOUND_EFFECT, 1.f);

					int iRing = dynamic_cast<CPlayer*>(_Dest)->Get_Ring();
					float fX = _Dest->Get_Info().fX;
					float fY = _Dest->Get_Info().fY;

					while (iRingCount < iRing)
					{
						CSoundMgr::Get_Instance()->PlaySound(L"ring-lose.mp3", SOUND_EFFECT, 1.f);

						CObj* pObj = CAbstractFactory<CRing>::Create(fX, fY);
						CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);
						dynamic_cast<CRing*>(pObj)->Set_Losing(true);
						dynamic_cast<CRing*>(pObj)->Set_Ground(_Dest->Get_Rect().bottom - 16.f);
						dynamic_cast<CRing*>(pObj)->SetAngle(fRingAngle);

						if (iRingCount == 16)
						{
							dynamic_cast<CRing*>(pObj)->Set_Speed(2.f);
							dynamic_cast<CRing*>(pObj)->SetAngle(fRingAngle);
						}

						dynamic_cast<CRing*>(pObj)->MoveRing();

						if (bFlip == true)
						{
							dynamic_cast<CRing*>(pObj)->ToggleSpeed();
							fRingAngle += 22.5f;
						}


						bFlip = !bFlip;
						iRingCount += 1;
					}

					dynamic_cast<CPlayer*>(_Dest)->Reset_Ring();
					CObj* pUI = CObjMgr::Get_Instance()->Get_OBJType(OBJ_UI)->back();
					dynamic_cast<CUIScore*>(pUI)->Rest_Ring();
					iRingCount = 0;
				}
				else
				{

				}
			}
			else
			{
				CollisionTime = GetTickCount();
				float fSpeed = dynamic_cast<CPlayer*>(_Dest)->Get_Speed();
				dynamic_cast<CPlayer*>(_Dest)->Set_Jumping(true);
				dynamic_cast<CPlayer*>(_Dest)->Set_CurState(HIT);
				dynamic_cast<CPlayer*>(_Dest)->Set_PosAddX(-2);
				dynamic_cast<CPlayer*>(_Dest)->Set_Speed(-(fSpeed / 5));
				CSoundMgr::Get_Instance()->PlaySound(L"spiked.mp3", SOUND_EFFECT, 1.f);

				int iRing = dynamic_cast<CPlayer*>(_Dest)->Get_Ring();
				float fX = _Dest->Get_Info().fX;
				float fY = _Dest->Get_Info().fY;

				while (iRingCount < iRing)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"ring-lose.mp3", SOUND_EFFECT, 1.f);
					CObj* pObj = CAbstractFactory<CRing>::Create(fX, fY);
					CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);
					dynamic_cast<CRing*>(pObj)->Set_Losing(true);
					dynamic_cast<CRing*>(pObj)->Set_Ground(_Dest->Get_Rect().bottom - 16.f);
					dynamic_cast<CRing*>(pObj)->SetAngle(fRingAngle);

					if (iRingCount == 16)
					{
						dynamic_cast<CRing*>(pObj)->Set_Speed(2.f);
						dynamic_cast<CRing*>(pObj)->SetAngle(fRingAngle);
					}

					dynamic_cast<CRing*>(pObj)->MoveRing();

					if (bFlip == true)
					{
						dynamic_cast<CRing*>(pObj)->ToggleSpeed();
						fRingAngle += 22.5f;
					}


					bFlip = !bFlip;  
					iRingCount += 1;

				}

				dynamic_cast<CPlayer*>(_Dest)->Reset_Ring();
				CObj* pUI = CObjMgr::Get_Instance()->Get_OBJType(OBJ_UI)->back();
				dynamic_cast<CUIScore*>(pUI)->Rest_Ring();
				iRingCount = 0;
			}
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
			if (CollisionTime)
			{
				DWORD CheckTime = GetTickCount() - CollisionTime;

				if (CheckTime > 500)
				{
					CollisionTime = GetTickCount();
					dynamic_cast<CPlayer*>(_Dest)->Set_JumpPower(JUMP + 10);
					dynamic_cast<CPlayer*>(_Dest)->Set_Jumping(true);
					dynamic_cast<CPlayer*>(_Dest)->Set_FrameKey(L"SonicR");
					dynamic_cast<CPlayer*>(_Dest)->Set_CurState(JUMPING);
					dynamic_cast<CSpring*>(*iter)->Add_iDrawID();
					CSoundMgr::Get_Instance()->PlaySound(L"spring.mp3", SOUND_EFFECT, 1.f);


				}
			}
			else
			{
				CollisionTime = GetTickCount();
				dynamic_cast<CPlayer*>(_Dest)->Set_JumpPower(JUMP + 10);
				dynamic_cast<CPlayer*>(_Dest)->Set_Jumping(true);
				dynamic_cast<CPlayer*>(_Dest)->Set_FrameKey(L"SonicR");
				dynamic_cast<CPlayer*>(_Dest)->Set_CurState(JUMPING);
				dynamic_cast<CSpring*>(*iter)->Add_iDrawID();
				CSoundMgr::Get_Instance()->PlaySound(L"spring.mp3", SOUND_EFFECT, 1.f);
			}
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
			dynamic_cast<CPlayer*>(_Dest)->Set_CurState(IDLE);

			if (!bIsPoint)
			{
				CObj* pObj = CAbstractFactory<InGameEnd>::Create();
				CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pObj);
				bIsPoint = true;
				CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
				CSoundMgr::Get_Instance()->PlaySound(L"Clear.wav", SOUND_EFFECT, 1.f);
			}

		}
	}

}

void CCollisionMgr::Collision_Player_MushRoom(CObj * _Dest, list<CObj*>* _Sour)
{
	RECT rc{};

	list<CObj*>::iterator iter = _Sour->begin();
	list<CObj*>::iterator iterEnd = _Sour->end();

	for (iter = _Sour->begin(); iter != iterEnd; ++iter)
	{
		//if(Check_Rect())
		if (IntersectRect(&rc, &(_Dest->Get_Rect()), &((*iter)->Get_Rect())))
		{
			if (CollisionTime)
			{
				DWORD CheckTime = GetTickCount() - CollisionTime;

				if (CheckTime > 500)
				{
					CollisionTime = GetTickCount();
					dynamic_cast<CPlayer*>(_Dest)->Set_JumpPower(JUMP + 10);
					dynamic_cast<CPlayer*>(_Dest)->Set_Jumping(true);
					dynamic_cast<CPlayer*>(_Dest)->Set_FrameKey(L"SonicR");
					dynamic_cast<CPlayer*>(_Dest)->Set_CurState(JUMPING);
					CSoundMgr::Get_Instance()->PlaySound(L"spring.mp3", SOUND_EFFECT, 1.f);
				}
			}
			else
			{
				CollisionTime = GetTickCount();
				dynamic_cast<CPlayer*>(_Dest)->Set_JumpPower(JUMP + 10);
				dynamic_cast<CPlayer*>(_Dest)->Set_Jumping(true);
				dynamic_cast<CPlayer*>(_Dest)->Set_FrameKey(L"SonicR");
				dynamic_cast<CPlayer*>(_Dest)->Set_CurState(JUMPING);
				CSoundMgr::Get_Instance()->PlaySound(L"spring.mp3", SOUND_EFFECT, 1.f);
			}
		}
		else
		{
		}
	}
}

void CCollisionMgr::Collision_Player_Boss()
{
	RECT rc{};

	CObj* Player = CObjMgr::Get_Instance()->Get_Player();
	CObj* Boss = CObjMgr::Get_Instance()->Get_OBJType(OBJ_MONSTER)->front();

	if (dynamic_cast<CBossMonster*>(Boss)->Get_KnockDown())
	{
		return;
	}

	if (IntersectRect(&rc, &Player->Get_Rect(), &Boss->Get_Rect()))
	{
		if (CollisionTime)
		{
			DWORD CheckTime = GetTickCount() - CollisionTime;

			if (CheckTime > 500)
			{
				if (dynamic_cast<CPlayer*>(Player)->Get_Player_State() == ROLLING)
				{
					CollisionTime = GetTickCount();
					dynamic_cast<CBossMonster*>(Boss)->Hit();
					float fSpeed = dynamic_cast<CPlayer*>(Player)->Get_Speed();
					dynamic_cast<CPlayer*>(Player)->Set_Jumping(true);
					dynamic_cast<CPlayer*>(Player)->Set_CurState(HIT);
					dynamic_cast<CPlayer*>(Player)->Set_Speed(-(fSpeed / 5));
					CSoundMgr::Get_Instance()->PlaySound(L"crash.mp3", SOUND_PLAYER, 1.f);


				}
				else
				{
					CollisionTime = GetTickCount();
					float fSpeed = dynamic_cast<CPlayer*>(Player)->Get_Speed();
					dynamic_cast<CPlayer*>(Player)->Set_Jumping(true);
					dynamic_cast<CPlayer*>(Player)->Set_CurState(HIT);
					dynamic_cast<CPlayer*>(Player)->Set_Speed(-(fSpeed / 5));
					CSoundMgr::Get_Instance()->PlaySound(L"death.mp3", SOUND_MONSTER, 1.f);

					int iRing = dynamic_cast<CPlayer*>(Player)->Get_Ring();
					float fX = Player->Get_Info().fX;
					float fY = Player->Get_Info().fY;

					while (iRingCount < iRing)
					{
						CSoundMgr::Get_Instance()->PlaySound(L"ring-lose.mp3", SOUND_EFFECT, 1.f);

						CObj* pObj = CAbstractFactory<CRing>::Create(fX, fY);
						CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);
						dynamic_cast<CRing*>(pObj)->Set_Losing(true);
						dynamic_cast<CRing*>(pObj)->Set_Ground(Player->Get_Rect().bottom - 16.f);
						dynamic_cast<CRing*>(pObj)->SetAngle(fRingAngle);

						if (iRingCount == 16)
						{
							dynamic_cast<CRing*>(pObj)->Set_Speed(2.f);
							dynamic_cast<CRing*>(pObj)->SetAngle(fRingAngle);
						}

						dynamic_cast<CRing*>(pObj)->MoveRing();

						if (bFlip == true)
						{
							dynamic_cast<CRing*>(pObj)->ToggleSpeed();
							fRingAngle += 22.5f;
						}


						bFlip = !bFlip;
						iRingCount += 1;
					}

					dynamic_cast<CPlayer*>(Player)->Reset_Ring();
					CObj* pUI = CObjMgr::Get_Instance()->Get_OBJType(OBJ_UI)->back();
					dynamic_cast<CUIScore*>(pUI)->Rest_Ring();
					iRingCount = 0;
				}
			}
		}
		else
		{
			if (dynamic_cast<CPlayer*>(Player)->Get_Player_State() == ROLLING)
			{
				CollisionTime = GetTickCount();
				dynamic_cast<CBossMonster*>(Boss)->Hit();
				float fSpeed = dynamic_cast<CPlayer*>(Player)->Get_Speed();
				dynamic_cast<CPlayer*>(Player)->Set_Jumping(true);
				dynamic_cast<CPlayer*>(Player)->Set_CurState(HIT);
				dynamic_cast<CPlayer*>(Player)->Set_Speed(-(fSpeed / 5));
				CSoundMgr::Get_Instance()->PlaySound(L"crash.mp3", SOUND_PLAYER, 1.f);

			}
			else
			{
				CollisionTime = GetTickCount();
				float fSpeed = dynamic_cast<CPlayer*>(Player)->Get_Speed();
				dynamic_cast<CPlayer*>(Player)->Set_Jumping(true);
				dynamic_cast<CPlayer*>(Player)->Set_CurState(HIT);
				dynamic_cast<CPlayer*>(Player)->Set_PosAddX(-2);
				dynamic_cast<CPlayer*>(Player)->Set_Speed(-(fSpeed / 5));
				CSoundMgr::Get_Instance()->PlaySound(L"death.mp3", SOUND_MONSTER, 1.f);

				int iRing = dynamic_cast<CPlayer*>(Player)->Get_Ring();
				float fX = Player->Get_Info().fX;
				float fY = Player->Get_Info().fY;

				while (iRingCount < iRing)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"ring-lose.mp3", SOUND_EFFECT, 1.f);
					CObj* pObj = CAbstractFactory<CRing>::Create(fX, fY);
					CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);
					dynamic_cast<CRing*>(pObj)->Set_Losing(true);
					dynamic_cast<CRing*>(pObj)->Set_Ground(Player->Get_Rect().bottom - 16.f);
					dynamic_cast<CRing*>(pObj)->SetAngle(fRingAngle);

					if (iRingCount == 16)
					{
						dynamic_cast<CRing*>(pObj)->Set_Speed(2.f);
						dynamic_cast<CRing*>(pObj)->SetAngle(fRingAngle);
					}

					dynamic_cast<CRing*>(pObj)->MoveRing();

					if (bFlip == true)
					{
						dynamic_cast<CRing*>(pObj)->ToggleSpeed();
						fRingAngle += 22.5f;
					}


					bFlip = !bFlip;
					iRingCount += 1;

				}

				dynamic_cast<CPlayer*>(Player)->Reset_Ring();
				CObj* pUI = CObjMgr::Get_Instance()->Get_OBJType(OBJ_UI)->back();
				dynamic_cast<CUIScore*>(pUI)->Rest_Ring();
				iRingCount = 0;
			}
		}

	}
}
