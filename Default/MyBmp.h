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

// DDB : 장치에 의존적인 비트맷 포맷 형태, 이미지의 크기, 색상 등 기본적인 정보와 이미지 데이토러 구성되어 있어 다양한 해상도의 장치에 광범위하게 사용되지 못한다.
//		 흑백 비트맵은 흑백 장치로 컬러 비트맵은 컬러 장치로만 출력할 수 있다.

// DIB : 장치에 독립적인 비트맵 포맷 형태, DDB에 비해 색상 테이블, 해상도 정보 등의 추가 정보를 가지므로, 장치에 종속되지 않아 활용도가 더 광범위하고 호환성이 뛰어나다.