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
	D3DXVECTOR3 tempPos1;
	tempPos1 = *m_pCharacter->GetPosition();
	tempPos1.y += 3;
	D3DXVECTOR2 pos1 = Util::Convert3DTo2D(tempPos1);
	TEXT->Add(to_string(m_Status->chr.nCurrentHP), pos1.x, pos1.y, 30);
	//TEXT->Add(to_string(m_Status->chr.nCurrentHP), 300, 300, 30);
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

	//�ǰ� 0�Ʒ��� �������� �ʵ��� ����
	if (m_Status->chr.nCurrentHP <= 0)
	{
		m_Status->chr.nCurrentHP = 0;
	}
	
	//m_pParticle->SetPosition(*m_pCharacter->GetPosition());
	m_pParticle->World();
	m_pParticle->Update();

	m_pParticle2->World();
	m_pParticle2->Update();

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
		/*D3DXVECTOR3 tempPos; 
		tempPos = *m_pCharacter->GetPosition();
		tempPos.y += 3;
		D3DXVECTOR2 pos =  Util::Convert3DTo2D(tempPos);
		TEXT->Add(to_string(m_Status->chr.nCurrentStam), pos.x, pos.y, 30);*/
		TEXT->Add(to_string(m_Status->chr.nCurrentHP), 300, 300, 30);

		CAMERA->SetMode(CAMERA_FREE);
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
			m_pParticle2->SetPosition(*m_pCharacter->GetPosition());
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

	totalDamage = damage - totalDamage;

	totalDamage /= 3;

	if (totalDamage <= 1) totalDamage = 1;

	totalDamage = round(totalDamage);

	SetCurrentHP(totalDamage);
}

