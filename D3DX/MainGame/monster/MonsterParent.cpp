#include "../../stdafx.h"
#include "MonsterParent.h"


MonsterParent::MonsterParent()
: m_pModel(NULL)
{
}


MonsterParent::~MonsterParent()
{

}

void MonsterParent::Setup(Map* map,  D3DXVECTOR3 spawnPos)
{
	m_nResPawnCount = m_bIsRespawn = 0;
	m_eState = MS_ATTACK;

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