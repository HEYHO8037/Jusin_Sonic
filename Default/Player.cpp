#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "SoundMgr.h"

CPlayer::CPlayer()
	: m_eCurState(IDLE), m_ePreState(END)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 100.f;
	m_tInfo.fY = 400.f;

	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;

	m_fSpeed = 0.f;

	m_fDiagonal = 100.f;

	m_bJump = false;
	m_fJumpPower = JUMP;
	m_fPower = 2.5;
	m_fFalling = 0.f;
	m_fJumpTime = 0.f;
	m_bFalling = true;
	m_fGroundY = -1.f;
	m_eGravity = DOWN_VERTICAL;
	m_bIsCircle = false;
	m_tPivot = POSITION(0.5, 0.5);
	m_fAngle = 90.f;
	m_fMaxAngle = 450.f;

	m_bIsGetPoint = false;
	m_bIsRunStart = false;
	m_bIsRollingStart = false;
	m_bIsRolling = false;
	m_bIsQuatorCircle = false;
	m_bIsCharging = false;
	m_bIsLR = false;


	m_fCircleX = 0;
	m_fCircleY = 0;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicR0.bmp", L"SonicR0");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicR45.bmp", L"SonicR45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicR90.bmp", L"SonicR90");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicR135.bmp", L"SonicR135");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicR180.bmp", L"SonicR180");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicR225.bmp", L"SonicR225");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicR270.bmp", L"SonicR270");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicR315.bmp", L"SonicR315");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicL0.bmp", L"SonicL0");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicL45.bmp", L"SonicL45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicL90.bmp", L"SonicL90");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicL135.bmp", L"SonicL135");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicL180.bmp", L"SonicL180");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicL225.bmp", L"SonicL225");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicL270.bmp", L"SonicL270");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicL315.bmp", L"SonicL315");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicR.bmp", L"SonicR");


	m_pFrameKey = L"SonicR0";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 1;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_iRing = 0;
	m_fSoundVol = 1.f;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bIsGetPoint)
	{
		return OBJ_NOEVENT;
	}

	// ?????? ????
	Key_Input();
	Jumping();
	Falling();

	if (m_bIsQuatorCircle)
	{
		QuaterCircling();
	}

	if (m_fCircleX)
	{
		Circling();
	}


	// ???? ?????? ???? ???? ???????? ?????? ????
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	Motion_Change();
	Move_Frame();
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	
	POSITION tPos;
	tPos.x = m_tInfo.fX - m_tInfo.fCX * m_tPivot.x;
	tPos.y = m_tInfo.fY - m_tInfo.fCY * m_tPivot.y;
	tPos -= CCamera::Get_Instance()->GetPos();

	RESOLUTION tClientRS = CCamera::Get_Instance()->GetClientRS();

	bool bInClient = true;

	if (tPos.x + m_tInfo.fX < 0)
	{
		bInClient = false;
	}
	else if (tPos.x > tClientRS.iW)
	{
		bInClient = false;
	}
	else if (tPos.y + m_tInfo.fY < 0)
	{
		bInClient = false;
	}
	else if (tPos.y > tClientRS.iH)
	{
		bInClient = false;
	}

	if (bInClient)
	{
		GdiTransparentBlt(hDC, 					// ???? ????, ?????????? ?????? ???? DC
			tPos.x,	// 2,3 ???? :  ???????? ???? X, Y
			tPos.y,
			int(m_tInfo.fCX),				// 4,5 ???? : ???????? ????, ???? ????
			int(m_tInfo.fCY),
			hMemDC,							// ???????? ?????? ???? DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ?????? ???? ???? ????, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX - 13,				// ?????? ???????? ????, ???? ????
			(int)m_tInfo.fCY - 13,
			RGB(255, 0, 255));			// ?????????? ???? ????
	}
}
void CPlayer::Release(void)
{
	
}

