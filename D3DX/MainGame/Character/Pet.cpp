#include "../../stdafx.h"
#include "Pet.h"
#include "../Map.h"


bool Pet::TargetUpdate()
{
	auto vecNavMesh = m_pMap->GetNavMesh();
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

bool Pet::TargetEqualCell()
{
	auto vecNavMesh = m_pMap->GetNavMesh();
	ST_PET_CELL temp;
	for (int i = 0; i < vecNavMesh.size(); i += 3)
	{
		D3DXVECTOR3 pos = *m_pModel->GetPosition();
		if (D3DXIntersectTri(&vecNavMesh[i], &vecNavMesh[i + 1], &vecNavMesh[i + 2],
			&D3DXVECTOR3(pos.x, 300, pos.z), &D3DXVECTOR3(0, -1, 0), NULL, NULL, NULL))
		{
			temp.v0 = vecNavMesh[i];
			temp.v1 = vecNavMesh[i + 1];
			temp.v2 = vecNavMesh[i + 2];
			temp.center = (temp.v0 + temp.v1 + temp.v2) / 3.0f;
			break;
		}
	}
	if (D3DXVec3Length(&(temp.center - m_stTargetCell.center)) < 1)
		return true;
	else
		return false;
}

void Pet::AStar()
{
	m_vecFindPath.clear();

	vector<ST_PET_NODE*> closeList;
	vector<ST_PET_NODE*> openList;
	int lastIndex = 0;

	// 네브메시를 노드로 변환
	vector<ST_PET_NODE> vecNode;
	auto vecNavMesh = m_pMap->GetNavMesh();
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
				OptimizePath();
				break;
			}
		}
		else
			break;
	}
}

void Pet::OptimizePath()
{
	if (!m_isOptimize) return;
	// 패스 사이드 작업
	auto tempPath = m_vecFindPath;
	m_vecFindPath.clear();
	for (int i = 0; i < tempPath.size() - 1; i++)
	{
		D3DXVECTOR3 s[3];
		s[0] = (tempPath[i].c.v0 + tempPath[i].c.v1) / 2;
		s[1] = (tempPath[i].c.v1 + tempPath[i].c.v2) / 2;
		s[2] = (tempPath[i].c.v2 + tempPath[i].c.v0) / 2;
		int sideIndex = 0;
		for (int j = 0; j < 3; j++)
		{
			if (D3DXVec3Length(&(s[j] - tempPath[i + 1].c.center)) <
				D3DXVec3Length(&(s[sideIndex] - tempPath[i + 1].c.center)))
				sideIndex = j;
		}
		ST_PET_NODE center;
		center.c.center = s[sideIndex];
		m_vecFindPath.push_back(center);
	}
	ST_PET_NODE target;
	target.c = m_stTargetCell;
	m_vecFindPath.push_back(target);
}

void Pet::Move()
{
	D3DXVECTOR3 pos = *m_pModel->GetPosition();

	if (!m_vecFindPath.empty())
	{
		D3DXVECTOR3 next = m_vecFindPath.front().c.center;
		float targetRotY;

		if (TargetEqualCell())
			targetRotY = GetAngle(pos.x, pos.z, m_pTarget->x, m_pTarget->z) - D3DX_PI / 2;
		else
			targetRotY = GetAngle(pos.x, pos.z, next.x, next.z) - D3DX_PI / 2;

		D3DXVECTOR3 rot = *m_pModel->GetRotation();
		rot.y += 0.1 * (targetRotY - rot.y);
		TEXT->Add(to_string(targetRotY), 20, 40, 20, "", 0xFFFFFFFF);
		TEXT->Add(to_string(0.1 * (targetRotY - rot.y)), 20, 60, 20, "", 0xFFFFFFFF);
		//rot.y = targetRotY;
		m_pModel->SetRotation(rot);

		D3DXVECTOR3 front; D3DXVec3Normalize(&front, &(next - pos));

		if (D3DXVec3Length(&(*m_pModel->GetPosition() - *m_pTarget)) > 2.0f)
			m_pModel->SetPosition(*m_pModel->GetPosition() + front * m_eStatus.speed);
		else
		{
			m_vecFindPath.clear();
			return;
		}

		if (D3DXVec3Length(&(*m_pModel->GetPosition() - next)) < 1)
			m_vecFindPath.erase(m_vecFindPath.begin());
	}

	pos = *m_pModel->GetPosition();
	float y = m_pMap->GetHeight(pos.x, pos.z);
	if (y > 0)
		m_pModel->SetPosition(D3DXVECTOR3(pos.x, y, pos.z));
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
		DEVICE->SetFVF(D3DFVF_XYZ);
		DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, vecVertex.size() - 1, &vecVertex[0], sizeof(D3DXVECTOR3));
	}
}

