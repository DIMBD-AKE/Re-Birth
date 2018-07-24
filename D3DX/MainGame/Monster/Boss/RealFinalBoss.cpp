#include "../MonsterUseHeader.h"
#include "../Magic/MagicCircle.h"
#include "RealFinalboss.h"

RealFinalboss::RealFinalboss()
{
}

RealFinalboss::~RealFinalboss()
{
	for (int i = 0; i < STONENUM; ++i)
	{
		SAFE_DELETE(m_vMagicCircle[i]);
		SAFE_DELETE(m_vEffectObject[i]);
	}
	SAFE_DELETE(m_pSkill);
	
}

void RealFinalboss::SetupBoss(Map* map, D3DXVECTOR3 pos)
{
	//모델 바꿔야함
	m_pModel = MODELMANAGER->GetModel("최종보스", MODELTYPE_X);

	BossParent::SetupBoss(map, pos);

	//m_eBossState = BS_ENTER;
	m_eBossState = BS_SKILL1;

	ChangeAni();
	//판정 박스 
	ST_SIZEBOX box;
	box.highX = 200.0f;
	box.highY = 1000.0f;
	box.highZ = 200.0f;
	box.lowX = -200.0f;
	box.lowY = 10.0f;
	box.lowZ = -200.0f;


	m_pModel->SetScale(D3DXVECTOR3(0.025f, 0.025f, 0.025f));

	m_pModel->CreateBound(box);
	m_pModel->SetBoundSphere(m_pModel->GetOrigBoundSphere().center - D3DXVECTOR3(0,300,0), 300.0f);

	//피흡 바꿔야함
	m_pSkill = SKILL->GetSkill("RealBossPassive");
	
	m_pSkill2 = NULL;

	//2스킬 셋업
	SetupSkill2();

	m_bSkill2Use = m_bUsingSkill = false;
	m_bIsTargeting = true;

	m_vMagicCircle.resize(STONENUM);
	m_vEffectObject.resize(STONENUM);
	for (int i = 0; i < STONENUM; ++i)
	{
		m_vMagicCircle[i] = new MagicCircle;
		m_vMagicCircle[i]->Setup();

		m_vEffectObject[i] = new EffectObject;
	}

	m_pModel->SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));


	ZeroMemory(&m_stEffect, sizeof(ST_EFFECT));
	m_stEffect.dir = D3DXVECTOR3(0,-1,0);
	m_stEffect.SetAlpha(255, 255, 255);
	m_stEffect.isSphere = true;
	m_stEffect.SetSpeed(0.9f, 0, 1.5f);
	m_stEffect.SetScale(1, 1, 1);
	m_stEffect.height = 3;
	m_stEffect.time = 3.5;
	//effect.SetMotorSpeed(1, 1, 1);
	//effect.mot = D3DXVECTOR3(0, 0, 1);
	m_stEffect.tex = TEXTUREMANAGER->GetTexture("돌");
	
	BoolInit();

	CAMERA->SetCamOffset(D3DXVECTOR3(0, 15, 40));
	//CAMERA->SetTarget(m_pModel->GetPosition(), m_pModel->GetRotation());
	//CAMERA->Cinematic(D3DXVECTOR2(85.0f, 60.0f), D3DXVECTOR2(-10.0f, 10.0f), 40, 1,10);
}

void RealFinalboss::Update()
{
	if (CAMERA->IsActionEnd())
		CAMERA->SetTarget(CHARACTER->GetPosition(), CHARACTER->GetRotation());
	if (m_bSkill2Use)
	{
		for (int i = 0; i < STONENUM; ++i)
		{
			m_vMagicCircle[i]->Update();
			if (m_vEffectObject[i])
			m_vEffectObject[i]->Update();
		}
	}
		
	BossParent::Update();

}

void RealFinalboss::Render()
{
	Debug();

	if (m_bSkill2Use)
	{
		for (int i = 0; i < STONENUM; ++i)
		{
			m_vMagicCircle[i]->Render();
			if(m_vEffectObject[i])
			m_vEffectObject[i]->Render();
		}
	}

	if (m_pModel && (m_eState != MS_NONE && m_eBossState != BS_NONE))
	{
		if (IsEnter() || m_eBossState == BS_SKILL1)
			m_pModel->Render();
		else
			m_pModel->DummyRender();

		if (m_bIsTargeting) m_pHPBar->Render();
	}

	if (m_pHPBar) m_pHPBar->Render();

	if (m_pSkill) m_pSkill->Render();
}