void CPlayer::Falling(void)
{
	if (m_bFalling)
	{
		m_fFalling += GRAVITY;

		if (m_fFalling > 16)
		{
			m_fFalling = 16;
		}

		if (m_eGravity == DOWN_VERTICAL)
		{
			m_tInfo.fY += m_fFalling;
		}
		else if (m_eGravity == LEFT_HORIZIONAL)
		{
			m_tInfo.fX += m_fFalling;
		}
		else if (m_eGravity == RIGHT_HORIZIONAL)
		{
			m_tInfo.fX -= m_fFalling;
		}
		else if (m_eGravity == UP_VERTICAL)
		{
			m_tInfo.fY -= m_fFalling;
		}

		if (m_tInfo.fY  + m_tInfo.fCY / 2 >= m_fGroundY && m_fGroundY != -1 && m_eGravity == DOWN_VERTICAL)
		{
			m_fFalling = 0.f;
			m_bFalling = false;
			m_tInfo.fY = m_fGroundY + m_tInfo.fCY / 2;
		}
	}
	else
	{
		m_fFalling = 0.f;

		if (m_tInfo.fY + m_tInfo.fCY / 2 >= m_fGroundY && m_fGroundY != -1 && m_eGravity == DOWN_VERTICAL)
		{
			m_fFalling = 0.f;
			m_bJump = false;
			m_bFalling = false;
			m_tInfo.fY = m_fGroundY + m_tInfo.fCY / 2;
		}
	}
}

void CPlayer::QuaterCircling(void)
{
	if (m_fAngle >= 45 && m_fAngle < 90)
	{
		m_pFrameKey = L"SonicR45";

		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}
	}
	else if (m_fAngle >= 90 && m_fAngle < 135)
	{
		m_pFrameKey = L"SonicR90";

		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}
	}
	else if (m_fAngle >= 135 && m_fAngle < 180)
	{
		m_pFrameKey = L"SonicR135";
		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}
	}
	else if (m_fAngle >= 180 && m_fAngle < 225)
	{
		m_pFrameKey = L"SonicR180";
		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}

	}
	else if (m_fAngle >= 225 && m_fAngle < 270)
	{
		m_pFrameKey = L"SonicR225";
		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}

	}
	else if (m_fAngle >= 270 && m_fAngle < 315)
	{
		m_pFrameKey = L"SonicR270";
		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}
	}
	else if (m_fAngle >= 315 && m_fAngle < 415)
	{
		m_pFrameKey = L"SonicR315";

		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}
	}
	else
	{
		m_pFrameKey = L"SonicR0";

		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}
	}

	if (m_fSaveSpeed < 5)
	{
		m_tInfo.fX += 2 * sinf(RADIAN * m_fAngle);
		m_tInfo.fY += 3 * cosf(RADIAN * m_fAngle);
	}
	else
	{
		m_tInfo.fX += 4 * sinf(RADIAN * m_fAngle);
		m_tInfo.fY += 6 * cosf(RADIAN * m_fAngle);
	}


	if (m_fSaveSpeed < 5)
	{
		m_fAngle += 5;
	}
	else
	{
		m_fAngle += 10;
	}

	if ((int)m_fAngle % 180 == 0)
	{
		m_fSpeed = (m_fSaveSpeed / 2);
		m_fAngle = 90.f;
		m_bIsQuatorCircle = false;
	}


}

void CPlayer::Circling(void)
{
	if (m_fAngle >= 45 && m_fAngle < 90)
	{
		m_pFrameKey = L"SonicR45";
		
		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}
	}
	else if (m_fAngle >= 90 && m_fAngle < 135)
	{
		m_pFrameKey = L"SonicR90";

		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}
	}
	else if (m_fAngle >= 135 && m_fAngle < 180)
	{
		m_pFrameKey = L"SonicR135";
		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}
	}
	else if (m_fAngle >= 180 && m_fAngle < 225)
	{
		m_pFrameKey = L"SonicR180";
		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}

	}
	else if (m_fAngle >= 225 && m_fAngle < 270)
	{
		m_pFrameKey = L"SonicR225";
		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}

	}
	else if (m_fAngle >= 270 && m_fAngle < 315)
	{
		m_pFrameKey = L"SonicR270";
		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}
	}
	else if (m_fAngle >= 315 && m_fAngle < 415)
	{
		m_pFrameKey = L"SonicR315";

		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}
	}
	else
	{
		m_pFrameKey = L"SonicR0";

		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else
		{
			m_eCurState = RUN;
		}
	}

	if (m_fSaveSpeed < 5)
	{
		m_tInfo.fX += 7 * sinf(m_fAngle * RADIAN);
		m_tInfo.fY += 6 * cosf(m_fAngle * RADIAN);
	}
	else
	{
		m_tInfo.fX += 14 * sinf(m_fAngle * RADIAN);
		m_tInfo.fY += 12 * cosf(m_fAngle * RADIAN);
	}


	if (m_fSaveSpeed < 5)
	{
		m_fAngle += 5;
	}
	else
	{
		m_fAngle += 10;
	}

	if ((int)m_fAngle % (int)m_fMaxAngle == 0)
	{
		if(m_fMaxAngle != 360.f)
		{ 
			m_fSpeed = m_fSaveSpeed;
		}
		m_fAngle = 90.f;
		m_fCircleX = 0.f;
		m_fCircleY = 0.f;
	}
}


