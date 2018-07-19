#include "../../stdafx.h"
#include "Character_Sword.h"
#include "../Map.h"
#include "Inventory.h"
#include "../Status.h"
#include "Character_Shield.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"


Character_Sword::Character_Sword()
{
}


Character_Sword::~Character_Sword()
{
}

void Character_Sword::Init(CHRTYPE type, CHARSELECT order)
{
	m_eChrType = CHRTYPE_SWORD;



	if (order == CHAR_ONE)
	{
		//�Ϻ�����ĳ
		m_pCharacter = MODELMANAGER->GetModel("��ī", MODELTYPE_X);

		
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
		m_Status->chr.nCurrentStam = 50;
		m_Status->chr.nDef = 2;
		m_Status->chr.nMaxHp = 10000;
		m_Status->chr.nMaxStam = 50;
		m_Status->chr.fRange = 3.0f;
		m_Status->chr.fScale = 1.0f;
		CharacterParant::Init(type, order);
		
		
		//��Ʈ����Ʈ UI
		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("��ī_����"));
		m_pUIobj->SetPosition(D3DXVECTOR3(1300, 550, 0));

	
	}
	else if (order == CHAR_TWO)
	{
		//��Į��ĳ
		m_pCharacter = MODELMANAGER->GetModel("����", MODELTYPE_X);
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
		m_Status->chr.nCurrentStam = 40;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 40;
		m_Status->chr.fRange = 5.0f;
		m_Status->chr.fScale = 3.2f;
		CharacterParant::Init(type, order);

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
		m_pUIobj->SetPosition(D3DXVECTOR3(1300, 550, 0));

	}
	else if (order == CHAR_THREE)
	{
		//������ ��ĳ
		m_pCharacter = MODELMANAGER->GetModel("����", MODELTYPE_X);
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

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
		m_pUIobj->SetPosition(D3DXVECTOR3(1300, 550, 0));
		
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

		Effect();

		PlayerProgressBar();
		CountAppearDamage();
	}
	CutScene();
	KeyControl();
}

void Character_Sword::Render()
{
	if (m_pCharacter && m_eCondition != CHAR_NONE)
	{
		m_pCharacter->Render();
		m_pInventory->Render();


		if (m_pShieldChr && m_bIsSubChr)
		{
			m_pShieldChr->Render();
		}

		//��Ʈ����Ʈ 
		m_pUIobj->Render();
		m_pHPBar->Render();
		m_pStaminaBar->Render();
		AppearDamage();
		
		CharacterParant::Render();
	}
}

