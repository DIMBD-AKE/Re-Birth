#include "../../stdafx.h"
#include "Character_Magic.h"
#include "../Map.h"
#include "Inventory.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"

Character_Magic::Character_Magic()
{
}


Character_Magic::~Character_Magic()
{
}


void Character_Magic::Init(CHRTYPE type, CHARSELECT order)
{
	m_eChrType = CHRTYPE_MAGIC;

	if (order == CHAR_ONE)
	{
		//법사 남캐
		m_pCharacter = MODELMANAGER->GetModel("아카날", MODELTYPE_X);
		//
		m_eCharSelect = CHAR_ONE;
		m_Status->chr.fAgi = 30.0f;
		m_Status->chr.fAtkSpeed = 1.0f;
		m_Status->chr.fCheRate = 5.0f;
		m_Status->chr.fHit = 5.0f;
		m_Status->chr.fMagicRate = 65.0f;
		m_Status->chr.fPhyRate = 25.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 35;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 10;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 10;
		m_Status->chr.fRange = 15.0f;
		m_Status->chr.fScale = 10.0f;
		CharacterParant::Init(type, order);

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("아카날_사진"));
		m_pUIobj->SetPosition(D3DXVECTOR3(1300, 550, 0));

	
	}
	else if (order == CHAR_TWO)
	{
		//법사 여캐
		m_pCharacter = MODELMANAGER->GetModel("헤스티아", MODELTYPE_X);
		m_eCharSelect = CHAR_TWO;
		m_Status->chr.fAgi = 30.0f;
		m_Status->chr.fAtkSpeed = 1.0f;
		m_Status->chr.fCheRate = 5.0f;
		m_Status->chr.fHit = 5.0f;
		m_Status->chr.fMagicRate = 65.0f;
		m_Status->chr.fPhyRate = 25.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 35;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 10;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 10;
		m_Status->chr.fRange = 10.0f;
		m_Status->chr.fScale = 15.2f;
		CharacterParant::Init(type, order);

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("헤스티아_사진"));
		m_pUIobj->SetPosition(D3DXVECTOR3(1300, 550, 0));

	
	}
}

void Character_Magic::Update()
{
	if (m_pCharacter)
	{
		Controller();
		KeyControl();
		Move();
		MgSkill();
		Effect();
		m_pInventory->Update();
		m_pCharacter->World();
		m_pUIobj->Update();

		PlayerProgressBar();
		CountAppearDamage();

	}
}

void Character_Magic::Render()
{
	if (m_pCharacter)
	{
		m_pCharacter->Render();
		m_pInventory->Render();

		//포트레이트 
		m_pUIobj->Render();
		m_pHPBar->Render();
		m_pStaminaBar->Render();
		AppearDamage();

		CharacterParant::Render();
	}
}

