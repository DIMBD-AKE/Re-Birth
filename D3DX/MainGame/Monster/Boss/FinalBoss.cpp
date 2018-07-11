#include "../MonsterUseHeader.h"
#include "FinalBoss.h"


FinalBoss::FinalBoss()
{
}


FinalBoss::~FinalBoss()
{
}

void FinalBoss::SetupBoss(Map* map, D3DXVECTOR3 pos)
{
	//¸ðµ¨ ¹Ù²ã¾ßÇÔ
	MODELMANAGER->AddModel("ÆÒÅÒ", "Model/Enemy/PhantomKnight/", "PhantomKnight.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("ÆÒÅÒ", MODELTYPE_X);

	BossParent::SetupBoss(map, pos);

	//ÆÇÁ¤ ¹Ú½º 
	ST_SIZEBOX box;
	box.highX = 50.0f;
	box.highY = 180.0f;
	box.highZ = 50.0f;
	box.lowX = -50.0f;
	box.lowY = 10.0f;
	box.lowZ = -50.0f;


	m_pModel->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));

	m_pModel->CreateBound(box);
	m_pModel->SetBoundSphere(m_pModel->GetOrigBoundSphere().center, 100.0f);


}

void FinalBoss::SetupStat()
{
	m_nMinMoveCount = 0;
	m_nMaxMoveCount = 0;

	ZeroMemory(&m_uMonsterStat, sizeof(m_uMonsterStat));

	CURRENTHP(m_uMonsterStat) = MAXHP(m_uMonsterStat) = 1500;
	ATK(m_uMonsterStat) = 20;
	PHYRATE(m_uMonsterStat) = 1.3f;
	MAGICRATE(m_uMonsterStat) = 0.8f;
	CHERATE(m_uMonsterStat) = 1.1f;
	ATKSPEED(m_uMonsterStat) = 0.75f;

	DEF(m_uMonsterStat) = 5;
	AGI(m_uMonsterStat) = 10.0f;
	HIT(m_uMonsterStat) = 10.0f;
	SPEED(m_uMonsterStat) = 0.08f;
	RANGE(m_uMonsterStat) = 2.2f;
}

void FinalBoss::DropItemSetup()
{
	m_nItemID[0] = SWORDMAN_NORMAL_ARMOR;
	m_nItemID[1] = SWORDMAN_NORMAL_ARMOR;
	m_nItemID[2] = SWORDMAN_NORMAL_ARMOR;
	m_nItemID[3] = SWORDMAN_NORMAL_ARMOR;
}

void FinalBoss::ChangeAni()
{
	//edd6switch (m_eState)
	//edd6{
	//edd6case MS_IDLE:
	//edd6	m_pModel->SetAnimation("IDLE");
	//edd6	break;
	//edd6case MS_RUN: case MS_MOVEFORATTACK:
	//edd6	m_pModel->SetAnimation("RUN");
	//edd6	break;
	//edd6case MS_SKILL:
	//edd6	m_pModel->SetAnimation("SKILL");
	//edd6	break;
	//edd6case MS_ATTACK:
	//edd6	m_pModel->SetAnimation("ATTACK");
	//edd6	break;
	//edd6case MS_DIE:
	//edd6	m_pModel->SetAnimation("DIE");
	//edd6	break;
	//edd6default:
	//edd6	break;
	//edd6}
}

void FinalBoss::Pattern()
{

}