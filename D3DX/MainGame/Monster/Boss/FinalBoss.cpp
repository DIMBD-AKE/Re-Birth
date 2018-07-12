#include "../MonsterUseHeader.h"
#include "../MonsterManager.h"
#include "FinalBoss.h"

//90, 80, ... 10퍼가 될때마다 소환
static int summonCount = 9;

FinalBoss::FinalBoss()
{
}


FinalBoss::~FinalBoss()
{
}

void FinalBoss::SetupBoss(Map* map, D3DXVECTOR3 pos)
{
	//모델 바꿔야함
	MODELMANAGER->AddModel("보스", "Model/Enemy/Boss/", "Boss.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("보스", MODELTYPE_X);

	BossParent::SetupBoss(map, pos);

	m_eBossState = BS_ENTER;
	ChangeAni();
	//판정 박스 
	ST_SIZEBOX box;
	box.highX = 50.0f;
	box.highY = 180.0f;
	box.highZ = 50.0f;
	box.lowX = -50.0f;
	box.lowY = 10.0f;
	box.lowZ = -50.0f;


	m_pModel->SetScale(D3DXVECTOR3(0.03f, 0.03f, 0.03f));

	m_pModel->CreateBound(box);
	m_pModel->SetBoundSphere(m_pModel->GetOrigBoundSphere().center, 100.0f);


}

void FinalBoss::SetupStat()
{
	m_nMinMoveCount = 0;
	m_nMaxMoveCount = 0;

	ZeroMemory(&m_uMonsterStat, sizeof(m_uMonsterStat));

	CURRENTHP(m_uMonsterStat) = MAXHP(m_uMonsterStat) = 1500;
	ATK(m_uMonsterStat) = 20;
	PHYRATE(m_uMonsterStat) = 1.3f;
	MAGICRATE(m_uMonsterStat) = 0.8f;
	CHERATE(m_uMonsterStat) = 1.1f;
	ATKSPEED(m_uMonsterStat) = 0.75f;

	DEF(m_uMonsterStat) = 5;
	AGI(m_uMonsterStat) = 10.0f;
	HIT(m_uMonsterStat) = 10.0f;
	SPEED(m_uMonsterStat) = 0.08f;
	RANGE(m_uMonsterStat) = 15.0f;
}

void FinalBoss::DropItemSetup()
{
	
}

void FinalBoss::ChangeAni()
{
	switch (m_eBossState)
	{
	case BS_ENTER:
		m_pModel->SetAnimation("ENTER");
		break;
	case BS_IDLE:
		m_pModel->SetAnimation("IDLE");
		break;
	case BS_RUN:
		m_pModel->SetAnimation("RUN");
		break;
	case BS_PASSIVE:
		m_pModel->SetAnimation("PASSIVE");
		break;
	case BS_ATTACK:
		m_pModel->SetAnimation("ATTACK");
		break;
	case BS_SKILL1:
		m_pModel->SetAnimation("SKILL1");
		break;
	case BS_SKILL2:
		m_pModel->SetAnimation("SKILL2");
		break;
	case BS_CASTING:
		m_pModel->SetAnimation("SKILL_CASTING");
		break;
	case BS_DIE:
		m_pModel->SetAnimation("DIE");
		break;
	case BS_NONE:
		break;
	default:
		break;
	}
}

void FinalBoss::Pattern()
{
	switch (m_eBossState)
	{
	case BS_ENTER:
	{
		if (m_pModel->IsAnimationEnd())
		{
			m_eBossState = BS_RUN;
			ChangeAni();
		}
	}
		break;
	case BS_RUN:
	{
		Move();
	}
		break;
	case BS_PASSIVE:
		if (m_pModel->IsAnimationEnd())
		{
			m_eBossState = BS_RUN;
			ChangeAni();
		}
		break;
	case BS_ATTACK:
		Attack();
		break;
	case BS_SKILL1:
		Skill1();
		break;
	case BS_SKILL2:
		Skill2();
		break;
	case BS_CASTING:
		Casting();
		break;
	case BS_DIE:
	{
				   if (m_pModel->IsAnimationEnd()) m_eBossState = BS_NONE;
	}
	default:
		break;
	}
}

void FinalBoss::Attack()
{
	if (PCHARACTER->GetIsDead())
	{
		m_eState = MS_IDLE;
		ChangeAni();
		return;
	}

	if (AbleSummon())
	{
		m_eBossState = BS_PASSIVE;
		ChangeAni();
		Passive();
	}

	float length = GetDistance(*m_pModel->GetPosition(), *CHARACTER->GetPosition());

	if (length > RANGE(m_uMonsterStat))
	{
			if (m_eBossState == BS_ATTACK)
			{
				m_eBossState = BS_RUN;
				ChangeAni();
			}
			return;
		
	}


		D3DXVECTOR3 dir =
			*CHARACTER->GetPosition() - *m_pModel->GetPosition();

		float angle = GetAngle(0, 0, dir.x, dir.z);

		angle -= D3DX_PI / 2;

		m_pModel->SetRotation(D3DXVECTOR3(0, angle, 0));
		//플레이어 공격기능 설정
		if (m_pModel->IsAnimationPercent(ATKSPEED(m_uMonsterStat)))
		{
			float tatalRate = PHYRATE(m_uMonsterStat) + MAGICRATE(m_uMonsterStat) + CHERATE(m_uMonsterStat);
			float tatalDamage = tatalRate * ATK(m_uMonsterStat);
			PCHARACTER->CalculDamage(tatalDamage);
		}
}

void FinalBoss::Move()
{
	if (AbleSummon())
	{
		m_eBossState = BS_PASSIVE;
		ChangeAni();
		Passive();
	}
	if (m_eBossState == BS_RUN)
	{
		m_vDir = *CHARACTER->GetPosition() - *m_pModel->GetPosition();
		D3DXVECTOR3 tempPos = *m_pModel->GetPosition() + m_vDir* SPEED(m_uMonsterStat);
		tempPos.y = m_pMap->GetHeight(tempPos.x, tempPos.z);

		float angle = GetAngle(0, 0, m_vDir.x, m_vDir.z);
		angle -= D3DX_PI / 2;

		m_pModel->SetRotation(D3DXVECTOR3(0, angle, 0));
		m_pModel->SetPosition(tempPos);

		float length = GetDistance(*m_pModel->GetPosition(), *CHARACTER->GetPosition());

		if (length < RANGE(m_uMonsterStat) - 4)
		{
			m_eBossState = BS_ATTACK;
			ChangeAni();
		}
	}
}

void FinalBoss::Passive()
{
	
	m_pMM->MakeMonster();

	
}

bool FinalBoss::AbleSummon()
{
	if (summonCount <= 0) return false;
	//현재 HP 비율
	float HPRatio = (float)CURRENTHP(m_uMonsterStat) / MAXHP(m_uMonsterStat);
	float summonRatio = (10 * summonCount / 100.0f);
	//현재 피 비율이 소환카운트 비율보다 적어졌다면
	if (HPRatio <= summonRatio)
	{
		summonCount--;
		return true;
	}

	return false;
}
void FinalBoss::Skill1()
{

}

void FinalBoss::Skill2()
{

}

void FinalBoss::Casting()
{
	
}