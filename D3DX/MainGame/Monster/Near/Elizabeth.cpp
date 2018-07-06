#include "../../../stdafx.h"
#include "Elizabeth.h"
#include "../../Map.h"
#include "../../Status.h"
#include <time.h>
#include "../../Character/CharacterParant.h"
#include "../../Item/ItemList.h"

Elizabeth::Elizabeth()
{

}


Elizabeth::~Elizabeth()
{
	SAFE_DELETE(m_pModel);
}

void Elizabeth::Setup(Map* map, D3DXVECTOR3 spawnPos)
{
	//�𵨺��� �����
	MODELMANAGER->AddModel("�����ں���", "Model/Enemy/Elizabeth/", "Elizabeth.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("�����ں���", MODELTYPE_X);

	//�θ��� �¾��� ȣ���ض�
	NearMonster::Setup(map, spawnPos);

	
	//MODELMANAGER->AddModel("�����ں���", "Model/Enemy/Assis/", "Assis.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("�����ں���", "Model/Enemy/DarkHell/", "DarkHell.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("�����ں���", "Model/Enemy/PhantomKnight/", "PhantomKnight.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("�����ں���", "Model/Enemy/Nike/", "Nike.x", MODELTYPE_X);



	//���� �ڽ� 
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
		int		nCurrentHP;		//ĳ����(��, �÷��̾�) ���� ��
		int		nMaxHp;			//ĳ����(��, �÷��̾�) �ִ� ��

		int		nAtk;			//�⺻���ݷ�
		float	fPhyRate;		//�������
		float	fMagicRate;		//�������
		float	fCheRate;		//ȭ�а��
		float	fAtkSpeed;		//���ݼӵ� (���ӵ��� * ����)

		int		nDef;			//����
		float	fAgi;			//ȸ�Ƿ�
		float	fHit;			//���߷�
		float	fSpeed;			//�̵��ӵ�
	*/
}

void Elizabeth::Attack()
{
	//�ϴ� ����ó�� -> �÷��̾� ������ �Ǿ��ٸ�

	if (m_pCharacter)
	{
		D3DXVECTOR3 tempV = *m_pModel->GetPosition() - *m_pCharacter->GetCharacter()->GetPosition();
		float length = D3DXVec3Length(&tempV);

		int a = 10;
		//���� ���� ��Ÿ����� �ϸ� �ɵ�
		if (length > 1)
		{
			MoveForAttack();
		}
		else
		{
			m_eState = MS_ATTACK;
		}
	}
}

void Elizabeth::Skill()
{

}

void Elizabeth::Move()
{
	
	if (m_nCount == m_nPatternChangeCount/*INPUT->KeyDown('O')*/)
	{
		MoveReset(false);
	}
	char ttest[111];
	sprintf_s(ttest, sizeof(ttest), "%f, %f, %f", m_vDir.x, m_vDir.y, m_vDir.z);
	TEXT->Add(ttest, 10, 10, 30);

	if (m_eState == MS_RUN)
	{
		D3DXVECTOR3 tempPos = *m_pModel->GetPosition() + m_vDir*0.03f;
		tempPos.y = m_pMap->GetHeight(tempPos.x, tempPos.z);

		//������ ���̴�.
		if (tempPos.y < 0)
		{
			MoveReset(true);
		}
		else
		{
			m_pModel->SetPosition(tempPos);
		}
		
	}
	
	m_nCount++;

	

	if (INPUT->KeyDown('L'))
		{
			m_bIsRespawn = true;
			m_eState = MS_DIE;
			ChangeAni();
		
		}
		
	
}

void Elizabeth::DropItemSetup()
{
	m_nItemID[0] = HEALTH_POTION;
	m_nItemID[1] = BASIC_SWORD;
	m_nItemID[2] = HEALTH_POTION;
	m_nItemID[3] = BASIC_SWORD;
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

