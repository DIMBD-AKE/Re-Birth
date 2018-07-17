#include "../MonsterUseHeader.h"
#include "../MonsterManager.h"
#include "BossParent.h"
#include "../Magic/MagicCircle.h"


BossParent::BossParent()
{
}


BossParent::~BossParent()
{
	SAFE_DELETE(m_pMagicCircle);
	m_pMM = NULL;

}



void BossParent::SetupBoss(Map* map, D3DXVECTOR3 pos)
{
	MonsterParent::SetupBoss(map, pos);

	m_pMagicCircle = new MagicCircle;
}

void BossParent::Update()
{
	if (m_pModel && (m_eState != MS_NONE && m_eBossState != BS_NONE))
	{
		m_pModel->World();
		m_pModel->Update();
	}

	if (INPUT->KeyDown('L'))
	{
		SetCurrentHP(100);
		//CURRENTHP(m_pMonsterStat) -= 100;
	}

	if (m_pHPBar)
	{
		float tempF = (float)CURRENTHP(m_pMonsterStat) / MAXHP(m_pMonsterStat);


		m_pHPBar->SetScale(D3DXVECTOR3(tempF, 1, 1));

		m_pHPBar->Update();
	}


	Pattern();

}
		//1536
void BossParent::Render()
{
	if (m_pModel && (m_eState != MS_NONE && m_eBossState != BS_NONE) )
	{
		m_pModel->Render();
		
		if (m_bIsTargeting) m_pHPBar->Render();
	}

	if (m_pHPBar) m_pHPBar->Render();

}

void BossParent::SetCurrentHP(int hp)
{
	CURRENTHP(m_pMonsterStat) -= hp;

	if (CURRENTHP(m_pMonsterStat) <= 0)
	{
		m_pMM->DeleteSummonMonster();
		CURRENTHP(m_pMonsterStat) = 0;
		m_bIsDead = true;
		m_bIsRespawn = true;
		m_eState = MS_DIE;
		m_eBossState = BS_DIE;
		ChangeAni();
		ItemDrop();
	}
}


void BossParent::SetupStat()
{

}


void BossParent::Attack()
{

}

void BossParent::Skill()
{

}

void BossParent::Move()
{

}


void BossParent::DropItemSetup()
{

}

void BossParent::ChangeAni()
{

}
void BossParent::Pattern()
{

}