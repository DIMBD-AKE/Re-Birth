#include "../MonsterUseHeader.h"
#include "../MonsterManager.h"
#include "FinalBoss.h"
#include "../Magic/MagicCircle.h"

//90, 80, ... 10�۰� �ɶ����� ��ȯ
static int summonCount = 9;

FinalBoss::FinalBoss()
{

}


FinalBoss::~FinalBoss()
{

}

void FinalBoss::SetupBoss(Map* map, D3DXVECTOR3 pos)
{
	//�� �ٲ����
	//MODELMANAGER->AddModel("����", "Model/Enemy/Boss/", "BOSS.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("����", MODELTYPE_X);

	BossParent::SetupBoss(map, pos);

	m_eBossState = BS_ENTER;
	ChangeAni();
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

	m_pSkill = SKILL->GetSkill("Boss Skill1");
	

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
	SPEED(m_pMonsterStat) = 0.08f;
	RANGE(m_pMonsterStat) = 8.0f;
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
	
	m_stSkill.buffStatus.chr.nCurrentHP = 100; //���� �� ���ȷ� �Ǖ��� ���θ޸�;
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
		m_pModel->SetAnimation("SKILL2");
		break;
	case BS_SKILL2:
		m_pModel->SetAnimation("SKILL1");
		break;
	case BS_CASTING:
		m_pModel->SetAnimation("SKILL2_CASTING");
		break;
	case BS_DIE:
		m_pModel->SetAnimation("DIE");
		break;
	case BS_NONE:
		break;
	default:
		break;
	}

	if (m_eBossState == BS_CASTING)
	{
		m_pModel->SetAnimationSpeed(0.5f);
	}
	else m_pModel->SetAnimationSpeed(1.0f);
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

		//���� ��ŵ�ϰ� �нú� �ߵ�
		return;
	}

	float length = GetDistance(*m_pModel->GetPosition(), *CHARACTER->GetPosition());

	//���� ����߿� �÷��̾ ����� ���ݸ�� �� ���������ض�
	if (length > RANGE(m_pMonsterStat) && !m_bIsAttack)
	{
		if (m_eBossState == BS_ATTACK)
		{
			m_eBossState = BS_RUN;
			ChangeAni();
		}
		return;
		
	}

	//��Ÿ� �ȿ� ���Դµ� ���� ������ �����ҷ��� �Ѵٸ�
	if (!m_bIsAttack)
	{
		//���� �� ������ ���ϰ�		
		D3DXVECTOR3 dir =
			*CHARACTER->GetPosition() - *m_pModel->GetPosition();

		float angle = GetAngle(0, 0, dir.x, dir.z);

		angle -= D3DX_PI / 2;

		//���� �����̼� �ض�
		m_pModel->SetRotation(D3DXVECTOR3(0, angle, 0));

		//ù ������ ���� ���������� �ٲ������μ� ������ ȸ���� ���´�.
		m_bIsAttack = true;

		//�÷��̾� ��ġ �������� �� ����
		m_pMagicCircle->SetPosAndRad(*CHARACTER->GetPosition(), 3);
	}
		
		//�÷��̾� ���ݱ�� ����
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

		//�̵� ���߰� �����ȯ
		return;
	}
	if (m_eBossState == BS_RUN)
	{
		m_vDir = *CHARACTER->GetPosition() - *m_pModel->GetPosition();
		D3DXVECTOR3 tempPos = *m_pModel->GetPosition() + m_vDir* SPEED(m_pMonsterStat);
		tempPos.y = m_pMap->GetHeight(tempPos.x, tempPos.z);

		float angle = GetAngle(0, 0, m_vDir.x, m_vDir.z);
		angle -= D3DX_PI / 2;

		m_pModel->SetRotation(D3DXVECTOR3(0, angle, 0));
		m_pModel->SetPosition(tempPos);

		float length = GetDistance(*m_pModel->GetPosition(), *CHARACTER->GetPosition());

		if (length < RANGE(m_pMonsterStat) - 4)
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
	//���� HP ����
	float HPRatio = (float)CURRENTHP(m_pMonsterStat) / MAXHP(m_pMonsterStat);
	float summonRatio = (10 * summonCount / 100.0f);
	//���� �� ������ ��ȯī��Ʈ �������� �������ٸ�
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
		m_eBossState = BS_IDLE;
		ChangeAni();
	}
}

void FinalBoss::Skill2()
{

}

void FinalBoss::Casting()
{
	if (m_pModel->IsAnimationPercent(0.5f))
	{
		m_eBossState = BS_SKILL1;
		ChangeAni();
	//	m_pModel->SetAnimationPosition(0.5f);
	}
}