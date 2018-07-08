#include "../MonsterUseHeader.h"
#include "MagicMonster.h"
#include "MagicCircle.h"


MagicMonster::MagicMonster()
{
}


MagicMonster::~MagicMonster()
{

}

void MagicMonster::Setup(Map* map, D3DXVECTOR3 spawnPos)
{
	MonsterParent::Setup(map, spawnPos);

	m_bIsAttack = false;
	m_pMagicCircle = new MagicCircle;
}

void MagicMonster::SetupStat()
{

}


//���� ���� �����Լ�
void MagicMonster::Attack()
{
	if ((*m_ppCharacter))
	{
		if ((*m_ppCharacter)->GetIsDead())
		{
			m_eState = MS_IDLE;
			ChangeAni();
			return;
		}
		//char test1[111];
		//sprintf_s(test1, sizeof(test1), "�÷��̾��� ü�� : %d, �����ں����� ü�� : %d", m_nAttackDelay);
		//
		//TEXT->Add(test1, 10, 10, 30);
		D3DXVECTOR3 tempV = *m_pModel->GetPosition() - *(*m_ppCharacter)->GetCharacter()->GetPosition();
		float length = D3DXVec3Length(&tempV);

		int a = 10;
		//���� ���� ��Ÿ����� �ϸ� �ɵ� && �������̳�
		if (length > RANGE(m_uMonsterStat) && !m_bIsAttack)
		{
			if (m_eState == MS_ATTACK)
			{
				m_eState = MS_MOVEFORATTACK;
				ChangeAni();
			}
			MoveForAttack();
		}

		//��Ÿ����� �����ϸ� �����ؾ� �ϴµ�
		else
		{
			//char test[111];
			//sprintf_s(test, sizeof(test), "���ݵ����� : %d", m_nAttackDelay);
			//
			//TEXT->Add(test, 10, 10, 30);

			//ó���� ���� �� ���� false�̴�.
			if (!m_bIsAttack)
			{
				//���������� �÷��̾� ��ġ�� �������� ������ 5��ŭ
				m_pMagicCircle->SetPosAndRad(*(*m_ppCharacter)->GetCharacter()->GetPosition(), 5);
				m_bIsAttack = true;
				m_eState = MS_ATTACK;
			}


			if (m_eState == MS_MOVEFORATTACK)
			{
				m_eState = MS_ATTACK;
				ChangeAni();
			}
			//�÷��̾� ���ݱ�� ����

			//���� �����̰� ����
			if (m_nAttackDelay >= ATKSPEED(m_uMonsterStat))
			{
				
				//����Ÿ�� ���ݹ�� �����ؾ���

				//�� �浹�� �Ͼ�ٸ� ������ġ�� �ִٴ°Ŵ�.
				//if�� �Ǵ��Ѵ�.
				m_pMagicCircle->PlayerCollision(
					*CHARACTER->GetPosition(),
					CHARACTER->GetBoundSphere().radius);

				float tatalRate = PHYRATE(m_uMonsterStat) + MAGICRATE(m_uMonsterStat) + CHERATE(m_uMonsterStat);
				float tatalDamage = tatalRate * ATK(m_uMonsterStat);
				(*m_ppCharacter)->CalculDamage(tatalDamage);
				m_nAttackDelay = 0;

				m_bIsAttack = false;
			}
			m_nAttackDelay++;
		}

	}
}

//���� ���� ��ų�Լ�
void MagicMonster::Skill()
{

}

//���� ���� �⺻ �̵��Լ�
void MagicMonster::Move()
{
	if (m_nCount == m_nPatternChangeCount/*INPUT->KeyDown('O')*/)
	{
		MoveReset(false, m_nMaxMoveCount, m_nMinMoveCount);
	}
	//char ttest[111];
	//sprintf_s(ttest, sizeof(ttest), "%f, %f, %f", m_vDir.x, m_vDir.y, m_vDir.z);
	//TEXT->Add(ttest, 10, 10, 30);

	if (m_eState == MS_RUN)
	{
		D3DXVECTOR3 tempPos = *m_pModel->GetPosition() + m_vDir* SPEED(m_uMonsterStat);
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
}


void MagicMonster::DropItemSetup()
{

}
