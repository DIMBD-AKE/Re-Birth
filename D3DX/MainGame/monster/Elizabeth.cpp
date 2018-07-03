#include "../../stdafx.h"
#include "Elizabeth.h"
#include "../Map.h"

Elizabeth::Elizabeth()
{

}


Elizabeth::~Elizabeth()
{
	SAFE_DELETE(m_pModel);
}

void Elizabeth::Setup(Map* map, D3DXVECTOR3 spawnPos)
{
	MODELMANAGER->AddModel("�����ں���", "Model/Enemy/Elizabeth/", "Elizabeth.x", MODELTYPE_X);
	
	m_pModel = MODELMANAGER->GetModel("�����ں���", MODELTYPE_X);
	//���� �ڽ� 
	ST_SIZEBOX box;
	box.highX = 50.0f;
	box.highY = 180.0f;
	box.highZ = 50.0f;
	box.lowX = -50.0f;
	box.lowY = 10.0f;
	box.lowZ = -50.0f;
	
	//�� ��ĳ�ϸ�

	//m_pModel = new Model;
	//��ĳ�ϸ� ���̸� �ȳ����°��� �̻��Ѱ��� �����°��� ���� �ϴ� �ּ�ó��
	//m_pModel->SetScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));

	m_pModel->SetPosition(D3DXVECTOR3(spawnPos.x, map->GetHeight(spawnPos), spawnPos.z));

	m_pModel->CreateBound(box);
	m_pModel->SetBoundSphere(m_pModel->GetOrigBoundSphere().center, 100.0f);




	
}

void Elizabeth::Update()
{

	TEXT->Add("����", 10, 10, 20);
	int a = 10;
	if (m_pModel)
	{
		m_pModel->World();
		m_pModel->Update();
	}
}

void Elizabeth::Render()
{
	TEXT->Render();

	if (m_pModel)
	{
		m_pModel->Render();
	}
}

