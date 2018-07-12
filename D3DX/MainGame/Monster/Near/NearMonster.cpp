#include "../../../stdafx.h"
#include "NearMonster.h"
#include "../MonsterUseHeader.h"

NearMonster::NearMonster()
{
}


NearMonster::~NearMonster()
{

}

void NearMonster::Setup(Map* map, D3DXVECTOR3 spawnPos, bool isSummon)
{
	//�θ��� �¾��� ȣ���ض�
	MonsterParent::Setup(map, spawnPos, isSummon);
}

void NearMonster::SetupStat()
{

}

void NearMonster::Attack()
{
	if (PCHARACTER)
	{
		//���� Ÿ������ �Ǿ����� �����Լ��� ������ ���״� ī��Ʈ ���� ����
		//��ȯ���� �̷��� ����.
		if (!m_bIsSummon)	m_nTargetingCount++;

		//�÷��̾� ������ �⺻�ൿ����
		if (PCHARACTER->GetIsDead())
		{
			m_eState = MS_IDLE;
			ChangeAni();
			return;
		}

		//�÷��̾���� �Ÿ��� ����ϰ�
		float length = GetDistance(*m_pModel->GetPosition(), *CHARACTER->GetPosition());

		//��Ÿ��� �����
		if (length > RANGE(m_uMonsterStat))
		{
			//�ʵ���� A*�����Ͽ� �̵�
			if (!m_bIsSummon)
			{
				if (m_eState == MS_ATTACK)
				{
					m_eState = MS_MOVEFORATTACK;
					ChangeAni();
				}
				MoveForAttack();
			}
			//��ȯ���� 
			else
			{
				//������Ʈ�� �ִϸ��̼� ��ü �� �����Լ� ������ ���Ͽ� �Լ� ����
				if (m_eState == MS_ATTACK)
				{
					m_eState = MS_RUN;
					ChangeAni();
				}
				return;
			}
		}
		//��Ÿ� �ȿ� ������
		else
		{
			//�÷��̾���� ���⺤�͸� ���ϰ�
			D3DXVECTOR3 dir =
				*CHARACTER->GetPosition() - *m_pModel->GetPosition();

			//������ ���ϰ�
			float angle = GetAngle(0, 0, dir.x, dir.z);


			angle -= D3DX_PI / 2;

			//������ŭ �����̼�
			m_pModel->SetRotation(D3DXVECTOR3(0, angle, 0));

			
			if (m_eState == MS_MOVEFORATTACK)
			{
				m_eState = MS_ATTACK;
				ChangeAni();
			}
			//�÷��̾� ���ݱ�� ����
			m_eState = MS_ATTACK;
			if (m_pModel->IsAnimationPercent(ATKSPEED(m_uMonsterStat)))
			{
				float tatalRate = PHYRATE(m_uMonsterStat) + MAGICRATE(m_uMonsterStat) + CHERATE(m_uMonsterStat);
				float tatalDamage = tatalRate * ATK(m_uMonsterStat);
				PCHARACTER->CalculDamage(tatalDamage);
			}
		}

		//200�� �ɵ��� ���̻��� ������ ���ٸ�
		if (m_nTargetingCount >= 200)
		{
			m_eState = MS_IDLE;
			ChangeAni();
			m_nTargetingCount = 0;
			m_bIsTargeting = false;
		}
	}
}

void NearMonster::Skill()
{

}

void NearMonster::Move()
{

	if (m_nCount == m_nPatternChangeCount)
	{
		MoveReset(false, m_nMaxMoveCount, m_nMinMoveCount);
	}

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

void NearMonster::SummonMove()
{
	if (m_eState == MS_RUN)
	{
		m_vDir = *CHARACTER->GetPosition() - *m_pModel->GetPosition();
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		D3DXVECTOR3 tempPos = *m_pModel->GetPosition() + m_vDir* SPEED(m_uMonsterStat);
		tempPos.y = m_pMap->GetHeight(tempPos.x, tempPos.z);

		float angle = GetAngle(0, 0, m_vDir.x, m_vDir.z);
		angle -= D3DX_PI / 2;

		m_pModel->SetRotation(D3DXVECTOR3(0, angle, 0));
		m_pModel->SetPosition(tempPos);

		float length = GetDistance(*m_pModel->GetPosition(), *CHARACTER->GetPosition());

		if (length < RANGE(m_uMonsterStat))
		{
			m_eState = MS_ATTACK;
			ChangeAni();
		}
	}
}

void NearMonster::DropItemSetup()
{

}