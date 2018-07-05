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

		//���� ��ȯ
		
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

