#include "../MonsterUseHeader.h"
#include "MiddleBoss.h"


MiddleBoss::MiddleBoss()
{
}


MiddleBoss::~MiddleBoss()
{

}

void MiddleBoss::SetupBoss(Map* map, D3DXVECTOR3 pos)
{
	//�𵨺��� �����
	MODELMANAGER->AddModel("���׷�", "Model/Enemy/Lagro/", "Lagro.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("���׷�", MODELTYPE_X);

	//m_bIsTargeting = true;

	//�θ��� �¾��� ȣ���ض�
	BossParent::SetupBoss(map, pos);

	//���� �ڽ� 
	ST_SIZEBOX box;
	box.highX = 50.0f;
	box.highY = 180.0f;
	box.highZ = 50.0f;
	box.lowX = -50.0f;
	box.lowY = 10.0f;
	box.lowZ = -50.0f;


	m_pModel->SetScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));

	m_pModel->CreateBound(box);
	m_pModel->SetBoundSphere(m_pModel->GetOrigBoundSphere().center, 100.0f);
}