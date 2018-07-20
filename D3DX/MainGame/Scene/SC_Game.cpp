#include "../../stdafx.h"
#include "SC_Game.h"
#include "../Map.h"
#include "../monster/MonsterManager.h"
#include "../Character/CharacterParant.h"
#include "../Item/DropManager.h"
#include "../Character/Inventory.h"
#include "../Item/ItemParent.h"

float SC_Game::m_fElapseTime = 0;

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
	SAFE_RELEASE(m_pUI);
}

void SC_Game::Init()
{
	g_clearColor = 0xFFFFFFFF;

	if (m_pData[0])
		m_pCharacter = (CharacterParant*)m_pData[0];
	if (m_pData[1])
		m_nStage = *(int*)m_pData[1];
	if (m_pData[2])
		m_fElapseTime = *(float*)m_pData[2];

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

	m_pUI = new UIObject;
	m_pUI->SetTexture(TEXTUREMANAGER->GetTexture("Game ElapseTime"));
	m_pUI->SetPosition(D3DXVECTOR3(1261, 754, 0));

	m_fGenTime = (GetTickCount() - m_fGenTime) * 0.001;
	if (m_fElapseTime > 0)
		m_fElapseTime -= m_fGenTime;
}

void SC_Game::Update()
{
	m_pMM->Update();
	m_pDropManager->GetDropItem(m_pCharacter);
	m_pCharacter->Update();
	m_pUI->Update();

	ShowElapseTime();

	TEXT->Add(to_string(TIME->GetFPS()), 0, 0, 20);

	if (INPUT->KeyDown(VK_RETURN))
		NextStage();

	if (INPUT->KeyDown(VK_ESCAPE))
		ClearStage();

	if (m_fElapseTime < 0.0001)
		m_fElapseTime -= m_fGenTime;
	m_fElapseTime += TIME->GetElapsedTime();
}

void SC_Game::Render()
{
	m_pMap->Render();

	m_pDropManager->Render();
	m_pCharacter->Render();
	m_pMM->Render();

	m_pUI->Render();
}

void SC_Game::ShowElapseTime()
{
	string time = "";

	int m = m_fElapseTime / 60;
	int s = (int)m_fElapseTime % 60;

	if (m > 0)
		time += to_string(m) + "분 ";
	if (s > 0)
		time += to_string(s) + "초";

	TEXT->Add(time, 1390, 767, 26, "나눔명조", 0xFFFFFFFF);
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

void SC_Game::WriteRank(string name, int item)
{
	ofstream outFile("Ranking.sav", ofstream::out | ofstream::app);

	outFile << name << "\t" << m_fElapseTime << "\t"
		<< item << endl;

	outFile.close();
}
