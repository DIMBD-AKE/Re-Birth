#include "../MonsterUseHeader.h"
#include "../MonsterManager.h"
#include "FinalBoss.h"
#include "../Magic/MagicCircle.h"

//90, 80, ... 10퍼가 될때마다 소환
static int summonCount = 4;

FinalBoss::FinalBoss()
{

}


FinalBoss::~FinalBoss()
{

}

void FinalBoss::SetupBoss(Map* map, D3DXVECTOR3 pos)
{
	//모델 바꿔야함
	//MODELMANAGER->AddModel("보스", "Model/Enemy/Boss/", "BOSS.x", MODELTYPE_X);
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


	m_pModel->SetScale(D3DXVECTOR3(0.02f, 0.02f, 0.02f));

	m_pModel->CreateBound(box);
	m_pModel->SetBoundSphere(m_pModel->GetOrigBoundSphere().center, 100.0f);

	//피흡스킬
	m_pSkill = SKILL->GetSkill("Boss Skill1");
	//3타스킬
	m_pSkill2 = SKILL->GetSkill("Boss Skill2");

	SetupSkill2();

	m_bUsingSkill = m_bUsingSkill2 = false;
	m_bIsTargeting = true;

}

void FinalBoss::SetupStat()
{
	m_nMinMoveCount = 0;
	m_nMaxMoveCount = 0;

	ZeroMemory(m_pMonsterStat, sizeof(STATUS));

	CURRENTHP(m_pMonsterStat) = 1400;
		MAXHP(m_pMonsterStat) = 1500;
	ATK(m_pMonsterStat) = 20;
	PHYRATE(m_pMonsterStat) = 1.3f;
	MAGICRATE(m_pMonsterStat) = 0.8f;
	CHERATE(m_pMonsterStat) = 1.1f;
	ATKSPEED(m_pMonsterStat) = 0.75f;

	DEF(m_pMonsterStat) = 5;
	AGI(m_pMonsterStat) = 10.0f;
	HIT(m_pMonsterStat) = 10.0f;
	SPEED(m_pMonsterStat) = 0.9f;
	RANGE(m_pMonsterStat) = 6.0f;
}

void FinalBoss::SetupSkill()
{
	ZeroMemory(&m_stSkill, sizeof(m_stSkill));

	m_stSkill.nMaxTarget = 1;
	m_stSkill.fMinLength = 0;
	m_stSkill.fMaxLength = 10;
	m_stSkill.fAngle = 360;
	
	m_stSkill.fDamage = 100; //v
	m_stSkill.nDamageCount = 5;
	m_stSkill.fDamageInterval =
		((m_pModel->GetAnimationPeriod("SKILL2") * 3) / 4) / m_stSkill.nDamageCount;
	m_stSkill.fDamageDelay = 0;
	
	m_stSkill.fBuffTime = -1;//<0;
	
	
	
	//m_stSkill.fYOffset ;
	//m_stSkill.isAutoRot;
	//m_stSkill.fParticleTime;
	//m_stSkill.fParticleSpeed;
	m_stSkill.fEffectTime = m_pModel->GetAnimationPeriod("SKILL2") / 4;
	
	m_stSkill.buffStatus.chr.nCurrentHP = 100; //증가 될 스탯량 피뺴고 제로메모리;

	m_fSkillCoolTimeCount = 0;
	m_nSkillCooltime = 200;
}

void FinalBoss::SetupSkill2()
{
	ZeroMemory(&m_stSkill2, sizeof(m_stSkill2));

	m_stSkill2.nMaxTarget = 1;
	m_stSkill2.fMinLength = 0;
	m_stSkill2.fMaxLength = 6;
	m_stSkill2.fAngle = 360;

	m_stSkill2.fDamage = 100; //v
	m_stSkill2.nDamageCount = 1;
	m_stSkill2.fDamageInterval = 0;
	m_stSkill2.fDamageDelay = 0;

	m_stSkill2.fBuffTime = -1;//<0;

	m_fSkillCoolTimeCount2 = 0;
	m_nSkillCooltime2 = 70;
	


	//m_stSkill.fYOffset ;
	//m_stSkill.isAutoRot;
	//m_stSkill.fParticleTime;
	//m_stSkill.fParticleSpeed;
	m_stSkill.fEffectTime = 0;

	//	m_stSkill.buffStatus.chr.nCurrentHP = 100; //증가 될 스탯량 피뺴고 제로메모리;
}



//void FinalBoss::ChangeAni()
//{
//
//}

