#include "../MonsterUseHeader.h"
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
	//모델부터 만들고
	MODELMANAGER->AddModel("엘리자베스", "Model/Enemy/Elizabeth/", "Elizabeth.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("엘리자베스", MODELTYPE_X);

	m_fUIMoveX = 50.0f;
	m_fUIMoveY = 5.0f;

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
	m_nMinMoveCount = 800;
	m_nMaxMoveCount = 300;
	ZeroMemory(&m_uMonsterStat, sizeof(m_uMonsterStat));

	CURRENTHP(m_uMonsterStat) = MAXHP(m_uMonsterStat)  = 100;
	ATK(m_uMonsterStat) = 3;
	PHYRATE(m_uMonsterStat) = 0.9f;
	MAGICRATE(m_uMonsterStat) = 1.3f;
	CHERATE(m_uMonsterStat) = 1.0f;
	ATKSPEED(m_uMonsterStat) = 0.5f;

	DEF(m_uMonsterStat) = 4;
	AGI(m_uMonsterStat) = 10.0f;
	HIT(m_uMonsterStat) = 10.0f;
	SPEED(m_uMonsterStat) = 0.05f;
	RANGE(m_uMonsterStat) = 1.5f;
	//PHYRATE(m_uMonsterStat) = 

	//m_uMonsterStat.CURRENTHP = m_uMonsterStat.MAXHP = 100;


	/*
	int		nCurrentHP;		//캐릭터(적, 플레이어) 현재 피
		int		nMaxHp;			//캐릭터(적, 플레이어) 최대 피

		int		nCurrentStam;	//캐릭터 현재 스테미나
		int		nMaxStam;		//캐릭터 전체 스테미나

		int		nAtk;			//기본공격력
		float	fPhyRate;		//물리계수
		float	fMagicRate;		//마법계수
		float	fCheRate;		//화학계수
		float	fAtkSpeed;		//공격속도 (장비속도에 * 연산)

		int		nDef;			//방어력
		float	fAgi;			//회피력
		float	fHit;			//명중률
		float	fSpeed;			//이동속도
		float	fRange;			//공격 거리
		float	fScale;			//공격 범위
	*/
}

//void Elizabeth::Attack()
//{
//	//일단 예외처리 -> 플레이어 연결이 되었다면
//
//	if (m_pCharacter)
//	{
//		if (m_pCharacter->GetIsDead())
//		{
//			m_eState = MS_IDLE;
//			ChangeAni();
//			return;
//		}
//		//char test1[111];
//		//sprintf_s(test1, sizeof(test1), "플레이어의 체력 : %d, 엘리자베스의 체력 : %d", m_nAttackDelay);
//		//
//		//TEXT->Add(test1, 10, 10, 30);
//		D3DXVECTOR3 tempV = *m_pModel->GetPosition() - *m_pCharacter->GetCharacter()->GetPosition();
//		float length = D3DXVec3Length(&tempV);
//
//		int a = 10;
//		//공격 가능 사거리까지 하면 될듯
//		if (length > RANGE(m_uMonsterStat))
//		{
//			if (m_eState == MS_ATTACK)
//			{
//				m_eState = MS_MOVEFORATTACK;
//				ChangeAni();
//			}
//			MoveForAttack();
//		}
//		else
//		{
//			char test[111];
//			sprintf_s(test, sizeof(test), "공격딜레이 : %d", m_nAttackDelay);
//
//			TEXT->Add(test, 10, 10, 30);
//
//			if (m_eState == MS_MOVEFORATTACK)
//			{
//				m_eState = MS_ATTACK;
//				ChangeAni();
//			}
//			//플레이어 공격기능 설정
//			m_eState = MS_ATTACK;
//			if (m_nAttackDelay >= ATKSPEED(m_uMonsterStat))
//			{
//				float tatalRate = PHYRATE(m_uMonsterStat) + MAGICRATE(m_uMonsterStat) + CHERATE(m_uMonsterStat);
//				float tatalDamage = tatalRate * ATK(m_uMonsterStat);
//				m_pCharacter->CalculDamage(tatalDamage);
//				m_nAttackDelay = 0;
//			}
//			m_nAttackDelay++;
//		}
//	
//	}
//}

void Elizabeth::Skill()
{

}

//void Elizabeth::Move()
//{
//	
//	if (m_nCount == m_nPatternChangeCount/*INPUT->KeyDown('O')*/)
//	{
//		MoveReset(false,800,300);
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
//	//	{
//	//		m_bIsRespawn = true;
//	//		m_eState = MS_DIE;
//	//		ChangeAni();
//	//		SetCurrentHP(1000);
//	//	}
//		
//	
//}

void Elizabeth::DropItemSetup()
{
	m_nItemID[0] = SWORDMAN_NORMAL_ARMOR;
	m_nItemID[1] = SWORDMAN_NORMAL_ARMOR;
	m_nItemID[2] = SWORDMAN_NORMAL_ARMOR;
	m_nItemID[3] = SWORDMAN_NORMAL_ARMOR;
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

