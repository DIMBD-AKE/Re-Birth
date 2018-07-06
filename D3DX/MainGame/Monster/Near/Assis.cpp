#include "../../../stdafx.h"
#include "Assis.h"
#include "../../Map.h"
#include "../../Status.h"

Assis::Assis()
{
}


Assis::~Assis()
{

}

void Assis::Setup(Map* map, D3DXVECTOR3 spawnPos)
{
	//�𵨺��� �����
	MODELMANAGER->AddModel("�ƽý�", "Model/Enemy/Assis/", "Assis.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("�ƽý�", MODELTYPE_X);

	//�θ��� �¾��� ȣ���ض�
	NearMonster::Setup(map, spawnPos);


	//MODELMANAGER->AddModel("�����ں���", "Model/Enemy/Assis/", "Assis.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("�����ں���", "Model/Enemy/DarkHell/", "DarkHell.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("�����ں���", "Model/Enemy/PhantomKnight/", "PhantomKnight.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("�����ں���", "Model/Enemy/Nike/", "Nike.x", MODELTYPE_X);



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

void Assis::SetupStat()
{

}


//���� ���� �����Լ�
void Assis::Attack()
{

}

//���� ���� ��ų�Լ�
void Assis::Skill()
{

}

//���� ���� �⺻ �̵��Լ�
void Assis::Move()
{

}


void Assis::DropItemSetup()
{

}
