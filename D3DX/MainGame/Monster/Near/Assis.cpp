#include "../MonsterUseHeader.h"
#include "Assis.h"

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

	m_fUIMoveX = 50.0f;
	m_fUIMoveY = 3.5f;

	//m_bIsTargeting = true;
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
	m_nMinMoveCount = 555;
	m_nMaxMoveCount = 222;

	ZeroMemory(&m_uMonsterStat, sizeof(m_uMonsterStat));

	CURRENTHP(m_uMonsterStat) = MAXHP(m_uMonsterStat) = 150;
	ATK(m_uMonsterStat) = 20;
	PHYRATE(m_uMonsterStat) = 1.3f;
	MAGICRATE(m_uMonsterStat) = 0.8f;
	CHERATE(m_uMonsterStat) = 1.1f;
	ATKSPEED(m_uMonsterStat) = 0.75f;

	DEF(m_uMonsterStat) = 5;
	AGI(m_uMonsterStat) = 10.0f;
	HIT(m_uMonsterStat) = 10.0f;
	SPEED(m_uMonsterStat) = 0.08f;
	RANGE(m_uMonsterStat) = 2.2f;

}


//근접 몬스터 공격함수
//void Assis::Attack()
//{
//	
//}

//근접 몬스터 스킬함수
void Assis::Skill()
{

}

//근접 몬스터 기본 이동함수
//void Assis::Move()
//{
//	if (m_nCount == m_nPatternChangeCount/*INPUT->KeyDown('O')*/)
//	{
//		MoveReset(false, 500, 100);
//	}
//	//char ttest[111];
//	//sprintf_s(ttest, sizeof(ttest), "%f, %f, %f", m_vDir.x, m_vDir.y, m_vDir.z);
//	//TEXT->Add(ttest, 10, 10, 30);
//
//	if (m_eState == MS_RUN)
//	{
//		D3DXVECTOR3 tempPos = *m_pModel->GetPosition() + m_vDir* SPEED(m_uMonsterStat);
//		tempPos.y = m_pMap->GetHeight(tempPos.x, tempPos.z);
//
//		//못가는 곳이다.
//		if (tempPos.y < 0)
//		{
//			MoveReset(true);
//		}
//		else
//		{
//			m_pModel->SetPosition(tempPos);
//		}
//
//	}
//
//	m_nCount++;
//
//
//
//	//if (INPUT->KeyDown('L'))
//	//{
//	//	m_bIsRespawn = true;
//	//	m_eState = MS_DIE;
//	//	ChangeAni();
//	//	SetCurrentHP(1000);
//	//}
//}


void Assis::DropItemSetup()
{
	m_nItemID[0] = SWORDMAN_NORMAL_ARMOR;
	m_nItemID[1] = SWORDMAN_NORMAL_ARMOR;
	m_nItemID[2] = SWORDMAN_NORMAL_ARMOR;
	m_nItemID[3] = SWORDMAN_NORMAL_ARMOR;
}
