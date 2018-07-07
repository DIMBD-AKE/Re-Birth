#include "../../../stdafx.h"
#include "NifilHeim.h"


NifilHeim::NifilHeim()
{
}


NifilHeim::~NifilHeim()
{

}

void NifilHeim::Setup(Map* map, D3DXVECTOR3 spawnPos)
{
	//�𵨺��� �����
	MODELMANAGER->AddModel("��������", "Model/Enemy/NifilHeim/", "NifilHeim.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("��������", MODELTYPE_X);

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

void NifilHeim::SetupStat()
{

}


//���� ���� �����Լ�
void NifilHeim::Attack()
{

}

//���� ���� ��ų�Լ�
void NifilHeim::Skill()
{

}

//���� ���� �⺻ �̵��Լ�
void NifilHeim::Move()
{

}


void NifilHeim::DropItemSetup()
{

}
