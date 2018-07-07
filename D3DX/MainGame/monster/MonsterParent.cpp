#include "../../stdafx.h"
#include "MonsterParent.h"
#include "../Map.h"
#include "../AStar/AStar.h"
#include <time.h>
#include "../Character/CharacterParant.h"
#include "../Item/DropManager.h"

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
	m_vDir = D3DXVECTOR3(0, 0, 1);

	m_nCount = 0;
	m_nPatternChangeCount = 0;
	m_nAttackDelay = 0;

	m_pAStar = new AStar;
	m_pAStar->SetCurrentCell(map->GetNavMesh());
	//m_pAStar->SetCell(0, 0);
	//D3DXVECTOR3 temp =  m_pAStar->GetNextCell();

	m_nResPawnCount = m_bIsRespawn = 0;
	m_eState = MS_RUN;
	m_pMap = map;
	m_pModel->SetPosition(D3DXVECTOR3(spawnPos.x, m_pMap->GetHeight(spawnPos.x, spawnPos.z), spawnPos.z));
	ChangeAni();

	SetupStat();
	//ST_SIZEBOX box;
}

void MonsterParent::SetupStat()
{

}

void MonsterParent::Update()
{
	if (!DEBUG)
	{
		if (INPUT->KeyDown('O'))
		{
			m_eState = MS_ATTACK;
		}
		switch (m_eState)
		{
			//기본 및 움직이는 상태일때 move함수 호출해서 행동
		case MS_IDLE: case MS_RUN:
		{
						  Move();
		}
			break;
			//스킬상태이면 스킬상태 함수 호출
		case MS_SKILL:
		{
						 Skill();
		}
			break;
			//공격상태이면 공격상태 호출
		case MS_ATTACK: case MS_MOVEFORATTACK:
		{
							Attack();
		}
			break;
		default:
			break;
		}


		if (!m_bIsRespawn)
		{
			if (m_pModel)
			{
				m_pModel->World();
				m_pModel->Update();
			}
		}
	}
	//ChangeAni();
}

void MonsterParent::RespawnUpdate()
{
	//char test[111];
	//
	//sprintf_s(test, sizeof(test), "%d", m_nResPawnCount);
	//TEXT->Add(test, 10, 10, 20);

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
	if (m_pModel && m_eState != MS_NONE)
	{
		m_pModel->Render();
		if (DEBUG)
		{
			POINT temp = MoveForAttack();

			m_pAStar->Render( temp.y, temp.x, m_pCharacter->GetCharacter()->GetPosition());
		}
	}
}

void MonsterParent::ChangeAni()
{
	switch (m_eState)
	{
	case MS_IDLE:
		m_pModel->SetAnimation("IDLE");
		break;
	case MS_RUN: case MS_MOVEFORATTACK:
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

void MonsterParent::CalculDamage(float damage)
{
	m_eState = MS_ATTACK;
	/*
		float	fPhyRate;		//물리계수
		float	fMagicRate;		//마법계수
		float	fCheRate;		//화학계수
	*/
	float totalRate =
		m_uMonsterStat.chr.fPhyRate +
		m_uMonsterStat.chr.fMagicRate +
		m_uMonsterStat.chr.fCheRate;

	float totalDamage = totalRate * m_uMonsterStat.chr.nDef;

	totalDamage = round(totalDamage);

	SetCurrentHP(totalDamage);

}

void MonsterParent::Attack()
{

}

void MonsterParent::Skill()
{

}

void MonsterParent::Move()
{

}

void MonsterParent::MoveReset(bool isReverse, int max, int min)
{
	if (!isReverse)
	{

		m_vDir = D3DXVECTOR3(0, 0, -1);
		srand(time(NULL));

		m_nPatternChangeCount = rand() % (max-min) + min;

		if (m_eState == MS_IDLE)
		{
			float temp = D3DXToRadian(rand() % 180 - 90);

			D3DXMATRIX matRotY;
			D3DXMatrixRotationY(&matRotY, temp);

			D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matRotY);

			D3DXVec3Normalize(&m_vDir, &m_vDir);

			m_pModel->SetRotation(D3DXVECTOR3(0, temp, 0));
			m_eState = MS_RUN;
			//ChangeAni();
		}
		else
		{
			m_eState = MS_IDLE;
		}
		ChangeAni();
		m_nCount = 0;
	}
	else
	{
		m_vDir.x = -m_vDir.x; m_vDir.z = -m_vDir.z;
		m_pModel->SetRotation(*m_pModel->GetRotation() + D3DXVECTOR3(0, D3DX_PI, 0));
	}
}

POINT MonsterParent::MoveForAttack()
{
	m_eState = MS_MOVEFORATTACK;

	int playerIndex = m_pAStar->GetCellIndex(*m_pCharacter->GetCharacter()->GetPosition());

	int myIndex = m_pAStar->GetCellIndex(*m_pModel->GetPosition());

	if (DEBUG) { return{ playerIndex, myIndex }; }
	D3DXVECTOR3 dir;
	//같은 셀에 있으면
	if (playerIndex == myIndex)
	{
		dir = *m_pCharacter->GetCharacter()->GetPosition()
			- *m_pModel->GetPosition();
	}
	else
	{
		m_pAStar->SetCell(myIndex, playerIndex);

		D3DXVECTOR3 nextCell = m_pAStar->GetNextCell();

		dir = nextCell - *m_pModel->GetPosition();

		if (nextCell == D3DXVECTOR3(-1, -1, -1))
		{
			dir = *m_pCharacter->GetCharacter()->GetPosition()
				- *m_pModel->GetPosition();
		}
		
	}
		D3DXVec3Normalize(&dir, &dir);
		if (!DEBUG)
			m_pModel->SetPosition(*m_pModel->GetPosition() + dir* SPEED(m_uMonsterStat));
	
	//char ttest[111];
	//sprintf_s(ttest, sizeof(ttest), "%f, %f, %f", dir.x, dir.y, dir.z);
	//TEXT->Add(ttest, 10, 10, 30);


	//if (m_eState == MS_RUN)
	//{
	//	D3DXVECTOR3 tempPos = *m_pModel->GetPosition() + m_vDir*0.03f;
	//	tempPos.y = m_pMap->GetHeight(tempPos.x, tempPos.z);
	//
	//	//못가는 곳이다.
	//	if (tempPos.y < 0)
	//	{
	//		MoveReset(true);
	//	}
	//	else
	//	{
	//		m_pModel->SetPosition(tempPos);
	//	}
	//
	//}
	return{ -1, -1 };
}

void MonsterParent::DropItemSetup()
{

}

void MonsterParent::ItemDrop()
{
	srand(time(NULL));

	//0~99값
	int ranNum = rand() % 100;

	//60퍼 확률
	//if (ranNum < 60)
	//{
	//	//m_pDropManager->AddDropItem(m_nItemID[0], *m_pModel->GetPosition());
	//	//드랍없음
	//}
	
	//20퍼 확률
	if (ranNum < 80)
	{
		m_pDropManager->AddDropItem(m_nItemID[1], *m_pModel->GetPosition());
		//드랍1
	}

	//15퍼 확률
	else if (ranNum < 95)
	{
		m_pDropManager->AddDropItem(m_nItemID[2], *m_pModel->GetPosition());
		//드랍2
	}

	//5퍼 확률
	else if (ranNum < 100)
	{
		m_pDropManager->AddDropItem(m_nItemID[3], *m_pModel->GetPosition());
		//드랍3
	}
	//확률연산
	
}