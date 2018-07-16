#include "../MonsterUseHeader.h"
#include "MiddleBoss.h"


MiddleBoss::MiddleBoss()
{
}


MiddleBoss::~MiddleBoss()
{

}

void MiddleBoss::SetupBoss(Map* map, D3DXVECTOR3 pos)
{
	//모델부터 만들고
	//MODELMANAGER->AddModel("나그로", "Model/Enemy/Lagro/", "Lagro.x", MODELTYPE_X);
	m_pModel = MODELMANAGER->GetModel("나그로", MODELTYPE_X);

	//m_bIsTargeting = true;

	//부모의 셋업을 호출해라
	BossParent::SetupBoss(map, pos);

	//중간 보스의 상태값은 기본 몹이랑 같다.
	m_eState = MS_RUN;
	MonsterParent::ChangeAni();


	//판정 박스 
	ST_SIZEBOX box;
	box.highX = 50.0f;
	box.highY = 180.0f;
	box.highZ = 50.0f;
	box.lowX = -50.0f;
	box.lowY = 10.0f;
	box.lowZ = -50.0f;


	m_pModel->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));

	m_pModel->CreateBound(box);
	m_pModel->SetBoundSphere(m_pModel->GetOrigBoundSphere().center, 100.0f);
}

void MiddleBoss::SetupStat()
{
	m_nMinMoveCount = 0;
	m_nMaxMoveCount = 0;

	ZeroMemory(&m_uMonsterStat, sizeof(m_uMonsterStat));

	CURRENTHP(m_uMonsterStat) = MAXHP(m_uMonsterStat) = 1000;
	ATK(m_uMonsterStat) = 20;
	PHYRATE(m_uMonsterStat) = 1.3f;
	MAGICRATE(m_uMonsterStat) = 0.8f;
	CHERATE(m_uMonsterStat) = 1.1f;
	ATKSPEED(m_uMonsterStat) = 0.75f;

	DEF(m_uMonsterStat) = 5;
	AGI(m_uMonsterStat) = 10.0f;
	HIT(m_uMonsterStat) = 10.0f;
	SPEED(m_uMonsterStat) = 0.08f;
	RANGE(m_uMonsterStat) = 2.2f;
}

void MiddleBoss::DropItemSetup()
{
	m_vItemID.push_back(RARE_OVE);
	m_vItemID.push_back(NORMAL_RECOVERYBOOK);
	m_vItemID.push_back(NORMAL_SIDE);
	m_vItemID.push_back(BABARIAN_RARE_HELMET);
	m_vItemID.push_back(BABARIAN_RARE_ARMOR);
	m_vItemID.push_back(NORMAL_HEALTHPOTION);
	m_vItemID.push_back(NORMAL_RECOVERYBOOK);
}

void MiddleBoss::ChangeAni()
{
	MonsterParent::ChangeAni();
	//switch (m_eState)
	//{
	//case MS_IDLE:
	//	m_pModel->SetAnimation("IDLE");
	//	break;
	//case MS_RUN: case MS_MOVEFORATTACK:
	//	m_pModel->SetAnimation("RUN");
	//	break;
	//case MS_SKILL:
	//	m_pModel->SetAnimation("SKILL");
	//	break;
	//case MS_ATTACK:
	//	m_pModel->SetAnimation("ATTACK");
	//	break;
	//case MS_DIE:
	//	m_pModel->SetAnimation("DIE");
	//	break;
	//default:
	//	break;
	//}
}

void MiddleBoss::Pattern()
{
	switch (m_eState)
	{
	case MS_IDLE:
		break;
	case MS_RUN:
		Move();
		break;
	case MS_SKILL:
		break;
	case MS_ATTACK:
		Attack();
		break;
	case MS_MOVEFORATTACK:
		break;
	case MS_DIE:
	{
				   if (m_pModel->IsAnimationEnd()) m_eState = MS_NONE;
	}
		break;
	case MS_NONE:
		break;
	default:
		break;
	}
}

void MiddleBoss::Move()
{
	//char ttest[111];
	//sprintf_s(ttest, sizeof(ttest), "%f, %f, %f", m_vDir.x, m_vDir.y, m_vDir.z);
	//TEXT->Add(ttest, 10, 10, 30);

	if (m_eState == MS_RUN)
	{
		m_vDir = *CHARACTER->GetPosition() - *m_pModel->GetPosition();
		D3DXVECTOR3 tempPos = *m_pModel->GetPosition() + m_vDir* SPEED(m_uMonsterStat);
		tempPos.y = m_pMap->GetHeight(tempPos.x, tempPos.z);

		float angle = GetAngle(0, 0, m_vDir.x, m_vDir.z);
		angle -= D3DX_PI / 2;

		m_pModel->SetRotation(D3DXVECTOR3(0, angle, 0));
		m_pModel->SetPosition(tempPos);

		//tempPos.y = m_pMap->GetHeight(tempPos.x, tempPos.z);

		//못가는 곳이다.
		//if (tempPos.y < 0)
		//{
		//	MoveReset(true);
		//}
		//else
		//{
		//	m_pModel->SetPosition(tempPos);
		//}

	}

	//m_nCount++;
}

void MiddleBoss::Attack()
{

}

void MiddleBoss::Skill()
{

}
