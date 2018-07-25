#include "../../stdafx.h"
#include "Follower.h"
#include "../Map.h"


void Follower::AStar(vector<D3DXVECTOR3> vecNavMesh)
{
	m_vecFindPath.clear();

	vector<ST_FOLLOWER_NODE*> closeList;
	vector<ST_FOLLOWER_NODE*> openList;
	int lastIndex = 0;

	// �׺�޽ø� ���� ��ȯ
	vector<ST_FOLLOWER_NODE> vecNode;
	for (int i = 0; i < vecNavMesh.size(); i += 3)
	{
		ST_FOLLOWER_NODE temp;
		ZeroMemory(&temp, sizeof(ST_FOLLOWER_NODE));
		temp.c.v0 = vecNavMesh[i];
		temp.c.v1 = vecNavMesh[i + 1];
		temp.c.v2 = vecNavMesh[i + 2];
		temp.c.center = (temp.c.v0 + temp.c.v1 + temp.c.v2) / 3.0f;
		vecNode.push_back(temp);
	}

	// Ÿ�� �� �߽���
	D3DXVECTOR3 targetCenter;
	for (int i = 0; i < vecNode.size(); i++)
	{
		if (D3DXIntersectTri(&vecNode[i].c.v0, &vecNode[i].c.v1, &vecNode[i].c.v2,
			&(*m_pTarget + D3DXVECTOR3(0, 300, 0)), &D3DXVECTOR3(0, -1, 0), NULL, NULL, NULL))
		{
			targetCenter = (vecNode[i].c.v0 + vecNode[i].c.v1 + vecNode[i].c.v2) / 3.0f;
			break;
		}
	}

	// ���� �� Ŭ���� �߰�
	D3DXVECTOR3 rayPos = *m_pModel->GetPosition() + D3DXVECTOR3(0, 300, 0);
	for (int i = 0; i < vecNode.size(); i++)
	{
		if (D3DXIntersectTri(&vecNode[i].c.v0, &vecNode[i].c.v1, &vecNode[i].c.v2,
			&rayPos, &D3DXVECTOR3(0, -1, 0), NULL, NULL, NULL))
		{
			vecNode[i].isList = true;
			closeList.push_back(&vecNode[i]);
			break;
		}
	}

	while (true)
	{
		// ���¸���Ʈ �߰�
		if (closeList.size() > 0)
		{
			float cg = closeList[lastIndex]->G;
			ST_FOLLOWER_CELL cc = closeList[lastIndex]->c;

			// �̿� �� ��ġ ���
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
		
		// ���¸���Ʈ �� ���
		for (int i = 0; i < openList.size(); i++)
		{
			openList[i]->H = D3DXVec3Length(&(openList[i]->c.center - *m_pTarget));
			openList[i]->F = openList[i]->G + openList[i]->H;
		}

		// Ŭ�����Ʈ �߰�
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
				ST_FOLLOWER_NODE * temp = closeList[lastIndex];
				while (temp != NULL)
				{
					m_vecFindPath.push_back(temp);
					temp = temp->pParent;
				}
				break;
			}
		}
		else
			break;
	}
}

Follower::Follower()
{
}


Follower::~Follower()
{
}

void Follower::Init(D3DXVECTOR3 * target, Map * map)
{
	m_pModel = MODELMANAGER->GetModel("�Ƹ�", MODELTYPE_X);
	m_pModel->SetPosition(map->GetSpawnPlayer());
	m_pTarget = target;
	m_pMap = map;
}

void Follower::Update()
{
	//if (INPUT->KeyDown('T'))
	{
		AStar(m_pMap->GetNavMesh());
		m_vecFindPath;
		int a = 0;
	}
}

void Follower::Render()
{
}
