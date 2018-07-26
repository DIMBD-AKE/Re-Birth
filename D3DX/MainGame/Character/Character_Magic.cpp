#include "../../stdafx.h"
#include "Character_Magic.h"
#include "../Map.h"
#include "Inventory.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "Npc.h"
#include "../DamageUI.h"

Character_Magic::Character_Magic()
{
}


Character_Magic::~Character_Magic()
{
	SAFE_DELETE(m_pMeteorPaticle);
	SAFE_DELETE(m_pMegaCristalPaticle);
	SAFE_DELETE(m_pMeteorAfterPaticle);
}


void Character_Magic::Init(CHRTYPE type, CHARSELECT order)
{
	m_eChrType = CHRTYPE_MAGIC;

	if (order == CHAR_ONE)
	{
		//법사 남캐
		m_pCharacter = MODELMANAGER->GetModel("아카날", MODELTYPE_X);
	
		m_eNumTarget = NUM_SINGLE;
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
		m_Status->chr.nCurrentStam = 100;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 100;
		m_Status->chr.fRange = 15.0f;
		m_Status->chr.fScale = 10.0f;
		CharacterParant::Init(type, order);

		//매직실드 이미지
		if (m_pMagicShield == NULL) m_pMagicShield = new UIObject;
		m_pMagicShield->SetTexture(TEXTUREMANAGER->GetTexture("실드_마법"));
		m_pMagicShield->SetPosition(*m_pCharacter->GetPosition() - m_vfront * 1.0f);


		m_pSkillBar->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스킬창"));
		m_pSkillBar->SetPosition(D3DXVECTOR3(588, 695, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("마법_이동"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(609, 733, 0));

		m_pInheritateIco2->SetTexture(TEXTUREMANAGER->GetTexture("마법_아이스"));
		m_pInheritateIco2->SetPosition(D3DXVECTOR3(722, 733, 0));

		m_pInheritateIco3->SetTexture(TEXTUREMANAGER->GetTexture("마법_메테오"));
		m_pInheritateIco3->SetPosition(D3DXVECTOR3(839, 733, 0));

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스테이터스"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 668, 0));

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("아카날_사진"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));

	}
	else if (order == CHAR_TWO)
	{
		//법사 여캐
		m_pCharacter = MODELMANAGER->GetModel("헤스티아", MODELTYPE_X);

		m_eNumTarget = NUM_SINGLE;
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
		m_Status->chr.nCurrentStam = 100;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 100;
		m_Status->chr.fRange = 10.0f;
		m_Status->chr.fScale = 15.2f;
		CharacterParant::Init(type, order);


		m_pSkillBar->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스킬창"));
		m_pSkillBar->SetPosition(D3DXVECTOR3(588, 695, 0));


		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("마법_이동"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(609, 733, 0));
		m_pInheritateIco->SetName("마법_이동");
		//m_pInheritateIco->SetFunction(this)


		m_pInheritateIco2->SetTexture(TEXTUREMANAGER->GetTexture("마법_파이어볼"));
		m_pInheritateIco2->SetPosition(D3DXVECTOR3(722, 733, 0));

		m_pInheritateIco3->SetTexture(TEXTUREMANAGER->GetTexture("마법_메테오"));
		m_pInheritateIco3->SetPosition(D3DXVECTOR3(839, 733, 0));

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스테이터스"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 668, 0));
		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("헤스티아_사진"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));

	
	}

	m_nMagicCount = 0;
	m_pMeteorPaticle = PARTICLE->GetParticle("Meteor"); //메테오 파티클
	m_pMegaCristalPaticle = PARTICLE->GetParticle("MegaCristal"); //메가 크리스탈 파티클
	m_pMeteorAfterPaticle = PARTICLE->GetParticle("MeteorAfter");	//메테오 잔열 파티클


	m_bIsFire = false;
}

