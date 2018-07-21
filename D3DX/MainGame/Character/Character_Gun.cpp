#include "../../stdafx.h"
#include "Character_Gun.h"
#include "../Map.h"
#include "Inventory.h"
#include "../Status.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../DamageUI.h"


Character_Gun::Character_Gun()
{
}


Character_Gun::~Character_Gun()
{
}


void Character_Gun::Init(CHRTYPE type, CHARSELECT order, DropManager* Drop)
{
	m_eChrType = CHRTYPE_GUN;
	if (order == CHAR_ONE)
	{
		//총남캐
		m_pCharacter = MODELMANAGER->GetModel("메그너스", MODELTYPE_X);
		m_eNumTarget = NUM_SINGLE;
		m_eCharSelect = CHAR_ONE;
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 1.7f;
		m_Status->chr.fCheRate = 70.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 25.0f;
		m_Status->chr.fPhyRate = 25.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 20;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 50;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 50;
		m_Status->chr.fRange = 20.0f;
		m_Status->chr.fScale = 3.2f;
		CharacterParant::Init(type, order, Drop);


		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스테이터스"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 550, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("원거리_공격"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(33, 598, 0));


		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("메그너스_사진"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));
	
	}
	else if (order == CHAR_TWO)
	{
		//활여캐
		m_pCharacter = MODELMANAGER->GetModel("스카디", MODELTYPE_X);
		m_eNumTarget = NUM_SINGLE;
		m_eCharSelect = CHAR_TWO;
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 2.2f;
		m_Status->chr.fCheRate = 70.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 25.0f;
		m_Status->chr.fPhyRate = 25.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 22;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 100;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 100;
		m_Status->chr.fRange = 25.0f;
		m_Status->chr.fScale = 3.2f;
		CharacterParant::Init(type, order, Drop);

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스테이터스"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 550, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("원거리_공격"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(33, 598, 0));

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("스카디_사진"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));

	
	}
}

void Character_Gun::Update()
{
	if (m_pCharacter)
	{
		Controller();
	
		KeyControl();
		Move();


		m_pInventory->Update();
		m_pCharacter->World();
		m_pUIobj->Update();
		m_pChrStat->Update();
		m_pInheritateIco->Update();
		Effect();

		PlayerProgressBar();
		//CountAppearDamage();
		m_pDamage->Update(*m_pCharacter->GetPosition());
	}
}

void Character_Gun::Render()
{
	if (m_pCharacter)
	{
		m_pCharacter->Render();
		//CharacterParant::Render();
		m_pInventory->Render();

		//포트레이트 
	
		m_pDamage->Render();
		//AppearDamage();


		CharacterParant::Render();
		m_pUIobj->Render();
		m_pInheritateIco->Render();
		m_pHPBar->Render();
		m_pStaminaBar->Render();
	}
}