void Character_Magic::KeyControl()
{
	//앞으로 달리기
	if (INPUT->KeyDown('W'))
	{
		SOUND->Play("FootStep");
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_HIT)
		{
			m_eCondition = CHAR_RUN_FRONT;

			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('W'))
	{
		SOUND->Stop("FootStep");
		if (m_eCondition == CHAR_RUN_FRONT)
		{
			m_eCondition = CHAR_IDLE;

			ChangeAnimation();
		}
	}
	//뒤로 달리기
	if (INPUT->KeyDown('S'))
	{
		SOUND->Play("FootStep");
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_HIT)
		{
			m_eCondition = CHAR_RUN_BACK;

			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('S'))
	{
		SOUND->Stop("FootStep");
		if (m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_IDLE;

			ChangeAnimation();
		}
	}
	//앞으로 대쉬
	if (INPUT->KeyDown('Q'))
	{
		if (m_eCondition == CHAR_RUN_FRONT)
		{
			m_eCondition = CHAR_DASH_FRONT;

			m_bIsDash = true;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('Q'))
	{
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
		if (m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_DASH_BACK;

			m_bIsDash = true;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('E'))
	{
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
		SOUND->Play("SwordAttack");
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

	//순간이동 제어
	if (INPUT->KeyDown('T'))
	{
		m_bIsPotal = true;
	}
	else if (INPUT->KeyUp('T'))
	{
		m_bIsPotal = false;
		m_pCharacter->SetPosition(D3DXVECTOR3(m_pParticle3->GetPosition()->x + 1.0f, m_pParticle3->GetPosition()->y, m_pParticle3->GetPosition()->z - 1.0f));
		m_pParticle4->SetPosition(*m_pCharacter->GetPosition());
		m_pParticle4->TimeReset();
	}

	if (m_bIsPotal)
	{
		if (INPUT->KeyDown(VK_LBUTTON))
		{
			m_bIsPotal = false;
			m_pCharacter->SetPosition(D3DXVECTOR3(m_pParticle3->GetPosition()->x + 1.0f, m_pParticle3->GetPosition()->y, m_pParticle3->GetPosition()->z - 1.0f));
			m_pParticle4->SetPosition(*m_pCharacter->GetPosition());
			m_pParticle4->TimeReset();
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
}

void Character_Magic::Attack()
{
	D3DXVECTOR3 front;
	D3DXMATRIX matY;
	D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
	D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
	D3DXVECTOR3 v0 = front;
	//대상방향
	D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
	D3DXVECTOR3 v1 = MonPos - pos;
	D3DXVec3Normalize(&v0, &v1);
	float dot = D3DXVec3Dot(&v0, &v1) / D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
	if (dot >= cos(m_Status->chr.fScale / 2))
	{
		//if (m_nIndex == -1) return;
		if (m_fElpTime < m_fPrevTime + m_fEffectInterval) return;

		m_fPrevTime = m_fElpTime;

		m_nDamageCount++;
		if (m_eCharSelect == CHAR_ONE)
		{
			if (m_nDamageCount <= 3)
			{
				ST_EFFECT tempEffect;
				ZeroMemory(&tempEffect, sizeof(tempEffect));

				tempEffect.time = FRand(0.1, 0.4);
				tempEffect.isRY = true;
				tempEffect.isRX = true;
				tempEffect.height = 3.0f;
				tempEffect.SetAlpha(255, 255, 0);
				tempEffect.SetScale(1, 0.8, 0.8);
				tempEffect.tex = TEXTUREMANAGER->AddTexture("akanal", "Texture/Effect/akanal.png");
				EffectObject* tempEFOBJ;
				tempEFOBJ = new EffectObject;

				D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				testSkillpos.y += 1.0f;
				testSkillpos.x += FRand(-0.5, 0.5);
				tempEFOBJ->Init(tempEffect, testSkillpos);

				m_vecEffect.push_back(tempEFOBJ);
				m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
			}
		}
		else if (m_eCharSelect == CHAR_TWO)
		{
			if (m_nDamageCount <= 3)
			{
				ST_EFFECT tempEffect;
				ZeroMemory(&tempEffect, sizeof(tempEffect));

				tempEffect.time = FRand(0.1, 0.4);
				tempEffect.isRY = true;
				tempEffect.isRX = true;
				tempEffect.height = 3.0f;
				tempEffect.SetAlpha(255, 255, 0);
				tempEffect.SetScale(1, 0.8, 0.8);
				tempEffect.tex = TEXTUREMANAGER->AddTexture("Hestia", "Texture/Effect/Hestia.png");
				EffectObject* tempEFOBJ;
				tempEFOBJ = new EffectObject;

				D3DXVECTOR3 TempDir;
				TempDir = *m_pCharacter->GetPosition() - *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				D3DXVec3Normalize(&TempDir, &TempDir);

				D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				testSkillpos.y += 1.0f;
				testSkillpos.x += FRand(-0.5, 0.5);
				testSkillpos.z += FRand(-0.5, 0.5);
				testSkillpos += TempDir * 4.0f;
				tempEFOBJ->Init(tempEffect, testSkillpos);



				m_vecEffect.push_back(tempEFOBJ);
				m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);

			}

		}
	}
}

void Character_Magic::MgSkill()
{
	if (!m_bIsPotal) m_pParticle3->SetPosition(*m_pCharacter->GetPosition());


	D3DXVECTOR3 Potalpos = *m_pParticle3->GetPosition();
	D3DXVECTOR3	playerTempPos = *m_pCharacter->GetPosition();
	D3DXVECTOR3 Potalrot = *m_pParticle3->GetRotation();

	D3DXMATRIX matPotalAngle;
	D3DXMatrixRotationYawPitchRoll(&matPotalAngle, m_pParticle3->GetRotation()->y, m_pParticle3->GetRotation()->x, m_pParticle3->GetRotation()->z);

	m_vPotalfront = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vPotalfront, &m_vPotalfront, &matPotalAngle);
	//이동파티클 키보드 제어 
	if (INPUT->KeyPress(VK_LEFT))
	{
		m_pParticle3->GetRotation()->y -= 0.05f;
	}
	if (INPUT->KeyPress(VK_RIGHT))
	{
		m_pParticle3->GetRotation()->y += 0.05f;
	}
	if (INPUT->KeyPress(VK_UP))
	{
		float Potalheight = m_pSampleMap->GetHeight(Potalpos.x - m_vPotalfront.x *0.3, Potalpos.z - m_vPotalfront.z *0.3);
		if (Potalheight >= 0)
		{
			Potalpos.y = Potalheight;
			if (D3DXVec3Length(&(playerTempPos - Potalpos)) <= 14.0f)
			{
				m_pParticle3->SetPosition(Potalpos + m_vPotalfront * 0.3);
			}
		}
		else if (Potalheight == -1)
		{
			return;
		}
	}
	if (INPUT->KeyPress(VK_DOWN))
	{
		float Potalheight = m_pSampleMap->GetHeight(Potalpos.x - m_vPotalfront.x *0.3, Potalpos.z - m_vPotalfront.z *0.3);
		if (Potalheight >= 0)
		{
			Potalpos.y = Potalheight;
			if (D3DXVec3Length(&(playerTempPos - Potalpos)) <= 7.0f)
			{
				m_pParticle3->SetPosition(Potalpos - m_vPotalfront * 0.3);
			}
		}
		else if (Potalheight == -1)
		{
			return;
		}
	}

	if (m_bIsPotal)
	{
		m_pParticle3->World();
		m_pParticle3->Update();

		auto nav = m_pSampleMap->GetNavMesh();
		auto r = RayAtWorldSpace(g_ptMouse);
		float tempdistance;
		for (int i = 0; i < nav.size(); i += 3)
		{
			if (D3DXIntersectTri(&nav[i], &nav[i + 1], &nav[i + 2], &r.orig, &r.dir, NULL, NULL, &tempdistance))
			{
				if (D3DXVec3Length(&(playerTempPos - Potalpos)) < 14.0f)
				{
					m_pParticle3->SetPosition(r.orig + r.dir* tempdistance);
				}
			}
		}
	}
}


