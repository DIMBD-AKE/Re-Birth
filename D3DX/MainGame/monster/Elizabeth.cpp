#include "../../stdafx.h"
#include "Elizabeth.h"


Elizabeth::Elizabeth()
{

}


Elizabeth::~Elizabeth()
{
	SAFE_DELETE(m_pModel);
}

void Elizabeth::Setup(Map* map, D3DXVECTOR3 spawnPos)
{
	//MODELMANAGER->AddModel("�����ں���", "Model/Enemy/Elizabeth/", "Elizabeth.x", MODELTYPE_X);
	//
	////���� �ڽ� 
	//ST_SIZEBOX box;
	//box.highX = 50.0f;
	//box.highY = 180.0f;
	//box.highZ = 50.0f;
	//box.lowX = -50.0f;
	//box.lowY = 10.0f;
	//box.lowZ = -50.0f;
	//
	////�� ��ĳ�ϸ�
	//m_pModel->SetScale(D3DXVECTOR3(0.02f, 0.02f, 0.02f));




	
}

void Elizabeth::Update()
{

	TEXT->Add("����", 10, 10, 20);
}

void Elizabeth::Render()
{
	TEXT->Render();
}

