#include "../../stdafx.h"
#include "MonsterParent.h"
#include "../Map.h"

MonsterParent::MonsterParent()
: m_pModel(NULL)
{
}


MonsterParent::~MonsterParent()
{
	SAFE_DELETE(m_pModel);
	//SAFE_DELETE(m_pDeathModel);
}

void MonsterParent::Setup(Map* map,  D3DXVECTOR3 spawnPos)
{
	m_nResPawnCount = m_bIsRespawn = 0;
	m_eState = MS_ATTACK;
	m_pMap = map;

	//ST_SIZEBOX box;
}

void MonsterParent::Update()
{

}

void MonsterParent::RespawnUpdate()
{
	char test[111];

	sprintf_s(test, sizeof(test), "%d", m_nResPawnCount);
	TEXT->Add(test, 10, 10, 20);

	m_nResPawnCount++;

	m_pModel->World();
	m_pModel->Update();

	if (m_pModel->IsAnimationEnd() && m_eState == MS_DIE)
	{
		m_eState = MS_NONE;
		//ChangeAnimation();
	}

	if (m_nResPawnCount >= 300)
	{
		m_bIsRespawn = false;
		m_nResPawnCount = 0;
	}
}
void MonsterParent::Render()
{

}

void MonsterParent::ChangeAni()
{
	switch (m_eState)
	{
	case MS_IDLE:
		m_pModel->SetAnimation("IDLE");
		break;
	case MS_RUN:
		m_pModel->SetAnimation("RUN");
		break;
	case MS_SKILL:
		m_pModel->SetAnimation("SKILL");
		break;
	case MS_ATTACK:
		m_pModel->SetAnimation("ATTACK");
		break;
	case MS_DIE:
		m_pModel->SetAnimation("DIE");
		break;
	default:
		break;
	}
}
void MonsterParent::Respawn(D3DXVECTOR3 spawnPos)
{
	m_nResPawnCount = m_bIsRespawn = 0;
	m_eState = MS_IDLE;
	ChangeAni();

	

	m_pModel->SetPosition(D3DXVECTOR3(spawnPos.x, m_pMap->GetHeight(spawnPos.x, spawnPos.z), spawnPos.z));
}