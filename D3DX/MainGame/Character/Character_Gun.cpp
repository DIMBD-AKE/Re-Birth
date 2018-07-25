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
	m_pMagicBullet = NULL;
}


Character_Gun::~Character_Gun()
{
	SAFE_DELETE(m_pMagicBullet);
	for (auto p : m_vecWindStorm)
		SAFE_DELETE(p);
}


void Character_Gun::Init(CHRTYPE type, CHARSELECT order)
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
		m_Status->chr.nCurrentStam = 100;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 100;
		m_Status->chr.fRange = 14.0f;
		m_Status->chr.fScale = 3.2f;
		CharacterParant::Init(type, order);


		m_pSkillBar->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스킬창"));
		m_pSkillBar->SetPosition(D3DXVECTOR3(588, 695, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("원거리_공격"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(609, 733, 0));

		m_pInheritateIco2->SetTexture(TEXTUREMANAGER->GetTexture("원거리_이동"));
		m_pInheritateIco2->SetPosition(D3DXVECTOR3(722, 733, 0));

		m_pInheritateIco3->SetTexture(TEXTUREMANAGER->GetTexture("원거리_레이저"));
		m_pInheritateIco3->SetPosition(D3DXVECTOR3(839, 733, 0));

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스테이터스"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 668, 0));



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
		m_Status->chr.fRange = 14.0f;
		m_Status->chr.fScale = 3.2f;
		CharacterParant::Init(type, order);

		m_pSkillBar->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스킬창"));
		m_pSkillBar->SetPosition(D3DXVECTOR3(588, 695, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("원거리_공격"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(609, 733, 0));

		m_pInheritateIco2->SetTexture(TEXTUREMANAGER->GetTexture("원거리_이동"));
		m_pInheritateIco2->SetPosition(D3DXVECTOR3(722, 733, 0));

		m_pInheritateIco3->SetTexture(TEXTUREMANAGER->GetTexture("원거리_레이저"));
		m_pInheritateIco3->SetPosition(D3DXVECTOR3(839, 733, 0));

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스테이터스"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 668, 0));

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("스카디_사진"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));

	
	}

	m_bshoot = false;
	m_pAimLine->SetTexture(TEXTUREMANAGER->GetTexture("조준선"));

}

void Character_Gun::Update()
{
	if (m_pCharacter)
	{
		Controller();
	
		if (!m_bIsStun)KeyControl();
		Move();
		setCameraView();
		GunClick();
		m_pInventory->Update();
		m_pCharacter->World();
		m_pUIobj->Update();
		m_pChrStat->Update();
		m_pInheritateIco->Update();
		m_pInheritateIco2->Update();
		m_pInheritateIco3->Update();
		m_pSkillBar->Update();
		Effect();

		PlayerProgressBar();
		//CountAppearDamage();
//		m_pDamage->Update(*m_pCharacter->GetPosition());
		CharacterParant::Update();

		if (m_bIsGunView)
		{
			GunClick();
			GunShot();
		}
	}

	MagicBulletUpdate();
	WindStormUpdate();
}

void Character_Gun::Render()
{
	if (m_pCharacter)
	{
		m_pCharacter->Render();
		//CharacterParant::Render();
		m_pInventory->Render();

		//포트레이트 
	
	//	m_pDamage->Render();
		//AppearDamage();


		CharacterParant::Render();
		
		m_pUIobj->Render();
		m_pSkillBar->Render();
		m_pInheritateIco->Render();
		m_pInheritateIco2->Render();
		m_pInheritateIco3->Render();
		m_pHPBar->Render();
		m_pStaminaBar->Render();

	}

	if (m_pMagicBullet)
		m_pMagicBullet->Render();

	for (auto p : m_vecWindStorm)
		p->Render();
}

void Character_Gun::KeyControl()
{
	//앞으로 달리기
	if (INPUT->KeyDown('W'))
	{
		SOUND->Play("FootStep4", g_fVolume);
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
		SOUND->Play("FootStep4", g_fVolume);
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
		SOUND->Play("FootStep3", g_fVolume);
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
		SOUND->Play("FootStep3", g_fVolume);
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
			SOUND->Play("GunAttack", g_fVolume);
			SOUND->Play("메그너스_공격", g_fVolume);
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			SOUND->Play("스카디_공격", g_fVolume);
			SOUND->Play("BowAttack", g_fVolume);
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
		case CHAR_INHERENT1:
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
			if (!SOUND->IsPlaySound("메그너스_피격")) SOUND->Play("메그너스_피격", g_fVolume);
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			if (!SOUND->IsPlaySound("스카디_피격")) SOUND->Play("스카디_피격", g_fVolume);
		}

		if (INPUT->KeyDown(VK_SPACE))
		{
			m_eCondition = CHAR_ATTACK;
			m_bIsAttack = true;
			SetTarget();
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


	//고유스킬======================================
	if (INPUT->KeyDown('R'))
	{
		if (m_eCharSelect == CHAR_ONE)
		{
			SOUND->Play("메그너스_고유_총", g_fVolume);
			SOUND->Play("메그너스_고유", g_fVolume);
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			SOUND->Play("스카디_고유", g_fVolume);
			SOUND->Play("BowAttack", g_fVolume);
		}
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_INHERENT1;
			MultiAttack();
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('R'))
	{
		m_nDamageCount = 0;
	}

	if (INPUT->KeyDown('F'))
	{
		m_bIsGunView = true;
	}
	else if (INPUT->KeyUp('F'))
	{
		m_bIsGunView = false;
	}

	if (INPUT->KeyDown('V'))
	{
		if (m_eCharSelect == CHAR_ONE)
			MagicBullet();
		if (m_eCharSelect == CHAR_TWO)
			WindStorm();
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
	m_vecTarget.clear();
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();

	if (m_fElpTime < m_fPrevTime + m_fEffectInterval) return;

	m_fPrevTime = m_fElpTime;

	m_nDamageCount++;

	for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); i++)
	{
		if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn()) continue;
		D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition();
		float length = D3DXVec3Length(&(MonPos - pos));

		if (length <= m_Status->chr.fRange)
		{	// 시선
			D3DXVECTOR3 front;
			D3DXMATRIX matY;
			D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
			D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
			D3DXVECTOR3 v0 = front;
			// 대상방향
			D3DXVECTOR3 v1 = MonPos - pos;
			D3DXVec3Normalize(&v1, &v1);
			float dot = D3DXVec3Dot(&v0, &v1) / D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
			if (dot >= cos(m_Status->chr.fScale / 2))
			{
				m_vecTarget.push_back(i);
			}
		}
	}


	for (int j = 0; j < m_vecTarget.size(); j++)
	{
		D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[m_vecTarget[j]]->GetModel()->GetPosition();
		D3DXVECTOR3 TempDir;
		TempDir = MonPos - pos;
		D3DXVec3Normalize(&TempDir, &TempDir);

		float Length = D3DXVec3Length(&(MonPos - pos));

		ST_EFFECT tempEffect;
		ZeroMemory(&tempEffect, sizeof(tempEffect));

		tempEffect.time = FRand(0.4, 0.7);
		//tempEffect.isRY = true;
		//tempEffect.isRX = true;
		//tempEffect.isRZ = true;
		tempEffect.dir = TempDir;
		tempEffect.SetSpeed(0.2, 0.2, 0.2);
		tempEffect.height = 3.0f;
		tempEffect.SetAlpha(255, 255, 0);
		tempEffect.SetScale(0.5, 0.5, 0);
		tempEffect.isSphere = true;
		tempEffect.tex = TEXTUREMANAGER->GetTexture("총알");
	

	
		EffectObject* tempEFOBJ;
		tempEFOBJ = new EffectObject;

		D3DXVECTOR3 testSkillpos = *m_pCharacter->GetPosition();
		testSkillpos.y += 2.0f;
		testSkillpos.x += FRand(-2.0, 2.0);
		testSkillpos.z += FRand(-1.3, 1.3);
		//testSkillpos += TempDir * (Length * 0.3f);
		tempEFOBJ->Init(tempEffect, testSkillpos);

		m_vecEffect.push_back(tempEFOBJ);
		m_pMonsterManager->GetMonsterVector()[m_vecTarget[j]]->CalculDamage(1);
	}
}

