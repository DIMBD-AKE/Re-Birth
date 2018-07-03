#include "../../stdafx.h"
#include "CharacterParant.h"
#include "Inventory.h"
#include "../Map.h"
#include "../Status.h"


void CharacterParant::SKill()
{
	//특정 키를 누르면 아이템 클래스의 skill을 실행한다. 
}

void CharacterParant::Move()
{
	//전후좌우 점프 움직임


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
	//달리는모션
	if (m_eCondition == CHAR_RUN)
	{												//이동속도
		m_pCharacter->SetPosition(pos - m_vfront *	0.7f);
	}

	/*if (m_pSampleMap)
	{
		if (m_pSampleMap->GetHeight(pos))
		{
			m_pCharacter->SetPosition(pos);
		}
	}

	*/
	pos = *m_pCharacter->GetPosition();
	pos.y = 300.0f;

	float temp = m_pSampleMap->GetHeight(pos.x, pos.z);
	m_pCharacter->SetPosition(D3DXVECTOR3(pos.x, temp, pos.z));
}

void CharacterParant::Controller()
{
	//===============기능키 제어=====================//
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


CharacterParant::CharacterParant()
{
	MODELMANAGER->AddModel("아린", "Model/Character/Arin/", "Arin.x", MODELTYPE_X);
	MODELMANAGER->AddModel("아카날", "Model/Character/Aknal/", "Aknal.x", MODELTYPE_X);
	MODELMANAGER->AddModel("헤스티아", "Model/Character/Hestia/", "Hestia.x", MODELTYPE_X);
	MODELMANAGER->AddModel("메그너스", "Model/Character/Meguns/", "Meguns.x", MODELTYPE_X);
	MODELMANAGER->AddModel("리아", "Model/Character/Riah/", "Riah.x", MODELTYPE_X);
	MODELMANAGER->AddModel("스카디", "Model/Character/Skadi/", "Skadi.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("자일로", "Model/Character/Xylo/", "Xylo.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("아리토", "Model/Character/Arito/", "Arito.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("에스타", "Model/Character/Esta/", "Esta.x", MODELTYPE_X);
}


CharacterParant::~CharacterParant()
{
	SAFE_DELETE(m_pCharacter);
}

void CharacterParant::Init(Map* map, CHARSELECT order)
{
	m_pSampleMap = map;
	
	//TODO : 바운딩 박스 만들기 (캐릭터 크기마다 일일히 입력해주자
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

	//인벤토리
	m_pInventory = new Inventory;
	m_pInventory->CreateInventory(5,3);

	//TODO : 바운딩 박스 만들기 (캐릭터 크기마다 일일히 입력해주자
	m_pCharacter->CreateBound(box);
	m_pCharacter->SetBoundSphere(m_pCharacter->GetOrigBoundSphere().center, 100.0f);

	CAMERA->SetMode(CAMERA_FOLLOW_HOLD);
	CAMERA->SetCamOffset(D3DXVECTOR3(0, 5, 20));
	CAMERA->SetTargetOffset(D3DXVECTOR3(0, 5, 0));
	CAMERA->SetTarget(m_pCharacter->GetPosition(), m_pCharacter->GetRotation());

	
	m_temp = 0;
	m_nCalAction = 0;

	//기본 상태세팅
	m_eCondition = CHAR_IDLE;
	ChangeAnimation();
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
			m_eCondition = CHAR_RUN;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('W'))
	{
		if (m_eCondition == CHAR_RUN)
		{
			m_eCondition = CHAR_IDLE;
			ChangeAnimation();
		}
	}

	if (INPUT->KeyDown(VK_SPACE))
	{
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN)
		{
			m_eCondition = CHAR_ATTACK;
			ChangeAnimation();
		}
	}


	if (m_pCharacter->IsAnimationEnd()&& m_eCondition == CHAR_ATTACK)
	{
  		m_eCondition = CHAR_IDLE;
		ChangeAnimation();
	}
	

}

void CharacterParant::ChangeAnimation()
{
	switch (m_eCondition)
	{
	case CHAR_IDLE:
			m_pCharacter->SetBlendAnimation("IDLE");
		break;
	case CHAR_RUN:
			m_pCharacter->SetAnimation("RUN");
		break;
	case CHAR_SKILL:
			m_pCharacter->SetAnimation("SKILL");
		break;
	case CHAR_ATTACK:
			m_pCharacter->SetBlendAnimation("ATTACK");
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
