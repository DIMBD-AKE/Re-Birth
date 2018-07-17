#include "../MonsterUseHeader.h"
#include "Nerisa.h"


Nerisa::Nerisa()
{
}


Nerisa::~Nerisa()
{

}

void Nerisa::Setup(Map* map, D3DXVECTOR3 spawnPos, bool isSummon)
{
	//�𵨺��� �����
	//MODELMANAGER->AddModel("�ʸ���", "Model/Enemy/Nerisa/", "Nerisa.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("�ʸ���", MODELTYPE_X);

	m_fUIMoveX = 50.0f;
	m_fUIMoveY =4.0f;

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
	m_pSkill = SKILL->GetSkill("Nerisa Skill");
}

void Nerisa::SetupStat()
{
	m_nMinMoveCount = 444;
	m_nMaxMoveCount = 333;

	ZeroMemory(m_pMonsterStat, sizeof(STATUS));

	CURRENTHP(m_pMonsterStat) = MAXHP(m_pMonsterStat) = 80;
	ATK(m_pMonsterStat) = 14;
	PHYRATE(m_pMonsterStat) = 0.9f;
	MAGICRATE(m_pMonsterStat) = 0.9f;
	CHERATE(m_pMonsterStat) = 1.3f;
	ATKSPEED(m_pMonsterStat) = 0.8f;

	DEF(m_pMonsterStat) = 3;
	AGI(m_pMonsterStat) = 20.0f;
	HIT(m_pMonsterStat) = 20.0f;
	SPEED(m_pMonsterStat) = 0.09f;
	RANGE(m_pMonsterStat) = 6.5f;
}

void Nerisa::SetupSkill()
{

}

//���� ���� �����Լ�
//void Nerisa::Attack()
//{
//
//}

//���� ���� ��ų�Լ�
void Nerisa::Skill()
{

}

//���� ���� �⺻ �̵��Լ�
//void Nerisa::Move()
//{
//
//}


void Nerisa::DropItemSetup()
{
	m_vItemID.push_back(ITEM_NULL);
	m_vItemID.push_back(NORMAL_RECOVERYBOOK);
	m_vItemID.push_back(NORMAL_BLADE);
	m_vItemID.push_back(ARCHER_NORMAL_GAUNTLET);
	m_vItemID.push_back(ARCHER_NORMAL_BOOTS);
	m_vItemID.push_back(KNIGHT_NORMAL_ARMOR);
	m_vItemID.push_back(KNIGHT_NORMAL_GAUNTLET);
}
