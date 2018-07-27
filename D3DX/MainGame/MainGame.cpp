#include "../stdafx.h"
#include "MainGame.h"

#include "Item\ItemManager.h"
#include "Scene\SC_Loading.h"
#include "Scene\SC_Main.h"
#include "Scene\SC_Game.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
	SAFE_RELEASE(SPRITE);
	SCENE->Destroy();
	TEXT->Release();
	TEXTUREMANAGER->Release();
	ITEMMANAGER->Destroy();
	MODELMANAGER->Release();
	PARTICLE->Release();
	SOUND->Release();
	DEVICEMANAGER->Destroy();
}

void MainGame::Setup()
{
	//ITEMMANAGER->SetUp();

	SCENE->AddScene("Loading", new SC_Loading);
	SCENE->AddScene("Main", new SC_Main);
	SCENE->AddScene("Game", new SC_Game);

	SCENE->ChangeScene("Loading", true);

	m_isWire = false;

	SetLight();
}

void MainGame::Update()
{
	SCENE->Update();
	CAMERA->Update();
	SOUND->Update();
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
