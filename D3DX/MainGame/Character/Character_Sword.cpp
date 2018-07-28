#include "../../stdafx.h"
#include "Character_Sword.h"
#include "../Map.h"
#include "Inventory.h"
#include "../Status.h"
#include "Character_Shield.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../DamageUI.h"
#include "Npc.h"


Character_Sword::Character_Sword()
{		//다이얼로그			위치				사이즈  폰트       속도    색깔
		//	m_pContext->Init(D3DXVECTOR2(550, 280), 30, "나눔명조", 0.05, 0xFFFFFFFF);

}


Character_Sword::~Character_Sword()
{
}

void Character_Sword::Init(CHRTYPE type, CHARSELECT order)
{
	m_eChrType = CHRTYPE_SWORD;

	// 
	m_bIsFskill = false;
	m_fDeltaY = 3.0f;
	m_fDelta = 10.0f;
	m_bEnemySkillMoving = false;
	m_bIsTarget = false;
	VskillInterval = 1.0;
	//

	if (order == CHAR_ONE)
	{
		//일본도여캐
		m_pCharacter = MODELMANAGER->GetModel("베카", MODELTYPE_X);

		m_eNumTarget = NUM_MULTI;
		m_eCharSelect = CHAR_ONE;
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 1.0f;
		m_Status->chr.fCheRate = 5.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 1.0f;
		m_Status->chr.fPhyRate = 1.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 100;
		m_Status->chr.nCurrentHP = 10000;
		m_Status->chr.nCurrentStam = 100;
		m_Status->chr.nDef = 2;
		m_Status->chr.nMaxHp = 10000;
		m_Status->chr.nMaxStam = 100;
		m_Status->chr.fRange = 5.0f;
		m_Status->chr.fScale = 5.0f;

		CharacterParant::Init(type, order);

		m_pSkillBar->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스킬창"));
		m_pSkillBar->SetPosition(D3DXVECTOR3(588, 695, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("근접_방패"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(609, 733, 0));

		m_pInheritateIco2->SetTexture(TEXTUREMANAGER->GetTexture("근접_무적"));
		m_pInheritateIco2->SetPosition(D3DXVECTOR3(722, 733, 0));

		m_pInheritateIco3->SetTexture(TEXTUREMANAGER->GetTexture("근접_이동공격"));
		m_pInheritateIco3->SetPosition(D3DXVECTOR3(839, 733, 0));

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스테이터스"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 668, 0));


		//포트레이트 UI
		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("베카_사진"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));


	}
	else if (order == CHAR_TWO)
	{
		//긴칼여캐
		m_pCharacter = MODELMANAGER->GetModel("리아", MODELTYPE_X);
		m_eNumTarget = NUM_SINGLE;
		m_eCharSelect = CHAR_TWO;
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 1.0f;
		m_Status->chr.fCheRate = 5.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 25.0f;
		m_Status->chr.fPhyRate = 60.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 60;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 100;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 100;
		m_Status->chr.fRange = 5.0f;
		m_Status->chr.fScale = 3.2f;
		CharacterParant::Init(type, order);


		m_pSkillBar->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스킬창"));
		m_pSkillBar->SetPosition(D3DXVECTOR3(588, 695, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("근접_방패"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(609, 733, 0));

		m_pInheritateIco2->SetTexture(TEXTUREMANAGER->GetTexture("근접_무적"));
		m_pInheritateIco2->SetPosition(D3DXVECTOR3(722, 733, 0));

		m_pInheritateIco3->SetTexture(TEXTUREMANAGER->GetTexture("근접_이동공격"));
		m_pInheritateIco3->SetPosition(D3DXVECTOR3(839, 733, 0));

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스테이터스"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 668, 0));


		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("리아_사진"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));
	}
	else if (order == CHAR_THREE)
	{
		//전기톱 여캐
		m_pCharacter = MODELMANAGER->GetModel("벨벳", MODELTYPE_X);
		m_eNumTarget = NUM_SINGLE;
		m_eCharSelect = CHAR_THREE;
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 1.0f;
		m_Status->chr.fCheRate = 5.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 25.0f;
		m_Status->chr.fPhyRate = 60.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 15;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 100;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 100;
		m_Status->chr.fRange = 5.0f;
		m_Status->chr.fScale = 3.0f;
		CharacterParant::Init(type, order);


		m_bIsVelvetFinal = false;
		m_nVelvetCount = 0;
		velvetFinal = m_pCharacter->GetBoneMatrix("Bone_sawtooth01");
		m_vVelvetFinal = D3DXVECTOR3(0, 0, 0);
		m_fVelvetInterval = 15.0f;
		m_fOriginSpeed = 0.0f;
		m_nVelvetEnd = 0;

		m_pSkillBar->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스킬창"));
		m_pSkillBar->SetPosition(D3DXVECTOR3(588, 695, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("근접_방패"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(609, 733, 0));

		m_pInheritateIco2->SetTexture(TEXTUREMANAGER->GetTexture("근접_무적"));
		m_pInheritateIco2->SetPosition(D3DXVECTOR3(722, 733, 0));

		m_pInheritateIco3->SetTexture(TEXTUREMANAGER->GetTexture("근접_이동공격"));
		m_pInheritateIco3->SetPosition(D3DXVECTOR3(839, 733, 0));

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스테이터스"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 668, 0));


		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("벨벳_사진"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));

	}

}

void Character_Sword::Update()
{
	if (m_pCharacter && m_eCondition != CHAR_NONE && !m_isCutScene)
	{
		Controller();
		Move();

		m_pInventory->Update();
		m_pCharacter->World();
		m_pUIobj->Update();
		m_pChrStat->Update();
		m_pInheritateIco->Update();
		m_pInheritateIco2->Update();
		m_pSkillBar->Update();

		SetCameraNormalView();
		m_pTalkBar->Update();
		if (m_bSkillUnSealed)m_pInheritateIco3->Update();

		if (m_bIsSubChr)
		{
			if (m_pShieldChr)
			{
				m_pShieldChr->Update(*m_pCharacter->GetPosition() - m_vfront * 3.0f, *m_pCharacter->GetRotation());
			}
			else
			{
				m_pShieldChr = new Character_Shield;
				m_pShieldChr->Init(*m_pCharacter->GetPosition());
			}
		}

		if (m_bIsFskill)
		{
			if (m_eCharSelect == CHAR_ONE) //베카
			{
				this->Shunpo();
			}
			else if (m_eCharSelect == CHAR_TWO) //리아
			{
				this->Bash();
			}
			else if (m_eCharSelect == CHAR_THREE) //벨벳
			{
				this->GrabSlash();
			}
			else return;

		}

		if (m_bEnemySkillMoving)
		{
			SkillEnemyMoving();
		}

		Effect();



		PlayerProgressBar();


		//m_pDamage->Update(*m_pCharacter->GetPosition());
		if (m_eCharSelect == CHAR_THREE)
		{
			D3DXVec3TransformCoord(&m_vVelvetFinal, &D3DXVECTOR3(0, 0, 0), velvetFinal);
		}
		if (m_bIsVelvetFinal)
		{
			m_pVelvetFinal->SetPosition(m_vVelvetFinal);
			m_pVelvetFinal->SetRotation(*m_pCharacter->GetRotation());
			m_pVelvetFinal->ApplyWorld();
			m_pVelvetFinal->Update();
		}
		VelvetCount();
	}
	CutScene();
	if (!m_bIsStun)KeyControl();
	if (m_bIsTarget)TargetSword();

	
	CharacterParant::Update();

}

void Character_Sword::Render()
{
	if (m_pCharacter && m_eCondition != CHAR_NONE)
	{
		m_pCharacter->Render();



		if (m_pShieldChr && m_bIsSubChr)
		{
			m_pShieldChr->Render();
		}




	//	m_pDamage->Render();
		CharacterParant::Render();
		if (m_pNpc->GetCollision()) m_pTalkBar->Render();
		//포트레이트 
		if (!m_pNpc->GetCollision())m_pUIobj->Render();
		
		if (!m_pNpc->GetCollision())m_pSkillBar->Render();
		if (!m_pNpc->GetCollision())m_pInheritateIco->Render();
		if (!m_pNpc->GetCollision())m_pInheritateIco2->Render();
		if (m_bSkillUnSealed && !m_pNpc->GetCollision())m_pInheritateIco3->Render();
		if (!m_pNpc->GetCollision())m_pHPBar->Render();
		if (!m_pNpc->GetCollision())m_pStaminaBar->Render();
		if (m_bIsVelvetFinal)
		{
			m_pVelvetFinal->Render();
		}
		m_pInventory->Render();
	}
}

void Character_Sword::KeyControl()
{
	//앞으로 달리기
	if (INPUT->KeyDown('W'))
	{
		SOUND->Play("FootStep", g_fVolume);
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_HIT)
		{
			m_eCondition = CHAR_RUN_FRONT;
			if (m_bIsSubChr)
			{
				m_pShieldChr->SetShieldCondition(SUB_RUN);
				m_pShieldChr->ChangeSubChrAni();
			}
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('W'))
	{
		SOUND->Stop("FootStep");
		if (m_eCondition == CHAR_RUN_FRONT)
		{
			m_eCondition = CHAR_IDLE;
			if (m_bIsSubChr)
			{
				m_pShieldChr->SetShieldCondition(SUB_IDLE);
				m_pShieldChr->ChangeSubChrAni();
			}
			ChangeAnimation();
		}
	}
	//뒤로 달리기
	if (INPUT->KeyDown('S'))
	{
		SOUND->Play("FootStep", g_fVolume);
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_HIT)
		{
			m_eCondition = CHAR_RUN_BACK;
			if (m_bIsSubChr)
			{
				m_pShieldChr->SetShieldCondition(SUB_RUN);
				m_pShieldChr->ChangeSubChrAni();
			}
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('S'))
	{
		SOUND->Stop("FootStep");
		if (m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_IDLE;
			if (m_bIsSubChr)
			{
				m_pShieldChr->SetShieldCondition(SUB_IDLE);
				m_pShieldChr->ChangeSubChrAni();
			}
			ChangeAnimation();
		}
	}
	//앞으로 대쉬
	if (INPUT->KeyDown('Q'))
	{
		SOUND->Play("FootStep3", g_fVolume);
		SOUND->Stop("FootStep");
		if (m_eCondition == CHAR_RUN_FRONT)
		{
			m_eCondition = CHAR_DASH_FRONT;
			if (m_bIsSubChr)
			{
				m_pShieldChr->SetShieldCondition(SUB_RUN);
				m_pShieldChr->ChangeSubChrAni();
			}
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
			if (m_bIsSubChr)
			{
				m_pShieldChr->SetShieldCondition(SUB_RUN);
				m_pShieldChr->ChangeSubChrAni();
			}
			m_bIsDash = false;
			ChangeAnimation();
		}
	}
	//뒤로 대쉬
	if (INPUT->KeyDown('E'))
	{
		SOUND->Play("FootStep3", g_fVolume);
		SOUND->Stop("FootStep");
		if (m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_DASH_BACK;
			if (m_bIsSubChr)
			{
				m_pShieldChr->SetShieldCondition(SUB_RUN);
				m_pShieldChr->ChangeSubChrAni();
			}
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
			if (m_bIsSubChr)
			{
				m_pShieldChr->SetShieldCondition(SUB_RUN);
				m_pShieldChr->ChangeSubChrAni();
			}
			m_bIsDash = false;
			ChangeAnimation();
		}
	}

	//일반공격
	if (INPUT->KeyDown(VK_SPACE))
	{
		if (m_eCharSelect == CHAR_ONE)
		{
			SOUND->Play("SwordAttack", g_fVolume);
			SOUND->Play("베카_공격", g_fVolume);
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			SOUND->Play("SwordAttack_TWO", g_fVolume);
			SOUND->Play("리아_공격", g_fVolume);
		}
		if (m_eCharSelect == CHAR_THREE)
		{
			SOUND->Play("SwordAttack_THREE", g_fVolume);
			SOUND->Play("벨벳_공격", g_fVolume);
		}

		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_ATTACK;
			if (m_bIsSubChr)
			{
				m_pShieldChr->SetShieldCondition(SUB_IDLE);
				m_pShieldChr->ChangeSubChrAni();
			}
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
		SKill();
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
		case CHAR_GUARD:
			m_eCondition = CHAR_IDLE;
			//m_bIsInvincible = false;
			break;
		}
		ChangeAnimation();
	}

	//피격 도중에 공격 가능하게 만들기
	if (m_eCondition == CHAR_HIT)
	{
		if (m_eCharSelect == CHAR_ONE)
		{
			if (!SOUND->IsPlaySound("베카_피격")) SOUND->Play("베카_피격", g_fVolume);
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			if (m_bIsUnderAttacked)
			{
				if (!SOUND->IsPlaySound("리아_피격")) SOUND->Play("리아_피격", g_fVolume);
			}
		}
		if (m_eCharSelect == CHAR_THREE)
		{
			if (!SOUND->IsPlaySound("벨벳_피격")) SOUND->Play("벨벳_피격", g_fVolume);
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

	//공격상태시 공격 제어.
	if (m_eCondition == CHAR_ATTACK)
	{
		Attack();
	}

	if (m_eCondition == CHAR_IDLE)
	{
		if (SOUND->IsPlaySound("FootStep")) SOUND->Stop("FootStep");
		if (SOUND->IsPlaySound("FootStep3")) SOUND->Stop("FootStep3");
	}

	if (INPUT->KeyDown('M'))
	{
		m_isCutScene = true;
	}
	if (INPUT->KeyDown('L'))
	{
		m_isCutScene = false;
	}


	//고유스킬 제어======================================

	//서브캐릭터 제어
	if (INPUT->KeyDown('R'))
	{
		if (m_Status->chr.nCurrentStam >= 50.0f)
		{
			m_Status->chr.nCurrentStam -= 50.0f;
			if (!m_bIsSubChr)
			{
				m_bIsSubChr = true;
				CAMERA->Shake(0.2f, 0.5f);
			}
		}
	}

	if (INPUT->KeyDown('F'))
	{
		if (m_Status->chr.nCurrentStam >= 30.0f)
		{
			m_Status->chr.nCurrentStam -= 30.0f;
			m_eCondition = CHAR_SKILL;
			m_bIsFskill = true;
			m_nDamageCount = 0;
			m_nDC = 0;
			if (m_eCharSelect == CHAR_ONE)
			{
				SOUND->Play("SwordAttack");
				SOUND->Play("베카_공격");
			}
			if (m_eCharSelect == CHAR_TWO)
			{
				SOUND->Play("SwordAttack_TWO");
				SOUND->Play("리아_공격");
			}
			if (m_eCharSelect == CHAR_THREE)
			{
				SOUND->Play("SwordAttack_THREE");
				SOUND->Play("벨벳_공격");
			}

			if (m_eCharSelect == CHAR_TWO)
			{
				m_fDelta = 10.0f;
			}
			if (m_eCharSelect == CHAR_THREE)
			{
				m_fDeltaY = 3.0f;
			}
			ChangeAnimation();
		}
	}

	if (m_bSkillUnSealed)
	{
		if (INPUT->KeyDown('V'))
		{
			m_nDamageCount = 0;
			//TargetSword();
			if (m_eCharSelect == CHAR_ONE)
			{
				m_bIsTarget = true;
			}

			if (m_eCharSelect == CHAR_THREE)
			{
				SetTarget();
				velvetFinalSKILL();
			}
		}
	}


	//가드를 올려야해요!
	if (INPUT->KeyDown('Z'))
	{
		m_eCondition = CHAR_GUARD;
		ChangeAnimation();
	}



}

void Character_Sword::Attack()
{
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();

	if (m_fElpTime < m_fPrevTime + m_fEffectInterval) return;

	m_fPrevTime = m_fElpTime;

	m_nDamageCount++;
	if (m_eCharSelect == CHAR_ONE)
	{
		if (m_vecTarget.size() <= 0) return;
		if (m_nDamageCount <= 3)
		{
			for (int i = 0; i < m_vecTarget.size(); i++)
			{
				D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->GetModel()->GetPosition();
				ST_EFFECT tempEffect;
				ZeroMemory(&tempEffect, sizeof(tempEffect));

				tempEffect.time = FRand(0.1, 0.4);
				tempEffect.isRY = true;
				tempEffect.isRX = true;
				tempEffect.height = 3.0f;

				//TODO : 알파값도 랜덤으로, 스케일도 랜덤으로 RND써서 수정
				tempEffect.SetAlpha(FRand(100, 255), FRand(100, 255), 0);
				tempEffect.SetScale(FRand(1.4, 3.0), FRand(1.4, 3.0), FRand(1.4, 3.0));
				tempEffect.tex = TEXTUREMANAGER->AddTexture("testSkill", "Texture/Effect/TestSkill.png");
				EffectObject* tempEFOBJ;
				tempEFOBJ = new EffectObject;

				D3DXVECTOR3 TempDir;
				TempDir = *m_pCharacter->GetPosition() - *m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->GetModel()->GetPosition();
				D3DXVec3Normalize(&TempDir, &TempDir);

				float Length = D3DXVec3Length(&(MonPos - pos));

				D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->GetModel()->GetPosition();
				testSkillpos.y += 1.0f;
				testSkillpos.x += FRand(-0.5, 0.5);
				testSkillpos.z += FRand(-0.3, 0.3);
				testSkillpos += TempDir * (Length * 0.3f);
				tempEFOBJ->Init(tempEffect, testSkillpos);

				m_vecEffect.push_back(tempEFOBJ);

				if (m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->GetIsResPawn())return;
				//m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
				m_pMonsterManager->DamageMonster(m_vecTarget[i], m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
				//m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->GetModel()->SetShaderRimColor(D3DXVECTOR3(255, 0, 0));
				//m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->GetModel()->SetShaderRimPower(1.0f);
			}
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
			tempEffect.SetAlpha(FRand(100, 255), FRand(100, 255), 0);
			tempEffect.SetScale(FRand(1.4, 3.0), FRand(1.4, 3.0), FRand(1.4, 3.0));
			tempEffect.tex = TEXTUREMANAGER->AddTexture("Step", "Texture/Effect/step.png");
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
			//m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
			m_pMonsterManager->DamageMonster(m_nIndex, m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
		}
	}
	else if (m_eCharSelect == CHAR_THREE)
	{
		if (m_nIndex < 0) return;
		if (m_nDamageCount <= 20)
		{
			D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
			ST_EFFECT tempEffect;
			ZeroMemory(&tempEffect, sizeof(tempEffect));

			tempEffect.time = FRand(0.1, 0.4);
			tempEffect.isRY = true;
			tempEffect.isRX = true;
			tempEffect.height = 3.0f;
			tempEffect.SetAlpha(FRand(100, 255), FRand(100, 255), 0);
			tempEffect.SetScale(FRand(1.4, 3.0), FRand(1.4, 3.0), FRand(1.4, 3.0));
			tempEffect.tex = TEXTUREMANAGER->AddTexture("Blood", "Texture/Effect/velvet.png");
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
			//m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
			m_pMonsterManager->DamageMonster(m_nIndex, m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
		}
	}
}

void Character_Sword::Shunpo()
{
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();

	if (m_fElpTime < m_fPrevTime + m_fEffectInterval) return;

	m_fPrevTime = m_fElpTime;

	if (m_eCharSelect == CHAR_ONE)
	{
		m_nDamageCount++;
		if (m_nDamageCount <= 1)
		{
			ST_EFFECT tempEffect;
			ZeroMemory(&tempEffect, sizeof(tempEffect));

			D3DXVECTOR3 front;
			D3DXMATRIX matY;
			D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
			D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);

			tempEffect.time = FRand(0.1, 0.5) + 2;
			//tempEffect.isRY = true;
			tempEffect.isRX = true;
			tempEffect.dir = front;
			tempEffect.height = 3.0f;
			tempEffect.SetSpeed(1.0, 1.0, 1.0);
			//TODO : 알파값도 랜덤으로, 스케일도 랜덤으로 RND써서 수정
			tempEffect.SetAlpha(FRand(100, 255), FRand(100, 255), 0);
			tempEffect.SetScale(FRand(1.4, 3.0), FRand(1.4, 3.0), FRand(1.4, 3.0));
			tempEffect.tex = TEXTUREMANAGER->AddTexture("testSkill", "Texture/Effect/TestSkill.png");
			EffectObject* tempEFOBJ;
			tempEFOBJ = new EffectObject;


			D3DXVECTOR3 TempDir;
			TempDir = front;
			D3DXVec3Normalize(&TempDir, &TempDir);


			D3DXVECTOR3 testSkillpos = pos;
			testSkillpos.y += 1.0f;
			//testSkillpos.x += FRand(-0.5, 0.5);
			//testSkillpos.z += FRand(-0.3, 0.3);
			////testSkillpos += TempDir * (10.0f * 0.3f);
			tempEFOBJ->Init(tempEffect, testSkillpos);

			m_vecEffect.push_back(tempEFOBJ);

		}

		this->SkillDealing();

		if (m_pCharacter->IsAnimationEnd())
		{
			m_bIsFskill = false;
		}
	}
	else return;
}

void Character_Sword::Bash()
{

	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();

	if (m_fElpTime < m_fPrevTime + m_fEffectInterval) return;

	m_fPrevTime = m_fElpTime;

	if (m_eCharSelect == CHAR_TWO)
	{
		m_nDamageCount++;
		if (m_nDamageCount < 10)
		{
			ST_EFFECT tempEffect;
			ZeroMemory(&tempEffect, sizeof(tempEffect));

			D3DXVECTOR3 front;
			D3DXMATRIX matY;
			D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
			D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);

			tempEffect.time = FRand(0.5, 0.5);
			//tempEffect.isRY = true;
			tempEffect.isRX = true;
			tempEffect.dir = front;
			tempEffect.autoY = true;
			tempEffect.height = 3.0f;
			//tempEffect.SetSpeed(1.0, 1.0, 1.0);
			//TODO : 알파값도 랜덤으로, 스케일도 랜덤으로 RND써서 수정
			tempEffect.SetAlpha(FRand(100, 255), FRand(100, 255), 0);
			tempEffect.SetScale(FRand(1.4, 3.0), FRand(1.4, 3.0), FRand(1.4, 3.0));
			tempEffect.tex = TEXTUREMANAGER->AddTexture("testSkill", "Texture/Effect/TestSkill.png");
			EffectObject* tempEFOBJ;
			tempEFOBJ = new EffectObject;


			D3DXVECTOR3 TempDir;
			TempDir = front;
			D3DXVec3Normalize(&TempDir, &TempDir);


			D3DXVECTOR3 testSkillpos = pos;
			testSkillpos.y += 1.0f;
			tempEFOBJ->Init(tempEffect, testSkillpos);

			m_vecEffect.push_back(tempEFOBJ);

		}

		this->SkillDealing();

		if (m_pCharacter->IsAnimationEnd())
		{//m_vecEffect.size() <= 0

			m_bIsFskill = false;
		}
	}
	else return;
}

void Character_Sword::GrabSlash()
{
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();

	if (m_fElpTime < m_fPrevTime + m_fEffectInterval) return;

	m_fPrevTime = m_fElpTime;

	if (m_eCharSelect == CHAR_THREE)
	{
		m_nDamageCount++;
		if (m_nDamageCount <= 1)
		{
			ST_EFFECT tempEffect;
			ZeroMemory(&tempEffect, sizeof(tempEffect));

			D3DXVECTOR3 front;
			D3DXMATRIX matY;
			D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
			D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);

			tempEffect.time = FRand(0.5, 0.5);
			tempEffect.isRY = true;
			//tempEffect.isRZ = true;
			//tempEffect.isRX = true;
			tempEffect.dir = front;
			tempEffect.autoY = true;
			tempEffect.height = 3.0f;
			tempEffect.SetSpeed(1.0, 1.0, 1.0);
			//TODO : 알파값도 랜덤으로, 스케일도 랜덤으로 RND써서 수정
			tempEffect.SetAlpha(FRand(100, 255), FRand(100, 255), 0);
			tempEffect.SetScale(FRand(1.4, 3.0), FRand(1.4, 3.0), FRand(1.4, 3.0));
			tempEffect.tex = TEXTUREMANAGER->AddTexture("testSkill", "Texture/Effect/chain.png");
			EffectObject* tempEFOBJ;
			tempEFOBJ = new EffectObject;


			D3DXVECTOR3 TempDir;
			TempDir = front;
			D3DXVec3Normalize(&TempDir, &TempDir);


			D3DXVECTOR3 testSkillpos = pos;
			testSkillpos.y += 1.0f;
			tempEFOBJ->Init(tempEffect, testSkillpos);

			m_vecEffect.push_back(tempEFOBJ);

		}

		this->SkillDealing();

		if (m_pCharacter->IsAnimationEnd())
		{
			m_bIsFskill = false;
		}
	}
	else return;

}

void Character_Sword::SkillDealing()
{

	if (m_eCharSelect == CHAR_ONE)
	{
		if (m_vecEffect.size() <= 0) return;
		m_nIndex = -1;

		if (m_nDC < 1)
		{
			for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); i++)
			{
				
				D3DXVECTOR3 s1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().center;
				D3DXVECTOR3 s2 = m_vecEffect.back()->GetBoundSphere().center;
				D3DXVECTOR3 v = s1 - s2;
				float distance = D3DXVec3Length(&v);

				float r1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
				float r2 = m_vecEffect.back()->GetBoundSphere().radius;

				if (r1 + r2 >= distance)
				{
					
					
					m_nIndex = i;
					D3DXVECTOR3 front;
					D3DXMATRIX matY;
					D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
					D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
					D3DXVECTOR3 pos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
					if (m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetIsResPawn())return;
					//m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(1);
					m_pMonsterManager->DamageMonster(m_nIndex, m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
					m_pCharacter->SetPosition(pos - front * 4);

					m_nDC++;
				}

			}
		}
		else return;
	}
	else if (m_eCharSelect == CHAR_TWO)
	{
		if (m_vecEffect.size() <= 0) return;
		m_nIndex = -1;

		if (m_nDC < 10)
		{
			for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); i++)
			{

				D3DXVECTOR3 s1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().center;
				D3DXVECTOR3 s2 = m_vecEffect.back()->GetBoundSphere().center;
				D3DXVECTOR3 v = s1 - s2;
				float distance = D3DXVec3Length(&v);

				float r1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
				float r2 = m_vecEffect.back()->GetBoundSphere().radius;

				if (r1 + r2 >= distance)
				{
					m_fDelta -= 1.0f;
					m_nIndex = i;
					m_bEnemySkillMoving = true;
					if (m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetIsResPawn())return;
					//m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(999);
					m_pMonsterManager->DamageMonster(m_nIndex, m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
					m_nDC++;
				}

			}
		}
		else return;
	}
	else if (m_eCharSelect == CHAR_THREE)
	{
		if (m_vecEffect.size() <= 0) return;
		m_nIndex = -1;

		for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); i++)
		{

			D3DXVECTOR3 s1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().center;
			D3DXVECTOR3 s2 = m_vecEffect.back()->GetBoundSphere().center;
			D3DXVECTOR3 v = s1 - s2;
			float distance = D3DXVec3Length(&v);

			float r1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
			float r2 = m_vecEffect.back()->GetBoundSphere().radius;

			if (r1 + r2 >= distance)
			{
				m_fDeltaY -= 0.5f;
				
				m_nIndex = i;
				m_bEnemySkillMoving = true;
				if (m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetIsResPawn())return;
				//m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(1);
				m_pMonsterManager->DamageMonster(m_nIndex, m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
			}

		}
	}

}

void Character_Sword::SkillEnemyMoving()
{
	if (!m_bEnemySkillMoving) return;

	if (m_eCharSelect == CHAR_TWO)
	{
		m_fDelta -= 1.0f;
		D3DXVECTOR3 front;
		D3DXMATRIX matY;
		D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
		D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
		D3DXVECTOR3 pos = *m_pCharacter->GetPosition();

		if (m_nIndex >= 0)
		{
			D3DXVECTOR3 pos2 = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
			if (m_pSampleMap->GetHeight((pos2 + front * (10.0f - m_fDelta)).x, (pos2 + front * (10.0f - m_fDelta)).z) >= 0.0f)
			{
				m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->SetPosition(pos + front * (10.0f - m_fDelta));
			}
		}

		if (m_fDelta < 0)
		{
			m_bEnemySkillMoving = false;
		}
	}
	else if (m_eCharSelect == CHAR_THREE)
	{
		m_fDeltaY -= 0.5f;
		D3DXVECTOR3 front;
		D3DXMATRIX matY;
		D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
		D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
		D3DXVECTOR3 pos = *m_pCharacter->GetPosition();

		if (m_nIndex >= 0)
		{
			m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->SetPosition(pos + front * 5.0f + D3DXVECTOR3(0, m_fDeltaY, 0));
		}

		if (m_fDeltaY < 0)
		{
			m_bEnemySkillMoving = false;
		}
	}
}

void Character_Sword::TargetSword()
{
	if (m_fElpTime < m_fPrevTime + VskillInterval) return;

	m_fPrevTime = m_fElpTime;

	m_nDamageCount++;

	m_nIndex = -1;

	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
	
	if (m_nDamageCount <= 3)
	{
		for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); i++)
		{
			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn()) continue;
			D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition();
			float length = D3DXVec3Length(&(MonPos - pos));

			if (length <= m_Status->chr.fRange + 15.0f)
			{
				m_nIndex = i;
				D3DXVECTOR3 indexMonsterPos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				D3DXVECTOR3 SkillPos = D3DXVECTOR3(indexMonsterPos.x + FRand(-3, 3), indexMonsterPos.y, indexMonsterPos.z + FRand(-3, 3));
				//맵 밖으로 안나가게 처리
				while (true)
				{
					float y = m_pSampleMap->GetHeight(SkillPos.x, SkillPos.z);
					if (y > 0)
					{
						SkillPos.y = y;
						break;
					}
					else
					{
						SkillPos = D3DXVECTOR3(indexMonsterPos.x + FRand(-3, 3), indexMonsterPos.y, indexMonsterPos.z + FRand(-3, 3));
					}

				}
				m_pCharacter->SetPosition(SkillPos);
				
				m_pCharacter->SetRotation(D3DXVECTOR3(0, GetAngle(*m_pCharacter->GetPosition(), *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition()), 0));
				m_pCharacter->SetAnimation("SKILL");
				m_pParticle4->SetPosition(*m_pCharacter->GetPosition());
				m_pParticle4->TimeReset();
				CAMERA->Shake(0.25, 0.2);
				m_pMonsterManager->DamageMonster(m_nIndex, 999);
				break;
			}
		}
	}

}

