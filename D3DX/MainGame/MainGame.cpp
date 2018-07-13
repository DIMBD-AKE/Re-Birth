#include "../stdafx.h"
#include "MainGame.h"

#include "Item\ItemManager.h"
#include "Scene\SC_Test.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
	SAFE_RELEASE(SPRITE);
	SCENE->Destroy();
	TEXT->Release();
	TEXTUREMANAGER->Release();
	MODELMANAGER->Release();
	PARTICLE->Release();
	ITEMMANAGER->Destroy();
	DEVICEMANAGER->Destroy();
}

void MainGame::Setup()
{
	SCENE->AddScene("Test", new SC_Test);
	SCENE->ChangeScene("Test", true);

	m_isWire = false;

	SetLight();
}

void MainGame::Update()
{
	SCENE->Update();
	CAMERA->Update();
	if (INPUT->KeyDown(VK_F2))
		m_isWire = !m_isWire;
}

void MainGame::Render()
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->SetRenderState(D3DRS_FILLMODE, m_isWire ? D3DFILL_WIREFRAME : D3DFILL_SOLID);

	SCENE->Render();
	TEXT->Render();
}

void MainGame::SetLight()
{
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = light.Diffuse = D3DXCOLOR(1, 1, 1, 0);
	light.Direction = D3DXVECTOR3(1, -1, 1);
	LIGHTMANAGER->AddLight(this, light, 0);
}
