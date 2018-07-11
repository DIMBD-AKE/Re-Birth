#include "MonsterUseHeader.h"
#include "MonsterParent.h"
#include "../AStar/AStar.h"
#include "../Item/DropManager.h"

MonsterParent::MonsterParent()
: m_pModel(NULL)
{
}


MonsterParent::~MonsterParent()
{
	SAFE_DELETE(m_pAStar);
	SAFE_DELETE(m_pModel);


	m_pMap = NULL;
	m_ppCharacter = NULL;
	m_pDropManager = NULL;
	/*
	GET(Model*, m_pModel, Model);
	SET(CharacterParant**, m_ppCharacter, Character);
	SET(DropManager*, m_pDropManager, DropManager);
	*/
}

void MonsterParent::Setup(Map* map, D3DXVECTOR3 spawnPos)
{
	m_vDir = D3DXVECTOR3(0, 0, 1);

	m_nCount = 0;
	m_nPatternChangeCount = 0;

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
	DropItemSetup();

	m_pHPBar = new UIObject;

	TEXTUREMANAGER->AddTexture("MonBackBar", "./Model/Enemy/UI/백바.jpg");
	TEXTUREMANAGER->AddTexture("MonFrontBar", "./Model/Enemy/UI/프론트바.jpg");

	m_pHPBar->SetTexture(TEXTUREMANAGER->GetTexture("MonFrontBar"));

	D3DXVECTOR3 UIPos = *m_pModel->GetPosition();

	UIPos.x -= m_fUIMoveX;
	UIPos.y -= m_fUIMoveY;

	auto temp = Convert3DTo2D(UIPos);
	UIPos.x = temp.x;
	UIPos.y = temp.y;
	UIPos.z = 0;

	m_pHPBar->SetPosition(UIPos);

	UIObject* backBar = new UIObject;

	backBar->SetPosition(D3DXVECTOR3(0, 0, 0.1));
	backBar->SetTexture(TEXTUREMANAGER->GetTexture("MonBackBar"));


	m_pHPBar->AddChild(backBar);
	//ST_SIZEBOX box;
}

void MonsterParent::SetupBoss(Map* map, D3DXVECTOR3 pos)
{
	m_pMap = map;
	m_pModel->SetPosition(D3DXVECTOR3(pos.x, m_pMap->GetHeight(pos.x, pos.z), pos.z));
	SetupStat();

	m_pHPBar = new UIObject;

	TEXTUREMANAGER->AddTexture("BossBackBar", "./Model/Enemy/UI/보스백바.jpg");
	TEXTUREMANAGER->AddTexture("BossFrontBar", "./Model/Enemy/UI/보스프론트바.jpg");

	m_pHPBar->SetTexture(TEXTUREMANAGER->GetTexture("BossFrontBar"));

	m_pHPBar->SetPosition(D3DXVECTOR3(0,0,0));

	UIObject* backBar = new UIObject;

	backBar->SetPosition(D3DXVECTOR3(0, 0, 0.1));
	backBar->SetTexture(TEXTUREMANAGER->GetTexture("BossBackBar"));


	m_pHPBar->AddChild(backBar);
}

void MonsterParent::SetupStat()
{

}