void Character_Magic::Update()
{
	if (m_pCharacter && !m_bIsMeteo &&!m_bIsMegaCristal)
	{
		Controller();
		SetCameraNormalView();
		Move();
		MgSkill();
		if(!m_bIsStun)KeyControl();
		CharacterParant::Update();
		SetModelAlpha();
		m_pInventory->Update();
		m_pCharacter->World();
		m_pUIobj->Update();
		m_pChrStat->Update();
		m_pTalkBar->Update();
		m_pInheritateIco->Update();
		m_pInheritateIco2->Update();
		if(m_bSkillUnSealed)m_pInheritateIco3->Update();
		m_pSkillBar->Update();
		PlayerProgressBar();
		//m_pDamage->Update(*m_pCharacter->GetPosition());
	}
	Effect();
	VskillUpdate();
	MeteorAfter();
	

}

void Character_Magic::Render()
{
	if (m_pCharacter)
	{
		m_pCharacter->Render();
		

		
		//m_pDamage->Render();
		//AppearDamage();

		CharacterParant::Render();

		if (!m_pNpc->GetCollision())m_pUIobj->Render();
		if (!m_pNpc->GetCollision())m_pSkillBar->Render();
		if (!m_pNpc->GetCollision())m_pInheritateIco->Render();
		if (!m_pNpc->GetCollision())m_pInheritateIco2->Render();
		if (m_bSkillUnSealed && !m_pNpc->GetCollision())m_pInheritateIco3->Render();
		if (!m_pNpc->GetCollision())m_pHPBar->Render();
		if (!m_pNpc->GetCollision())m_pStaminaBar->Render();
		if (m_pNpc->GetCollision()) m_pTalkBar->Render();
		if(m_bIsMeteoClick) m_pMeteorPaticle->Render();
		if (m_bIsMegaCirstalClick) m_pMegaCristalPaticle->Render();
		if (m_bIsFire) m_pMeteorAfterPaticle->Render();
		m_pInventory->Render();
	}
}

