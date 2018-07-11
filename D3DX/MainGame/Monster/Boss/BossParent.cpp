#include "../MonsterUseHeader.h"
#include "BossParent.h"


BossParent::BossParent()
{
}


BossParent::~BossParent()
{

}



void BossParent::SetupBoss(Map* map, D3DXVECTOR3 pos)
{
	MonsterParent::SetupBoss(map, pos);


}

void BossParent::Update()
{
	m_pModel->World();
	m_pModel->Update();
	Pattern();

}
		//1536
void BossParent::Render()
{
	if (m_pModel)
	{
		m_pModel->Render();
		
		if (m_bIsTargeting) m_pHPBar->Render();
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