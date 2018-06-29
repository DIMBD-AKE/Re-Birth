#include "../../stdafx.h"
#include "SC_Test.h"
#include "../Map.h"


SC_Test::SC_Test()
{
}


SC_Test::~SC_Test()
{
}

void SC_Test::Release()
{
	SAFE_DELETE(m_pTestModel);
	SAFE_DELETE(m_pSampleMap);
}

void SC_Test::Init()
{
	MODELMANAGER->AddModel("아린", "Model/Character/Arin/", "Arin.x", MODELTYPE_X);
	m_pTestModel = MODELMANAGER->GetModel("아린", MODELTYPE_X);

	m_pSampleMap = new Map;
	m_pSampleMap->Load("Map/Sample.map");

	m_pTestModel->SetScale(D3DXVECTOR3(0.03, 0.03, 0.03));
	D3DXVECTOR3 startPos = m_pSampleMap->GetSpawnPlayer();
	float y = m_pSampleMap->GetHeight(D3DXVECTOR3(startPos.x, 256, startPos.z));
	m_pTestModel->SetPosition(D3DXVECTOR3(startPos.x, y, startPos.z));

	CAMERA->SetMode(CAMERA_FOLLOW_FREE);
	CAMERA->SetCamOffset(D3DXVECTOR3(0, 5, 0));
	CAMERA->SetTargetOffset(D3DXVECTOR3(0, 5, 0));
	CAMERA->SetTarget(m_pTestModel->GetPosition(), m_pTestModel->GetRotation());
}

void SC_Test::Update()
{
	if (m_pTestModel)
	{
		m_pTestModel->World();
		m_pTestModel->Update();
	}

	D3DXVECTOR3 pos = *m_pTestModel->GetPosition();
	D3DXVECTOR3 rot = *m_pTestModel->GetRotation();
	if (INPUT->KeyPress(VK_UP))		pos.z += 0.2;
	if (INPUT->KeyPress(VK_DOWN))	pos.z -= 0.2;
	if (INPUT->KeyPress(VK_LEFT))	rot.y -= 0.05;
	if (INPUT->KeyPress(VK_RIGHT))	rot.y += 0.05;
	m_pTestModel->SetPosition(pos);
	m_pTestModel->SetRotation(rot);
}

void SC_Test::Render()
{
	if (m_pTestModel)
		m_pTestModel->Render();

	if (m_pSampleMap)
		m_pSampleMap->Render();
}
