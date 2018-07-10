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
	//�𵨺��� �����
	MODELMANAGER->AddModel("�����ں���", "Model/Enemy/Elizabeth/", "Elizabeth.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("�����ں���", MODELTYPE_X);

	m_fUIMoveX = 50.0f;
	m_fUIMoveY = 5.0f;

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
	int		nCurrentHP;		//ĳ����(��, �÷��̾�) ���� ��
		int		nMaxHp;			//ĳ����(��, �÷��̾�) �ִ� ��

		int		nCurrentStam;	//ĳ���� ���� ���׹̳�
		int		nMaxStam;		//ĳ���� ��ü ���׹̳�

		int		nAtk;			//�⺻���ݷ�
		float	fPhyRate;		//�������
		float	fMagicRate;		//�������
		float	fCheRate;		//ȭ�а��
		float	fAtkSpeed;		//���ݼӵ� (���ӵ��� * ����)

		int		nDef;			//����
		float	fAgi;			//ȸ�Ƿ�
		float	fHit;			//���߷�
		float	fSpeed;			//�̵��ӵ�
		float	fRange;			//���� �Ÿ�
		float	fScale;			//���� ����
	*/
}

//void Elizabeth::Attack()
//{
//	//�ϴ� ����ó�� -> �÷��̾� ������ �Ǿ��ٸ�
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
//		//sprintf_s(test1, sizeof(test1), "�÷��̾��� ü�� : %d, �����ں����� ü�� : %d", m_nAttackDelay);
//		//
//		//TEXT->Add(test1, 10, 10, 30);
//		D3DXVECTOR3 tempV = *m_pModel->GetPosition() - *m_pCharacter->GetCharacter()->GetPosition();
//		float length = D3DXVec3Length(&tempV);
//
//		int a = 10;
//		//���� ���� ��Ÿ����� �ϸ� �ɵ�
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
//			sprintf_s(test, sizeof(test), "���ݵ����� : %d", m_nAttackDelay);
//
//			TEXT->Add(test, 10, 10, 30);
//
//			if (m_eState == MS_MOVEFORATTACK)
//			{
//				m_eState = MS_ATTACK;
//				ChangeAni();
//			}
//			//�÷��̾� ���ݱ�� ����
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
//		//������ ���̴�.
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

