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
	//모델부터 만들고
	MODELMANAGER->AddModel("아시스", "Model/Enemy/Assis/", "Assis.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("아시스", MODELTYPE_X);

	//부모의 셋업을 호출해라
	NearMonster::Setup(map, spawnPos);


	//MODELMANAGER->AddModel("엘리자베스", "Model/Enemy/Assis/", "Assis.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("엘리자베스", "Model/Enemy/DarkHell/", "DarkHell.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("엘리자베스", "Model/Enemy/PhantomKnight/", "PhantomKnight.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("엘리자베스", "Model/Enemy/Nike/", "Nike.x", MODELTYPE_X);



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

void Assis::SetupStat()
{

}


//근접 몬스터 공격함수
void Assis::Attack()
{

}

//근접 몬스터 스킬함수
void Assis::Skill()
{

}

//근접 몬스터 기본 이동함수
void Assis::Move()
{

}


void Assis::DropItemSetup()
{

}