void Character_Gun::KeyControl()
{
	//앞으로 달리기
	if (INPUT->KeyDown('W'))
	{
		SOUND->Play("FootStep4");
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_HIT)
		{
			m_eCondition = CHAR_RUN_FRONT;
		
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('W'))
	{
		SOUND->Stop("FootStep4");
		if (m_eCondition == CHAR_RUN_FRONT)
		{
			m_eCondition = CHAR_IDLE;
		
			ChangeAnimation();
		}
	}
	//뒤로 달리기
	if (INPUT->KeyDown('S'))
	{
		SOUND->Play("FootStep4");
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_HIT)
		{
			m_eCondition = CHAR_RUN_BACK;
			
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('S'))
	{
		SOUND->Stop("FootStep4");
		if (m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_IDLE;
			
			ChangeAnimation();
		}
	}
	//앞으로 대쉬
	if (INPUT->KeyDown('Q'))
	{
		SOUND->Play("FootStep3");
		SOUND->Stop("FootStep4");
		if (m_eCondition == CHAR_RUN_FRONT)
		{
			m_eCondition = CHAR_DASH_FRONT;
		
			m_bIsDash = true;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('Q'))
	{
		SOUND->Stop("FootStep3");
		if (m_eCondition == CHAR_DASH_FRONT)
		{
			m_eCondition = CHAR_RUN_FRONT;
		
			m_bIsDash = false;
			ChangeAnimation();
		}
	}
	//뒤로 대쉬
	if (INPUT->KeyDown('E'))
	{
		SOUND->Play("FootStep3");
		SOUND->Stop("FootStep4");
		if (m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_DASH_BACK;
			
			m_bIsDash = true;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('E'))
	{
		SOUND->Stop("FootStep3");
		if (m_eCondition == CHAR_DASH_BACK)
		{
			m_eCondition = CHAR_RUN_BACK;
			
			m_bIsDash = false;
			ChangeAnimation();
		}
	}

	//일반공격
	if (INPUT->KeyDown(VK_SPACE))
	{
		if (m_eCharSelect == CHAR_ONE)
		{
			SOUND->Play("GunAttack");
			SOUND->Play("메그너스_공격");
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			SOUND->Play("스카디_공격");
			SOUND->Play("BowAttack");
		}
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_ATTACK;
		
			m_bIsAttack = true;
			SetTarget();
			m_nDamageCount = 0;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp(VK_SPACE))
	{
		m_bIsAttack = false;
	}


	//스킬공격
	if (INPUT->KeyDown('K'))
	{
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_SKILL;
			
			m_bIsSkill = true;
			ChangeAnimation();
		}
	}


	//고유스킬
	if (INPUT->KeyDown('T'))
	{
		if (m_eCharSelect == CHAR_ONE)
		{
			SOUND->Play("메그너스_고유_총");
			SOUND->Play("메그너스_고유");
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			SOUND->Play("스카디_고유");
			SOUND->Play("BowAttack");
		}
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_INHERENT;
			MultiAttack();
			ChangeAnimation();
		}
	}
	if (INPUT->KeyUp('T'))
	{
		m_nDamageCount = 0;
	}

	
	//애니메이션 한바퀴 돌고나서 상태제어
	if (m_pCharacter->IsAnimationEnd())
	{
		switch (m_eCondition)
		{
		case CHAR_SKILL:
			m_eCondition = CHAR_IDLE;
			break;
		case CHAR_ATTACK:
			m_eCondition = CHAR_IDLE;
			break;
		case CHAR_HIT:
			m_eCondition = CHAR_IDLE;
			break;
		case CHAR_INHERENT:
			m_eCondition = CHAR_IDLE;
			break;
		case CHAR_DIE:
			m_eCondition = CHAR_NONE;
			m_bIsDead = false;
			break;
		}
		ChangeAnimation();
	}

	//피격 도중에 공격 가능하게 만들기
	if (m_eCondition == CHAR_HIT)
	{
		if (m_eCharSelect == CHAR_ONE)
		{
			if (!SOUND->IsPlaySound("메그너스_피격")) SOUND->Play("메그너스_피격");
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			if (!SOUND->IsPlaySound("스카디_피격")) SOUND->Play("스카디_피격");
		}

		if (INPUT->KeyDown(VK_SPACE))
		{
			m_eCondition = CHAR_ATTACK;
			m_bIsAttack = true;
			//Attack();
			ChangeAnimation();
		}
	}

	//대쉬일때 애니메이션 스피드 제어
	if (m_eCondition == CHAR_DASH_FRONT || m_eCondition == CHAR_DASH_BACK)
	{
		m_pCharacter->SetAnimationSpeed(5.0f);
	}

	//공격상태일때 애니메이션 스피드 제어
	if (m_eCondition == CHAR_ATTACK)
	{
		m_pCharacter->SetAnimationSpeed(1.0f * (m_Status->chr.fAtkSpeed + m_pInventory->GetEquipStat().chr.fAtkSpeed));
	}

	if (m_eCondition == CHAR_ATTACK)
	{
		Attack();
	}

	if (m_eCondition == CHAR_IDLE)
	{
		if (SOUND->IsPlaySound("FootStep4")) SOUND->Stop("FootStep4");
		if (SOUND->IsPlaySound("FootStep3")) SOUND->Stop("FootStep3");
	}
}

