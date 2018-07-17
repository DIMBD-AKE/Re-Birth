#include "../MonsterUseHeader.h"
#include "Nike.h"


Nike::Nike()
{
}


Nike::~Nike()
{

}

void Nike::Setup(Map* map, D3DXVECTOR3 spawnPos, bool isSummon)
{
	//�𵨺��� �����
	MODELMANAGER->AddModel("����", "Model/Enemy/Nike/", "Nike.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("����", MODELTYPE_X);

	m_fUIMoveX = 50.0f;
	m_fUIMoveY = 4.0f;

	//m_bIsTargeting = true;

	//�θ��� �¾��� ȣ���ض�
	DistanceMonster::Setup(map, spawnPos, isSummon);

	//���� �ڽ� 
	ST_SIZEBOX box;
	box.highX = 50.0f;
	box.highY = 180.0f;
	box.highZ = 50.0f;
	box.lowX = -50.0f;
	box.lowY = 10.0f;
	box.lowZ = -50.0f;


	m_pModel->SetScale(D3DXVECTOR3(0.02f, 0.02f, 0.02f));

	m_pModel->CreateBound(box);
	m_pModel->SetBoundSphere(m_pModel->GetOrigBoundSphere().center, 100.0f);

	//��ų
	m_pSkill = SKILL->GetSkill("Nike Skill");
}

void Nike::SetupSkill()
{

}

void Nike::SetupStat()
{
	m_nMinMoveCount = 450;
	m_nMaxMoveCount = 100;

	ZeroMemory(m_pMonsterStat, sizeof(STATUS));

	CURRENTHP(m_pMonsterStat) = MAXHP(m_pMonsterStat) = 90;
	ATK(m_pMonsterStat) = 20;
	PHYRATE(m_pMonsterStat) = 0.9f;
	MAGICRATE(m_pMonsterStat) = 0.9f;
	CHERATE(m_pMonsterStat) = 1.3f;
	ATKSPEED(m_pMonsterStat) = 0.8f;

	DEF(m_pMonsterStat) = 4;
	AGI(m_pMonsterStat) = 20.0f;
	HIT(m_pMonsterStat) = 20.0f;
	SPEED(m_pMonsterStat) = 0.09f;
	RANGE(m_pMonsterStat) = 7.0f;
}


//���� ���� �����Լ�
//void Nike::Attack()
//{
//
//}

//���� ���� ��ų�Լ�
void Nike::SkillUse()
{

}

//���� ���� �⺻ �̵��Լ�
//void Nike::Move()
//{
//
//}


void Nike::DropItemSetup()
{
	m_vItemID.push_back(ITEM_NULL);
	m_vItemID.push_back(NORMAL_HEALTHPOTION);
	m_vItemID.push_back(NORMAL_ARROW);
	m_vItemID.push_back(ARCHER_NORMAL_HELMET);
	m_vItemID.push_back(ARCHER_NORMAL_ARMOR);
	m_vItemID.push_back(BABARIAN_RARE_GAUNTLET);
	m_vItemID.push_back(BABARIAN_RARE_BOOTS);
}
