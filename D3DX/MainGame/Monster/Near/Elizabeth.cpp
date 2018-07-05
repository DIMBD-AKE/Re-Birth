#include "../../../stdafx.h"
#include "Elizabeth.h"
#include "../../Map.h"
#include "../../Status.h"
#include <time.h>

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
	SPEED(m_uMonsterStat) = 0.01f;
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
	
	if (/*m_nCount == m_nPatternChangeCount*/INPUT->KeyDown(1))
	{
		//m_vDir = D3DXVECTOR3(0, 0, -1);
		srand(time(NULL));
		
		m_nPatternChangeCount = rand() % 500 + 300;

		//각도 변환
		
		//D3DXMatrixRotationYawPitchRoll(&matRot, m_pModel->GetRotation()->y, m_pModel->GetRotation()->x, m_pModel->GetRotation()->z);

		

		if (m_eState == MS_IDLE)
		{
			float temp = D3DXToRadian(rand() % 180 - 90) ;

			D3DXMATRIX matRotY;
			D3DXMatrixRotationY(&matRotY, temp);

			D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matRotY);

			D3DXVec3Normalize(&m_vDir, &m_vDir);
			
			m_pModel->SetRotation(D3DXVECTOR3(0,-temp,0));
			m_eState = MS_RUN;
			//ChangeAni();
		}
		else
		{
			m_eState = MS_IDLE;
		}
		ChangeAni();
		m_nCount = 0;
	}
	char ttest[111];
	sprintf_s(ttest, sizeof(ttest), "%f, %f, %f", m_vDir.x, m_vDir.y, m_vDir.z);
	TEXT->Add(ttest, 10, 10, 30);

	if (m_eState == MS_RUN)
	m_pModel->SetPosition(*m_pModel->GetPosition() + m_vDir*0.03f);
	
	m_nCount++;

	

	if (INPUT->KeyDown('P'))
		{
			m_bIsRespawn = true;
			m_eState = MS_DIE;
			ChangeAni();
		
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