void Character_Magic::KeyControl()
{
	//앞으로 달리기
	if (INPUT->KeyDown('W'))
	{
		SOUND->Play("FootStep2", g_fVolume);
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_HIT)
		{
			m_eCondition = CHAR_RUN_FRONT;

			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('W'))
	{
		SOUND->Stop("FootStep2");
		if (m_eCondition == CHAR_RUN_FRONT)
		{
			m_eCondition = CHAR_IDLE;

			ChangeAnimation();
		}
	}
	//뒤로 달리기
	if (INPUT->KeyDown('S'))
	{
		SOUND->Play("FootStep2", g_fVolume);
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_HIT)
		{
			m_eCondition = CHAR_RUN_BACK;

			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('S'))
	{
		SOUND->Stop("FootStep2");
		if (m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_IDLE;

			ChangeAnimation();
		}
	}
	//앞으로 대쉬
	if (INPUT->KeyDown('Q'))
	{
		SOUND->Stop("FootStep2");
		SOUND->Play("FootStep3", g_fVolume);
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
		SOUND->Stop("FootStep2");
		SOUND->Play("FootStep3", g_fVolume);
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
			SOUND->Play("SwordAttack", g_fVolume);
			SOUND->Play("아카날_공격", g_fVolume);
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			SOUND->Play("SwordAttack", g_fVolume);
			SOUND->Play("헤스티아_공격", g_fVolume);
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

	//if (m_pNpc->GetCollision())
	//{
	//	m_eCondition = CHAR_TALK;
	//	ChangeAnimation();
	//}
	//if (!m_pNpc->GetCollision())
	//{
	//	m_eCondition = CHAR_IDLE;
	//	ChangeAnimation();
	//}


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
		if (m_eCharSelect == CHAR_ONE)
		{
			if (!SOUND->IsPlaySound("아카날_피격")) SOUND->Play("아카날_피격", g_fVolume);
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			if (!SOUND->IsPlaySound("헤스티아_피격")) SOUND->Play("헤스티아_피격", g_fVolume);
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
		if (SOUND->IsPlaySound("FootStep2")) SOUND->Stop("FootStep2");
		if (SOUND->IsPlaySound("FootStep3")) SOUND->Stop("FootStep3");
	}


	// 아이템 스킬공격
	if (INPUT->KeyDown('K'))
	{
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_SKILL;

			m_bIsSkill = true;
			ChangeAnimation();
		}
	}



	//===========고유스킬 제어==========================//
	//아이스헤지오그 or 파이어볼
	if (INPUT->KeyDown('F'))
	{
		if (m_eCharSelect == CHAR_ONE)
		{
			CristalField();
			m_nDamageCount = 0;
			if (!m_vecTarget.size() <= 0) CAMERA->Shake(0.04f, 0.2f);
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			FireBall();
			m_nDamageCount = 0;
			if (m_nIndex > -1) CAMERA->Shake(0.1f, 0.2f);
		}
	}

	//순간이동 제어
	if (INPUT->KeyDown('R'))
	{
		m_bIsPotal = true;
	}
	else if (INPUT->KeyUp('R'))
	{
		m_bIsPotal = false;
		m_pCharacter->SetPosition(D3DXVECTOR3(m_pParticle3->GetPosition()->x + 1.0f, m_pParticle3->GetPosition()->y, m_pParticle3->GetPosition()->z - 1.0f));
		m_pParticle4->SetPosition(*m_pCharacter->GetPosition());
		m_pParticle4->TimeReset();
		CAMERA->Shake(0.1f, 0.7f);
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

	//메테오 제어 
	if (m_bSkillUnSealed)
	{
		if (INPUT->KeyDown('V'))
		{

			if (m_Status->chr.nCurrentStam >= 90.0f)
			{
				m_Status->chr.nCurrentStam -= 90.0f;
				if (m_eCharSelect == CHAR_ONE)
				{
					m_bIsMegaCristal = true;
				}
				if (m_eCharSelect == CHAR_TWO)
				{
					m_bIsMeteo = true;
				}
			}
		}
	}
	
}



void Character_Magic::Attack()
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

				tempEffect.time = FRand(0.1, 0.4)+5;
				tempEffect.isRY = true;
				tempEffect.isRX = true;
				tempEffect.dir = D3DXVECTOR3(1, 0, 0);
				tempEffect.height = 3.0f;
				tempEffect.SetAlpha(255, 255, 0);
				tempEffect.SetScale(1, 0.8, 0.8);
				tempEffect.tex = TEXTUREMANAGER->AddTexture("akanal", "Texture/Effect/akanal.png");
				EffectObject* tempEFOBJ;
				tempEFOBJ = new EffectObject;


				
				//tempEffect.dir = D3DXVECTOR3(0, 0, 1); 방향을 주고
				//tempEffect.SetSpeed(3, 3, 3); 스피드 주고 
				//tempEffect.time = FRand(0.1, 0.4) + 5; 타임 건드려주면 다양하게 활용 가능.(스피드 안주면 일정시간동안 설치형으로 사용가능)


				D3DXVECTOR3 TempDir;
				TempDir = pos - MonPos;
				D3DXVec3Normalize(&TempDir, &TempDir);

				float Length = D3DXVec3Length(&(MonPos - pos));

				D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				testSkillpos.y += 1.0f;
				testSkillpos.x += FRand(-0.5, 0.5);
				testSkillpos.z += FRand(-0.3, 0.3);
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
				tempEffect.SetScale(1, 0.8, 0.8);
				tempEffect.tex = TEXTUREMANAGER->AddTexture("Hestia", "Texture/Effect/Hestia.png");
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

void Character_Magic::targetAttack()
{
	m_nIndex = -1;
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
				m_nIndex = i;
			}
		}
	}
	
	
	if (m_nIndex < 0) return;

	D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
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
	tempEffect.tex = TEXTUREMANAGER->GetTexture("파이어볼_마법");
	EffectObject* tempEFOBJ;
	tempEFOBJ = new EffectObject;

	//tempEffect.dir = D3DXVECTOR3(0, 0, 1); 방향을 주고
	//tempEffect.SetSpeed(3, 3, 3); 스피드 주고 
	//tempEffect.time = FRand(0.1, 0.4) + 5; 타임 건드려주면 다양하게 활용 가능.(스피드 안주면 일정시간동안 설치형으로 사용가능)


	D3DXVECTOR3 testSkillpos = *m_pCharacter->GetPosition();
	testSkillpos.y += 2.0f;
	testSkillpos.x += FRand(-0.5, 0.5);
	testSkillpos.z += FRand(-0.3, 0.3);
	//testSkillpos += TempDir * (Length * 0.3f);
	tempEFOBJ->Init(tempEffect, testSkillpos);

	m_vecEffect.push_back(tempEFOBJ);


	m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(1);
		
}

