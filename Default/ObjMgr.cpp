#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Ring.h"
#include "Spike.h"
#include "Spring.h"
#include "Goal.h"
#include "AbstractFactory.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj*		pTarget = nullptr;
	float		fDistance = 0.f;
	
	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead())
			continue;

		float	fWidth = abs(pObj->Get_Info().fX - iter->Get_Info().fX);
		float	fHeight = abs(pObj->Get_Info().fY - iter->Get_Info().fY);

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}
		
	return pTarget;
}

void CObjMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if ((eID >= OBJ_END) || (nullptr == pObj))
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;
		}
	}
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}
}

void CObjMgr::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}


void CObjMgr::Save_Obj(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Obj.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD		dwByte = 0;


	for (auto& iter : m_ObjList[OBJ_ITEM])
	{
		WriteFile(hFile, &iter->Get_Info(), sizeof(INFO), &dwByte, NULL);
	}

	for (auto& iter : m_ObjList[OBJ_SPRING])
	{
		WriteFile(hFile, &iter->Get_Info(), sizeof(INFO), &dwByte, NULL);
	}

	for (auto& iter : m_ObjList[OBJ_SPIKE])
	{
		WriteFile(hFile, &iter->Get_Info(), sizeof(INFO), &dwByte, NULL);
	}

	for (auto& iter : m_ObjList[OBJ_POINT])
	{
		WriteFile(hFile, &iter->Get_Info(), sizeof(INFO), &dwByte, NULL);
	}

	CloseHandle(hFile);
}



void CObjMgr::Load_Obj(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Obj.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	INFO		tInfo{};
	FRAME		tFrame{};
	DWORD		dwByte = 0;

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj*		pObj = CAbstractFactory<CRing>::Create(tInfo.fX, tInfo.fY);
		pObj->Initialize();

		m_ObjList[OBJ_ITEM].push_back(pObj);

	}

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj*		pObj = CAbstractFactory<CSpring>::Create(tInfo.fX, tInfo.fY);
		pObj->Initialize();

		m_ObjList[OBJ_SPRING].push_back(pObj);

	}

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj*		pObj = CAbstractFactory<CSpike>::Create(tInfo.fX, tInfo.fY);
		pObj->Initialize();

		m_ObjList[OBJ_SPIKE].push_back(pObj);

	}


	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj*		pObj = CAbstractFactory<CGoal>::Create(tInfo.fX, tInfo.fY);
		pObj->Initialize();

		m_ObjList[OBJ_POINT].push_back(pObj);

	}

	CloseHandle(hFile);

}

