#include "../../../stdafx.h"
#include "NearMonster.h"
#include "../MonsterUseHeader.h"

NearMonster::NearMonster()
{
}


NearMonster::~NearMonster()
{

}

void NearMonster::Setup(Map* map, D3DXVECTOR3 spawnPos)
{
	//부모의 셋업을 호출해라
	MonsterParent::Setup(map, spawnPos);
}

void NearMonster::SetupStat()
{

}

void NearMonster::Attack()
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
		//sprintf_s(test1, sizeof(test1), "플레이어의 체력 : %d, 엘리자베스의 체력 : %d", m_nAttackDelay);
		//
		//TEXT->Add(test1, 10, 10, 30);
		D3DXVECTOR3 tempV = *m_pModel->GetPosition() - *(*m_ppCharacter)->GetCharacter()->GetPosition();
		float length = D3DXVec3Length(&tempV);

		int a = 10;
		//공격 가능 사거리까지 하면 될듯
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
			char test[111];
			sprintf_s(test, sizeof(test), "공격딜레이 : %d", m_nAttackDelay);

			TEXT->Add(test, 10, 10, 30);

			if (m_eState == MS_MOVEFORATTACK)
			{
				m_eState = MS_ATTACK;
				ChangeAni();
			}
			//플레이어 공격기능 설정
			m_eState = MS_ATTACK;
			if (m_nAttackDelay >= ATKSPEED(m_uMonsterStat))
			{
				float tatalRate = PHYRATE(m_uMonsterStat) + MAGICRATE(m_uMonsterStat) + CHERATE(m_uMonsterStat);
				float tatalDamage = tatalRate * ATK(m_uMonsterStat);
				(*m_ppCharacter)->CalculDamage(tatalDamage);
				m_nAttackDelay = 0;
			}
			m_nAttackDelay++;
		}

	}
}

void NearMonster::Skill()
{

}

void NearMonster::Move()
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

		//못가는 곳이다.
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

void NearMonster::DropItemSetup()
{

}