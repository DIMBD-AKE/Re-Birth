#include "../../stdafx.h"
#include "CharacterParant.h"
#include "Inventory.h"
#include "../Map.h"
#include "../Status.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../Item/ItemParent.h"


void CharacterParant::SKill()
{
	//Ư�� Ű�� ������ ������ Ŭ������ skill�� �����Ѵ�. 
}

void CharacterParant::Move()
{
	Debug();
	Attack();
	//��Ʈ����Ʈ
	//m_pUIobj->Update();

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
		float height = m_pSampleMap->GetHeight(pos.x - m_vfront.x * m_Status->chr.fSpeed, pos.z - m_vfront.z * m_Status->chr.fSpeed);
		if (height >= 0)
		{
			pos.y = height;
			m_pCharacter->SetPosition(pos - m_vfront * m_Status->chr.fSpeed);
		}
		else
		{
			return;
		}
	}
	else if (m_eCondition == CHAR_RUN_BACK)
	{
		float height = m_pSampleMap->GetHeight(pos.x - m_vfront.x * (m_Status->chr.fSpeed-0.2f), pos.z - m_vfront.z * (m_Status->chr.fSpeed-0.2f));
		if (height >= 0)
		{
			pos.y = height;
			m_pCharacter->SetPosition(pos + m_vfront * (m_Status->chr.fSpeed-0.2f));
		}
		else
		{
			return;
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
	if (DEBUG)
	{
		D3DXVECTOR3 tempPos; 
		tempPos = *m_pCharacter->GetPosition();
		tempPos.y += 3;
		D3DXVECTOR2 pos =  Util::Convert3DTo2D(tempPos);
		TEXT->Add(to_string(m_Status->chr.nCurrentStam), pos.x, pos.y, 30);
		TEXT->Add(to_string(m_Status->chr.nCurrentHP), 300, 300, 30);

	//	CAMERA->SetMode(CAMERA_FREE);
	}
}

void CharacterParant::CheckDirection()
{

}

void CharacterParant::ControllStamina()
{

	if (m_eCondition == CHAR_DASH_FRONT || m_eCondition == CHAR_DASH_BACK)
	{
		m_Status->chr.nCurrentStam -= 1;
	}

	if (m_Status->chr.nCurrentStam <= 0)
	{
		m_eCondition = CHAR_IDLE;
		m_bIsDash = false;
		ChangeAnimation();
	}


	if (m_eCondition == CHAR_IDLE)
	{
		if (m_Status->chr.nCurrentStam <= m_Status->chr.nMaxStam)
		{
			m_Status->chr.nCurrentStam += 1;
			if (m_Status->chr.nCurrentStam >= m_Status->chr.nMaxStam)
			{
				m_Status->chr.nCurrentStam = m_Status->chr.nMaxStam;
			}
		}
	}


}

void CharacterParant::UnderAttacked()
{
	if (INPUT->KeyDown('Z'))
	{
		m_Status->chr.nCurrentHP -= 50;
	}
		if (m_Status->chr.nCurrentHP <= 0 && !m_bIsDead)
		{
			m_bIsDead = true;
			m_eCondition = CHAR_DIE;
			ChangeAnimation();
		}
}

void CharacterParant::SetCurrentHP(int hp)
{
	m_Status->chr.nCurrentHP -= hp;
	
	if (m_Status->chr.nCurrentHP <= 0 && !m_bIsDead)
	{
		m_bIsDead = true;
		m_eCondition = CHAR_DIE;
		ChangeAnimation();
	}
}



void CharacterParant::CalculDamage(float damage)
{
	float totalRate =
		m_Status->chr.fPhyRate +
		m_Status->chr.fMagicRate +
		m_Status->chr.fCheRate;

	float totalDamage = totalRate * m_Status->chr.nDef;

	totalDamage = round(totalDamage);

	SetCurrentHP(totalDamage);
}

void CharacterParant::Attack()
{	
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();														//�÷��̾� ������ �ް� 
	D3DXVECTOR3 rot = *m_pCharacter->GetRotation();														//�÷��̾� ���� �ް� 
	

	for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
	{											
		if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;								//�����Ҷ��� �ǵ帮�� �ʰ� 
		else
		{
			float radius = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;		//������ �ٿ�� ������� ������ �ް� 
			D3DXVECTOR3 mosPos = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//���� ������ �ް� 
			float distance = D3DXVec3Length(&(mosPos - pos));												//�Ÿ�������� ���� ��ġ�� �÷��̾� ������ �� ���� �����ϴ� ���������
			if (distance - radius > m_fRange) continue;														//�Ÿ��� �������� �� ���� ���� ���̺��� ũ�� ó������ �ʰ�
			else
			{
				D3DXVECTOR3 delta = mosPos - pos;															//��Ÿ ������ ���� �����ǰ� �� �������� �� ���Ͱ����� �ΰ�
				if(atan2(delta.x, delta.z)>m_fScale) continue;												//��ź2�� ��� �������� fScale���� ũ�� �׳� �ѱ�� 
						
				int Atk = m_Status->chr.nAtk;																//�÷��̾� ���ݷ� ��� �����ε� �̰� ���� �ʿ� ���� 
				m_pMonsterManager->GetMonsterVector()[i]->SetCurrentHP(100);									//�׳� ���� ������ �� �����ϸ� ���� �� �տ� �ִ� ���� ü��0���� ����������
				//pMonsterManager->GetMonsterVector()[i]->CalculDamage(,);
				//m_pMonsterManager->GetMonsterVector()[i]->
			}
		}
	}
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
	TEXTUREMANAGER->AddTexture("��ī��_����", "Model/Character/Portrait/Portrait_PC_Aknal_S_Icon.tga");
	TEXTUREMANAGER->AddTexture("�Ƹ�_����", "Model/Character/Portrait/Portrait_PC_Arin_S_Icon.tga");
	TEXTUREMANAGER->AddTexture("��ī_����", "Model/Character/Portrait/Portrait_PC_BeakAh_S_Icon.tga");
	TEXTUREMANAGER->AddTexture("�콺Ƽ��_����", "Model/Character/Portrait/Portrait_PC_Hestia_S_Icon.tga");
	TEXTUREMANAGER->AddTexture("�ޱ׳ʽ�_����", "Model/Character/Portrait/Portrait_Pc_Magnus_Icon.tga");
	TEXTUREMANAGER->AddTexture("����_����", "Model/Character/Portrait/Portrait_PC_Riah_S_Icon.tga");
	TEXTUREMANAGER->AddTexture("��ī��_����", "Model/Character/Portrait/Portrait_PC_Skadi_S_Icon.tga");
	TEXTUREMANAGER->AddTexture("����_����", "Model/Character/Portrait/velvet.png");

}


CharacterParant::~CharacterParant()
{
	SAFE_DELETE(m_pCharacter);
}

void CharacterParant::Init(Map* map, CHARSELECT order, MonsterManager* pMonsterManager)
{
	m_pSampleMap = map;
	m_pMonsterManager = pMonsterManager;
	
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
	m_bIsDead = false;
	m_fStamina = 10.0f;
	m_fRange = 30.0f;
	m_fScale = 30.0f;


	//��Ʈ����Ʈ UI
	m_pUIobj = new UIObject;



}



void CharacterParant::Render()
{
	//��Ʈ����Ʈ 
	//m_pUIobj->Render();
}

void CharacterParant::KeyControl()
{
	//������ �޸���
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
	//�ڷ� �޸���
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
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_ATTACK;
			ChangeAnimation();
		}
	}

	//��ų����
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
	
	//�뽬�϶� �ִϸ��̼� ���ǵ� ����
	if (m_bIsDash)
	{
		m_pCharacter->SetAnimationSpeed(5.0f);
	}
	else
	{
		m_pCharacter->SetAnimationSpeed(1.0f);
	}

	//���� �ֱ�
	if (m_pCharacter->IsAnimationEnd() && m_eCondition == CHAR_DIE)
	{
		m_eCondition = CHAR_NONE;
		m_bIsDead = false;
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
	case CHAR_NONE :
		break;
	}
}