void Character_Magic::CristalField()
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
	
		if (m_vecTarget.size() <= 0) return;
		
		ST_EFFECT tempEffect;
		ZeroMemory(&tempEffect, sizeof(tempEffect));
		tempEffect.time = FRand(0.4, 0.7);
		tempEffect.isRY = true;
		//tempEffect.isRX = true;
		//tempEffect.isRZ = true;
		//tempEffect.dir = *m_pCharacter->GetRotation();
		//tempEffect.SetSpeed(0, 0.2, 0);
		tempEffect.height = 3.0f;
		tempEffect.SetAlpha(255, 255, 0);
		tempEffect.SetScale(FRand(2,5), FRand(2, 5), 0);
		tempEffect.tex = TEXTUREMANAGER->GetTexture("수정");
	
		for (int j = 0; j < m_vecTarget.size(); j++)
		{
			EffectObject* tempEFOBJ;
			tempEFOBJ = new EffectObject;
			D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_vecTarget[j]]->GetModel()->GetPosition();
			testSkillpos.y -= 1.0f;
			//testSkillpos.x += FRand(-0.5, 0.5);
			//testSkillpos.z += FRand(-0.3, 0.3);
			//testSkillpos += TempDir * (Length * 0.3f);
			tempEFOBJ->Init(tempEffect, testSkillpos);
			m_vecEffect.push_back(tempEFOBJ);
			m_pMonsterManager->GetMonsterVector()[m_vecTarget[j]]->CalculDamage(1);
		}
	
}

void Character_Magic::FireBall()
{
	m_nIndex = -1;
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
				m_nIndex = i;
			}
		}
	}


	if (m_nIndex < 0) return;

	D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
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
	tempEffect.tex = TEXTUREMANAGER->GetTexture("파이어볼_마법");
	EffectObject* tempEFOBJ;
	tempEFOBJ = new EffectObject;

	//tempEffect.dir = D3DXVECTOR3(0, 0, 1); 방향을 주고
	//tempEffect.SetSpeed(3, 3, 3); 스피드 주고 
	//tempEffect.time = FRand(0.1, 0.4) + 5; 타임 건드려주면 다양하게 활용 가능.(스피드 안주면 일정시간동안 설치형으로 사용가능)


	D3DXVECTOR3 testSkillpos = *m_pCharacter->GetPosition();
	testSkillpos.y += 2.0f;
	testSkillpos.x += FRand(-0.5, 0.5);
	testSkillpos.z += FRand(-0.3, 0.3);
	//testSkillpos += TempDir * (Length * 0.3f);
	tempEFOBJ->Init(tempEffect, testSkillpos);

	m_vecEffect.push_back(tempEFOBJ);


	m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(1);

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
		m_pParticle3->ApplyWorld();
		m_pParticle3->Update();

		auto nav = m_pSampleMap->GetNavMesh();
		auto r = RayAtWorldSpace(g_ptMouse);
		float tempdistance;
		for (int i = 0; i < nav.size(); i += 3)
		{
			if (D3DXIntersectTri(&nav[i], &nav[i + 1], &nav[i + 2], &r.orig, &r.dir, NULL, NULL, &tempdistance))
			{
				if (D3DXVec3Length(&(playerTempPos - Potalpos)) < 14.0f)//최대 이동거리 안으로 
				{
					m_pParticle3->SetPosition(r.orig + r.dir* tempdistance);
				}
			}
		}
	}
}

