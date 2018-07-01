#include "../../stdafx.h"
#include "CharacterParant.h"
#include "Inventory.h"
#include "../Map.h"


void CharacterParant::SKill()
{
	//Ư�� Ű�� ������ ������ Ŭ������ skill�� �����Ѵ�. 
}

void CharacterParant::Move()
{
	//�����¿� ���� ������


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

	if (INPUT->KeyPress('W'))
	{
		m_pCharacter->SetPosition(pos - m_vfront*0.1f);
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



	pos.y = 300.0f;
	float temp = m_pSampleMap->GetHeight(pos);


	pos = *m_pCharacter->GetPosition();
	m_pCharacter->SetPosition(D3DXVECTOR3(pos.x, temp, pos.z));

}

CharacterParant::CharacterParant()
{
	MODELMANAGER->AddModel("�Ƹ�", "Model/Character/Arin/", "Arin.x", MODELTYPE_X);
	MODELMANAGER->AddModel("�Ƹ���", "Model/Character/Arito/", "Arito.x", MODELTYPE_X);
}


CharacterParant::~CharacterParant()
{
	SAFE_DELETE(m_pCharacter);
}

void CharacterParant::Init()
{

	m_pCharacter->SetScale(D3DXVECTOR3(0.02, 0.02, 0.02));
	D3DXVECTOR3 startPos = m_pSampleMap->GetSpawnPlayer();
	startPos.y = 300.0f;
	m_pCharacter->SetPosition(D3DXVECTOR3(startPos.x, m_pSampleMap->GetHeight(startPos), startPos.z));


	CAMERA->SetMode(CAMERA_FOLLOW_HOLD);
	CAMERA->SetCamOffset(D3DXVECTOR3(0, 5, 20));
	CAMERA->SetTargetOffset(D3DXVECTOR3(0, 5, 0));
	CAMERA->SetTarget(m_pCharacter->GetPosition(), m_pCharacter->GetRotation());
}


void CharacterParant::Render()
{
}

void CharacterParant::SetMap(Map * map)
{
	m_pSampleMap = map;
}