void Character_Gun::setCameraView()
{

	if (!m_bIsGunView)
	{
		CAMERA->SetCamOffset(D3DXVECTOR3(0, 3, 20));
		CAMERA->SetTargetOffset(D3DXVECTOR3(0, 4, 0));
		CAMERA->SetTarget(m_pCharacter->GetPosition(), m_pCharacter->GetRotation());
	}
	else
	{
		CAMERA->SetCamOffset(D3DXVECTOR3(0, 10, 20));
		CAMERA->SetTargetOffset(D3DXVECTOR3(0, 10, 0));
		CAMERA->SetTarget(m_pCharacter->GetPosition(), m_pCharacter->GetRotation());
	}
}

void Character_Gun::GunClick()
{
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		m_bshoot = true;
	}
	else if (INPUT->KeyUp(VK_LBUTTON))
	{
		m_bshoot = false;
	}

	if (m_bshoot)
	{
		auto nav = m_pSampleMap->GetNavMesh();
		auto r = RayAtWorldSpace(g_ptMouse);
		float tempdistance;
		for (int i = 0; i < nav.size(); i += 3)
		{
			if (D3DXIntersectTri(&nav[i], &nav[i + 1], &nav[i + 2], &r.orig, &r.dir, NULL, NULL, &tempdistance))
			{
				m_vGun = r.orig + (r.dir* tempdistance);
			}
		}
	}
}