void Character_Magic::MgShield()
{
	
}

void Character_Magic::Meteor()
{
		ST_EFFECT tempEffect1;
		ZeroMemory(&tempEffect1, sizeof(tempEffect1));
		tempEffect1.time = 5;
		tempEffect1.rot = D3DXVECTOR3(90, 0, 0);
		tempEffect1.mot = D3DXVECTOR3(0, 10, 0);
		tempEffect1.ms0 = 9.0f;
		//tempEffect.isRY = true;
		//tempEffect.isRX = true;
		//tempEffect.isRZ = true;
		//tempEffect.dir = *m_pCharacter->GetRotation();
		//tempEffect.SetSpeed(0, 0.2, 0);
		tempEffect1.height = 3.0f;
		tempEffect1.SetAlpha(255, 255, 0);
		tempEffect1.SetScale(5, 5, 0);
		tempEffect1.tex = TEXTUREMANAGER->GetTexture("실드_마법");


		EffectObject* tempEFOBJ1;
		tempEFOBJ1 = new EffectObject;
		D3DXVECTOR3 testSkillpos1 = *m_pCharacter->GetPosition() - m_vfront * 1.0f;
		testSkillpos1.y -= 1.0f;
		//testSkillpos.x += FRand(-0.5, 0.5);
		//testSkillpos.z += FRand(-0.3, 0.3);
		//testSkillpos += TempDir * (Length * 0.3f);
		tempEFOBJ1->Init(tempEffect1, testSkillpos1);
		m_vecEffect.push_back(tempEFOBJ1);


		//메테오
		ST_EFFECT tempEffect;
		ZeroMemory(&tempEffect, sizeof(tempEffect));
		tempEffect.time = 10;
		tempEffect.rot = D3DXVECTOR3(90, 0, 0);
		tempEffect.isRY = true;
		tempEffect.isRX = true;
		tempEffect.isRZ = true;
		tempEffect.dir = D3DXVECTOR3(1, -1, 1);
		tempEffect.SetSpeed(0.05, 1, 0.05);
		tempEffect.height = 3.0f;
		tempEffect.SetAlpha(255, 255, 0);
		tempEffect.SetScale(10, 10, 0);
		tempEffect.tex = TEXTUREMANAGER->GetTexture("메테오");


		

		EffectObject* tempEFOBJ;
		tempEFOBJ = new EffectObject;
		D3DXVECTOR3 testSkillpos = m_vMeteo;
		testSkillpos.y += 60.0f;
		testSkillpos.x += -60.0f;
		testSkillpos.z += -60.0f;
		//testSkillpos += TempDir * (Length * 0.3f);
		tempEFOBJ->Init(tempEffect, testSkillpos);
		m_vecEffect.push_back(tempEFOBJ);
		
		m_pMeteorPaticle->SetPosition(m_vecEffect.back()->GetBoundSphere().center);
		

}

void Character_Magic::MeteorClick()
{
	//메테오 좌표를 받기위한 사전 실행
	D3DXVECTOR3 Potalpos = *m_pParticle3->GetPosition();
	D3DXVECTOR3	playerTempPos = *m_pCharacter->GetPosition();

	
	m_pParticle3->ApplyWorld ();
	m_pParticle3->Update();

	auto nav = m_pSampleMap->GetNavMesh();
	auto r = RayAtWorldSpace(g_ptMouse);
	float tempdistance;
	for (int i = 0; i < nav.size(); i += 3)
	{
		if (D3DXIntersectTri(&nav[i], &nav[i + 1], &nav[i + 2], &r.orig, &r.dir, NULL, NULL, &tempdistance))
		{
			if (D3DXVec3Length(&(playerTempPos - Potalpos)) < 14.0f)//최대 이동거리 안으로 
			{
				m_pParticle3->SetPosition(r.orig + r.dir* tempdistance);
			}
		}
	}
	
}

