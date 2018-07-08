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
	//모델부터 만들고
	MODELMANAGER->AddModel("다크헬", "Model/Enemy/DarkHell/", "DarkHell.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("다크헬", MODELTYPE_X);

	//부모의 셋업을 호출해라
	MagicMonster::Setup(map, spawnPos);

	//판정 박스 
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


//근접 몬스터 공격함수
//void DarkHell::Attack()
//{
//
//}

//근접 몬스터 스킬함수
void DarkHell::Skill()
{

}

//근접 몬스터 기본 이동함수
//void DarkHell::Move()
//{
//
//}


void DarkHell::DropItemSetup()
{

}
