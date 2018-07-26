#include "../../stdafx.h"
#include "../Map.h"
#include "Inventory.h"
#include "../Status.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../DamageUI.h"
#include "Character_fist.h"
#include "Npc.h"



Character_fist::Character_fist()
{
}


Character_fist::~Character_fist()
{
}

void Character_fist::Init(CHRTYPE type, CHARSELECT order)
{
	m_eChrType = CHRTYPE_FIST;

	if (order == CHAR_ONE)
	{
		m_pCharacter = MODELMANAGER->GetModel("파이란", MODELTYPE_X);
	
		m_pFistBody[FISTBODY_LEFTHAND] = m_pCharacter->GetBoneMatrix("Bip001-L-Hand");
		m_pFistBody[FISTBODY_RIGHTHAND] = m_pCharacter->GetBoneMatrix("Bip001-R-Hand");
		m_pFistBody[FISTBODY_LEFTLEG] = m_pCharacter->GetBoneMatrix("Bip001-L-Foot");
		m_pFistBody[FISTBODY_RIGHTLEG] = m_pCharacter->GetBoneMatrix("Bip001-R-Foot");


		m_eNumTarget = NUM_SINGLE;
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
		m_Status->chr.fRange = 3.0f;
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
		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("파이란_사진"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));

	}


	m_fAttackInterval = 0.7f;

	//for (int i = 0; i < FISTBODY_END; i++)
	//{
	//	D3DXVECTOR3 temp(0, 0, 0);
	//	D3DXVec3TransformCoord(&temp, &temp, m_pFistBody[i]);
	//	m_stBound[i].center = temp;
	//	m_stBound[i].radius = 0.5f;
	//}

}

void Character_fist::Update()
{
	if (m_pCharacter)
	{
		Controller();

		if (!m_bIsStun)KeyControl();
		Move();
		//Attack();
		m_pInventory->Update();
		m_pCharacter->World();
		m_pUIobj->Update();
		m_pChrStat->Update();
		m_pTalkBar->Update();
		m_pInheritateIco->Update();
		m_pInheritateIco2->Update();
		if (m_bSkillUnSealed) m_pInheritateIco3->Update();
		m_pSkillBar->Update();
		Effect();
		SetCameraNormalView();
		PlayerProgressBar();
		//CountAppearDamage();
		//m_pDamage->Update(*m_pCharacter->GetPosition());
		
		
		for (int i = 0; i < FISTBODY_END; i++)
		{
			D3DXVECTOR3 temp(0, 0, 0);
			D3DXVec3TransformCoord(&temp, &temp, m_pFistBody[i]);
			m_stBound[i].center = temp;
			m_stBound[i].radius = 0.5f;
		}
	}
}

void Character_fist::Render()
{
	if (m_pCharacter)
	{
		m_pCharacter->Render();
		//CharacterParant::Render();
		

		//포트레이트 

		//m_pDamage->Render();
		//AppearDamage();


		CharacterParant::Render();

		if (!m_pNpc->GetCollision())m_pUIobj->Render();
		if (!m_pNpc->GetCollision())m_pSkillBar->Render();
		if (!m_pNpc->GetCollision())m_pInheritateIco->Render();
		if (!m_pNpc->GetCollision())m_pInheritateIco2->Render();
		if (m_bSkillUnSealed && !m_pNpc->GetCollision()) m_pInheritateIco3->Render();
		if (!m_pNpc->GetCollision())m_pHPBar->Render();
		if (!m_pNpc->GetCollision())m_pStaminaBar->Render();
		if (m_pNpc->GetCollision()) m_pTalkBar->Render();
		Debug();
		m_pInventory->Render();
	}
}

void Character_fist::KeyControl()
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
			//SetTarget();
		
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
			Attack();
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
			Attack();
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

void Character_fist::Attack()
{

	if (m_fElpTime < m_fPrevTime + m_fAttackInterval) return;

	m_fPrevTime = m_fElpTime;
	
	//m_nDamageCount++;

	//if (m_nDamageCount <= 1)
	
		for (int i = 0; i < FISTBODY_END; i++)
		{
			for (int j = 0; j < m_pMonsterManager->GetMonsterVector().size(); j++)
			{
				if (m_pMonsterManager->GetMonsterVector()[j]->GetIsResPawn()) continue;
				if (IntersectSphere(m_stBound[i], m_pMonsterManager->GetMonsterVector()[j]->GetModel()->GetBoundSphere()))
				{
					m_pMonsterManager->GetMonsterVector()[j]->CalculDamage(10);
					

					ST_EFFECT tempEffect;
					ZeroMemory(&tempEffect, sizeof(tempEffect));
					tempEffect.time = FRand(3, 5);
					tempEffect.height = 1.0f;
					tempEffect.SetAlpha(255, 255, 0);
					tempEffect.SetScale(1,1,1);
					tempEffect.tex = TEXTUREMANAGER->GetTexture("숫자0");

					EffectObject* tempEFOBJ;
					tempEFOBJ = new EffectObject;
					D3DXVECTOR3 testSkillpos = m_stBound[i].center;
					tempEFOBJ->Init(tempEffect, testSkillpos);
					m_vecEffect.push_back(tempEFOBJ);
				}
			}
		}

}

void Character_fist::Debug()
{
	//if (DEBUG)
	//{
		DWORD prevFillMode;
		DEVICE->GetRenderState(D3DRS_FILLMODE, &prevFillMode);
		DEVICE->SetTexture(0, NULL);
		DEVICE->SetRenderState(D3DRS_LIGHTING, false);
		DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		// BoundSphere
		LPD3DXMESH mesh;
		D3DXMATRIX matT;

		for (int i = 0; i < FISTBODY_END; i++)
		{
			float radius = m_stBound[i].radius;
			if (radius < 0) radius = 0;
			D3DXCreateSphere(DEVICE, radius, 8, 8, &mesh, NULL);
			D3DXVECTOR3 pos = m_stBound[i].center;
			D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);
			DEVICE->SetTransform(D3DTS_WORLD, &matT);
			mesh->DrawSubset(0);
			SAFE_RELEASE(mesh);
		}
		DEVICE->SetRenderState(D3DRS_FILLMODE, prevFillMode);
	//}
}
