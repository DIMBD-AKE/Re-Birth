#include "../MonsterUseHeader.h"
#include "FinalBoss.h"


FinalBoss::FinalBoss()
{
}


FinalBoss::~FinalBoss()
{
}

void FinalBoss::SetupBoss(Map* map, D3DXVECTOR3 pos)
{
	//�� �ٲ����
	MODELMANAGER->AddModel("����", "Model/Enemy/PhantomKnight/", "PhantomKnight.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("����", MODELTYPE_X);

	BossParent::SetupBoss(map, pos);

	//���� �ڽ� 
	ST_SIZEBOX box;
	box.highX = 50.0f;
	box.highY = 180.0f;
	box.highZ = 50.0f;
	box.lowX = -50.0f;
	box.lowY = 10.0f;
	box.lowZ = -50.0f;


	m_pModel->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));

	m_pModel->CreateBound(box);
	m_pModel->SetBoundSphere(m_pModel->GetOrigBoundSphere().center, 100.0f);
}