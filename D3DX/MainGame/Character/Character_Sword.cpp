#include "../../stdafx.h"
#include "Character_Sword.h"
#include "../Map.h"
#include "Inventory.h"
#include "../Status.h"
#include "Character_Shield.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../DamageUI.h"


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
		m_Status->chr.fRange = 3.0f;
		m_Status->chr.fScale = 5.0f;

		// 
		m_bIsFskill = false;
		m_fDeltaY = 3.0f;
		m_fDelta = 5.0f;
		//

		CharacterParant::Init(type, order);

		m_pSkillBar->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_��ųâ"));
		m_pSkillBar->SetPosition(D3DXVECTOR3(588, 695, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(609, 733, 0));

		m_pInheritateIco2->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
		m_pInheritateIco2->SetPosition(D3DXVECTOR3(722, 733, 0));

		m_pInheritateIco3->SetTexture(TEXTUREMANAGER->GetTexture("����_�̵�����"));
		m_pInheritateIco3->SetPosition(D3DXVECTOR3(839, 733, 0));

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_�������ͽ�"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 668, 0));


		//��Ʈ����Ʈ UI
		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("��ī_����"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));


	}
	else if (order == CHAR_TWO)
	{
		//��Į��ĳ
		m_pCharacter = MODELMANAGER->GetModel("����", MODELTYPE_X);
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


		m_pSkillBar->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_��ųâ"));
		m_pSkillBar->SetPosition(D3DXVECTOR3(588, 695, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(609, 733, 0));

		m_pInheritateIco2->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
		m_pInheritateIco2->SetPosition(D3DXVECTOR3(722, 733, 0));

		m_pInheritateIco3->SetTexture(TEXTUREMANAGER->GetTexture("����_�̵�����"));
		m_pInheritateIco3->SetPosition(D3DXVECTOR3(839, 733, 0));

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_�������ͽ�"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 668, 0));


		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));
	}
	else if (order == CHAR_THREE)
	{
		//������ ��ĳ
		m_pCharacter = MODELMANAGER->GetModel("����", MODELTYPE_X);
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



		m_pSkillBar->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_��ųâ"));
		m_pSkillBar->SetPosition(D3DXVECTOR3(588, 695, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(609, 733, 0));

		m_pInheritateIco2->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
		m_pInheritateIco2->SetPosition(D3DXVECTOR3(722, 733, 0));

		m_pInheritateIco3->SetTexture(TEXTUREMANAGER->GetTexture("����_�̵�����"));
		m_pInheritateIco3->SetPosition(D3DXVECTOR3(839, 733, 0));

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_�������ͽ�"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 668, 0));


		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
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
		m_pInheritateIco3->Update();
		m_pSkillBar->Update();




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
			if (m_eCharSelect == CHAR_ONE) //��ī
			{
				this->Shunpo();
			}
			else if (m_eCharSelect == CHAR_TWO) //����
			{
				this->Bash();
			}
			else if (m_eCharSelect == CHAR_THREE) //����
			{
				this->GrabSlash();
			}
			else return;

		}

		Effect();



		PlayerProgressBar();


		m_pDamage->Update(*m_pCharacter->GetPosition());


	}
	CutScene();
	KeyControl();


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




		m_pDamage->Render();
		CharacterParant::Render();
		//��Ʈ����Ʈ 
		m_pUIobj->Render();
		m_pInventory->Render();
		m_pSkillBar->Render();
		m_pInheritateIco->Render();
		m_pInheritateIco2->Render();
		m_pInheritateIco3->Render();
		m_pHPBar->Render();
		m_pStaminaBar->Render();

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


	//������ų ����======================================

	//����ĳ���� ����
	if (INPUT->KeyDown('R'))
	{
		if (!m_bIsSubChr)
		{
			m_bIsSubChr = true;
			CAMERA->Shake(0.2f, 0.5f);
		}
	}

	if (INPUT->KeyDown('F'))
	{
		m_eCondition = CHAR_SKILL;
		m_bIsFskill = true;
		m_nDamageCount = 0;
		m_nDC = 0;
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

		if (m_eCharSelect == CHAR_THREE)
		{
			m_fDeltaY = 3.0f;
		}
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

				//TODO : ���İ��� ��������, �����ϵ� �������� RND�Ἥ ����
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
				m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
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
			m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
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
			m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
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
			//TODO : ���İ��� ��������, �����ϵ� �������� RND�Ἥ ����
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

			tempEffect.time = FRand(0.1, 0.1);
			//tempEffect.isRY = true;
			tempEffect.isRX = true;
			tempEffect.dir = front;
			tempEffect.height = 3.0f;
			tempEffect.SetSpeed(1.0, 1.0, 1.0);
			//TODO : ���İ��� ��������, �����ϵ� �������� RND�Ἥ ����
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
			tempEffect.height = 3.0f;
			tempEffect.SetSpeed(1.0, 1.0, 1.0);
			//TODO : ���İ��� ��������, �����ϵ� �������� RND�Ἥ ����
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
				if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn()) continue;
				D3DXVECTOR3 s1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().center;
				D3DXVECTOR3 s2 = m_vecEffect.back()->GetBoundSphere().center;
				D3DXVECTOR3 v = s1 - s2;
				float distance = D3DXVec3Length(&v);

				float r1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
				float r2 = m_vecEffect.back()->GetBoundSphere().radius;

				if (r1 + r2 >= distance)
				{
					m_pMonsterManager->GetMonsterVector()[i]->CalculDamage(1);
					m_nIndex = i;
					D3DXVECTOR3 front;
					D3DXMATRIX matY;
					D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
					D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
					D3DXVECTOR3 pos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();

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
				if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn()) continue;
				D3DXVECTOR3 s1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().center;
				D3DXVECTOR3 s2 = m_vecEffect.back()->GetBoundSphere().center;
				D3DXVECTOR3 v = s1 - s2;
				float distance = D3DXVec3Length(&v);

				float r1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
				float r2 = m_vecEffect.back()->GetBoundSphere().radius;

				if (r1 + r2 >= distance)
				{
					m_fDelta -= 1.0f;
					m_pMonsterManager->GetMonsterVector()[i]->CalculDamage(1);
					m_nIndex = i;
					D3DXVECTOR3 front;
					D3DXMATRIX matY;
					D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
					D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
					D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
					//m_pCharacter->SetPosition(pos - front * 5);
					m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->SetPosition(pos + front * (10.0f - m_fDelta));
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
			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn()) continue;
			D3DXVECTOR3 s1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().center;
			D3DXVECTOR3 s2 = m_vecEffect.back()->GetBoundSphere().center;
			D3DXVECTOR3 v = s1 - s2;
			float distance = D3DXVec3Length(&v);

			float r1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
			float r2 = m_vecEffect.back()->GetBoundSphere().radius;

			if (r1 + r2 >= distance)
			{
				m_fDeltaY -= 0.5f;
				m_pMonsterManager->GetMonsterVector()[i]->CalculDamage(1);
				m_nIndex = i;
				D3DXVECTOR3 front;
				D3DXMATRIX matY;
				D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
				D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
				D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
				//m_pCharacter->SetPosition(pos - front*4);
				/*if (m_fDeltaY <= 0.0f)
				{
				m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->SetPosition(pos + front * 5.0f);
				}
				else
				{*/
				m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->SetPosition(pos + front * 5.0f + D3DXVECTOR3(0, m_fDeltaY, 0));
				//}

			}

		}
	}

}









