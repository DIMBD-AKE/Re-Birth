#include "../../stdafx.h"
#include "Character_Magic.h"
#include "../Map.h"
#include "Inventory.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../DamageUI.h"

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
		//���� ��ĳ
		m_pCharacter = MODELMANAGER->GetModel("��ī��", MODELTYPE_X);
	
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
		m_Status->chr.nCurrentStam = 10;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 10;
		m_Status->chr.fRange = 15.0f;
		m_Status->chr.fScale = 10.0f;
		CharacterParant::Init(type, order);

		m_pSkillBar->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_��ųâ"));
		m_pSkillBar->SetPosition(D3DXVECTOR3(588, 695, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("����_�̵�"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(609, 733, 0));

		m_pInheritateIco2->SetTexture(TEXTUREMANAGER->GetTexture("����_���̽�"));
		m_pInheritateIco2->SetPosition(D3DXVECTOR3(722, 733, 0));

		m_pInheritateIco3->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
		m_pInheritateIco3->SetPosition(D3DXVECTOR3(839, 733, 0));

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_�������ͽ�"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 668, 0));

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("��ī��_����"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));
	
	}
	else if (order == CHAR_TWO)
	{
		//���� ��ĳ
		m_pCharacter = MODELMANAGER->GetModel("�콺Ƽ��", MODELTYPE_X);

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
		m_Status->chr.nCurrentStam = 10;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 10;
		m_Status->chr.fRange = 10.0f;
		m_Status->chr.fScale = 15.2f;
		CharacterParant::Init(type, order);


		m_pSkillBar->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_��ųâ"));
		m_pSkillBar->SetPosition(D3DXVECTOR3(588, 695, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("����_�̵�"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(609, 733, 0));

		m_pInheritateIco2->SetTexture(TEXTUREMANAGER->GetTexture("����_���̾"));
		m_pInheritateIco2->SetPosition(D3DXVECTOR3(722, 733, 0));

		m_pInheritateIco3->SetTexture(TEXTUREMANAGER->GetTexture("����_���׿�"));
		m_pInheritateIco3->SetPosition(D3DXVECTOR3(839, 733, 0));

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_�������ͽ�"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 668, 0));
		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("�콺Ƽ��_����"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));

	
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
		m_pChrStat->Update();
		m_pInheritateIco->Update();
		m_pInheritateIco2->Update();
		m_pInheritateIco3->Update();
		m_pSkillBar->Update();

		PlayerProgressBar();
		//CountAppearDamage();
		m_pDamage->Update(*m_pCharacter->GetPosition());
	}
}

void Character_Magic::Render()
{
	if (m_pCharacter)
	{
		m_pCharacter->Render();
		m_pInventory->Render();

		
		m_pDamage->Render();
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
}

void Character_Magic::KeyControl()
{
	//������ �޸���
	if (INPUT->KeyDown('W'))
	{
		SOUND->Play("FootStep2");
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
	//�ڷ� �޸���
	if (INPUT->KeyDown('S'))
	{
		SOUND->Play("FootStep2");
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
	//������ �뽬
	if (INPUT->KeyDown('Q'))
	{
		SOUND->Stop("FootStep2");
		SOUND->Play("FootStep3");
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
	//�ڷ� �뽬
	if (INPUT->KeyDown('E'))
	{
		SOUND->Stop("FootStep2");
		SOUND->Play("FootStep3");
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

	//�Ϲݰ���
	if (INPUT->KeyDown(VK_SPACE))
	{
		if(m_eCharSelect == CHAR_ONE)
		{
			SOUND->Play("SwordAttack");
			SOUND->Play("��ī��_����");
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			SOUND->Play("SwordAttack");
			SOUND->Play("�콺Ƽ��_����");
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
			if (!SOUND->IsPlaySound("��ī��_�ǰ�")) SOUND->Play("��ī��_�ǰ�");
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			if (!SOUND->IsPlaySound("�콺Ƽ��_�ǰ�")) SOUND->Play("�콺Ƽ��_�ǰ�");
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

	if (m_eCondition == CHAR_ATTACK)
	{
		Attack();
	}

	if (m_eCondition == CHAR_IDLE)
	{
		if (SOUND->IsPlaySound("FootStep2")) SOUND->Stop("FootStep2");
		if (SOUND->IsPlaySound("FootStep3")) SOUND->Stop("FootStep3");
	}


	// ������ ��ų����
	if (INPUT->KeyDown('K'))
	{
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_SKILL;

			m_bIsSkill = true;
			ChangeAnimation();
		}
	}



	//===========������ų ����==========================//
	//���̽��������� or ���̾
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

	//�����̵� ����
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


				
				//tempEffect.dir = D3DXVECTOR3(0, 0, 1); ������ �ְ�
				//tempEffect.SetSpeed(3, 3, 3); ���ǵ� �ְ� 
				//tempEffect.time = FRand(0.1, 0.4) + 5; Ÿ�� �ǵ���ָ� �پ��ϰ� Ȱ�� ����.(���ǵ� ���ָ� �����ð����� ��ġ������ ��밡��)


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
		{	// �ü�
			D3DXVECTOR3 front;
			D3DXMATRIX matY;
			D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
			D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
			D3DXVECTOR3 v0 = front;
			// ������
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
	tempEffect.tex = TEXTUREMANAGER->GetTexture("���̾_����");
	EffectObject* tempEFOBJ;
	tempEFOBJ = new EffectObject;

	//tempEffect.dir = D3DXVECTOR3(0, 0, 1); ������ �ְ�
	//tempEffect.SetSpeed(3, 3, 3); ���ǵ� �ְ� 
	//tempEffect.time = FRand(0.1, 0.4) + 5; Ÿ�� �ǵ���ָ� �پ��ϰ� Ȱ�� ����.(���ǵ� ���ָ� �����ð����� ��ġ������ ��밡��)


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
		{	// �ü�
			D3DXVECTOR3 front;
			D3DXMATRIX matY;
			D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
			D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
			D3DXVECTOR3 v0 = front;
			// ������
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
		tempEffect.tex = TEXTUREMANAGER->GetTexture("����");
	
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
		{	// �ü�
			D3DXVECTOR3 front;
			D3DXMATRIX matY;
			D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
			D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
			D3DXVECTOR3 v0 = front;
			// ������
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
	tempEffect.tex = TEXTUREMANAGER->GetTexture("���̾_����");
	EffectObject* tempEFOBJ;
	tempEFOBJ = new EffectObject;

	//tempEffect.dir = D3DXVECTOR3(0, 0, 1); ������ �ְ�
	//tempEffect.SetSpeed(3, 3, 3); ���ǵ� �ְ� 
	//tempEffect.time = FRand(0.1, 0.4) + 5; Ÿ�� �ǵ���ָ� �پ��ϰ� Ȱ�� ����.(���ǵ� ���ָ� �����ð����� ��ġ������ ��밡��)


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
	//�̵���ƼŬ Ű���� ���� 
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


