#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

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
	m_fFalling = 0.f;
	m_fJumpTime = 0.f;
	m_bFalling = true;
	m_fGroundY = -1.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicR0.bmp", L"SonicR0");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sonic/SonicL0.bmp", L"SonicL0");


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

	// ������ ����
	Key_Input();
	//Jumping();
	OffSet();
	Falling();


	// ��� ������ ���� �ڿ� �������� ��ǥ�� �ϼ�
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
	

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));			// �����ϰ��� �ϴ� ����
				
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

		m_tInfo.fY += m_fFalling;

		if (m_tInfo.fY  + FIXPIXEL + m_tInfo.fCY / 2 >= m_fGroundY && m_fGroundY != -1)
		{
			m_fFalling = 0.f;
			m_tRect.bottom = m_fGroundY - FIXPIXEL - m_tInfo.fCY / 2;
		}
	}
	else
	{
		m_fFalling = 0.f;
	}
}

void CPlayer::Key_Input(void)
{
	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_pFrameKey = L"SonicL0";

		if (m_fSpeed > 0) //���ǵ尡 ��� �� �����϶�
		{
			m_fSpeed -= DEC;  // ����
			if (m_fSpeed <= 0)
				m_fSpeed = -1.0;  //���ǵ尡 ����������� ������ ������ ���ѹ���
		}
		else if (m_fSpeed > -TOPXSPEED) //���ǵ尡 ���� �� ����
		{
			m_fSpeed -= ACC;  // ����
			m_eCurState = RUN;
			if (m_fSpeed <= -TOPXSPEED)
				m_fSpeed = -TOPXSPEED; //�ְ� �ӷ±����� �����̵��� ��
		}
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_pFrameKey = L"SonicR0";

		if (m_fSpeed < 0) //�� �ڵ��� �ݴ�
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
	else if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
		m_bJump = true;
		return;
	}

	else
	{
		m_fSpeed -= fminf(fabsf(m_fSpeed), FRC) * sinf(m_fSpeed); // Ű���� �Է��� �� ������ ����
		
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
	float		fY = 0.f;

	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_fJumpTime += 0.2f;

		if (bLineCol && (fY < m_tInfo.fY))
		{
			m_bJump = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY;
	}
}

void CPlayer::OffSet(void)
{
	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	int		iItvX = 0;
	int		iItvY = 0;

	if (iOffSetX - iItvX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffSetX + iItvX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
	
	if (iOffSetY - iItvY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fFalling);

	if (iOffSetY + iItvY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fFalling);
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
