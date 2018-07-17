#include "../../stdafx.h"
#include "Character_Gun.h"
#include "../Map.h"
#include "Inventory.h"
#include "../Status.h"


Character_Gun::Character_Gun()
{
}


Character_Gun::~Character_Gun()
{
}


void Character_Gun::Init(Map * map, CHARSELECT order, MonsterManager* pMonsterManager)
{
	m_eChrType = CHRTYPE_GUN;
	if (order == CHAR_ONE)
	{
		//�ѳ�ĳ
		m_pCharacter = MODELMANAGER->GetModel("�ޱ׳ʽ�", MODELTYPE_X);
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 5.0f;
		m_Status->chr.fCheRate = 70.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 25.0f;
		m_Status->chr.fPhyRate = 25.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 50;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 10;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 10;
		m_Status->chr.fRange = 20.0f;
		m_Status->chr.fScale = 3.2f;
		CharacterParant::Init(map, order, pMonsterManager);

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("�ޱ׳ʽ�_����"));
		m_pUIobj->SetPosition(D3DXVECTOR3(1300, 550, 0));

	
	}
	else if (order == CHAR_TWO)
	{
		//Ȱ��ĳ
		m_pCharacter = MODELMANAGER->GetModel("��ī��", MODELTYPE_X);
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 4.0f;
		m_Status->chr.fCheRate = 70.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 25.0f;
		m_Status->chr.fPhyRate = 25.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 50;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 10;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 10;
		m_Status->chr.fRange = 25.0f;
		m_Status->chr.fScale = 3.2f;
		CharacterParant::Init(map, order, pMonsterManager);

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("��ī��_����"));
		m_pUIobj->SetPosition(D3DXVECTOR3(1300, 550, 0));

	
	}
}

void Character_Gun::Update()
{
	if (m_pCharacter)
	{
		Controller();
		//UnderAttacked();
		KeyControl();
		Move();

		m_pInventory->Update();

		m_pCharacter->World();

		m_pUIobj->Update();

		PlayerProgressBar();
		CountAppearDamage();
	}
}

void Character_Gun::Render()
{
	if (m_pCharacter)
	{
		m_pCharacter->Render();
		//CharacterParant::Render();
		m_pInventory->Render();

		//��Ʈ����Ʈ 
		m_pUIobj->Render();
		m_pHPBar->Render();
		m_pStaminaBar->Render();
		AppearDamage();


		CharacterParant::Render();
	}
}

void Character_Gun::KeyControl()
{
	//������ �޸���
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
	//�ڷ� �޸���
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
	//������ �뽬
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
	//�ڷ� �뽬
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

	//�Ϲݰ���
	if (INPUT->KeyDown(VK_SPACE))
	{
		SOUND->Play("SwordAttack");
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_ATTACK;
		
			m_bIsAttack = true;
			Attack();
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
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_SKILL;
			
			m_bIsSkill = true;
			ChangeAnimation();
		}
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
		}
		ChangeAnimation();
	}


	//�ǰ� ���߿� ���� �����ϰ� �����
	if (m_eCondition == CHAR_HIT)
	{
		if (INPUT->KeyDown(VK_SPACE))
		{
			m_eCondition = CHAR_ATTACK;
			m_bIsAttack = true;
			Attack();
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

	//���� �ֱ�
	if (m_pCharacter->IsAnimationEnd() && m_eCondition == CHAR_DIE)
	{
		m_eCondition = CHAR_NONE;
		m_bIsDead = false;
	}
}


