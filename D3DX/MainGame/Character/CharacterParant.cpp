#include "../../stdafx.h"
#include "CharacterParant.h"
#include "Inventory.h"
#include "../Map.h"
#include "../Status.h"


void CharacterParant::SKill()
{
	//Ư�� Ű�� ������ ������ Ŭ������ skill�� �����Ѵ�. 
}

void CharacterParant::Move()
{
	//�����¿� ���� ������


	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
	D3DXVECTOR3 rot = *m_pCharacter->GetRotation();
	//if (INPUT->KeyPress(VK_LEFT))	rot.y -= 0.05;
	//if (INPUT->KeyPress(VK_RIGHT))	rot.y += 0.05;

	

	D3DXMATRIX matAngle;
	D3DXMatrixRotationYawPitchRoll(&matAngle, m_pCharacter->GetRotation()->y, m_pCharacter->GetRotation()->x, m_pCharacter->GetRotation()->z);

	m_vfront = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vfront, &m_vfront, &matAngle);
	


	if (INPUT->KeyPress('A'))
	{
		m_pCharacter->GetRotation()->y -= 0.05f;
	}
	if (INPUT->KeyPress('D'))
	{
		m_pCharacter->GetRotation()->y += 0.05f;
	}
	//�޸��¸��
	D3DXVECTOR3 vPos = *m_pCharacter->GetPosition();
	if (m_eCondition == CHAR_RUN_FRONT)
	{
		float height = m_pSampleMap->GetHeight(pos.x - m_vfront.x *0.25, pos.z - m_vfront.z *0.25);
		if (height >= 0)
		{
			pos.y = height;
			m_pCharacter->SetPosition(pos - m_vfront * 0.25);
		}
		else
		{

		}
	}
	else if (m_eCondition == CHAR_RUN_BACK)
	{
		float height = m_pSampleMap->GetHeight(pos.x - m_vfront.x *0.15, pos.z - m_vfront.z *0.15);
		if (height >= 0)
		{
			pos.y = height;
			m_pCharacter->SetPosition(pos + m_vfront * 0.15);
		}
		else
		{

		}
	}
	//�뽬��
	if (m_eCondition == CHAR_DASH_FRONT)
	{
		float height = m_pSampleMap->GetHeight(pos.x - m_vfront.x *0.57, pos.z - m_vfront.z *0.57);
		if (height >= 0)
		{
			pos.y = height;
			m_pCharacter->SetPosition(pos - m_vfront * 0.57);
		}
		else
		{

		}
	}
	if (m_eCondition == CHAR_DASH_BACK)
	{
		float height = m_pSampleMap->GetHeight(pos.x - m_vfront.x *0.33, pos.z - m_vfront.z *0.33);
		if (height >= 0)
		{
			pos.y = height;
			m_pCharacter->SetPosition(pos + m_vfront * 0.33);
		}
		else
		{

		}
	}
	ControllStamina();
}

void CharacterParant::Controller()
{
	//===============���Ű ����=====================//
	if (INPUT->KeyDown('I'))
	{
		m_pInventory->OpenInventory();
	}
	if (INPUT->KeyDown('P'))
	{
		m_pInventory->OpenEquip();
	}
	
}

void CharacterParant::Debug()
{
}

void CharacterParant::CheckDirection()
{
	//
}

void CharacterParant::ControllStamina()
{

	if (m_eCondition == CHAR_DASH_FRONT || m_eCondition == CHAR_DASH_BACK)
	{
		m_fStamina -= 0.2f;
	}

	if (m_fStamina <= 0)
	{
		m_eCondition = CHAR_IDLE;
		m_bIsDash = false;
		ChangeAnimation();
	}


	if (m_eCondition == CHAR_IDLE)
	{
		if (m_fStamina <= 10.0f)
		{
			m_fStamina += 0.07;
			if (m_fStamina >= 10.0f)
			{
				m_fStamina = 10.0f;
			}
		}
	}

	TEXT->Add(to_string(m_fStamina), 300, 300, 30);
}


