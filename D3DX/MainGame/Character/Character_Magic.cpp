#include "../../stdafx.h"
#include "Character_Magic.h"
#include "../Map.h"
#include "Inventory.h"
#include "../Status.h"


Character_Magic::Character_Magic()
{
}


Character_Magic::~Character_Magic()
{
}


void Character_Magic::Init(Map * map, CHARSELECT order, MonsterManager* pMonsterManager)
{
	m_eChrType = CHRTYPE_MAGIC;

	if (order == CHAR_ONE)
	{
		//���� ��ĳ
		m_pCharacter = MODELMANAGER->GetModel("��ī��", MODELTYPE_X);
		//
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
		CharacterParant::Init(map, order, pMonsterManager);

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("��ī��_����"));
		m_pUIobj->SetPosition(D3DXVECTOR3(1300, 550, 0));

	
	}
	else if (order == CHAR_TWO)
	{
		//���� ��ĳ
		m_pCharacter = MODELMANAGER->GetModel("�콺Ƽ��", MODELTYPE_X);
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
		CharacterParant::Init(map, order, pMonsterManager);

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("�콺Ƽ��_����"));
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

		//��Ʈ����Ʈ 
		m_pUIobj->Render();
		m_pHPBar->Render();
		m_pStaminaBar->Render();
		AppearDamage();

		CharacterParant::Render();
	}
}

void Character_Magic::KeyControl()
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

	//�����̵� ����
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


