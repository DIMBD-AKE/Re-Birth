#include "../MonsterUseHeader.h"
#include "Nerisa.h"


Nerisa::Nerisa()
{
}


Nerisa::~Nerisa()
{

}

void Nerisa::Setup(Map* map, D3DXVECTOR3 spawnPos)
{
	//�𵨺��� �����
	MODELMANAGER->AddModel("�ʸ���", "Model/Enemy/Nerisa/", "Nerisa.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("�ʸ���", MODELTYPE_X);

	m_fUIMoveX = 50.0f;
	m_fUIMoveY =4.0f;

	//m_bIsTargeting = true;

	//�θ��� �¾��� ȣ���ض�
	DistanceMonster::Setup(map, spawnPos);
	
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
}

void Nerisa::SetupStat()
{
	m_nMinMoveCount = 444;
	m_nMaxMoveCount = 333;

	ZeroMemory(&m_uMonsterStat, sizeof(m_uMonsterStat));

	CURRENTHP(m_uMonsterStat) = MAXHP(m_uMonsterStat) = 80;
	ATK(m_uMonsterStat) = 6;
	PHYRATE(m_uMonsterStat) = 0.9f;
	MAGICRATE(m_uMonsterStat) = 0.9f;
	CHERATE(m_uMonsterStat) = 1.3f;
	ATKSPEED(m_uMonsterStat) = 0.8f;

	DEF(m_uMonsterStat) = 3;
	AGI(m_uMonsterStat) = 20.0f;
	HIT(m_uMonsterStat) = 20.0f;
	SPEED(m_uMonsterStat) = 0.09f;
	RANGE(m_uMonsterStat) = 6.5f;
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
	m_nItemID[0] = SWORDMAN_NORMAL_ARMOR;
	m_nItemID[1] = SWORDMAN_NORMAL_ARMOR;
	m_nItemID[2] = SWORDMAN_NORMAL_ARMOR;
	m_nItemID[3] = SWORDMAN_NORMAL_ARMOR;
}
