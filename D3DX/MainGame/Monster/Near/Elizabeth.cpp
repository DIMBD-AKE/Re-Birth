#include "../../../stdafx.h"
#include "Elizabeth.h"
#include "../../Map.h"
#include "../../Status.h"

Elizabeth::Elizabeth()
{

}


Elizabeth::~Elizabeth()
{
	SAFE_DELETE(m_pModel);
}

void Elizabeth::Setup(Map* map, D3DXVECTOR3 spawnPos)
{
	//모델부터 만들고
	MODELMANAGER->AddModel("엘리자베스", "Model/Enemy/Elizabeth/", "Elizabeth.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("엘리자베스", MODELTYPE_X);

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

void Elizabeth::SetupStat()
{
	CURRENTHP(m_uMonsterStat) = MAXHP(m_uMonsterStat)  = 100;
	ATK(m_uMonsterStat) = 10;
	//PHYRATE(m_uMonsterStat) = 

	//m_uMonsterStat.CURRENTHP = m_uMonsterStat.MAXHP = 100;


	/*
		int		nCurrentHP;		//캐릭터(적, 플레이어) 현재 피
		int		nMaxHp;			//캐릭터(적, 플레이어) 최대 피

		int		nAtk;			//기본공격력
		float	fPhyRate;		//물리계수
		float	fMagicRate;		//마법계수
		float	fCheRate;		//화학계수
		float	fAtkSpeed;		//공격속도 (장비속도에 * 연산)

		int		nDef;			//방어력
		float	fAgi;			//회피력
		float	fHit;			//명중률
		float	fSpeed;			//이동속도
	*/
}

void Elizabeth::Attack()
{

}

void Elizabeth::Skill()
{

}

void Elizabeth::Move()
{
	if (INPUT->KeyDown('P'))
		{
			m_bIsRespawn = true;
			m_eState = MS_DIE;
			ChangeAni();
		
		}
		
	if (!m_bIsRespawn)
	{
		if (m_pModel)
		{
			m_pModel->World();
			m_pModel->Update();
		}
	}
}


//void Elizabeth::Update()
//{
//	if (INPUT->KeyDown('P'))
//	{
//		m_bIsRespawn = true;
//		m_eState = MS_DIE;
//		ChangeAni();
//
//	}
//	
//		if (!m_bIsRespawn)
//		{
//			if (m_pModel)
//			{
//				m_pModel->World();
//				m_pModel->Update();
//			}
//		}
//		else
//		{
//			//if (m_pDeathModel)
//			//{
//			//	m_pDeathModel->World();
//			//	m_pDeathModel->Update();
//			//}
//		}
//	
//}