void Character_Gun::Attack()
{
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
	if (m_fElpTime < m_fPrevTime + m_fEffectInterval) return;

	m_fPrevTime = m_fElpTime;

	m_nDamageCount++;
	
		if (m_eCharSelect == CHAR_ONE)
		{
			if (m_nIndex < 0) return;
			if (m_nDamageCount <= 3)
			{
				D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				ST_EFFECT tempEffect;
				ZeroMemory(&tempEffect, sizeof(tempEffect));

				tempEffect.time = FRand(0.1, 0.4);
				tempEffect.isRY = true;
				tempEffect.isRX = true;
				tempEffect.height = 3.0f;
				tempEffect.SetAlpha(255, 255, 0);
				tempEffect.SetScale(2, 2, 2);
				tempEffect.tex = TEXTUREMANAGER->AddTexture("Gun", "Texture/Effect/gun.png");
				EffectObject* tempEFOBJ;
				tempEFOBJ = new EffectObject;

				D3DXVECTOR3 TempDir;
				TempDir = *m_pCharacter->GetPosition() - *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				D3DXVec3Normalize(&TempDir, &TempDir);

				float Length = D3DXVec3Length(&(MonPos - pos));

				D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				testSkillpos.y += 1.0f;
				testSkillpos.x += FRand(-0.5, 0.5);
				testSkillpos.z += FRand(-0.5, 0.5);
				testSkillpos += TempDir * (Length * 0.3f);
				tempEFOBJ->Init(tempEffect, testSkillpos);

				m_vecEffect.push_back(tempEFOBJ);
				m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
			}
		}
		else if (m_eCharSelect == CHAR_TWO)
		{
			if (m_nIndex < 0) return;
			if (m_nDamageCount <= 3)
			{
				D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				ST_EFFECT tempEffect;
				ZeroMemory(&tempEffect, sizeof(tempEffect));

				tempEffect.time = FRand(0.1, 0.4);
				tempEffect.isRY = true;
				tempEffect.isRX = true;
				tempEffect.height = 3.0f;
				tempEffect.SetAlpha(255, 255, 0);
				tempEffect.SetScale(2, 2, 2);
				tempEffect.tex = TEXTUREMANAGER->AddTexture("Gun", "Texture/Effect/gun.png");
				EffectObject* tempEFOBJ;
				tempEFOBJ = new EffectObject;

				D3DXVECTOR3 TempDir;
				TempDir = *m_pCharacter->GetPosition() - *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				D3DXVec3Normalize(&TempDir, &TempDir);

				float Length = D3DXVec3Length(&(MonPos - pos));

				D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				testSkillpos.y += 1.0f;
				testSkillpos.x += FRand(-0.5, 0.5);
				testSkillpos.z += FRand(-0.5, 0.5);
				testSkillpos += TempDir * (Length * 0.3f);
				tempEFOBJ->Init(tempEffect, testSkillpos);

				m_vecEffect.push_back(tempEFOBJ);
				m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
			}
		}

}