void Character_Gun::GunShot()
{
	m_nIndex = -1;
	
	D3DXVECTOR3 pos = m_vGun;

	if (m_bshoot)
	{

		for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); i++)
		{
			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn()) continue;
			D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition();
			float length = D3DXVec3Length(&(MonPos - pos));

			if (length <= 5.0f)
			{
				m_nIndex = i;

			}
		}
		if (m_nIndex < 0)
		{
			return;
		}
		else
		{
			CAMERA->Shake(0.08, 0.3);

			ST_EFFECT tempEffect;
			ZeroMemory(&tempEffect, sizeof(tempEffect));

			tempEffect.time = FRand(0.4, 0.7);
			//tempEffect.isRY = true;
			//tempEffect.isRX = true;
			//tempEffect.isRZ = true;
			//tempEffect.SetSpeed(0.2, 0.2, 0.2);
			tempEffect.height = 3.0f;
			tempEffect.SetAlpha(255, 255, 0);
			tempEffect.SetScale(0.5, 0.5, 0);
			tempEffect.isSphere = true;
			tempEffect.tex = TEXTUREMANAGER->GetTexture("총알");



			EffectObject* tempEFOBJ;
			tempEFOBJ = new EffectObject;

			D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
			testSkillpos.y += FRand(-2.0, 3.0);
			testSkillpos.x += FRand(-2.0, 2.0);
			testSkillpos.z += FRand(-1.3, 1.3);
			//testSkillpos += TempDir * (Length * 0.3f);
			tempEFOBJ->Init(tempEffect, testSkillpos);

			m_vecEffect.push_back(tempEFOBJ);
			if (!SOUND->IsPlaySound("탑뷰샷")) SOUND->Play("탑뷰샷", g_fVolume);
			if (!SOUND->IsPlaySound("탑뷰탄피")) SOUND->Play("탑뷰탄피", g_fVolume);
			m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(1);
		}
	}
}

void Character_Gun::MagicBullet()
{
	// 첫 타겟 지정
	m_vecTarget.clear();
	//if (m_vecTarget.empty())
	{
		int minIndex = FindNearTarget(-1, *m_pCharacter->GetPosition(), D3DX_PI / 2, 20);

		auto monsterVector = m_pMonsterManager->GetMonsterVector();
		D3DXVECTOR3 chrPos = *m_pCharacter->GetPosition();
		if (minIndex >= 0)
		{
			m_vecTarget.push_back(minIndex);

			ST_EFFECT effect;
			ZeroMemory(&effect, sizeof(ST_EFFECT));
			effect.dir = *monsterVector[minIndex]->GetModel()->GetPosition() - chrPos;
			effect.SetAlpha(255, 255, 255);
			effect.isSphere = true;
			effect.SetSpeed(3, 3, 2);
			effect.SetScale(1, 1, 1);
			effect.height = 2.5;
			effect.time = 3;
			effect.SetMotorSpeed(1, 1, 1);
			effect.mot = D3DXVECTOR3(0, 0, 1);
			effect.tex = TEXTUREMANAGER->GetTexture("Magic Bullet");

			SAFE_DELETE(m_pMagicBullet);
			m_pMagicBullet = new EffectObject;
			m_pMagicBullet->Init(effect, chrPos + D3DXVECTOR3(0, 1.5, 0));
		}
	}
}

