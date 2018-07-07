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
	//�𵨺��� �����
	MODELMANAGER->AddModel("�ƽý�", "Model/Enemy/Assis/", "Assis.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("�ƽý�", MODELTYPE_X);

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

void Assis::SetupStat()
{

}


//���� ���� �����Լ�
void Assis::Attack()
{
	//�ϴ� ����ó�� -> �÷��̾� ������ �Ǿ��ٸ�

	if (m_pCharacter)
	{
		if (m_pCharacter->GetIsDead())
		{
			m_eState = MS_IDLE;
			ChangeAni();
			return;
		}

		D3DXVECTOR3 tempV = *m_pModel->GetPosition() - *m_pCharacter->GetCharacter()->GetPosition();
		float length = D3DXVec3Length(&tempV);

		int a = 10;
		//���� ���� ��Ÿ����� �ϸ� �ɵ�
		if (length > 1)
		{
			if (m_eState == MS_ATTACK)
			{
				m_eState = MS_MOVEFORATTACK;
				ChangeAni();
			}
			MoveForAttack();
		}
		else
		{
			if (m_eState == MS_MOVEFORATTACK)
			{
				m_eState = MS_ATTACK;
				ChangeAni();
			}
			//�÷��̾� ���ݱ�� ����
			m_eState = MS_ATTACK;

		}
	}
}

//���� ���� ��ų�Լ�
void Assis::Skill()
{

}

//���� ���� �⺻ �̵��Լ�
void Assis::Move()
{
	if (m_nCount == m_nPatternChangeCount/*INPUT->KeyDown('O')*/)
	{
		MoveReset(false, 500, 100);
	}
	//char ttest[111];
	//sprintf_s(ttest, sizeof(ttest), "%f, %f, %f", m_vDir.x, m_vDir.y, m_vDir.z);
	//TEXT->Add(ttest, 10, 10, 30);

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



	//if (INPUT->KeyDown('L'))
	//{
	//	m_bIsRespawn = true;
	//	m_eState = MS_DIE;
	//	ChangeAni();
	//	SetCurrentHP(1000);
	//}
}


void Assis::DropItemSetup()
{

}
