#include "stdafx.h"
#include "MyBmp.h"

CMyBmp::CMyBmp()
{
	BmpData = nullptr;
}

CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	// �켱 getDC�� �ҷ��� ��, CreateCompatibleDC�� ȣȯ�Ǵ� dc�� �Ҵ��Ѵ�.
	m_hMemDC = CreateCompatibleDC(hDC);
	
	ReleaseDC(g_hWnd, hDC);

	m_hBitMap = (HBITMAP)LoadImage(NULL,		// ���α׷� �ν��Ͻ� �ڵ�, �̹����� ���α׷����� ������ ���� �ƴ϶� ���Ϸκ��� �о� ���̱� ������ NULL��
									pFilePath,  // ���� ���
									IMAGE_BITMAP, // � Ÿ���� ���� ���ΰ�
									0,			// ����, ���� ������
									0,
									LR_LOADFROMFILE | LR_CREATEDIBSECTION);	// LR_LOADFROMFILE : ���Ͽ��� �̹����� �ҷ����� �ɼ�, LR_CREATEDIBSECTION : �о�� ������ DIB ���·� ��ȯ
	
	// 1. LoadImage�� ��Ʈ���� ���� ������ ������ �ִ� ���������� �׸��� ������ �ʴ�.
	// 2. ��Ʈ���� �׸��� ���ؼ��� m_hMemDC�� �غ�������, ���� ���õ� gdi ������Ʈ ���� ����Ʈ �����̴�.
	// 3. �غ��� dc�� gdi ������Ʈ�� �ҷ��� ��Ʈ���� �����ϱ� ���� �Լ��� SelectObject�̴�.
	// 4. SelectObject�� gdi ������Ʈ�� �����ϱ� ���� ������ ������ �ִ� ������Ʈ�� ��ȯ�Ѵ�.

	m_hOldMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
}

void CMyBmp::Get_Bmp_Rgb(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	// �켱 getDC�� �ҷ��� ��, CreateCompatibleDC�� ȣȯ�Ǵ� dc�� �Ҵ��Ѵ�.
	m_hMemDC = CreateCompatibleDC(hDC);

	m_hBitMap = (HBITMAP)LoadImage(NULL,		// ���α׷� �ν��Ͻ� �ڵ�, �̹����� ���α׷����� ������ ���� �ƴ϶� ���Ϸκ��� �о� ���̱� ������ NULL��
		pFilePath,  // ���� ���
		IMAGE_BITMAP, // � Ÿ���� ���� ���ΰ�
		0,			// ����, ���� ������
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);	// LR_LOADFROMFILE : ���Ͽ��� �̹����� �ҷ����� �ɼ�, LR_CREATEDIBSECTION : �о�� ������ DIB ���·� ��ȯ
	
	BITMAPINFOHEADER bmi = { 0 };
	bmi.biSize = sizeof(BITMAPINFOHEADER);
	bmi.biPlanes = 1;
	bmi.biBitCount = 32;
	bmi.biWidth = TOTALTILEX;
	bmi.biHeight = -TOTALTILEY;
	bmi.biCompression = BI_RGB;
	bmi.biSizeImage = TOTALTILEX * TOTALTILEY;
	SelectObject(m_hMemDC, m_hBitMap);

	if (BmpData)
	{
		free(BmpData);
	}

	BmpData = (BYTE*)malloc(4 * TOTALTILEX * TOTALTILEY);

	GetDIBits(m_hMemDC, m_hBitMap, 0, TOTALTILEY, BmpData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

	ReleaseDC(g_hWnd, hDC);

}

void CMyBmp::Release(void)
{
	SelectObject(m_hMemDC, m_hOldMap);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}