void Character_Gun::MagicBulletUpdate()
{
	if (m_pMagicBullet)
	{
		if (m_pMagicBullet->IsFinish())
		{
			m_vecTarget.clear();
			SAFE_DELETE(m_pMagicBullet);
		}
		else if (!m_vecTarget.empty())
		{
			ST_SPHERE bullet = m_pMagicBullet->GetBoundSphere();
			ST_SPHERE target = m_pMonsterManager->GetMonsterVector()[m_vecTarget[0]]->GetModel()->GetBoundSphere();

			// 방향 조정
			ST_EFFECT current = m_pMagicBullet->GetInfo();
			current.dir = target.center - bullet.center;
			D3DXVec3Normalize(&current.dir, &current.dir);
			m_pMagicBullet->SetInfo(current);

			m_pMagicBullet->Update();

			// 잔상
			ST_EFFECT effect;
			ZeroMemory(&effect, sizeof(ST_EFFECT));
			effect.SetAlpha(200, 100, 0);
			effect.isSphere = true;
			effect.SetScale(1, 0.5, 0);
			effect.height = 2;
			effect.time = 1;
			effect.tex = TEXTUREMANAGER->GetTexture("Magic Bullet");
			EffectObject * object = new EffectObject;
			object->Init(effect, m_pMagicBullet->GetBoundSphere().center - D3DXVECTOR3(0, 1, 0));
			m_vecEffect.push_back(object);

			// 새 타겟 지정
			if (IntersectSphere(bullet, target))
			{
				ST_OBB bul = m_pMagicBullet->GetOBB();
				ST_OBB tar = m_pMonsterManager->GetMonsterVector()[m_vecTarget[0]]->GetModel()->GetBoundBox().obb;
				if (CollisionOBB(bul, tar))
				{
					int randIndex = FindRandomTarget(m_vecTarget[0], bullet.center, D3DX_PI * 2, 20);
					if (!m_pMonsterManager->GetMonsterVector()[m_vecTarget[0]]->GetIsResPawn())
					{
						m_pMonsterManager->GetMonsterVector()[m_vecTarget[0]]->CalculDamage(10);
						ZeroMemory(&effect, sizeof(ST_EFFECT));
						effect.SetAlpha(100, 50, 0);
						effect.isSphere = true;
						effect.SetScale(1, 0.5, 0);
						effect.height = FRand(2, 4);
						effect.time = 1;
						effect.SetMotorSpeed(0.3, 0.1, 0);
						effect.mot = D3DXVECTOR3(0, 0, 1);
						effect.tex = TEXTUREMANAGER->GetTexture("Magic Bullet");
						object = new EffectObject;
						object->Init(effect, m_pMagicBullet->GetBoundSphere().center -
							D3DXVECTOR3(FRand(-1, 1), FRand(0, 2), FRand(-1, 1)));
						m_vecEffect.push_back(object);
					}
					if (randIndex >= 0)
					{
						m_vecTarget.clear();
						m_vecTarget.push_back(randIndex);
					}
					else
					{
						m_vecTarget.clear();
						SAFE_DELETE(m_pMagicBullet);
					}
				}
			}
		}
	}
}

void Character_Gun::WindStorm()
{
	for (auto p : m_vecWindStorm)
		SAFE_DELETE(p);
	m_vecWindStorm.clear();
	m_vecWSDir.clear();

	int maxStorm = 10;
	float radius = 8;
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
	D3DXVECTOR3 front = GetFront(*m_pCharacter->GetRotation(), D3DXVECTOR3(0, 0, -1));
	pos += front * (radius + 2);
	vector<D3DXVECTOR3> vecPos;
	for (int i = 0; vecPos.size() < maxStorm; i++)
	{
		D3DXVECTOR3 temp = pos;
		temp.x += FRand(-radius, radius);
		temp.z += FRand(-radius, radius);

		float height = m_pSampleMap->GetHeight(temp.x, temp.z);
		temp.y = height;
		if (height > 0)
			vecPos.push_back(temp);
	}

	for (int i = 0; i < vecPos.size(); i++)
	{
		Particle * particle = PARTICLE->GetParticle("WindStorm");
		particle->SetPosition(vecPos[i]);
		particle->World();
		m_vecWSDir.push_back(D3DXVECTOR3(FRand(-1, 1), 0, FRand(-1, 1)));
		m_vecWindStorm.push_back(particle);
	}

	m_fWindTime = 0;
}

