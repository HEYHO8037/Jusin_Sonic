#pragma once

#include <Windows.h>

typedef	struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

}INFO;


typedef	struct	tagLinePoint 
{
	float		fX;
	float		fY;

	tagLinePoint(){	ZeroMemory(this, sizeof(tagLinePoint));	}
	tagLinePoint(float _fX, float _fY) : fX(_fX) , fY(_fY){	}

}LINEPOINT;

typedef	struct	tagLineInfo 
{
	LINEPOINT		tLPoint;
	LINEPOINT		tRPoint;

	tagLineInfo()	{	ZeroMemory(this, sizeof(tagLineInfo));	}
	tagLineInfo(LINEPOINT& tLeft, LINEPOINT& tRight) : tLPoint(tLeft), tRPoint(tRight)	{	}

}LINE;

typedef struct tagFrame
{
	int		iFrameStart;		// ���ϴ� �������� ��������Ʈ �̹��� ���� ����
	int		iFrameEnd;			// ��������Ʈ�� ������ ������ ����
	int		iMotion;			// ��� �ε���

	DWORD	dwSpeed;			// ��������Ʈ�� ���ư��� �ӵ�
	DWORD	dwTime;				// ��������Ʈ ��ġ�� ����Ǵ� �ð� 

}FRAME;


typedef struct _tagResolution
{
	unsigned int iW;
	unsigned int iH;

	_tagResolution() :
		iW(0),
		iH(0)
	{
	}

	_tagResolution(int x, int y) :
		iW(x),
		iH(y)
	{
	}

}RESOLUTION, *PRESOLUTION;

typedef struct _tagPosition
{
	float x, y;

	_tagPosition() :
		x(0.f), y(0.f)
	{
	}

	_tagPosition(float _x, float _y)
		: x(_x), y(_y)
	{
	}

	_tagPosition(const _tagPosition& pos)
	{
		x = pos.x;
		y = pos.y;
	}

	_tagPosition(const POINT& pt)
	{
		x = pt.x;
		y = pt.y;
	}

	void operator = (const _tagPosition& pos)
	{
		x = pos.x;
		y = pos.y;
	}

	void operator = (const POINT& pt)
	{
		x = pt.x;
		y = pt.y;
	}

	void operator = (float f[2])
	{
		x = f[0];
		y = f[1];
	}

	// + 
	_tagPosition operator + (float f) const
	{
		_tagPosition tPos;
		tPos.x += f;
		tPos.y += f;

		return tPos;
	}


	_tagPosition operator + (const _tagPosition& pos) const
	{
		_tagPosition tPos;
		tPos.x = x + pos.x;
		tPos.y = y + pos.y;

		return tPos;
	}

	_tagPosition operator + (const POINT& pt) const
	{
		_tagPosition tPos;
		tPos.x = x + pt.x;
		tPos.y = y + pt.y;

		return tPos;
	}

	_tagPosition operator + (float f[2]) const
	{
		_tagPosition tPos;
		tPos.x = x + f[0];
		tPos.y = y + f[1];

		return tPos;
	}

	void operator += (const _tagPosition& pos)
	{
		x += pos.x;
		y += pos.y;
	}

	// -

	_tagPosition operator - (float f) const
	{
		_tagPosition tPos;
		tPos.x -= f;
		tPos.y -= f;

		return tPos;
	}

	void operator -= (const _tagPosition& pos)
	{
		x -= pos.x;
		y -= pos.y;
	}

	_tagPosition operator - (const _tagPosition& pos) const
	{
		_tagPosition tPos;
		tPos.x = x - pos.x;
		tPos.y = y - pos.y;

		return tPos;
	}

	_tagPosition operator - (const POINT& pt) const
	{
		_tagPosition tPos;
		tPos.x = x - pt.x;
		tPos.y = y - pt.y;

		return tPos;
	}

	_tagPosition operator - (float f[2]) const
	{
		_tagPosition tPos;
		tPos.x = x - f[0];
		tPos.y = y - f[1];

		return tPos;
	}

	// *

	_tagPosition operator * (float f) const
	{
		_tagPosition tPos;
		tPos.x *= f;
		tPos.y *= f;

		return tPos;
	}

	_tagPosition operator * (const _tagPosition& pos) const
	{
		_tagPosition tPos;
		tPos.x = x * pos.x;
		tPos.y = y * pos.y;

		return tPos;
	}

	_tagPosition operator * (const POINT& pt) const
	{
		_tagPosition tPos;
		tPos.x = x * pt.x;
		tPos.y = y * pt.y;

		return tPos;
	}

	_tagPosition operator * (float f[2]) const
	{
		_tagPosition tPos;
		tPos.x = x * f[0];
		tPos.y = y * f[1];

		return tPos;
	}

	// /

	_tagPosition operator / (float f) const
	{
		_tagPosition tPos;
		tPos.x /= f;
		tPos.y /= f;

		return tPos;
	}

	_tagPosition operator / (const _tagPosition& pos) const
	{
		_tagPosition tPos;
		tPos.x = x / pos.x;
		tPos.y = y / pos.y;

		return tPos;
	}

	_tagPosition operator / (const POINT& pt) const
	{
		_tagPosition tPos;
		tPos.x = x / pt.x;
		tPos.y = y / pt.y;

		return tPos;
	}

	_tagPosition operator / (float f[2]) const
	{
		_tagPosition tPos;
		tPos.x = x / f[0];
		tPos.y = y / f[1];

		return tPos;
	}

}POSITION, *PPOSITION, _SIZE, *_PSIZE;