void MonsterParent::Update()
{
	
	//if (INPUT->KeyDown('K'))
	//{
	//	SetCurrentHP(10);
	//}

	if (m_bIsTargeting)
	{
		float tempF = (float)CURRENTHP(m_uMonsterStat) / MAXHP(m_uMonsterStat);


		m_pHPBar->SetScale(D3DXVECTOR3(tempF, 1, 1));

		//if (INPUT->KeyDown('L'))
		//{
		//	m_bIsRespawn = true;
		//	m_eState = MS_DIE;
		//	ChangeAni();
		//	SetCurrentHP(1000);
		//}

		//m_pModel->GetBoundBox();
		//
		D3DXVECTOR3 UIPos = *m_pModel->GetPosition();
		//UIPos.x -= m_fUIMoveX;
		UIPos.y += m_fUIMoveY;

		auto temp = Convert3DTo2D(UIPos);
		UIPos.x = temp.x - m_fUIMoveX;
		UIPos.y = temp.y;
		UIPos.z = 0;
		m_pHPBar->SetPosition(UIPos);

		m_pHPBar->Update();

	}
	//if (INPUT->KeyDown(VK_RIGHT))
	//{
	//	m_fUIMoveX -= 10;
	//}
	//
	//if (INPUT->KeyDown(VK_LEFT))
	//{
	//	m_fUIMoveX += 10;
	//}
	//
	//if (INPUT->KeyDown(VK_DOWN))
	//{
	//	m_fUIMoveY -= 10;
	//}
	//
	//if (INPUT->KeyDown(VK_UP))
	//{
	//	m_fUIMoveY += 10;
	//}
	//char test[111];
	//
	//sprintf_s(test, sizeof(test), "%f, %f", m_fUIMoveX, m_fUIMoveY);
	//TEXT->Add(test, 10, 10, 30);

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
	/*

	D3DXVECTOR3 UIPos = *m_pModel->GetPosition();
	//UIPos.x -= m_fUIMoveX;
	//UIPos.y += m_fUIMoveY;

	auto temp = Convert3DTo2D(UIPos);
	UIPos.x = temp.x - m_fUIMoveX;
	UIPos.y = temp.y - m_fUIMoveY;
	UIPos.z = 0;
	m_pHPBar->SetPosition(UIPos);
	*/
	if (m_pModel && m_eState != MS_NONE)
	{
		m_pModel->Render();
		if (DEBUG)
		{
			POINT temp = MoveForAttack();

			m_pAStar->Render(temp.y, temp.x, CHARACTER->GetPosition());
		}


		//UIPos.x = temp.x - m_fUIMoveX;
		//UIPos.y = temp.y - m_fUIMoveY;
		//UIPos.z = 0;
		//m_pHPBar->SetPosition(UIPos);

		if (m_bIsTargeting) m_pHPBar->Render();
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
	CURRENTHP(m_uMonsterStat) = MAXHP(m_uMonsterStat);


	m_pModel->SetPosition(D3DXVECTOR3(spawnPos.x, m_pMap->GetHeight(spawnPos.x, spawnPos.z), spawnPos.z));
}

void MonsterParent::CalculDamage(float damage)
{
	
	/*
	float	fPhyRate;		//물리계수
	float	fMagicRate;		//마법계수
	float	fCheRate;		//화학계수
	*/
	float totalRate =
		PHYRATE(m_uMonsterStat) +
		CHERATE(m_uMonsterStat) +
		MAGICRATE(m_uMonsterStat);

	float totalDamage = totalRate * DEF(m_uMonsterStat);

	totalDamage = damage - totalDamage;

	totalDamage /= 3;

	if (totalDamage <= 1) totalDamage = 1;

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

		m_nPatternChangeCount = rand() % (max - min) + min;

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

	int playerIndex = m_pAStar->GetCellIndex(*CHARACTER->GetPosition());

	int myIndex = m_pAStar->GetCellIndex(*m_pModel->GetPosition());

	if (DEBUG) { return{ playerIndex, myIndex }; }
	D3DXVECTOR3 dir;
	//같은 셀에 있으면
	if (playerIndex == myIndex)
	{
		dir = *CHARACTER->GetPosition()
			- *m_pModel->GetPosition();
	}
	else
	{
		m_pAStar->SetCell(myIndex, playerIndex);

		D3DXVECTOR3 nextCell = m_pAStar->GetNextCell();

		dir = nextCell - *m_pModel->GetPosition();

		if (nextCell == D3DXVECTOR3(-1, -1, -1))
		{
			dir = *CHARACTER->GetPosition()
				- *m_pModel->GetPosition();
		}

	}
	D3DXVec3Normalize(&dir, &dir);
	if (!DEBUG)
	{
		//D3DXVECTOR3 dirVector = *m_pModel->GetPosition() + dir;
		//
		//D3DXVECTOR3 test = *m_pModel->GetPosition();

		float angle = GetAngle(0, 0, dir.x, dir.z);

		//float x = dir.x - 0;
		//float y = dir.z - 0;
		//
		//float distance = sqrtf(x * x + y * y);
		//
		//float angle = acosf(x / distance);
		//
		//if (dir.z > 0)
		//{
		//	angle = D3DX_PI * 2 - angle;
		//	if (angle >= D3DX_PI * 2) angle -= D3DX_PI * 2;
		//}

		angle -= D3DX_PI / 2;

		m_pModel->SetRotation(D3DXVECTOR3(0, angle, 0));
		m_pModel->SetPosition(*m_pModel->GetPosition() + dir* SPEED(m_uMonsterStat));
	}

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
	//최종보스같은경우 드랍하지 않으므로
	if (m_vItemID.size() <= 0) return;

	srand(time(NULL));

	//0~99값
	int ranNum = rand() % 100;

	float chancePerNum = 100.0f / m_vItemID.size();
	
	for (int i = 0; i < m_vItemID.size(); i++)
	{
		if (ranNum < chancePerNum * (i + 1))
		{
			m_pDropManager->AddDropItem(m_vItemID[i], *m_pModel->GetPosition());
			break;
		}
	}

}