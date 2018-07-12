#include "../MonsterUseHeader.h"
#include "DistanceMonster.h"

DistanceMonster::DistanceMonster()
{
}


DistanceMonster::~DistanceMonster()
{

}

void DistanceMonster::Setup(Map* map, D3DXVECTOR3 spawnPos, bool isSummon)
{
	//�θ��� �¾��� ȣ���ض�
	MonsterParent::Setup(map, spawnPos, isSummon);


}

void DistanceMonster::SetupStat()
{

}


//���Ÿ� ���� �����Լ�
void DistanceMonster::Attack()
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

		float length = GetDistance(*m_pModel->GetPosition(), *CHARACTER->GetPosition());

		//D3DXVECTOR3 tempV = *m_pModel->GetPosition() - *(*m_ppCharacter)->GetCharacter()->GetPosition();
		//float length = D3DXVec3Length(&tempV);

		int a = 10;
		//���� ���� ��Ÿ����� �ϸ� �ɵ�
		if (length > RANGE(m_uMonsterStat))
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
			D3DXVECTOR3 dir =
				*CHARACTER->GetPosition() - *m_pModel->GetPosition();

			float angle = GetAngle(0, 0, dir.x, dir.z);

			//float x = dir.x - 0;
			//float y = dir.z - 0;
			//
			//float distance = sqrtf(x * x + y * y);
			//
			//float angle = acosf(x / distance);
			//
			//if (dir.z > 0)
			//{
			//	angle = D3DX_PI * 2 - angle;
			//	if (angle >= D3DX_PI * 2) angle -= D3DX_PI * 2;
			//}

			angle -= D3DX_PI / 2;

			m_pModel->SetRotation(D3DXVECTOR3(0, angle, 0));
			//char test[111];
			//sprintf_s(test, sizeof(test), "���ݵ����� : %d", m_nAttackDelay);
			//
			//TEXT->Add(test, 10, 10, 30);

			//��Ÿ��� ���ͼ� ������ ������ ��ġ���
			if (AttackPossible())
			{
				//GetWall
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
					(*m_ppCharacter)->CalculDamage(tatalDamage);
				}

			}
			
		}

	}
}

//���Ÿ� ���� ��ų�Լ�
void DistanceMonster::Skill()
{

}

//���Ÿ� ���� �⺻ �̵��Լ�
void DistanceMonster::Move()
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

void DistanceMonster::SummonMove()
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

void DistanceMonster::DropItemSetup()
{

}

bool DistanceMonster::AttackPossible()
{
	m_vWallVertex = m_pMap->GetWall();
	D3DXVECTOR3 dir;
	dir = *CHARACTER->GetPosition() - *m_pModel->GetPosition();

	float length = D3DXVec3Length(&dir);

	for (int i = 0; i < m_vWallVertex.size(); i += 3)
	{
		float wallLength;
		if (D3DXIntersectTri(&m_vWallVertex[i], &m_vWallVertex[i + 1], &m_vWallVertex[i + 2], m_pModel->GetPosition(), &dir, NULL, NULL, &wallLength))
		{
			if (wallLength < length)
				return false;
		}
	}
	return true;
}