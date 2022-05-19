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




#define ACC 0.046875 //가속력
#define DEC 0.5 // 감속력
#define FRC 0.046875 // 마찰력
#define TOPXSPEED 6 // 수평가속력 최대값
#define SLOPE 0.125 // 슬로프 걷기/뛰기 일반값
#define ROLLINGUP 0.078125 // 슬로프 상승 값
#define ROLLINGDOWN 0.3125 // 슬로프 하강 값
#define FALL 2.5 // 낙하속도

//Sonic's Airborne Speed Constants ( 공중 스피드 관련값 )
#define AIR 0.09375 // 공기저항계수
#define JUMP 15 // 점프력
#define GRAVITY 0.21875 // 중력값



extern HWND			g_hWnd;