void Character_Sword::velvetFinalSKILL()
{
	m_pCharacter->SetAnimation("SKILL");
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();


	if (m_nIndex < 0) return;

	D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
	ST_EFFECT tempEffect;
	ZeroMemory(&tempEffect, sizeof(tempEffect));

	tempEffect.time = FRand(0.1, 0.4);
	tempEffect.isRY = true;
	tempEffect.isRX = true;
	tempEffect.height = 3.0f;
	tempEffect.SetAlpha(FRand(100, 255), FRand(100, 255), 0);
	tempEffect.SetScale(FRand(1.4, 3.0), FRand(1.4, 3.0), FRand(1.4, 3.0));
	tempEffect.tex = TEXTUREMANAGER->AddTexture("Blood", "Texture/Effect/velvet.png");
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
	//m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
	
	m_nVelvetCount++;

	if (m_nVelvetCount <= 2)
	{
		m_pMonsterManager->DamageMonster(m_nIndex, m_Status->chr.nAtk + 10 + m_pInventory->GetEquipStat().item.nAtk);
		m_pCharacter->SetShaderRimColor(D3DXVECTOR3(255, 0, 0));
		m_pCharacter->SetShaderRimPower(0.2f);
	}
	if (m_nVelvetCount > 2 && m_nVelvetCount <= 4)
	{
		m_pMonsterManager->DamageMonster(m_nIndex, m_Status->chr.nAtk + 20 + m_pInventory->GetEquipStat().item.nAtk);
		m_pCharacter->SetShaderRimColor(D3DXVECTOR3(255, 0, 0));
		m_pCharacter->SetShaderRimPower(0.5f);
	}
	if (m_nVelvetCount > 4 && m_nVelvetCount <= 6)
	{
		m_pMonsterManager->DamageMonster(m_nIndex, m_Status->chr.nAtk + 80 + m_pInventory->GetEquipStat().item.nAtk);
		m_pCharacter->SetShaderRimColor(D3DXVECTOR3(255, 0, 0));
		m_pCharacter->SetShaderRimPower(0.8f);
	}
	if (m_nVelvetCount >= 7)
	{
		m_bIsVelvetFinal = true;
		m_pMonsterManager->DamageMonster(m_nIndex, m_Status->chr.nAtk + 300 + m_pInventory->GetEquipStat().item.nAtk);
		m_pCharacter->SetShaderRimColor(D3DXVECTOR3(255, 0, 0));
		m_pCharacter->SetShaderRimPower(1.0f);
		m_Status->chr.fSpeed = m_Status->chr.fSpeed + 0.3f;
	}
}

void Character_Sword::VelvetCount()
{
	if (m_bIsVelvetFinal)
	{
		if (m_fElpTime < m_fPrevTime + m_fVelvetInterval) return;

		m_fPrevTime = m_fElpTime;

		m_nVelvetEnd++;

		if (m_nVelvetEnd == 1)
		{
			m_bIsVelvetFinal = false;
			m_pCharacter->SetShaderRimColor(D3DXVECTOR3(0, 0, 0));
			m_pCharacter->SetShaderRimPower(0.0f);
			m_Status->chr.fSpeed = 0.32f;
			m_nVelvetCount = 0;
			m_nVelvetEnd = 0;
		}
	}
}