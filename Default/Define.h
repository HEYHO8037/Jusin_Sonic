#pragma once

#define		WINCX		800
#define		WINCY		600

#define		PI			3.141592f

#define		PURE		= 0


#define		OBJ_NOEVENT  0
#define		OBJ_DEAD	 1

#define		VK_MAX		 0xff

#define		TILECX		64
#define		TILECY		64

#define		TILEX		30
#define		TILEY		20

#define ACC 0.46875 //���ӷ�
#define DEC 0.5 // ���ӷ�
#define FRC 0.046875; // ������
#define TOPYSPEED 6 // �������ӷ� �ִ밪
#define SLOPE 0.125 // ������ �ȱ�/�ٱ� �Ϲݰ�
#define ROLLINGUP 0.078125 // ������ ��� ��
#define ROLLINGDOWN 0.3125 // ������ �ϰ� ��
#define FALL 2.5; // ���ϼӵ�

//Sonic's Airborne Speed Constants ( ���� ���ǵ� ���ð� )
#define AIR 0.09375 // �������װ��
#define JUMP 6.5 // ������
#define GRAVITY 0.21875 // �߷°�


extern HWND			g_hWnd;