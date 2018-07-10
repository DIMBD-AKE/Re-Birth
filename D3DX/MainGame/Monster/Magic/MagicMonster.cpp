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


//근접 몬스터 공격함수
void MagicMonster::Attack()
{
	if ((PCHARACTER))
	{
		if ((PCHARACTER)->GetIsDead())
		{
			m_eState = MS_IDLE;
			ChangeAni();
			return;
		}
		//char test1[111];
		//sprintf_s(test1, sizeof(test1), "플레이어의 체력 : %d, 엘리자베스의 체력 : %d", m_nAttackDelay);
		//
		//TEXT->Add(test1, 10, 10, 30);
		float length = GetDistance(*m_pModel->GetPosition(), *CHARACTER->GetPosition());

		//D3DXVECTOR3 tempV = *m_pModel->GetPosition() - *CHARACTER->GetPosition();
		//float length = D3DXVec3Length(&tempV);

		int a = 10;
		//공격 가능 사거리까지 하면 될듯 && 공격중이냐
		if (length > RANGE(m_uMonsterStat) && !m_bIsAttack)
		{
			if (m_eState == MS_ATTACK)
			{
				m_eState = MS_MOVEFORATTACK;
				ChangeAni();
			}
			MoveForAttack();
		}

		//사거리까지 도착하면 공격해야 하는데
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
			//sprintf_s(test, sizeof(test), "공격딜레이 : %d", m_nAttackDelay);
			//
			//TEXT->Add(test, 10, 10, 30);

			//처음에 오면 이 값은 false이다.
			if (!m_bIsAttack)
			{
				//공격장판은 플레이어 위치를 중점으로 반지름 5만큼
				m_pMagicCircle->SetPosAndRad(*CHARACTER->GetPosition(), 3);
				m_bIsAttack = true;
				m_eState = MS_ATTACK;
				ChangeAni();
			}


			if (m_eState == MS_MOVEFORATTACK)
			{
				m_eState = MS_ATTACK;
				ChangeAni();
			}
			//플레이어 공격기능 설정

			//공격 딜레이가 오면
			if (m_pModel->IsAnimationPercent(ATKSPEED(m_uMonsterStat)))
			{

				//마법타입 공격방식 수정해야함

				//구 충돌이 일어났다면 폭발위치에 있다는거다.
				//if로 판단한다.
				if (m_pMagicCircle->PlayerCollision(
					*CHARACTER->GetPosition(),
					CHARACTER->GetBoundSphere().radius))
				{

					float tatalRate = PHYRATE(m_uMonsterStat) + MAGICRATE(m_uMonsterStat) + CHERATE(m_uMonsterStat);
					float tatalDamage = tatalRate * ATK(m_uMonsterStat);
					PCHARACTER->CalculDamage(tatalDamage);
				}
					m_nAttackDelay = 0;
				
				m_bIsAttack = false;
			}
			m_nAttackDelay++;
		}

	}
}

//근접 몬스터 스킬함수
void MagicMonster::Skill()
{

}

//근접 몬스터 기본 이동함수
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


void MagicMonster::DropItemSetup()
{

}
