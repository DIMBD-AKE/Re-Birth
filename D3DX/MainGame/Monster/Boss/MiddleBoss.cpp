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
	//모델부터 만들고
	MODELMANAGER->AddModel("나그로", "Model/Enemy/Lagro/", "Lagro.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("나그로", MODELTYPE_X);

	//m_bIsTargeting = true;

	//부모의 셋업을 호출해라
	BossParent::SetupBoss(map, pos);

	//판정 박스 
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