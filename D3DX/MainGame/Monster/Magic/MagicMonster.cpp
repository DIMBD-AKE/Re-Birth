#include "../MonsterUseHeader.h"
#include "MagicMonster.h"
#include "MagicCircle.h"


MagicMonster::MagicMonster()
{
}


MagicMonster::~MagicMonster()
{
	SAFE_DELETE(m_pMagicCircle);
}

void MagicMonster::Setup(Map* map, D3DXVECTOR3 spawnPos, bool isSummon)
{
	MonsterParent::Setup(map, spawnPos, isSummon);

	m_bIsAttack = false;
	m_pMagicCircle = new MagicCircle;
	m_pMagicCircle->Setup();
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

		if (!m_bIsSummon)	m_nTargetingCount++;

		float length = GetDistance(*m_pModel->GetPosition(), *CHARACTER->GetPosition());
		
		int a = 10;

	

		//공격 가능 사거리까지 하면 될듯 && 공격중이냐
		if (length > RANGE(m_pMonsterStat) && !m_bIsAttack)
		{
			if (AbleSkill())
			{
				m_bIsAttack = false;
				m_eState = MS_SKILL;
				ChangeAni();
				return;
			}
			//피드몹은 A*적용
			if (!m_bIsSummon)
			{
				if (m_eState == MS_ATTACK)
				{
					m_eState = MS_MOVEFORATTACK;
					ChangeAni();
				}
				MoveForAttack();
			}
			//소환몹은
			else
			{
				//스태이트와 애니메이션 교체 후 무브함수 실행을 위하여 함수 종료
				if (m_eState == MS_ATTACK)
				{
					m_eState = MS_RUN;
					ChangeAni();
				}
				return;
			}
		}

		//사거리까지 도착하면 공격해야 하는데
		else
		{
			ChangeRot();

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
			if (m_pModel->IsAnimationPercent(ATKSPEED(m_pMonsterStat)))
			{

				//마법타입 공격방식 수정해야함

				//구 충돌이 일어났다면 폭발위치에 있다는거다.
				//if로 판단한다.
				if (m_pMagicCircle->PlayerCollision(
					*CHARACTER->GetPosition(),
					CHARACTER->GetBoundSphere().radius))
				{

					float tatalRate = PHYRATE(m_pMonsterStat) + MAGICRATE(m_pMonsterStat) + CHERATE(m_pMonsterStat);
					float tatalDamage = tatalRate * ATK(m_pMonsterStat);
					PCHARACTER->CalculDamage(tatalDamage);
				}
				
				m_bIsAttack = false;
			}
		}

		if (m_nTargetingCount >= 200)
		{
			m_eState = MS_IDLE;
			ChangeAni();
			m_nTargetingCount = 0;
			m_bIsTargeting = false;
		}

	}
}

//근접 몬스터 스킬함수
void MagicMonster::SkillUse()
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
		D3DXVECTOR3 tempPos = *m_pModel->GetPosition() + m_vDir* SPEED(m_pMonsterStat);
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

void MagicMonster::SummonMove()
{
	if (m_eState == MS_RUN)
	{
		m_vDir = *CHARACTER->GetPosition() - *m_pModel->GetPosition();
		D3DXVec3Normalize(&m_vDir, &m_vDir);

		D3DXVECTOR3 tempPos = *m_pModel->GetPosition() + m_vDir* SPEED(m_pMonsterStat);
		tempPos.y = m_pMap->GetHeight(tempPos.x, tempPos.z);

		ChangeRot();

		m_pModel->SetPosition(tempPos);

		float length = GetDistance(*m_pModel->GetPosition(), *CHARACTER->GetPosition());

		if (length < RANGE(m_pMonsterStat))
		{
			m_eState = MS_ATTACK;
			ChangeAni();
		}
	}
}

void MagicMonster::DropItemSetup()
{

}

 void MagicMonster::Update()
{
	 MonsterParent::Update();

	 if (m_bIsAttack)
	 {
		 if (m_pMagicCircle)		m_pMagicCircle->Update();
	 }
}

void MagicMonster::Render()
{
	MonsterParent::Render();

	if (m_bIsAttack)
	{
		if(m_pMagicCircle)		m_pMagicCircle->Render();
	}
}