void Character_Gun::WindStormUpdate()
{
	for (int i = 0; i < m_vecWindStorm.size();)
	{
		if (!m_vecWindStorm[i]->IsDie())
		{
			if (m_fWindTime > 3)
				m_vecWindStorm[i]->SetRegen(false);

			m_vecWindStorm[i]->GetPosition()->x += m_vecWSDir[i].x * 0.1;
			m_vecWindStorm[i]->GetPosition()->z += m_vecWSDir[i].z * 0.1;
			m_vecWindStorm[i]->Update();
			m_vecWindStorm[i]->World();
			ST_SPHERE particle;
			particle.center = *m_vecWindStorm[i]->GetPosition();
			particle.radius = 2;

			auto vecMonster = m_pMonsterManager->GetMonsterVector();
			for (int i = 0; i < vecMonster.size(); i++)
			{
				ST_SPHERE monster = vecMonster[i]->GetModel()->GetBoundSphere();
				if (IntersectSphere(particle, monster))
				{
					if (!vecMonster[i]->GetIsResPawn())
					{
						vecMonster[i]->CalculDamage(10);
					}
				}
			}
			i++;
		}
		else
		{
			SAFE_DELETE(m_vecWindStorm[i]);
			m_vecWindStorm.erase(m_vecWindStorm.begin() + i);
		}
	}

	m_fWindTime += TIME->GetElapsedTime();
}

int Character_Gun::FindNearTarget(int ignore, D3DXVECTOR3 pos, float angle, float maxLength)
{
	int minIndex = -1;
	float minLength = maxLength;
	auto monsterVector = m_pMonsterManager->GetMonsterVector();
	for (int i = 0; i < monsterVector.size(); i++)
	{
		if (monsterVector[i]->GetIsResPawn()) continue;
		if (i == ignore) continue;
		float length = D3DXVec3Length(&(*monsterVector[i]->GetModel()->GetPosition() - pos));

		if (length >= 0 && length <= maxLength)
		{
			// 시선
			D3DXVECTOR3 front;
			D3DXMATRIX matY;
			D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
			D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
			D3DXVECTOR3 v0 = front;
			// 대상방향
			D3DXVECTOR3 v1 = *monsterVector[i]->GetModel()->GetPosition() - pos;
			D3DXVec3Normalize(&v1, &v1);
			float dot = D3DXVec3Dot(&v0, &v1) / D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
			if (dot >= cos(angle / 2))
			{
				if (minLength > length)
				{
					minIndex = i;
					minLength = length;
				}
			}
		}
	}

	return minIndex;
}

int Character_Gun::FindRandomTarget(int ignore, D3DXVECTOR3 pos, float angle, float maxLength)
{
	vector<int> vecIndex;
	auto monsterVector = m_pMonsterManager->GetMonsterVector();
	for (int i = 0; i < monsterVector.size(); i++)
	{
		if (monsterVector[i]->GetIsResPawn()) continue;
		if (i == ignore) continue;
		float length = D3DXVec3Length(&(*monsterVector[i]->GetModel()->GetPosition() - pos));

		if (length >= 0 && length <= maxLength)
		{
			// 시선
			D3DXVECTOR3 front;
			D3DXMATRIX matY;
			D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
			D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
			D3DXVECTOR3 v0 = front;
			// 대상방향
			D3DXVECTOR3 v1 = *monsterVector[i]->GetModel()->GetPosition() - pos;
			D3DXVec3Normalize(&v1, &v1);
			float dot = D3DXVec3Dot(&v0, &v1) / D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
			if (dot >= cos(angle / 2))
				vecIndex.push_back(i);
		}
	}

	if (!vecIndex.empty())
		return vecIndex[rand() % vecIndex.size()];
	else
		return -1;
}


