#include "../../stdafx.h"
#include "CharacterParant.h"
#include "Inventory.h"
#include "../Map.h"


void CharacterParant::SKill()
{
	//특정 키를 누르면 아이템 클래스의 skill을 실행한다. 
}

void CharacterParant::Move()
{
	//전후좌우 점프 움직임


	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
	D3DXVECTOR3 rot = *m_pCharacter->GetRotation();
//	if (INPUT->KeyPress(VK_UP))		pos.z += 0.2;
//	if (INPUT->KeyPress(VK_DOWN))	pos.z -= 0.2;
	if (INPUT->KeyPress(VK_LEFT))	rot.y -= 0.05;
	if (INPUT->KeyPress(VK_RIGHT))	rot.y += 0.05;



	D3DXMATRIX matAngle;
	D3DXMatrixRotationYawPitchRoll(&matAngle, m_pCharacter->GetRotation()->y, m_pCharacter->GetRotation()->x, m_pCharacter->GetRotation()->z);

	m_vfront = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vfront, &m_vfront, &matAngle);
	//================움직임 제어===================//
	if (INPUT->KeyPress('W'))
	{											  //요 값을 무브스피드로
		m_pCharacter->SetPosition(pos - m_vfront * 0.1f);
		m_bIsPressW = true;
	}
	
	if (INPUT->KeyPress('S'))
	{
		m_pCharacter->SetPosition(pos + m_vfront * 0.1f);
	}
	if (INPUT->KeyPress('A'))
	{
		m_pCharacter->GetRotation()->y -= 0.05f;
	}
	if (INPUT->KeyPress('D'))
	{
		m_pCharacter->GetRotation()->y += 0.05f;
	}

	//===============기능키 제어=====================//
	/*if (INPUT->KeyDown('I'))
	{
		m_pInventory->OpenInventory();
	}*/
	if (INPUT->KeyDown('P'))
	{
		m_pInventory->OpenEquip();
	}
	//==============임시 애니메이션 제어===================//
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		m_temp++;
		m_pCharacter->SetAnimation(m_temp);
	}



	pos.y = 300.0f;
	float temp = m_pSampleMap->GetHeight(pos);


	pos = *m_pCharacter->GetPosition();
	m_pCharacter->SetPosition(D3DXVECTOR3(pos.x, temp, pos.z));


}




CharacterParant::CharacterParant()
{
	MODELMANAGER->AddModel("아린", "Model/Character/Arin/", "Arin.x", MODELTYPE_X);
	MODELMANAGER->AddModel("아카날", "Model/Character/Aknal/", "Aknal.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("아리토", "Model/Character/Arito/", "Arito.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("에스타", "Model/Character/Esta/", "Esta.x", MODELTYPE_X);
	MODELMANAGER->AddModel("헤스티아", "Model/Character/Hestia/", "Hestia.x", MODELTYPE_X);
	MODELMANAGER->AddModel("메그너스", "Model/Character/Meguns/", "Meguns.x", MODELTYPE_X);
	MODELMANAGER->AddModel("리아", "Model/Character/Riah/", "Riah.x", MODELTYPE_X);
	MODELMANAGER->AddModel("스카디", "Model/Character/Skadi/", "Skadi.x", MODELTYPE_X);
	//MODELMANAGER->AddModel("자일로", "Model/Character/Xylo/", "Xylo.x", MODELTYPE_X);
}


CharacterParant::~CharacterParant()
{
	SAFE_DELETE(m_pCharacter);
}

void CharacterParant::Init(Map* map)
{
	m_pSampleMap = map;
	
	m_pCharacter->SetScale(D3DXVECTOR3(0.02, 0.02, 0.02));
	D3DXVECTOR3 startPos = m_pSampleMap->GetSpawnPlayer();
	startPos.y = 300.0f;
	m_pCharacter->SetPosition(D3DXVECTOR3(startPos.x, m_pSampleMap->GetHeight(startPos), startPos.z));

	m_pInventory = new Inventory;
	
	m_pInventory->CreateInventory(5,3);


	CAMERA->SetMode(CAMERA_FOLLOW_HOLD);
	CAMERA->SetCamOffset(D3DXVECTOR3(0, 5, 20));
	CAMERA->SetTargetOffset(D3DXVECTOR3(0, 5, 0));
	CAMERA->SetTarget(m_pCharacter->GetPosition(), m_pCharacter->GetRotation());

	m_bIsPressW = false;
	m_temp = 0;
}



void CharacterParant::Render()
{
}

void CharacterParant::ChangeAnimation()
{
}
