#include "../MonsterUseHeader.h"
#include "DarkHell.h"


DarkHell::DarkHell()
{
}


DarkHell::~DarkHell()
{

}

void DarkHell::Setup(Map* map, D3DXVECTOR3 spawnPos)
{
	//�𵨺��� �����
	MODELMANAGER->AddModel("��ũ��", "Model/Enemy/DarkHell/", "DarkHell.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("��ũ��", MODELTYPE_X);

	//�θ��� �¾��� ȣ���ض�
	MagicMonster::Setup(map, spawnPos);

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

void DarkHell::SetupStat()
{

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

}