void Character_Magic::MeteorDamage()
{
	m_vecTarget.clear();
	D3DXVECTOR3 pos = m_vMeteo;

	for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); i++)
	{
		if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn()) continue;
		D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition();
		float length = D3DXVec3Length(&(MonPos - pos));

		if (length <= 50)
		{	
			m_vecTarget.push_back(i);
		}
	}

	for (int j = 0; j < m_vecTarget.size(); j++)
	{
		m_pMonsterManager->GetMonsterVector()[m_vecTarget[j]]->CalculDamage(999);
	}
}

void Character_Magic::MegaCristalReady()
{
	//메가 크리스탈 좌표를 받기위한 사전 실행
	D3DXVECTOR3 Potalpos = *m_pParticle3->GetPosition();
	D3DXVECTOR3	playerTempPos = *m_pCharacter->GetPosition();

	
	m_pParticle3->ApplyWorld();
	m_pParticle3->Update();

	auto nav = m_pSampleMap->GetNavMesh();
	auto r = RayAtWorldSpace(g_ptMouse);
	float tempdistance;
	for (int i = 0; i < nav.size(); i += 3)
	{
		if (D3DXIntersectTri(&nav[i], &nav[i + 1], &nav[i + 2], &r.orig, &r.dir, NULL, NULL, &tempdistance))
		{
			if (D3DXVec3Length(&(playerTempPos - Potalpos)) < 14.0f)//최대 이동거리 안으로 
			{
				m_pParticle3->SetPosition(r.orig + r.dir* tempdistance);
			}
		}
	}

}

void Character_Magic::MegaCristal()
{
	ST_EFFECT tempEffect1;
	ZeroMemory(&tempEffect1, sizeof(tempEffect1));
	tempEffect1.time = 5;
	tempEffect1.rot = D3DXVECTOR3(90, 0, 0);
	tempEffect1.mot = D3DXVECTOR3(0, 10, 0);
	tempEffect1.ms0 = 9.0f;
	//tempEffect.isRY = true;
	//tempEffect.isRX = true;
	//tempEffect.isRZ = true;
	//tempEffect.dir = *m_pCharacter->GetRotation();
	//tempEffect.SetSpeed(0, 0.2, 0);
	tempEffect1.height = 3.0f;
	tempEffect1.SetAlpha(255, 255, 0);
	tempEffect1.SetScale(5, 5, 0);
	tempEffect1.tex = TEXTUREMANAGER->GetTexture("실드_마법");


	EffectObject* tempEFOBJ1;
	tempEFOBJ1 = new EffectObject;
	D3DXVECTOR3 testSkillpos1 = *m_pCharacter->GetPosition() - m_vfront * 1.0f;
	testSkillpos1.y -= 1.0f;
	//testSkillpos.x += FRand(-0.5, 0.5);
	//testSkillpos.z += FRand(-0.3, 0.3);
	//testSkillpos += TempDir * (Length * 0.3f);
	tempEFOBJ1->Init(tempEffect1, testSkillpos1);
	m_vecEffect.push_back(tempEFOBJ1);


	//수정
	for (int i = 0; i < 5; i++)
	{
		ST_EFFECT tempEffect;
		ZeroMemory(&tempEffect, sizeof(tempEffect));
		tempEffect.time = FRand(3, 5);
		//tempEffect.rot = D3DXVECTOR3(90, 0, 0);
		tempEffect.isRY = true;
		//tempEffect.isRX = true;
		//tempEffect.isRZ = true;
		//tempEffect.dir = D3DXVECTOR3(1, -1, 1);
		//tempEffect.SetSpeed(0.05, 1, 0.05);
		tempEffect.height = 3.0f;
		tempEffect.SetAlpha(255, 255, 0);
		tempEffect.SetScale(FRand(7,13), FRand(7, 13), 0);
		tempEffect.tex = TEXTUREMANAGER->GetTexture("수정");

		EffectObject* tempEFOBJ;
		tempEFOBJ = new EffectObject;
		D3DXVECTOR3 testSkillpos = m_vMegaCri;
		testSkillpos.y -= 2.0f;
		testSkillpos.x += FRand(-5, 5);
		testSkillpos.z += FRand(-5, 5);
		tempEFOBJ->Init(tempEffect, testSkillpos);
		m_vecEffect.push_back(tempEFOBJ);

		m_pMegaCristalPaticle->SetPosition(m_vecEffect.back()->GetBoundSphere().center);
	}
}