void CPlayer::Key_Input(void)
{
	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_bIsLR = true;
		if (m_eGravity == UP_VERTICAL)
		{
			m_pFrameKey = L"SonicL90";
		}
		else
		{
			m_pFrameKey = L"SonicL0";
		}

		if (m_fSpeed > 0) //???????? ???? ?? ????????
		{
			if (m_eCurState == ROLLING)
			{
				m_fSpeed -= ROLLINGDEC;
			}
			else
			{
				m_fSpeed -= DEC;  // ????
			}

			if (m_fSpeed <= 0)
				m_fSpeed = 0.0;  //???????? ???????????? ?????? ?????? ????????
		}
		else if (m_fSpeed > -TOPXSPEED && m_eCurState != ROLLING) //???????? ???? ?? ????
		{
			m_fSpeed -= ACC;  // ????
			m_eCurState = RUN;
			if (m_fSpeed <= -TOPXSPEED)
				m_fSpeed = -TOPXSPEED; //???? ?????????? ?????????? ??
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			m_bJump = true;
			m_eCurState = ROLLING;
			CSoundMgr::Get_Instance()->PlaySound(L"jump.mp3", SOUND_PLAYER, 1.f);

		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		m_bIsLR = false;
		if (m_eGravity == UP_VERTICAL)
		{
			m_pFrameKey = L"SonicR90";
		}
		else
		{
			m_pFrameKey = L"SonicR0";
		}

		if (m_fSpeed < 0) //?? ?????? ????
		{
			if (m_eCurState == ROLLING)
			{
				m_fSpeed += ROLLINGDEC;
			}
			else
			{
				m_fSpeed += DEC;  // ????
			}

			if (m_fSpeed >= 0)
				m_fSpeed = 0.0;
		}
		else if (m_fSpeed < TOPXSPEED && m_eCurState != ROLLING)
		{
			m_fSpeed += ACC;
			m_eCurState = RUN;
			if (m_fSpeed >= TOPXSPEED)
				m_fSpeed = TOPXSPEED;
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			m_bJump = true;
			m_eCurState = ROLLING;
			CSoundMgr::Get_Instance()->PlaySound(L"jump.mp3", SOUND_PLAYER, 1.f);
		}

	
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = true;
		m_eCurState = ROLLING;
		CSoundMgr::Get_Instance()->PlaySound(L"jump.mp3", SOUND_PLAYER, 1.f);

	}

	else if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"spindash_1.mp3", SOUND_PLAYER, 1.f);
		m_fSpeed = 0.f;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		if (!m_bIsRollingStart)
		{
			m_eCurState = ROLLSTART;

			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_bIsRollingStart = true;

			}
		}
		else if (m_bIsRollingStart)
		{
			m_eCurState = CHARGEROLLING;
			m_bIsCharging = true;
		}
	}
	else if (GetKeyState(VK_DOWN) & 0x0001)
	{
		if (m_bIsCharging)
		{
			if (!m_bIsLR)
			{
				m_fSpeed = ROLLINGSPD;
			}
			else
			{
				m_fSpeed = -ROLLINGSPD;
			}
			m_eCurState = ROLLING;
			m_bIsCharging = false;
		}
	}
	else
	{
		m_fSpeed -= fminf(fabsf(m_fSpeed), FRC) * sinf(m_fSpeed); // ?????? ?????? ?? ?????? ????
		
		if (m_eCurState == ROLLING)
		{
			m_eCurState = ROLLING;
		}
		else if (abs(m_fSpeed) < 0.1)
		{
			m_eCurState = IDLE;
		}
	}


	m_tInfo.fX += m_fSpeed;

}

void CPlayer::Jumping(void)
{
	if (m_bJump)
	{
		if (m_fJumpPower >= m_fPower)
		{
			if (m_fSpeed > 5)
			{
				m_fSpeed /= 2;
			}
			m_tInfo.fY -= m_fPower;
			m_fPower += 0.7f;
		}
		else
		{
			if(m_eCurState == ROLLING)
			{ 
				m_eCurState = ROLLING;
			}
			else
			{
				m_eCurState = RUN;
			}
			m_fJumpPower = JUMP;
			m_fPower = 0;
			m_bJump = false;
			m_bFalling = true;
		}

	}
}

void CPlayer::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case STARTRUN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RUN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ROLLSTART:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;


		case STOPRUN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 9;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case CHARGEROLLING:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ROLLING:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ROLLEND:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case JUMPING:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 10;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}
