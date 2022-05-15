#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Camera.h"

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
	m_tInfo.fY = 10.f;

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


	m_pFrameKey = L"SonicR0";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 1;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 연산을 진행
	Key_Input();
	Jumping();
	Falling();

	if (m_fCircleX)
	{
		Circling();
	}


	// 모든 연산이 끝난 뒤에 최종적인 좌표를 완성
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

void CPlayer::Circling(void)
{
	if (m_fAngle >= 45 && m_fAngle < 90)
	{
		m_pFrameKey = L"SonicR45";
		m_eCurState = RUN;
	}
	else if (m_fAngle >= 90 && m_fAngle < 135)
	{
		m_pFrameKey = L"SonicR90";
		m_eCurState = RUN;
	}
	else if (m_fAngle >= 135 && m_fAngle < 180)
	{
		m_pFrameKey = L"SonicR135";
		m_eCurState = RUN;
	}
	else if (m_fAngle >= 180 && m_fAngle < 225)
	{
		m_pFrameKey = L"SonicR180";
		m_eCurState = RUN;

	}
	else if (m_fAngle >= 225 && m_fAngle < 270)
	{
		m_pFrameKey = L"SonicR225";
		m_eCurState = RUN;

	}
	else if (m_fAngle >= 270 && m_fAngle < 315)
	{
		m_pFrameKey = L"SonicR270";
		m_eCurState = RUN;
	}
	else if (m_fAngle >= 315 && m_fAngle < 415)
	{
		m_pFrameKey = L"SonicR315";
		m_eCurState = RUN;
	}
	else
	{
		m_pFrameKey = L"SonicR0";
	}

	m_tInfo.fX += 7 * sinf(RADIAN * m_fAngle);
	m_tInfo.fY += 6 * cosf(RADIAN * m_fAngle);


	m_fAngle += 5;

	if ((int)m_fAngle % 450 == 0)
	{
		m_fAngle = 0.f;
		m_fCircleX = 0.f;
		m_fCircleY = 0.f;
	}


}


void CPlayer::Key_Input(void)
{
	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
	{

		if (m_eGravity == UP_VERTICAL)
		{
			m_pFrameKey = L"SonicL90";
		}
		else
		{
			m_pFrameKey = L"SonicL0";
		}

		if (m_fSpeed > 0) //스피드가 양수 즉 우측일때
		{
			m_fSpeed -= DEC;  // 가속
			if (m_fSpeed <= 0)
				m_fSpeed = -1.0;  //스피드가 남아있을경우 빠르게 감속을 시켜버림
		}
		else if (m_fSpeed > -TOPXSPEED) //스피드가 음수 즉 좌측
		{
			m_fSpeed -= ACC;  // 가속
			m_eCurState = RUN;
			if (m_fSpeed <= -TOPXSPEED)
				m_fSpeed = -TOPXSPEED; //최고 속력까지만 움직이도록 함
		}


	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{

		if (m_eGravity == UP_VERTICAL)
		{
			m_pFrameKey = L"SonicR90";
		}
		else
		{
			m_pFrameKey = L"SonicR0";

		}


		if (m_fSpeed < 0) //위 코드의 반대
		{
			m_fSpeed += DEC;
			if (m_fSpeed >= 0)
				m_fSpeed = 1.0;
		}
		else if (m_fSpeed < TOPXSPEED)
		{
			m_fSpeed += ACC;
			m_eCurState = RUN;
			if (m_fSpeed >= TOPXSPEED)
				m_fSpeed = TOPXSPEED;
		}

	
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = true;
	}

	else
	{
		m_fSpeed -= fminf(fabsf(m_fSpeed), FRC) * sinf(m_fSpeed); // 키보드 입력을 안 받을시 감속
		
		if (abs(m_fSpeed) < 0.1)
		{
			m_eCurState = IDLE;
		}
		else
		{
			m_eCurState = STOPRUN;
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
			m_tInfo.fY -= m_fPower;
			m_fJumpTime += 0.5f;
		}
		else
		{
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