void Character_Magic::MegaCristalDamage()
{
	m_vecTarget.clear();
	D3DXVECTOR3 pos = m_vMegaCri;

	for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); i++)
	{
		if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn()) continue;
		D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition();
		float length = D3DXVec3Length(&(MonPos - pos));

		if (length <= 30)
		{
			m_vecTarget.push_back(i);
		}
	}

	for (int j = 0; j < m_vecTarget.size(); j++)
	{
		m_pMonsterManager->GetMonsterVector()[m_vecTarget[j]]->CalculDamage(999);
	}
}

void Character_Magic::VskillUpdate()
{

	if (m_bIsMeteo && m_nMagicCount == 0)
	{
		MeteorClick();

		//메테오 상황일때 클릭이 되면 
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			m_vMeteo = *m_pParticle3->GetPosition();
			m_bIsMeteoClick = true;

			Meteor();
			m_nMagicCount += 1;
		}
	}

	if (m_bIsMegaCristal && m_nMagicCount == 0)
	{
		MegaCristalReady();

		if (INPUT->KeyPress(VK_LBUTTON))
		{
			m_vMegaCri = *m_pParticle3->GetPosition();
			m_bIsMegaCirstalClick = true;

			MegaCristal();
			m_nMagicCount += 1;
		}
	}

	if (m_bIsMeteoClick)
	{
		//CAMERA->SetTarget((m_vecEffect.back()->GetPos()), 0);
		if (m_vecEffect.back()->GetBoundSphere().center.y >= 65)
		{
			CAMERA->Shake(0.3, 30);
		}
		else
		{
			MeteorDamage();
			CAMERA->Shake(5.8, 1);
		}
		if (m_vecEffect.back()->GetBoundSphere().center.y <= 61)
		{
			m_bIsMeteoClick = false;
			m_bIsMeteo = false;
			m_bIsFire = true;
			m_nMagicCount = 0;
		}
		m_pMeteorPaticle->SetPosition(m_vecEffect.back()->GetBoundSphere().center);
	}

	if (m_bIsMegaCirstalClick)
	{
		MegaCristalDamage();

		CAMERA->Shake(0.3, 1);

		if (m_vecEffect.back()->IsFinish())
		{
			m_bIsMegaCirstalClick = false;
			m_bIsMegaCristal = false;
			m_nMagicCount = 0;
		}
	}
	m_pMeteorPaticle->ApplyWorld();
	m_pMeteorPaticle->Update();

	m_pMegaCristalPaticle->ApplyWorld();
	m_pMegaCristalPaticle->Update();

	

	
}

void Character_Magic::MeteorAfter()
{
	if (m_bIsFire)
	{
		m_pMeteorAfterPaticle->ApplyWorld();
		m_pMeteorAfterPaticle->Update();
		m_pMeteorAfterPaticle->SetPosition(m_vMeteo);
	
	
		ST_SPHERE particle;
		particle.center = *m_pMeteorAfterPaticle->GetPosition();
		particle.radius = 2;
	
	
		if (IntersectSphere(particle, m_pCharacter->GetBoundSphere()))
		{
			SetCurrentHP(10);
		}
	}
	if (m_pMeteorAfterPaticle->IsDie())
	{
		m_bIsFire = false;
	}
}