void CharacterParant::Attack()
{	
	//1. ���� ������ �ε����� ������ ������ �����.
	//2. �Ÿ��� ���� ������ �����.
	//3. �ʱ�ȭ�� 0��° ����� �Ÿ��� ��´�.(0��°���� �׾������ ���� ū�� �ƹ��ų� �ִµ�)�ε����� 0�̴�.
	//4. i = 1���� ���ͻ����ŭ ���鼭 �Ÿ��� ���ϰ� 2���� ���� ������ �񱳸� �Ͽ� �������� ������ �ٽ� �ְ� �ε������� �ٲ۴�.


		D3DXVECTOR3 pos = *m_pCharacter->GetPosition();														//�÷��̾� ������ �ް� 
		D3DXVECTOR3 rot = *m_pCharacter->GetRotation();														//�÷��̾� ���� �ް� 
		
		int MinIndex = -1;
		int subMinIndex = -1;
		int MINIndex2 = -1;
		float MinDistance = 0.0f;
		float radius;
		D3DXVECTOR3 mosPos;
		float distance;
		float subDistance = 0.0f;

	if (m_eChrType == CHRTYPE_SWORD || m_eChrType == CHRTYPE_GUN)
	{
		//�������� �Ǵ� ���͸� ���ϰ� 
		for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
		{
			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;								//�����Ҷ��� �ǵ帮�� �ʰ� 
			
			float radius1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;		//������ �ٿ�� ������� ������ �ް� 
			D3DXVECTOR3 mosPos1 = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//���� ������ �ް� 
			float distance1 = D3DXVec3Length(&(mosPos1 - pos));
	
			if (distance1 - radius1 > m_Status->chr.fRange) continue;
			distance = distance1;
			distance = subDistance;
			//radius = radius1;

			MinIndex = i;
			break;
		}
		if (MinIndex != -1)//���� �������� �� ���Ͱ� ���������� 
		{
			for (int i = MinIndex+1; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
			{
				if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;	//�����Ҷ��� �ǵ帮�� �ʰ� 
				float radius2 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
				D3DXVECTOR3 mosPos2 = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());
				float distance2 = D3DXVec3Length(&(mosPos2 - pos));
				if (distance2 - radius2 > m_Status->chr.fRange) continue;
				if (distance > distance2)
				{
					distance = distance2;
					MinIndex = i;
				}
				
			}
			
			m_pMonsterManager->GetMonsterVector()[MinIndex]->CalculDamage(1.0f);
			m_pParticle->SetPosition(D3DXVECTOR3(m_pMonsterManager->GetMonsterVector()[MinIndex]->GetModel()->GetPosition()->x, 
				m_pMonsterManager->GetMonsterVector()[MinIndex]->GetModel()->GetPosition()->y+2.0f, 
				m_pMonsterManager->GetMonsterVector()[MinIndex]->GetModel()->GetPosition()->z));
			m_pParticle->TimeReset();

		}
		//============�����ȿ� �ִ� �ֵ� �� �����ϴ� ���� skill��====================
		//for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
		//{
		//	if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;
		//	float radius1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;		//������ �ٿ�� ������� ������ �ް� 
		//	D3DXVECTOR3 mosPos1 = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//���� ������ �ް� 
		//	float distance1 = D3DXVec3Length(&(mosPos1 - pos));
		//	if (distance1 - radius1 > m_Status->chr.fRange) continue;
		//	else
		//	{
		//		m_pMonsterManager->GetMonsterVector()[i]->CalculDamage(1000000.0f);
		//		m_pParticle->SetPosition(D3DXVECTOR3(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition()->x,
		//			m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition()->y + 2.0f,
		//			m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition()->z));
		//		m_pParticle->TimeReset();
		//	}
		//}
		//=========�����ȿ� �ִ� �ֵ��� ������ �׸��� �ι�° ������ �����ϴ� ���� ��ų��==================
		//�������� �Ǵ� ���͸� ���ϰ� 
		//for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
		//{
		//	if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;								//�����Ҷ��� �ǵ帮�� �ʰ� 

		//	float radius1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;		//������ �ٿ�� ������� ������ �ް� 
		//	D3DXVECTOR3 mosPos1 = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//���� ������ �ް� 
		//	float distance1 = D3DXVec3Length(&(mosPos1 - pos));

		//	if (distance1 - radius1 > m_Status->chr.fRange) continue;
		//	distance = distance1;
		//	subDistance = FLT_MAX;

		//	MinIndex = i;
		//	subMinIndex = i;
		//	break;
		//}
		//if (MinIndex != -1)//���� �������� �� ���Ͱ� ���������� 
		//{
		//	for (int i = MinIndex + 1; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
		//	{
		//		if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;	//�����Ҷ��� �ǵ帮�� �ʰ� 
		//		float radius2 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
		//		D3DXVECTOR3 mosPos2 = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());
		//		float distance2 = D3DXVec3Length(&(mosPos2 - pos));
		//		if (distance2 - radius2 > m_Status->chr.fRange) continue;
		//		if (distance > distance2)
		//		{
		//			distance = distance2;
		//			MinIndex = i;
		//		}

		//	}
		//	for (int j = subMinIndex + 1; j < m_pMonsterManager->GetMonsterVector().size(); ++j)
		//	{

		//		if (m_pMonsterManager->GetMonsterVector()[j]->GetIsResPawn())continue;	//�����Ҷ��� �ǵ帮�� �ʰ� 
		//		if (j == MinIndex) continue; //���� �ּҰ��� ���� �ε������� �糢��
		//		float radius3 = m_pMonsterManager->GetMonsterVector()[j]->GetModel()->GetBoundSphere().radius;
		//		D3DXVECTOR3 mosPos3 = *(m_pMonsterManager->GetMonsterVector()[j]->GetModel()->GetPosition());
		//		float distance3 = D3DXVec3Length(&(mosPos3 - pos));
		//		if (distance3 - radius3 > m_Status->chr.fRange) continue;
		//		if (subDistance > distance3)
		//		{
		//			subDistance = distance3;
		//			MINIndex2 = j;
		//		}
		//		
		//	}
		//	if (MINIndex2 != -1)
		//	{
		//		m_pMonsterManager->GetMonsterVector()[MINIndex2]->CalculDamage(100000.0f);
		//	}
		//	m_pMonsterManager->GetMonsterVector()[MinIndex]->CalculDamage(100000.0f);
		//	m_pParticle->SetPosition(D3DXVECTOR3(m_pMonsterManager->GetMonsterVector()[MinIndex]->GetModel()->GetPosition()->x,
		//		m_pMonsterManager->GetMonsterVector()[MinIndex]->GetModel()->GetPosition()->y + 2.0f,
		//		m_pMonsterManager->GetMonsterVector()[MinIndex]->GetModel()->GetPosition()->z));
		//	m_pParticle->TimeReset();

		//}
	}
	else if (m_eChrType == CHRTYPE_MAGIC)
	{
		//�������� �Ǵ� ���͸� ���ϰ� 
		for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
		{
			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;								//�����Ҷ��� �ǵ帮�� �ʰ� 

			float radius1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;		//������ �ٿ�� ������� ������ �ް� 
			D3DXVECTOR3 mosPos1 = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//���� ������ �ް� 
			float distance1 = D3DXVec3Length(&(mosPos1 - pos));

			if (distance1 - radius1 > m_Status->chr.fRange) continue;
			distance = distance1;
			//radius = radius1;

			MinIndex = i;
			break;
		}
		if (MinIndex != -1)//���� �������� �� ���Ͱ� ���������� 
		{
			for (int i = MinIndex + 1; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
			{
				if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;	//�����Ҷ��� �ǵ帮�� �ʰ� 
				radius = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
				D3DXVECTOR3 mosPos2 = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());
				float distance2 = D3DXVec3Length(&(mosPos2 - pos));
				if (distance2 - radius > m_Status->chr.fRange) continue;
				if (distance > distance2)
				{
					distance = distance2;
					MinIndex = i;
				}
			}
			m_pMonsterManager->GetMonsterVector()[MinIndex]->CalculDamage(1.0f);
			m_pParticle->SetPosition(D3DXVECTOR3(m_pMonsterManager->GetMonsterVector()[MinIndex]->GetModel()->GetPosition()->x,
				m_pMonsterManager->GetMonsterVector()[MinIndex]->GetModel()->GetPosition()->y + 2.0f,
				m_pMonsterManager->GetMonsterVector()[MinIndex]->GetModel()->GetPosition()->z));
			m_pParticle->TimeReset();
			
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
	TEXTUREMANAGER->AddTexture("��ī��_����", "Model/Character/Portrait/Portrait_PC_Aknal_S_Icon.png");
	TEXTUREMANAGER->AddTexture("�Ƹ�_����", "Model/Character/Portrait/Portrait_PC_Arin_S_Icon.png");
	TEXTUREMANAGER->AddTexture("��ī_����", "Model/Character/Portrait/Portrait_PC_BeakAh_S_Icon.png");
	TEXTUREMANAGER->AddTexture("�콺Ƽ��_����", "Model/Character/Portrait/Portrait_PC_Hestia_S_Icon.png");
	TEXTUREMANAGER->AddTexture("�ޱ׳ʽ�_����", "Model/Character/Portrait/Portrait_Pc_Magnus_Icon.png");
	TEXTUREMANAGER->AddTexture("����_����", "Model/Character/Portrait/Portrait_PC_Riah_S_Icon.png");
	TEXTUREMANAGER->AddTexture("��ī��_����", "Model/Character/Portrait/Portrait_PC_Skadi_S_Icon.png");
	TEXTUREMANAGER->AddTexture("����_����", "Model/Character/Portrait/velvet.png");
	//���ݽ� ��ƼŬ
	PARTICLE->AddParticle("ATTACK",
		TEXTUREMANAGER->AddTexture("��ƼŬ1", "Texture/Particle/Sphere.png"),
		"Particle/attack.ptc");
	//�÷��̾� �׾����� ��ƼŬ
	PARTICLE->AddParticle("Die",
		TEXTUREMANAGER->AddTexture("��ƼŬ2", "Texture/Particle/Sphere.png"),
		"Particle/PlayerDie.ptc");

}


CharacterParant::~CharacterParant()
{
	SAFE_DELETE(m_pCharacter);
	SAFE_DELETE(m_pParticle);
	SAFE_DELETE(m_pParticle2);
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
	m_bIsAttack = false;
	m_fStamina = 10.0f;


	//��Ʈ����Ʈ UI
	m_pUIobj = new UIObject;

	


	m_pParticle = PARTICLE->GetParticle("ATTACK");
	m_pParticle2 = PARTICLE->GetParticle("Die");
}



void CharacterParant::Render()
{
	//��Ʈ����Ʈ 
	//m_pUIobj->Render();
	m_pParticle->Render();
	m_pParticle2->Render();
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
	if (m_eCondition == CHAR_DASH_FRONT || m_eCondition == CHAR_DASH_BACK)
	{
		m_pCharacter->SetAnimationSpeed(5.0f);
	}

	//���ݻ����϶� �ִϸ��̼� ���ǵ� ����
	if (m_eCondition == CHAR_ATTACK)
	{
		m_pCharacter->SetAnimationSpeed(1.0f * m_Status->chr.fAtkSpeed);
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
			m_pCharacter->SetAnimationSpeed(1.0f);
		break;
	case CHAR_DASH_FRONT:
		m_pCharacter->SetAnimation("RUN");
	
		break;
	case CHAR_DASH_BACK:
		m_pCharacter->SetAnimation("RUN");
		break;
	case CHAR_RUN_FRONT:
			m_pCharacter->SetAnimation("RUN");
			m_pCharacter->SetAnimationSpeed(1.0f);
		break;
	case CHAR_RUN_BACK:
		m_pCharacter->SetAnimation("RUN");
		m_pCharacter->SetAnimationSpeed(1.0f);
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
