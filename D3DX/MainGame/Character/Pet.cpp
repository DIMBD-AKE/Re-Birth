#include "../../stdafx.h"
#include "Pet.h"
#include "../Map.h"


bool Pet::TargetUpdate(vector<D3DXVECTOR3> vecNavMesh)
{
	auto temp = m_stTargetCell;
	for (int i = 0; i < vecNavMesh.size(); i += 3)
	{
		if (D3DXIntersectTri(&vecNavMesh[i], &vecNavMesh[i + 1], &vecNavMesh[i + 2],
			&D3DXVECTOR3(m_pTarget->x, 300, m_pTarget->z), &D3DXVECTOR3(0, -1, 0), NULL, NULL, NULL))
		{
			m_stTargetCell.v0 = vecNavMesh[i];
			m_stTargetCell.v1 = vecNavMesh[i + 1];
			m_stTargetCell.v2 = vecNavMesh[i + 2];
			m_stTargetCell.center = (m_stTargetCell.v0 + m_stTargetCell.v1 + m_stTargetCell.v2) / 3.0f;
			break;
		}
	}
	if (D3DXVec3Length(&(temp.center - m_stTargetCell.center)) > 1)
		return true;
	else
		return false;
}

void Pet::AStar(vector<D3DXVECTOR3> vecNavMesh)
{
	m_vecFindPath.clear();

	vector<ST_PET_NODE*> closeList;
	vector<ST_PET_NODE*> openList;
	int lastIndex = 0;

	// 네브메시를 노드로 변환
	vector<ST_PET_NODE> vecNode;
	for (int i = 0; i < vecNavMesh.size(); i += 3)
	{
		ST_PET_NODE temp;
		ZeroMemory(&temp, sizeof(ST_PET_NODE));
		temp.c.v0 = vecNavMesh[i];
		temp.c.v1 = vecNavMesh[i + 1];
		temp.c.v2 = vecNavMesh[i + 2];
		temp.c.center = (temp.c.v0 + temp.c.v1 + temp.c.v2) / 3.0f;
		vecNode.push_back(temp);
	}

	D3DXVECTOR3 targetCenter;
	bool findTargetCenter = false, findCurrentCell = false;;
	for (int i = 0; i < vecNode.size(); i++)
	{
		// 타겟 셀 중심점
		if (D3DXIntersectTri(&vecNode[i].c.v0, &vecNode[i].c.v1, &vecNode[i].c.v2,
			&(*m_pTarget + D3DXVECTOR3(0, 300, 0)), &D3DXVECTOR3(0, -1, 0), NULL, NULL, NULL) && !findTargetCenter)
		{
			targetCenter = (vecNode[i].c.v0 + vecNode[i].c.v1 + vecNode[i].c.v2) / 3.0f;
			findTargetCenter = true;
		}

		// 현재 셀 클로즈 추가
		if (D3DXIntersectTri(&vecNode[i].c.v0, &vecNode[i].c.v1, &vecNode[i].c.v2,
			&(*m_pModel->GetPosition() + D3DXVECTOR3(0, 300, 0)), &D3DXVECTOR3(0, -1, 0), NULL, NULL, NULL) && !findCurrentCell)
		{
			vecNode[i].isList = true;
			closeList.push_back(&vecNode[i]);
			findCurrentCell = true;
		}

		if (findTargetCenter && findCurrentCell)
			break;
	}

	while (true)
	{
		// 오픈리스트 추가
		if (closeList.size() > 0)
		{
			float cg = closeList[lastIndex]->G;
			ST_PET_CELL cc = closeList[lastIndex]->c;

			// 이웃 셀 위치 계산
			float nl0 = D3DXVec3Length(&(cc.center - (cc.v0 + cc.v1) / 2.0f)) + 0.1;
			float nl1 = D3DXVec3Length(&(cc.center - (cc.v1 + cc.v2) / 2.0f)) + 0.1;
			float nl2 = D3DXVec3Length(&(cc.center - (cc.v2 + cc.v0) / 2.0f)) + 0.1;
			D3DXVECTOR3 n[3], nc;
			D3DXVec3Normalize(&n[0], &(cc.center - cc.v2)); n[0] *= nl0; n[0] += cc.center;
			D3DXVec3Normalize(&n[1], &(cc.center - cc.v0)); n[1] *= nl1; n[1] += cc.center;
			D3DXVec3Normalize(&n[2], &(cc.center - cc.v1)); n[2] *= nl2; n[2] += cc.center;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < vecNode.size(); j++)
				{
					if (D3DXIntersectTri(&vecNode[j].c.v0, &vecNode[j].c.v1, &vecNode[j].c.v2,
						&(n[i] + D3DXVECTOR3(0, 300, 0)), &D3DXVECTOR3(0, -1, 0), NULL, NULL, NULL))
					{
						float g = D3DXVec3Length(&(cc.center - vecNode[j].c.center));
						if (!vecNode[j].isList)
						{
							vecNode[j].isList = true;
							vecNode[j].G = cg + g;
							vecNode[j].pParent = closeList[lastIndex];
							openList.push_back(&vecNode[j]);
						}
						else if (cg + g < vecNode[j].G)
						{
							vecNode[j].G = cg + g;
							vecNode[j].pParent = closeList[lastIndex];
						}
					}
				}
			}
		}
		
		// 오픈리스트 값 계산
		for (int i = 0; i < openList.size(); i++)
		{
			openList[i]->H = D3DXVec3Length(&(openList[i]->c.center - *m_pTarget));
			openList[i]->F = openList[i]->G + openList[i]->H;
		}

		// 클로즈리스트 추가
		if (openList.size() > 0)
		{
			int index = 0;
			int lowest = openList[0]->F;
			for (int i = 0; i < openList.size(); i++)
			{
				if (openList[i]->F < lowest)
				{
					lowest = openList[i]->F;
					index = i;
				}
			}
			closeList.push_back(openList[index]);
			openList.erase(openList.begin() + index);
			lastIndex++;

			if (D3DXVec3Length(&(closeList[lastIndex]->c.center - targetCenter)) < 1)
			{
				ST_PET_NODE * temp = closeList[lastIndex];
				while (temp != NULL)
				{
					m_vecFindPath.push_back(*temp);
					temp = temp->pParent;
				}
				reverse(m_vecFindPath.begin(), m_vecFindPath.end());
				break;
			}
		}
		else
			break;
	}
}

