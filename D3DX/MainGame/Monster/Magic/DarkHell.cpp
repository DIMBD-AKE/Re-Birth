#include "../MonsterUseHeader.h"
#include "DarkHell.h"


DarkHell::DarkHell()
{
}


DarkHell::~DarkHell()
{

}

void DarkHell::Setup(Map* map, D3DXVECTOR3 spawnPos, bool isSummon)
{
	//�𵨺��� �����
	//MODELMANAGER->AddModel("��ũ��", "Model/Enemy/DarkHell/", "DarkHell.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("��ũ��", MODELTYPE_X);

	m_fUIMoveX = 50.0f;
	m_fUIMoveY = 6.0f;

	//�θ��� �¾��� ȣ���ض�
	MagicMonster::Setup(map, spawnPos, isSummon);

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
	m_pSkill = SKILL->GetSkill("DarkHell Skill");
}

void DarkHell::SetupStat()
{
	m_nMinMoveCount = 555;
	m_nMaxMoveCount = 222;

	ZeroMemory(m_pMonsterStat, sizeof(STATUS));

	CURRENTHP(m_pMonsterStat) = MAXHP(m_pMonsterStat) = 150;
	ATK(m_pMonsterStat) = 35;
	PHYRATE(m_pMonsterStat) = 0.8f;
	MAGICRATE(m_pMonsterStat) = 1.3f;
	CHERATE(m_pMonsterStat) = 0.8f;
	ATKSPEED(m_pMonsterStat) = 0.7f;

	DEF(m_pMonsterStat) = 4;
	AGI(m_pMonsterStat) = 5.0f;
	HIT(m_pMonsterStat) = 5.0f;
	SPEED(m_pMonsterStat) = 0.03f;
	RANGE(m_pMonsterStat) = 10.0f;
}


//���� ���� �����Լ�
//void DarkHell::Attack()
//{
//
//}

//���� ���� ��ų�Լ�
void DarkHell::Skill()
{

}

//���� ���� �⺻ �̵��Լ�
//void DarkHell::Move()
//{
//
//}


void DarkHell::DropItemSetup()
{
	m_vItemID.push_back(ITEM_NULL);
	m_vItemID.push_back(NORMAL_HEALTHPOTION);
	m_vItemID.push_back(NORMAL_WAND);
	m_vItemID.push_back(MAGE_NORMAL_ARMOR);
	m_vItemID.push_back(MAGE_NORMAL_BOOTS);
	m_vItemID.push_back(BABARIAN_RARE_HELMET);
	m_vItemID.push_back(VALKYRIE_RARE_GAUNTLET);
	m_vItemID.push_back(KNIGHT_NORMAL_BOOTS);
}
