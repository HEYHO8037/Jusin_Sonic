#pragma once

#include "Include.h"

class CMyBmp
{
public:
	CMyBmp();
	~CMyBmp();

public:
	HDC			Get_MemDC() { return m_hMemDC; }
public:
	void		Load_Bmp(const TCHAR* pFilePath);
	void		Get_Bmp_Rgb(const TCHAR* pFilePath);
	void		Release(void);

	inline int PosB(int x, int y)
	{
		return BmpData[4 * ((y*TOTALTILEX) + x)];
	}

	inline int PosG(int x, int y)
	{
		return BmpData[4 * ((y*TOTALTILEX) + x) + 1];
	}

	inline int PosR(int x, int y)
	{
		return BmpData[4 * ((y*TOTALTILEX) + x) + 2];
	}
	
private:
	BYTE*		BmpData;
	HDC			m_hMemDC;
	HBITMAP		m_hBitMap;
	HBITMAP		m_hOldMap;
};

// DDB : ��ġ�� �������� ��Ʈ�� ���� ����, �̹����� ũ��, ���� �� �⺻���� ������ �̹��� �����䷯ �����Ǿ� �־� �پ��� �ػ��� ��ġ�� �������ϰ� ������ ���Ѵ�.
//		 ��� ��Ʈ���� ��� ��ġ�� �÷� ��Ʈ���� �÷� ��ġ�θ� ����� �� �ִ�.

// DIB : ��ġ�� �������� ��Ʈ�� ���� ����, DDB�� ���� ���� ���̺�, �ػ� ���� ���� �߰� ������ �����Ƿ�, ��ġ�� ���ӵ��� �ʾ� Ȱ�뵵�� �� �������ϰ� ȣȯ���� �پ��.