void Character_Gun::MultiAttack()
{
//	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();														//플레이어 포지션 받고 
//	D3DXVECTOR3 rot = *m_pCharacter->GetRotation();														//플레이어 각도 받고 
//
//	m_vecTarget.clear();
//	m_nIndex = -1;
////	m_nIndex2 = -1;
////	m_nIndex3 = -1;
//	int subMinIndex = -1;
//
//	int MINIndex2 = -1;
//	float MinDistance = 0.0f;
//	float radius;
//	D3DXVECTOR3 mosPos;
//	float distance;
//	float subDistance = 0.0f;
//	float subDistance2 = 0.0f;
//
//
//	for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
//	{
//		if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;								//리젠할때는 건드리지 않고 
//
//		float radius1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;		//몬스터의 바운드 스페어의 반지름 받고 
//		mosPos = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//몬스터 포지션 받고 
//		float distance1 = D3DXVec3Length(&(mosPos - pos));
//
//		if (distance1 - radius1 > m_Status->chr.fRange) continue;
//		distance = distance1;
//		subDistance = distance;
//		subDistance2 = distance;
//
//		m_nIndex = i;
////		m_nIndex2 = i;
////		m_nIndex3 = i;
//		break;
//	}
//	if (m_nIndex != -1)//만약 기준점이 된 몬스터가 구해졌으면 
//	{
//		for (int i = m_nIndex + 1; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
//		{
//			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;	//리젠할때는 건드리지 않고 
//			float radius2 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
//			mosPos = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//몬스터 포지션 받고 
//			float distance2 = D3DXVec3Length(&(mosPos - pos));
//			if (distance2 - radius2 > m_Status->chr.fRange) continue;
//			if (distance >= distance2)
//			{
//				distance = distance2;
//				m_nIndex = i;
//			}
//		}
//		m_vecTarget.push_back(m_nIndex);
//		//두번째 가까운녀석도 추가
//		for (int i = m_nIndex2 + 1; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
//		{
//			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;	//리젠할때는 건드리지 않고 
//			if (i == m_nIndex) continue;//먼저 검출한 최소거리를 가진 몬스터면 재끼고 
//			float radius3 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
//			mosPos = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//몬스터 포지션 받고 
//			float distance3 = D3DXVec3Length(&(mosPos - pos));
//			if (distance3 - radius3 > m_Status->chr.fRange) continue;
//			if (subDistance >= distance3)
//			{
//				subDistance = distance3;
//				m_nIndex2 = i;
//			}
//		}
//		m_vecTarget.push_back(m_nIndex2);
//
//		//세번째 가까운 녀석도 추가
//		for (int i = m_nIndex3 + 1; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
//		{
//			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;	//리젠할때는 건드리지 않고 
//			if (i == m_nIndex) continue;//먼저 검출한 최소거리를 가진 몬스터면 재끼고 
//			if (i == m_nIndex2) continue;//먼저 검출한 최소거리를 가진 몬스터면 재끼고 
//			float radius4 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
//			mosPos = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//몬스터 포지션 받고 
//			float distance4 = D3DXVec3Length(&(mosPos - pos));
//			if (distance4 - radius4 > m_Status->chr.fRange) continue;
//			if (subDistance2 >= distance4)
//			{
//				subDistance2 = distance4;
//				m_nIndex3 = i;
//			}
//		}
//		m_vecTarget.push_back(m_nIndex3);
//	}
//
//	if (m_nIndex < 0) return;
//	D3DXVECTOR3 front;
//	D3DXMATRIX matY;
//	D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
//	D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
//	D3DXVECTOR3 v0 = front;
//	//대상방향
//	D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
//	//D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
//	D3DXVECTOR3 v1 = MonPos - pos;
//	D3DXVec3Normalize(&v0, &v1);
//	float dot = D3DXVec3Dot(&v0, &v1) / D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
//	if (dot >= cos(m_Status->chr.fScale / 2))
//	{
//		//if (m_nIndex == -1) return;
//		if (m_fElpTime < m_fPrevTime + m_fEffectInterval) return;
//
//		m_fPrevTime = m_fElpTime;
//
//		m_nDamageCount++;
//		if (m_eCharSelect == CHAR_ONE)
//		{
//			if (m_nDamageCount <= 3)
//			{
//				ST_EFFECT tempEffect;
//				ZeroMemory(&tempEffect, sizeof(tempEffect));
//
//				tempEffect.time = FRand(0.1, 0.4);
//				tempEffect.isRY = true;
//				tempEffect.isRX = true;
//				tempEffect.height = 3.0f;
//				tempEffect.SetAlpha(255, 255, 0);
//				tempEffect.SetScale(2, 2, 2);
//				tempEffect.tex = TEXTUREMANAGER->AddTexture("Gun", "Texture/Effect/gun.png");
//				EffectObject* tempEFOBJ;
//				tempEFOBJ = new EffectObject;
//
//				D3DXVECTOR3 TempDir;
//				TempDir = *m_pCharacter->GetPosition() - *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
//				D3DXVec3Normalize(&TempDir, &TempDir);
//
//				D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
//				testSkillpos.y += 1.0f;
//				testSkillpos.x += FRand(-0.5, 0.5);
//				testSkillpos.z += FRand(-0.5, 0.5);
//				testSkillpos += TempDir * 4.0f;
//				tempEFOBJ->Init(tempEffect, testSkillpos);
//
//				m_vecEffect.push_back(tempEFOBJ);
//
//				for (int i = 0; i < m_vecTarget.size(); i++)
//				{
//					if (m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->GetIsResPawn())return;
//					m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->CalculDamage(100);
//				}
//			}
//		}
//		else if (m_eCharSelect == CHAR_TWO)
//		{
//			if (m_nDamageCount <= 3)
//			{
//				ST_EFFECT tempEffect;
//				ZeroMemory(&tempEffect, sizeof(tempEffect));
//
//				tempEffect.time = FRand(0.1, 0.4);
//				tempEffect.isRY = true;
//				tempEffect.isRX = true;
//				tempEffect.height = 3.0f;
//				tempEffect.SetAlpha(255, 255, 0);
//				tempEffect.SetScale(2, 2, 2);
//				tempEffect.tex = TEXTUREMANAGER->AddTexture("Gun", "Texture/Effect/gun.png");
//				EffectObject* tempEFOBJ;
//				tempEFOBJ = new EffectObject;
//
//				D3DXVECTOR3 TempDir;
//				TempDir = *m_pCharacter->GetPosition() - *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
//				D3DXVec3Normalize(&TempDir, &TempDir);
//
//				D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
//				testSkillpos.y += 1.0f;
//				testSkillpos.x += FRand(-0.5, 0.5);
//				testSkillpos.z += FRand(-0.5, 0.5);
//				testSkillpos += TempDir * 4.0f;
//				tempEFOBJ->Init(tempEffect, testSkillpos);
//
//				m_vecEffect.push_back(tempEFOBJ);
//
//				for (int i = 0; i < m_vecTarget.size(); i++)
//				{
//					if (m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->GetIsResPawn())return;
//					m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->CalculDamage(100);
//				}
//			}
//
//		}
//	}
}