void RealFinalboss::SetupStat()
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
	RANGE(m_pMonsterStat) = 35.0f;
}

void RealFinalboss::SetupSkill()
{
	
}

//패시브 설정
void RealFinalboss::SetupSkill2()
{
	ZeroMemory(&m_stSkill, sizeof(ST_SKILL));
	m_stSkill.fDamage = 0;
	m_stSkill.fDamageDelay = 0;
	m_stSkill.fDamageInterval = 0;
	m_stSkill.fMaxLength = 0;
	m_stSkill.fAngle = 0;
	m_stSkill.nMaxTarget = 5;
	m_stSkill.nDamageCount = 0;
	m_stSkill.isAutoRot = true;
	m_stSkill.fYOffset = 1;
	m_stSkill.fBuffTime = 60;
	m_stSkill.fParticleTime = m_pModel->GetAnimationPeriod("PASSIVE");
	m_stSkill.fParticleSpeed = 0;
	m_stSkill.fEffectTime = 3;

	

	m_fSkillCoolTimeCount = 0;
	m_nSkillCooltime = 120;
}

//void RealFinalboss::ChangeAni()
//{
//	switch (m_eBossState)
//	{
//	case BS_ENTER:
//		m_pModel->SetAnimation("ENTER");
//		break;
//	case BS_IDLE:
//		m_pModel->SetAnimation("IDLE");
//		break;
//	case BS_RUN:
//		m_pModel->SetAnimation("RUN");
//		break;
//	case BS_PASSIVE:
//		m_pModel->SetAnimation("PASSIVE");
//		break;
//	case BS_ATTACK:
//		m_pModel->SetAnimation("ATTACK");
//		break;
//	case BS_SKILL1:
//		m_pModel->SetAnimation("SKILL2");
//		break;
//	case BS_SKILL2:
//		m_pModel->SetAnimation("SKILL1");
//		break;
//	case BS_CASTING:
//		m_pModel->SetAnimation("SKILL2_CASTING");
//		break;
//	case BS_DIE:
//		m_pModel->SetAnimation("DIE");
//		break;
//	case BS_NONE:
//		break;
//	default:
//		break;
//	}
//
//	if (m_eBossState == BS_CASTING)
//	{
//		m_pModel->SetAnimationSpeed(0.5f);
//	}
//	else m_pModel->SetAnimationSpeed(1.0f);
//}

