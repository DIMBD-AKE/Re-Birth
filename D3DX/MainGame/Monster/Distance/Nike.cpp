#include "../../../stdafx.h"
#include "Nike.h"


Nike::Nike()
{
}


Nike::~Nike()
{

}

void Nike::Setup(Map* map, D3DXVECTOR3 spawnPos)
{
	//�𵨺��� �����
	MODELMANAGER->AddModel("����", "Model/Enemy/Nike/", "Nike.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("����", MODELTYPE_X);

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

void Nike::SetupStat()
{

}


//���� ���� �����Լ�
void Nike::Attack()
{

}

//���� ���� ��ų�Լ�
void Nike::Skill()
{

}

//���� ���� �⺻ �̵��Լ�
void Nike::Move()
{

}


void Nike::DropItemSetup()
{

}
