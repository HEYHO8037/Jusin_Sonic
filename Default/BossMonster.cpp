#include "stdafx.h"
#include "BossMonster.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "SoundMgr.h"

CBossMonster::CBossMonster()
{
}


CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize(void)
{
	m_tInfo.fCX = 66.f;
	m_tInfo.fCY = 66.f;

	m_tInfo.fX = 600.f;
	m_tInfo.fY = 400.f;

	m_fSpeed = 5.f;
	m_fRollSpeed = 3.f;

	m_bJump = false;
	m_bIsKnockDown = false;

	m_fJumpPower = JUMP;
	m_fPower = 2.5;
	
	m_fFalling = 0.f;
	m_fJumpTime = 0.f;

	m_bFalling = true;
	m_fGroundY = -1.f;

	m_tPivot = POSITION(0.5, 0.5);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MechaSonic/MechaSonicL.bmp", L"MechaSonicL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MechaSonic/MechaSonicR.bmp", L"MechaSonicR");
	
	m_pFrameKey = L"MechaSonicL";
	m_eCurState = BOSS_IDLE;
	m_bIsIDLE = true;
	m_bIsLR = false;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_fMoveDist = 0;
	m_fMaxMove = WINCX;
	m_fSoundVol = 1.f;
	m_iHP = 5;

}

int CBossMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 연산을 진행
	Jumping();
	Falling();

	
	srand(time(NULL)); // 40% 확률로 공격
	int a = rand() % 5;

	if (a == 0 && m_bIsIDLE)
	{
		RollingAttack();
	}
	else if (a == 1 && m_bIsIDLE)
	{
		BackAttack();
	}

	else if (!m_bIsIDLE && m_eCurState == BOSS_ATTACK)
	{
		RollingAttack();
	}
	else if (!m_bIsIDLE && m_eCurState == BOSS_BACKATTACK)
	{
		BackAttack();
	}

	Die();
	

	// 모든 연산이 끝난 뒤에 최종적인 좌표를 완성
	Update_Rect();

	return OBJ_NOEVENT;

}

void CBossMonster::Late_Update(void)
{
	Motion_Change();
	Move_Frame();
}

void CBossMonster::Render(HDC hDC)
{
	POSITION tPos;
	tPos.x = m_tInfo.fX - m_tInfo.fCX * m_tPivot.x;
	tPos.y = m_tInfo.fY - m_tInfo.fCY * m_tPivot.y;
	tPos -= CCamera::Get_Instance()->GetPos();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		tPos.x,	// 2,3 인자 :  복사받을 위치 X, Y
		tPos.y,
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX - 13,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY - 13,
		RGB(255, 0, 255));			// 제거하고자 하는 색상
}


void CBossMonster::RollingAttack()
{
	if (m_pTarget)
	{
		float distX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		m_eCurState = BOSS_ATTACK;
		CSoundMgr::Get_Instance()->PlaySound(L"electric-double-jump.mp3", SOUND_EFFECT, 1.f);

		
		if (m_bIsIDLE)
		{
			float distX = m_pTarget->Get_Info().fX - m_tInfo.fX;
			m_bIsIDLE = false;

			if (distX < 0)
			{
				m_bIsLR = false;
			}
			else
			{
				m_bIsLR = true;
			}
		}


		if (m_fMaxMove <= m_fMoveDist) {
			m_fMoveDist = 0;
			m_eCurState = BOSS_IDLE;
			m_bIsIDLE = true;
			return;
		}

		if (abs(distX) < WINCX && !m_bIsLR)
		{
			m_pFrameKey = L"MechaSonicL";
			m_fMoveDist += m_fRollSpeed;
			m_tInfo.fX -= m_fRollSpeed;
		}
		else if(abs(distX) < WINCX && m_bIsLR)
		{
			m_pFrameKey = L"MechaSonicR";
			m_fMoveDist += m_fRollSpeed;
			m_tInfo.fX += m_fRollSpeed;
		}
	}

}

void CBossMonster::BackAttack()
{
	if (m_pTarget)
	{
		float distX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		m_eCurState = BOSS_BACKATTACK;
		CSoundMgr::Get_Instance()->PlaySound(L"mechanical-whirr.mp3", SOUND_MONSTER, 1.f);


		if (m_bIsIDLE)
		{
			float distX = m_pTarget->Get_Info().fX - m_tInfo.fX;
			m_bIsIDLE = false;

			if (distX < 0)
			{
				m_bIsLR = false;
			}
			else
			{
				m_bIsLR = true;
			}
		}

		if (m_fMaxMove <= m_fMoveDist) {
			m_fMoveDist = 0;
			m_eCurState = BOSS_IDLE;
			m_bIsIDLE = true;
			return;
		}

		if (abs(distX) < WINCX && !m_bIsLR)
		{
			m_pFrameKey = L"MechaSonicR";
			m_fMoveDist += m_fSpeed;
			m_tInfo.fX -= m_fSpeed;
		}
		else if (abs(distX) < WINCX && m_bIsLR)
		{
			m_pFrameKey = L"MechaSonicL";
			m_fMoveDist += m_fSpeed;
			m_tInfo.fX += m_fSpeed;
		}
	}
}

void CBossMonster::Hit()
{
	m_eCurState = BOSS_HIT;
	m_bIsIDLE = true;
	m_iHP--;
}

bool CBossMonster::Get_KnockDown()
{
	return m_bIsKnockDown;
}

void CBossMonster::Die()
{
	if (m_iHP <= 0)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"explosion.mp3", SOUND_MONSTER, 1.f);
		m_eCurState = BOSS_DEAD;
		m_bIsKnockDown = true;
	}
}

void CBossMonster::Falling(void)
{
	if (m_bFalling)
	{
		m_fFalling += GRAVITY;

		if (m_fFalling > 16)
		{
			m_fFalling = 16;
		}

		m_tInfo.fY += m_fFalling;

		if (m_tInfo.fY + m_tInfo.fCY / 2 >= m_fGroundY && m_fGroundY != -1)
		{
			m_fFalling = 0.f;
			m_bFalling = false;
			m_tInfo.fY = m_fGroundY + m_tInfo.fCY / 2;
		}
	}
	else
	{
		m_fFalling = 0.f;

		if (m_tInfo.fY + m_tInfo.fCY / 2 >= m_fGroundY && m_fGroundY != -1)
		{
			m_fFalling = 0.f;
			m_bJump = false;
			m_bFalling = false;
			m_tInfo.fY = m_fGroundY + m_tInfo.fCY / 2;
		}
	}

}

void CBossMonster::Jumping(void)
{
	if (m_bJump)
	{
		if (m_fJumpPower >= m_fPower)
		{
			m_tInfo.fY -= m_fPower;
			m_fPower += 0.7f;
		}
		else
		{
			m_eCurState = BOSS_IDLE;
			m_fJumpPower = JUMP;
			m_fPower = 0;
			m_bJump = false;
			m_bFalling = true;
		}

	}

}

void CBossMonster::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BOSS_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case BOSS_BACKATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case BOSS_ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case BOSS_HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case BOSS_DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		}

		m_ePreState = m_eCurState;
	}
}


void CBossMonster::Release(void)
{
	m_pTarget = nullptr;
}