CharacterParant::CharacterParant()
{
	m_Status = new STATUS;
	MODELMANAGER->AddModel("�Ƹ�", "Model/Character/Arin/", "Arin.x", MODELTYPE_X);
	MODELMANAGER->AddModel("��ī��", "Model/Character/Aknal/", "Aknal.x", MODELTYPE_X);
	MODELMANAGER->AddModel("�콺Ƽ��", "Model/Character/Hestia/", "Hestia.x", MODELTYPE_X);
	MODELMANAGER->AddModel("�ޱ׳ʽ�", "Model/Character/Meguns/", "Meguns.x", MODELTYPE_X);
	MODELMANAGER->AddModel("����", "Model/Character/Riah/", "Riah.x", MODELTYPE_X);
	MODELMANAGER->AddModel("��ī��", "Model/Character/Skadi/", "Skadi.x", MODELTYPE_X);
	MODELMANAGER->AddModel("��ī", "Model/Character/Beakah/", "Beakah.x", MODELTYPE_X);
	MODELMANAGER->AddModel("����", "Model/Character/Velvet/", "Velvet.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("���Ϸ�", "Model/Character/Xylo/", "Xylo.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("�Ƹ���", "Model/Character/Arito/", "Arito.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("����Ÿ", "Model/Character/Esta/", "Esta.x", MODELTYPE_X);
}


CharacterParant::~CharacterParant()
{
	SAFE_DELETE(m_pCharacter);
}

void CharacterParant::Init(Map* map, CHARSELECT order)
{
	m_pSampleMap = map;
	
	//TODO : �ٿ�� �ڽ� ����� (ĳ���� ũ�⸶�� ������ �Է�������
	ST_SIZEBOX box;
	box.highX = 50.0f;
	box.highY = 180.0f;
	box.highZ = 50.0f;
	box.lowX = -50.0f;
	box.lowY = 10.0f;
	box.lowZ = -50.0f;



	m_pCharacter->SetScale(D3DXVECTOR3(0.02, 0.02, 0.02));
	D3DXVECTOR3 startPos = m_pSampleMap->GetSpawnPlayer();
	startPos.y = 300.0f;
	m_pCharacter->SetPosition(D3DXVECTOR3(startPos.x, m_pSampleMap->GetHeight(startPos.x, startPos.z), startPos.z));

	//�κ��丮
	m_pInventory = new Inventory;
	m_pInventory->CreateInventory(5,3);
	m_pInventory->SetStatus(m_Status);

	//TODO : �ٿ�� �ڽ� ����� (ĳ���� ũ�⸶�� ������ �Է�������
	m_pCharacter->CreateBound(box);
	m_pCharacter->SetBoundSphere(m_pCharacter->GetOrigBoundSphere().center, 100.0f);

	CAMERA->SetMode(CAMERA_FOLLOW_HOLD);
	CAMERA->SetCamOffset(D3DXVECTOR3(0, 5, 20));
	CAMERA->SetTargetOffset(D3DXVECTOR3(0, 5, 0));
	CAMERA->SetTarget(m_pCharacter->GetPosition(), m_pCharacter->GetRotation());

	
	m_temp = 0;
	m_nCalAction = 0;

	//�⺻ ���¼���
	m_eCondition = CHAR_IDLE;
	ChangeAnimation();
	m_bIsFront = false;
	m_bIsDash = false;
	m_fStamina = 10.0f;
}



void CharacterParant::Render()
{
}

void CharacterParant::KeyControl()
{
	if (INPUT->KeyDown('W'))
	{
		if (m_eCondition == CHAR_IDLE)
		{
			m_eCondition = CHAR_RUN_FRONT;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('W'))
	{
		if (m_eCondition == CHAR_RUN_FRONT)
		{
			m_eCondition = CHAR_IDLE;
			ChangeAnimation();
		}
	}

	if (INPUT->KeyDown('S'))
	{
		if (m_eCondition == CHAR_IDLE)
		{
			m_eCondition = CHAR_RUN_BACK;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('S'))
	{
		if (m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_IDLE;
			ChangeAnimation();
		}
	}

	if (INPUT->KeyDown('Q'))
	{
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT)
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
			m_eCondition = CHAR_IDLE;
			m_bIsDash = false;
			ChangeAnimation();
		}
	}

	if (INPUT->KeyDown('E'))
	{
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_BACK)
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
			m_eCondition = CHAR_IDLE;
			m_bIsDash = false;
			ChangeAnimation();
		}
	}


	if (INPUT->KeyDown(VK_SPACE))
	{
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_ATTACK;
			ChangeAnimation();
		}
	}

	if (INPUT->KeyDown('K'))
	{
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_SKILL;
			ChangeAnimation();
		}
	}

	//���ݻ��¿��� �ִϸ��̼� �ѹ��� ������ �����·� ������
	if (m_pCharacter->IsAnimationEnd()&& m_eCondition == CHAR_ATTACK)
	{
  		m_eCondition = CHAR_IDLE;
		ChangeAnimation();
	}
	//��ų���¿��� �ִϸ��̼� �ѹ��� ������ �����·� ������
	if (m_pCharacter->IsAnimationEnd() && m_eCondition == CHAR_SKILL)
	{
		m_eCondition = CHAR_IDLE;
		ChangeAnimation();
	}
	

	if (m_bIsDash)
	{
		m_pCharacter->SetAnimationSpeed(5.0f);
	}
	else
	{
		m_pCharacter->SetAnimationSpeed(1.0f);
	}

}

void CharacterParant::ChangeAnimation()
{
	switch (m_eCondition)
	{
	case CHAR_IDLE:
			m_pCharacter->SetBlendAnimation("IDLE");
			m_pCharacter->SetBlendTime(0.27f);
		break;
	case CHAR_DASH_FRONT:
		m_pCharacter->SetAnimation("RUN");
	
		break;
	case CHAR_DASH_BACK:
		m_pCharacter->SetAnimation("RUN");
		break;
	case CHAR_RUN_FRONT:
			m_pCharacter->SetAnimation("RUN");
		break;
	case CHAR_RUN_BACK:
		m_pCharacter->SetAnimation("RUN");
		break;
	case CHAR_SKILL:
			m_pCharacter->SetAnimation("SKILL");
		break;
	case CHAR_ATTACK:
			m_pCharacter->SetAnimation("ATTACK");
		break;
	case CHAR_DIE:
		m_pCharacter->SetAnimation("DIE");
		break;
	case CHAR_HIT:
			m_pCharacter->SetAnimation("HIT");
		break;
	case CHAR_BATTLEREADY:
			m_pCharacter->SetAnimation("BATTLEREADY");
		break;
	}
}