void Pet::Move()
{
	D3DXVECTOR3 pos = *m_pModel->GetPosition();
	float y = m_pMap->GetHeight(pos.x, pos.z);
	if (y > 0)
		m_pModel->SetPosition(D3DXVECTOR3(pos.x, y, pos.z));

	if (!m_vecFindPath.empty())
	{
		D3DXVECTOR3 next = m_vecFindPath.front().c.center;
		float nextDir = GetAngle(pos.x, pos.z, next.x, next.z) - D3DX_PI / 2;
		m_pModel->SetRotation(D3DXVECTOR3(0, nextDir, 0));
		D3DXVECTOR3 front = GetFront(*m_pModel->GetRotation(), D3DXVECTOR3(0, 0, -1));
		m_pModel->SetPosition(*m_pModel->GetPosition() + front * 0.1);

		if (D3DXVec3Length(&(*m_pModel->GetPosition() - next)) < 1)
			m_vecFindPath.erase(m_vecFindPath.begin());
	}
}

void Pet::Debug()
{
	vector<D3DXVECTOR3> vecVertex;
	for (int i = 0; i < m_vecFindPath.size(); i++)
		vecVertex.push_back(m_vecFindPath[i].c.center + D3DXVECTOR3(0, 0.2, 0));

	if (!vecVertex.empty())
	{
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		DEVICE->SetTransform(D3DTS_WORLD, &mat);
		DEVICE->SetTexture(0, NULL);
		DEVICE->SetRenderState(D3DRS_LIGHTING, false);
		DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, vecVertex.size() - 1, &vecVertex[0], sizeof(D3DXVECTOR3));
	}
}

Pet::Pet()
{
}


Pet::~Pet()
{
	SAFE_DELETE(m_pModel);
}

void Pet::Init(D3DXVECTOR3 * target, Map * map)
{
	m_pModel = MODELMANAGER->GetModel("아린", MODELTYPE_X);
	m_pModel->SetPosition(map->GetSpawnPlayer());
	m_pModel->SetScale(D3DXVECTOR3(0.025, 0.025, 0.025));
	m_pModel->SetAnimation("RUN");
	m_pTarget = target;
	m_pMap = map;
}

void Pet::Update()
{
	if (TargetUpdate(m_pMap->GetNavMesh()))
		AStar(m_pMap->GetNavMesh());

	Move();
	m_pModel->World();
}

void Pet::Render()
{
	m_pModel->Render();

	Debug();
}