void FinalBoss::Pattern()
{
	if (AbleSkill() && !m_bUsingSkill2 && m_eBossState != BS_NONE && m_eBossState != BS_DIE)
	{
		m_eBossState = BS_CASTING;
		ChangeAni();
	}

	else if (AbleSkill2() && m_eBossState != BS_NONE && m_eBossState != BS_DIE)
	{
		m_eBossState = BS_SKILL2;
		ChangeAni();
	}

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
		SkillUse();
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

		//공격 스킵하고 패시브 발동
		return;
	}

	float length = GetDistance(*m_pModel->GetPosition(), *CHARACTER->GetPosition());

	//공격 모션중에 플레이어가 벗어나도 공격모션 및 판정진행해라
	if (length > RANGE(m_pMonsterStat) && !m_bIsAttack)
	{
		if (m_eBossState == BS_ATTACK)
		{
			m_eBossState = BS_RUN;
			ChangeAni();
		}
		return;
		
	}

	//사거리 안에 들어왔는데 이제 공격을 시작할려고 한다면
	if (!m_bIsAttack)
	{
		//방향 및 각도를 구하고		
		ChangeRot();

		//첫 판정후 이제 공격중으로 바꿔줌으로서 보스의 회전을 막는다.
		m_bIsAttack = true;

		//플레이어 위치 기준으로 구 생성
		m_pMagicCircle->SetPosAndRad(*CHARACTER->GetPosition(), 3);
	}
		
		//플레이어 공격기능 설정
		if (m_pModel->IsAnimationPercent(ATKSPEED(m_pMonsterStat)))
		{
			if (m_pMagicCircle->PlayerCollision(
				*CHARACTER->GetPosition(),
				CHARACTER->GetBoundSphere().radius))
			{

				float tatalRate = PHYRATE(m_pMonsterStat) + MAGICRATE(m_pMonsterStat) + CHERATE(m_pMonsterStat);
				float tatalDamage = tatalRate * ATK(m_pMonsterStat);
				PCHARACTER->CalculDamage(tatalDamage);
			}

			
			//float tatalRate = PHYRATE(m_pMonsterStat) + MAGICRATE(m_pMonsterStat) + CHERATE(m_pMonsterStat);
			//float tatalDamage = tatalRate * ATK(m_pMonsterStat);
			//PCHARACTER->CalculDamage(tatalDamage);
		}
		if (m_pModel->IsAnimationEnd())
		{
			m_bIsAttack = false;
		}
}

void FinalBoss::Move()
{
	if (AbleSummon())
	{
		m_eBossState = BS_PASSIVE;
		ChangeAni();
		Passive();

		//이동 멈추고 잡몹소환
		return;
	}
	if (m_eBossState == BS_RUN)
	{
		m_vDir = *CHARACTER->GetPosition() - *m_pModel->GetPosition();
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		D3DXVECTOR3 tempPos = *m_pModel->GetPosition() + m_vDir* SPEED(m_pMonsterStat);
		tempPos.y = m_pMap->GetHeight(tempPos.x, tempPos.z);

		ChangeRot();

		m_pModel->SetPosition(tempPos);

		float length = GetDistance(*m_pModel->GetPosition(), *CHARACTER->GetPosition());

		if (length < RANGE(m_pMonsterStat) )
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
	float HPRatio = (float)CURRENTHP(m_pMonsterStat) / MAXHP(m_pMonsterStat);
	float summonRatio = (20 * summonCount / 100.0f);
	//현재 피 비율이 소환카운트 비율보다 적어졌다면
	if (HPRatio <= summonRatio)
	{
		summonCount--;
		return true;
	}

	return false;
}
void FinalBoss::SkillUse()
{
	m_pSkill->Trigger();

	if (m_pModel->IsAnimationEnd())
	{
		m_bUsingSkill = false;
		m_fSkillCoolTimeCount = 0;
		m_eBossState = BS_RUN;
		ChangeAni();
	}
}

void FinalBoss::Skill2()
{
	vector<MonsterParent*> tt;


	if (m_pModel->IsAnimationPercent(0.3))
	{
		
		m_pSkill->Trigger();
	}

	if (m_pModel->IsAnimationPercent(0.6))
	{
		SkillPrepare2();
		m_pSkill->Trigger();
	}

	if (m_pModel->IsAnimationPercent(0.8))
	{
		SkillPrepare2();
		m_pSkill->Trigger();
	}

	if (m_pModel->IsAnimationEnd())
	{
		m_bUsingSkill2 = false;
		
		m_fSkillCoolTimeCount2 = 0;
		m_eBossState = BS_RUN;
		ChangeAni();
	}
}

//void FinalBoss::Casting()
//{
//	if (m_pModel->IsAnimationEnd())
//	//if (m_pModel->IsAnimationPercent(0.5f))
//	{
//		m_eBossState = BS_SKILL1;
//		ChangeAni();
//	//	m_pModel->SetAnimationPosition(0.5f);
//	}
//}