void RealFinalboss::Pattern()
{
	HandMatInit();

	//패시브가 발동 가능한 상태면
	bool plesawf = AblePassive();
	if (plesawf)
	{

		BuffDecide();
		m_bUsingSkill = true;
		SkillPrepare();
		m_eBossState = BS_PASSIVE;
		ChangeAni();
	}
	//char temp[222];
	//sprintf_s(temp, sizeof(temp), "%f",
	//	GetDistance(*m_pModel->GetPosition(), *CHARACTER->GetPosition()));
	//TEXT->Add(temp, 100, 100, 20);

	//if (AbleSkill() && !m_bSkill2Use)
	//{
	//	m_eBossState = BS_CASTING;
	//	ChangeAni();
	//}
	//
	//else if (AbleSkill2())
	//{
	//	m_eBossState = BS_SKILL2;
	//	ChangeAni();
	//}

	switch (m_eBossState)
	{
	case BS_ENTER: case BS_ENTER1: case BS_ENTER2: case BS_ENTER3:
	{
		EnterAni();
	}
	break;

	case BS_PASSIVE:
		Passive();
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

void RealFinalboss::Attack()
{
	if (PCHARACTER->GetIsDead())
	{
		m_eState = MS_IDLE;
		ChangeAni();
		return;
	}

	MakeSphere();


	//if (AbleSummon())
	//{
	//	m_eBossState = BS_PASSIVE;
	//	ChangeAni();
	//	Passive();
	//
	//	//공격 스킵하고 패시브 발동
	//	return;
	//}

	float length = GetDistance(*m_pModel->GetPosition(), *CHARACTER->GetPosition());

	//공격 모션중에 플레이어가 벗어나도 공격모션 및 판정진행해라
	if (length > RANGE(m_pMonsterStat))
	{
		if (!m_bIsAttack)
		{
			m_eBossState = BS_SKILL2;
			ChangeAni();
			
			return;
		}
	
	}

	m_bSkill2Use = false;

	//사거리 안에 들어왔는데 이제 공격을 시작할려고 한다면
	if (!m_bIsAttack)
	{
		//방향 및 각도를 구하고		
		//ChangeRot();

		D3DXVECTOR3 dir =
			*CHARACTER->GetPosition() - *m_pModel->GetPosition();

		//각도를 구하고
		float angle = GetAngle(0, 0, dir.x, dir.z);


		//angle -= D3DX_PI / 2;

		//각도만큼 로테이션
		m_pModel->SetRotation(D3DXVECTOR3(0, angle, 0));

		//첫 판정후 이제 공격중으로 바꿔줌으로서 보스의 회전을 막는다.
		m_bIsAttack = true;

	}
	
		if (HandCollision())
		{
			if (m_pModel->IsAnimationPercent(0.35)
				|| m_pModel->IsAnimationPercent(0.7))
				BoolInit();
			CAMERA->Shake(0.1f, 0.3f);
			float tatalRate = PHYRATE(m_pMonsterStat) + MAGICRATE(m_pMonsterStat) + CHERATE(m_pMonsterStat);
			float tatalDamage = tatalRate * ATK(m_pMonsterStat);

			PCHARACTER->CalculDamage(tatalDamage);
		}
	
	//플레이어 공격기능 설정
	//if (m_pModel->IsAnimationPercent(ATKSPEED(m_pMonsterStat)))
	//{
	//	if (m_pMagicCircle->PlayerCollision(
	//		*CHARACTER->GetPosition(),
	//		CHARACTER->GetBoundSphere().radius))
	//	{
	//
	//		
	//		PCHARACTER->CalculDamage(tatalDamage);
	//	}
	//
	//
	//	//float tatalRate = PHYRATE(m_pMonsterStat) + MAGICRATE(m_pMonsterStat) + CHERATE(m_pMonsterStat);
	//	//float tatalDamage = tatalRate * ATK(m_pMonsterStat);
	//	//PCHARACTER->CalculDamage(tatalDamage);
	
	if (m_pModel->IsAnimationEnd())
	{
		BoolInit();
		m_bIsAttack = false;
	}
}

void RealFinalboss::Move()
{
	
}

void RealFinalboss::Passive()
{
	m_pSkill->Trigger();

	if (m_pModel->IsAnimationEnd())
	{
		m_bUsingSkill = false;
		m_fSkillCoolTimeCount = 0;
		m_eBossState = BS_ATTACK;
		ChangeAni();
	}
	
}

//bool RealFinalboss::AbleSummon()
//{
//	//if (summonCount <= 0) return false;
//	////현재 HP 비율
//	//float HPRatio = (float)CURRENTHP(m_pMonsterStat) / MAXHP(m_pMonsterStat);
//	//float summonRatio = (10 * summonCount / 100.0f);
//	////현재 피 비율이 소환카운트 비율보다 적어졌다면
//	//if (HPRatio <= summonRatio)
//	//{
//	//	summonCount--;
//	//	return true;
//	//}
//	//
//	//return false;
//}
void RealFinalboss::SkillUse()
{
	//m_pSkill->Trigger();
	//
	//if (m_pModel->IsAnimationEnd())
	//{
	//	m_bUsingSkill = false;
	//	m_fSkillCoolTimeCount = 0;
	//	m_eBossState = BS_RUN;
	//	ChangeAni();
	//}
}

void RealFinalboss::Skill2()
{
	ST_SPHERE target = CHARACTER->GetBoundSphere();

	for (int i = 0; i < m_vEffectObject.size(); ++i)
	{
		ST_SPHERE stone;
			if (m_vEffectObject[i])
			{
				stone = m_vEffectObject[i]->GetBoundSphere();

				if (IntersectSphere(target, stone))
				{
					CAMERA->Shake(0.5f, 0.5f);
					PCHARACTER->CalculDamage(100);
					SAFE_DELETE(m_vEffectObject[i]);
				}
			}
	}
	if (m_pModel->IsAnimationPercent(0.65f))
	{
		DropTheStone();
		//돌을 떨구자
	}

	if (m_pModel->IsAnimationEnd())
	{
		m_eBossState = BS_ATTACK;
		ChangeAni();
	}
	//vector<MonsterParent*> tt;
	//
	//
	//if (m_pModel->IsAnimationPercent(0.3))
	//{
	//
	//	m_pSkill->Trigger();
	//}
	//
	//if (m_pModel->IsAnimationPercent(0.6))
	//{
	//	SkillPrepare2();
	//	m_pSkill->Trigger();
	//}
	//
	//if (m_pModel->IsAnimationPercent(0.8))
	//{
	//	SkillPrepare2();
	//	m_pSkill->Trigger();
	//}
	//
	//if (m_pModel->IsAnimationEnd())
	//{
	//	m_bSkill2Use = false;
	//
	//	m_fSkillCoolTimeCount2 = 0;
	//	m_eBossState = BS_RUN;
	//	ChangeAni();
	//}
}

//void RealFinalboss::Casting()
//{
//	if (m_pModel->IsAnimationEnd())
//		//if (m_pModel->IsAnimationPercent(0.5f))
//	{
//		m_eBossState = BS_SKILL1;
//		ChangeAni();
//		//	m_pModel->SetAnimationPosition(0.5f);
//	}
//}

void RealFinalboss::EnterAni()
{
	switch (m_eBossState)
	{
	case BS_ENTER:
		if (m_pModel->IsAnimationEnd())
		//if (m_pModel->IsAnimationPercent(98))
		{
			m_eBossState = BS_ENTER1;
			ChangeAni();
		}
		break;
	case BS_ENTER1:	//case BS_ENTER2:	
		//if (m_pModel->IsAnimationEnd())
		if (m_pModel->IsAnimationPercent(0.45f)
			|| m_pModel->IsAnimationPercent(0.47f))
		{
			m_eBossState = BOSS_STATE(m_eBossState+1);
			ChangeAni();
			
		}
		break;
	case BS_ENTER2:	//case BS_ENTER2:	
					//if (m_pModel->IsAnimationEnd())
		if (m_pModel->IsAnimationPercent(0.8f))
		{
			m_eBossState = BOSS_STATE(m_eBossState + 1);
			CAMERA->Shake(0.5f, 3.5f);
			ChangeAni();
		}
		break;
	case BS_ENTER3:
		if (m_pModel->IsAnimationEnd())
		//if (m_pModel->IsAnimationPercent(98))
		{
			m_eBossState = BS_ATTACK;
			ChangeAni();
		}
		break;
	default:
		break;
	}
}

void RealFinalboss::HandMatInit()
{
	m_stHandMat.LeftHand1 = m_pModel->GetBoneMatrix("Bip001-L-Hand");
	m_stHandMat.LeftHand2 = m_pModel->GetBoneMatrix("Bip002-L-Hand");
	m_stHandMat.RightHand1 = m_pModel->GetBoneMatrix("Bip001-R-Hand");
	m_stHandMat.RightHand2 = m_pModel->GetBoneMatrix("Bip002-R-Hand");
}

void RealFinalboss::DropTheStone()
{
	m_bSkill2Use = true;
	//for (int i = 0; i < STONENUM; ++i)
	//{
	//	SAFE_DELETE(m_vMagicCircle[i]);
	//}
	//
	//m_vMagicCircle.clear();
	/*
	
	static float FRand(float low, float high)
	{
		return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
	}
	*/
	for (int i = 0; i < STONENUM; ++i)
	{
		
		D3DXVECTOR3 rndPos = *CHARACTER->GetPosition();
		rndPos.x += FRand(RNDMIN,RNDMAX);
		rndPos.z += FRand(RNDMIN,RNDMAX);

		/* 	void Init(ST_EFFECT info, D3DXVECTOR3 pos);*/
		
		m_vMagicCircle[i]->SetParticlePos(rndPos);
		m_vMagicCircle[i]->GetParticle()->TimeReset();

		SAFE_DELETE(m_vEffectObject[i]);
		m_vEffectObject[i] = new EffectObject;
		m_vEffectObject[i]->Init(m_stEffect, rndPos + D3DXVECTOR3(0, FRand(7.0f, 27.0f), 0));
	}
}

void RealFinalboss::MakeSphere()
{
	D3DXVECTOR3 temp(0, 0, 0);
	D3DXVec3TransformCoord(&temp, &temp, m_stHandMat.LeftHand1);
	m_stHandSphere.LeftHand1.center = temp;

	temp = D3DXVECTOR3(0, 0, 0);
	D3DXVec3TransformCoord(&temp, &temp, m_stHandMat.LeftHand2);
	m_stHandSphere.LeftHand2.center = temp;

	temp = D3DXVECTOR3(0, 0, 0);
	D3DXVec3TransformCoord(&temp, &temp, m_stHandMat.RightHand1);
	m_stHandSphere.RightHand1.center = temp;

	temp = D3DXVECTOR3(0, 0, 0);
	D3DXVec3TransformCoord(&temp, &temp, m_stHandMat.RightHand2);
	m_stHandSphere.RightHand2.center = temp;

	m_stHandSphere.LeftHand1.radius =
		m_stHandSphere.LeftHand2.radius =
		m_stHandSphere.RightHand1.radius =
		m_stHandSphere.RightHand2.radius = 8;
}

void RealFinalboss::Debug()
{
	DWORD prevFillMode;
	DEVICE->GetRenderState(D3DRS_FILLMODE, &prevFillMode);
	DEVICE->SetTexture(0, NULL);
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// BoundSphere
	LPD3DXMESH mesh;
	D3DXMATRIX matT;

	float radius = m_stHandSphere.LeftHand1.radius;
	if (radius < 0) radius = 0;
	D3DXCreateSphere(DEVICE, radius, 8, 8, &mesh, NULL);
	D3DXVECTOR3 pos = m_stHandSphere.LeftHand1.center;
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);
	DEVICE->SetTransform(D3DTS_WORLD, &matT);
	mesh->DrawSubset(0);
	SAFE_RELEASE(mesh);


	DEVICE->SetRenderState(D3DRS_FILLMODE, prevFillMode);
}

bool RealFinalboss::HandCollision()
{
	if (IntersectSphere(m_stHandSphere.LeftHand1, CHARACTER->GetBoundSphere())
		&& !m_stHandSphere.IsOnceAttack1)
	{
		m_stHandSphere.IsOnceAttack1 = true;
		return true;
	}

	if (IntersectSphere(m_stHandSphere.LeftHand2, CHARACTER->GetBoundSphere())
		&& !m_stHandSphere.IsOnceAttack2)
	{
		m_stHandSphere.IsOnceAttack2 = true;
		return true;
	}

	if (IntersectSphere(m_stHandSphere.RightHand1, CHARACTER->GetBoundSphere())
		&& !m_stHandSphere.IsOnceAttack3)
	{
		m_stHandSphere.IsOnceAttack3 = true;
		return true;
	}

	if (IntersectSphere(m_stHandSphere.RightHand2, CHARACTER->GetBoundSphere())
		&& !m_stHandSphere.IsOnceAttack4)
	{
		m_stHandSphere.IsOnceAttack4 = true;
		return true;
	}

	return false;
}

bool RealFinalboss::AblePassive()
{
	/*
	if (m_fSkillCoolTimeCount >= m_nSkillCooltime
	&& leng <= m_stSkill.fMaxLength
	&& m_bIsTargeting
	&& !m_bIsRespawn
	&& !m_bUsingSkill
	&& m_pModel->IsAnimationEnd())
	*/
	//패시브 발동 조건
	if (m_pModel->IsAnimationEnd()
		&& m_fSkillCoolTimeCount >= m_nSkillCooltime
		&& !m_bIsDead
		&& !m_bUsingSkill)
	{

		return true;
	}

	return false;
}

void RealFinalboss::BuffDecide()
{
	ZeroMemory(&m_stSkill.buffStatus, sizeof(STATUS));

	int rndNum = rand() % 3;

	switch (rndNum)
	{
	case 0:
		m_stSkill.buffStatus.chr.nAtk = ATK(m_pMonsterStat);
		break;

	case 1:
		m_stSkill.buffStatus.chr.nDef = DEF(m_pMonsterStat);
		break;

	case 2:
		m_stSkill.buffStatus.chr.fHit = HIT(m_pMonsterStat);
		break;
	default:
		break;
	}
	
}
