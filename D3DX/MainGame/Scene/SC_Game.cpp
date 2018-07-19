#include "../../stdafx.h"
#include "SC_Game.h"
#include "../Map.h"
#include "../monster/MonsterManager.h"
#include "../Character/CharacterParant.h"
#include "../Item/DropManager.h"


SC_Game::SC_Game()
{
}


SC_Game::~SC_Game()
{
	SAFE_DELETE(m_pCharacter);
}

void SC_Game::Release()
{
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pDropManager);
	SAFE_DELETE(m_pMM);
}

void SC_Game::Init()
{
	g_clearColor = 0xFFFFFFFF;

	if (m_pData[0])
		m_pCharacter = (CharacterParant*)m_pData[0];
	if (m_pData[1])
		m_nStage = *(int*)m_pData[1];
	if (m_pData[2])
		m_fPlayTime = *(float*)m_pData[2];

	m_fGenTime = GetTickCount();

	m_pMap = new Map;
	if (m_nStage == 1)
		m_pMap->Load("Map/Sample.map");
	else if (m_nStage == 2)
		m_pMap->Load("Map/Stage 1.map");
	else if (m_nStage == 3)
		m_pMap->Load("Map/Sample.map");

	m_pDropManager = new DropManager;
	m_pDropManager->Init();

	m_pMM = new MonsterManager;

	m_pMM->Setup(m_pMap, &m_pCharacter);
	m_pMM->SetSpawnSpat(m_pMap->GetSpawnEnemy());
	m_pMM->MakeMonster(m_pDropManager);

	m_pCharacter->Reset(m_pMap, m_pMM);

	m_fGenTime = (GetTickCount() - m_fGenTime) * 0.001;
	if (m_fPlayTime > 0)
		m_fPlayTime -= m_fGenTime;
}

void SC_Game::Update()
{
	m_pMM->Update();
	m_pDropManager->GetDropItem(m_pCharacter);
	m_pCharacter->Update();

	TEXT->Add(to_string(TIME->GetFPS()), 0, 0, 20);
	TEXT->Add(to_string(m_fPlayTime), 0, 20, 20);

	if (INPUT->KeyDown(VK_RETURN))
		NextStage();

	if (INPUT->KeyDown(VK_ESCAPE))
		ClearStage();

	if (m_fPlayTime < 0.0001)
		m_fPlayTime -= m_fGenTime;
	m_fPlayTime += TIME->GetElapsedTime();
}

void SC_Game::Render()
{
	m_pMap->Render();

	m_pDropManager->Render();
	m_pCharacter->Render();
	m_pMM->Render();
}

void SC_Game::ClearStage()
{
	SCENE->ChangeScene("Main");
	CAMERA->SetTarget(NULL, NULL);
	SAFE_DELETE(m_pCharacter);
}

void SC_Game::NextStage()
{
	ZeroMemory(m_pData, sizeof(void*) * 10);
	m_nStage++;
	if (m_nStage > 3)
	{
		ClearStage();
		return;
	}
	Release();
	Init();
}
