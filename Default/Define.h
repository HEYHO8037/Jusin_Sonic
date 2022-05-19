#pragma once

#define		WINCX		320
#define		WINCY		240


#define		PI			3.141592f

#define		PURE		= 0


#define		OBJ_NOEVENT  0
#define		OBJ_DEAD	 1

#define		VK_MAX		 0xff

#define		TILECX		128
#define		TILECY		128

#define		TILEX		40
#define		TILEY		10

#define		TOTALTILEX 1024
#define		TOTALTILEY 1536

#define		BACKGROUNDX 4036
#define		BACKGROUNDY 768

#define		RADIAN		PI / 180




#define ACC 0.046875 //���ӷ�
#define DEC 0.5 // ���ӷ�
#define FRC 0.046875 // ������
#define TOPXSPEED 6 // ���򰡼ӷ� �ִ밪
#define SLOPE 0.125 // ������ �ȱ�/�ٱ� �Ϲݰ�
#define ROLLINGUP 0.078125 // ������ ��� ��
#define ROLLINGDOWN 0.3125 // ������ �ϰ� ��
#define FALL 2.5 // ���ϼӵ�

//Sonic's Airborne Speed Constants ( ���� ���ǵ� ���ð� )
#define AIR 0.09375 // �������װ��
#define JUMP 15 // ������
#define GRAVITY 0.21875 // �߷°�



extern HWND			g_hWnd;