void Pet::StateControll()
{
	if (m_eState != PET_ATTACK)
	{
		if (m_vecFindPath.empty() && m_eState == PET_MOVE)
		{
			m_eState = PET_IDLE;
			m_pModel->SetBlendTime(0.3);
			m_pModel->SetBlendAnimation("IDLE");
		}

		if (!m_vecFindPath.empty() && m_eState == PET_IDLE)
		{
			m_eState = PET_MOVE;
			m_pModel->SetAnimation("MOVE");
		}
	}

	if (m_eState == PET_SPAWN || m_eState == PET_DISAPPEAR)
	{
		m_pSpawnParticle->SetPosition(*m_pModel->GetPosition());
		m_pSpawnParticle->ApplyWorld();
		m_pSpawnParticle->Update();
		if (m_pSpawnParticle->IsDie())
		{
			if (m_eState == PET_SPAWN)
				m_eState = PET_IDLE;
			else if (m_eState == PET_DISAPPEAR)
				m_eState = PET_HIDE;
		}
	}

	if (m_eState == PET_MOVE)
	{
		Move();
	}

	if (m_eState == PET_ATTACK)
	{

	}

	if (m_eState != PET_HIDE)
	{
		if (TargetUpdate()) AStar();

		m_pModel->World();
	}
}

Pet::Pet()
{
}


Pet::~Pet()
{
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pSpawnParticle);
}

void Pet::Init(D3DXVECTOR3 * target, Map * map, PETTYPE type)
{
	if (type == PETTYPE_BENTLEY) m_pModel = MODELMANAGER->GetModel("강아지", MODELTYPE_X);
	if (type == PETTYPE_BUNNY) m_pModel = MODELMANAGER->GetModel("토끼", MODELTYPE_X);
	if (type == PETTYPE_MIHO) m_pModel = MODELMANAGER->GetModel("구미호", MODELTYPE_X);
	if (type == PETTYPE_MIRI) m_pModel = MODELMANAGER->GetModel("양", MODELTYPE_X);
	if (type == PETTYPE_NERO) m_pModel = MODELMANAGER->GetModel("고양이", MODELTYPE_X);
	if (type == PETTYPE_NIR) m_pModel = MODELMANAGER->GetModel("용", MODELTYPE_X);
	if (type == PETTYPE_NIX) m_pModel = MODELMANAGER->GetModel("피닉스", MODELTYPE_X);
	if (type == PETTYPE_PANDA) m_pModel = MODELMANAGER->GetModel("팬더", MODELTYPE_X);
	if (type == PETTYPE_PENNY) m_pModel = MODELMANAGER->GetModel("돼지", MODELTYPE_X);

	m_pModel->SetPosition(map->GetSpawnPlayer());
	m_pModel->SetScale(D3DXVECTOR3(0.025, 0.025, 0.025));
	m_pModel->SetAnimation("IDLE");
	m_eState = PET_HIDE;

	m_pSpawnParticle = PARTICLE->GetParticle("Pet Spawn");

	m_isOptimize = true;

	m_eStatus.speed = 0.1;

	m_pTarget = target;
	m_pMap = map;
}

void Pet::Update()
{
	if (INPUT->KeyDown('T'))
		m_isOptimize = !m_isOptimize;

	if (INPUT->KeyDown('X'))
		Spawn();

	if (m_isOptimize)
		TEXT->Add("최적화", 20, 20, 20, "", 0xFF00FF00);
	else
		TEXT->Add("최적화", 20, 20, 20, "", 0xFFFF0000);

	StateControll();
}

void Pet::Render()
{
	if (m_eState != PET_HIDE)
		m_pModel->Render();

	if (m_eState == PET_SPAWN || m_eState == PET_DISAPPEAR)
		m_pSpawnParticle->Render();

	Debug();
}

void Pet::AttackMode()
{
	if (m_eState != PET_HIDE)
	{
		if (m_eState == PET_ATTACK)
			m_eState = PET_IDLE;
		else
			m_eState = PET_ATTACK;
	}
}

void Pet::Spawn()
{
	if (m_eState == PET_HIDE)
	{
		m_eState = PET_SPAWN;
		m_pSpawnParticle->TimeReset();
		m_pModel->SetPosition(*m_pTarget);
	}
	else
	{
		m_eState = PET_DISAPPEAR;
		m_pSpawnParticle->TimeReset();
		m_pModel->SetAnimation("IDLE");
	}
}