void Character_Sword::KeyControl()
{
	//������ �޸���
	if (INPUT->KeyDown('W'))
	{
		SOUND->Play("FootStep");
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
	//�ڷ� �޸���
	if (INPUT->KeyDown('S'))
	{
		SOUND->Play("FootStep");
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
	//������ �뽬
	if (INPUT->KeyDown('Q'))
	{
		SOUND->Play("FootStep3");
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
	//�ڷ� �뽬
	if (INPUT->KeyDown('E'))
	{
		SOUND->Play("FootStep3");
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

	//�Ϲݰ���
	if (INPUT->KeyDown(VK_SPACE))
	{
		if (m_eCharSelect == CHAR_ONE)
		{
			SOUND->Play("SwordAttack");
			SOUND->Play("��ī_����");
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			SOUND->Play("SwordAttack_TWO");
			SOUND->Play("����_����");
		}
		if (m_eCharSelect == CHAR_THREE)
		{
			SOUND->Play("SwordAttack_THREE");
			SOUND->Play("����_����");
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

	//��ų����
	if (INPUT->KeyDown('K'))
	{
		SKill();
	}

	//����ĳ���� ����
	if (INPUT->KeyDown('T'))
	{
		m_bIsSubChr = true;
	}


	//�ִϸ��̼� �ѹ��� ������ ��������
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


	//�ǰ� ���߿� ���� �����ϰ� �����
	if (m_eCondition == CHAR_HIT)
	{
		if (m_eCharSelect == CHAR_ONE)
		{
			if (!SOUND->IsPlaySound("��ī_�ǰ�")) SOUND->Play("��ī_�ǰ�");
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			if (m_bIsUnderAttacked)
			{
				if (!SOUND->IsPlaySound("����_�ǰ�")) SOUND->Play("����_�ǰ�");
			}
		}
		if (m_eCharSelect == CHAR_THREE)
		{
			if (!SOUND->IsPlaySound("����_�ǰ�")) SOUND->Play("����_�ǰ�");
		}
		if (INPUT->KeyDown(VK_SPACE))
		{
			m_eCondition = CHAR_ATTACK;
			m_bIsAttack = true;
			//Attack();
			ChangeAnimation();
		}
		

	}

	//�뽬�϶� �ִϸ��̼� ���ǵ� ����
	if (m_eCondition == CHAR_DASH_FRONT || m_eCondition == CHAR_DASH_BACK)
	{
		m_pCharacter->SetAnimationSpeed(5.0f);
	}

	//���ݻ����϶� �ִϸ��̼� ���ǵ� ����
	if (m_eCondition == CHAR_ATTACK)
	{
		m_pCharacter->SetAnimationSpeed(1.0f * (m_Status->chr.fAtkSpeed + m_pInventory->GetEquipStat().chr.fAtkSpeed));
	}

	//���ݻ��½� ���� ����.
	if (m_eCondition == CHAR_ATTACK)
	{
		Attack();
	}

	if (m_eCondition == CHAR_IDLE)
	{
		if(SOUND->IsPlaySound("FootStep")) SOUND->Stop("FootStep");
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

}

void Character_Sword::Attack()
{
	if (m_nIndex < 0) return;
	D3DXVECTOR3 front;
	D3DXMATRIX matY;
	D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
	D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
	D3DXVECTOR3 v0 = front;
	//������
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

				//TODO : ���İ��� ��������, �����ϵ� �������� RND�Ἥ ����
				tempEffect.SetAlpha(FRand(100,255), FRand(100, 255), 0);
				tempEffect.SetScale(FRand(1.4, 3.0), FRand(1.4, 3.0), FRand(1.4, 3.0));
				tempEffect.tex = TEXTUREMANAGER->AddTexture("testSkill", "Texture/Effect/TestSkill.png");
				EffectObject* tempEFOBJ;
				tempEFOBJ = new EffectObject;


				D3DXVECTOR3 TempDir;
				TempDir = *m_pCharacter->GetPosition() - *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				D3DXVec3Normalize(&TempDir, &TempDir);

				float Length = D3DXVec3Length(&(MonPos - pos));

				D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				testSkillpos.y += 1.0f;
				testSkillpos.x += FRand(-0.5, 0.5);
				testSkillpos.z += FRand(-0.3, 0.3);
				testSkillpos += TempDir * (Length * 0.3f);
				tempEFOBJ->Init(tempEffect, testSkillpos);

				m_vecEffect.push_back(tempEFOBJ);
				

				for (int i = 0; i <m_vecTarget.size(); i++)
				{
					if (m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->GetIsResPawn())return;
					m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
				}
			}
		}
		else if (m_eCharSelect == CHAR_TWO)
		{
			if (m_nDamageCount <= 3)
			{
				ST_EFFECT tempEffect;
				ZeroMemory(&tempEffect, sizeof(tempEffect));

				tempEffect.time = FRand(0.1, 0.4);
				//tempEffect.isRY = true;
				tempEffect.isRX = true;
				tempEffect.height = 3.0f;
				tempEffect.SetAlpha(255, 255, 0);
				tempEffect.SetScale(2, 2, 2);
				tempEffect.tex = TEXTUREMANAGER->AddTexture("Step", "Texture/Effect/step.png");
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
		else if (m_eCharSelect == CHAR_THREE)
		{
			if (m_nDamageCount <= 20)
			{
				ST_EFFECT tempEffect;
				ZeroMemory(&tempEffect, sizeof(tempEffect));

				tempEffect.time = FRand(0.1, 0.4);
				//tempEffect.isRY = true;
				tempEffect.isRX = true;
				tempEffect.height = 3.0f;
				tempEffect.SetAlpha(255, 255, 0);
				tempEffect.SetScale(2, 2, 2);
				tempEffect.tex = TEXTUREMANAGER->AddTexture("Blood", "Texture/Effect/velvet.png");
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




