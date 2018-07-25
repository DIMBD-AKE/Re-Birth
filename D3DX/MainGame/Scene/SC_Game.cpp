#include "../../stdafx.h"
#include "SC_Game.h"
#include "../Map.h"
#include "../monster/MonsterManager.h"
#include "../Character/CharacterParant.h"
#include "../Character/Npc.h"
#include "../Item/DropManager.h"
#include "../Character/Inventory.h"
#include "../Item/ItemParent.h"

SC_Game::SC_Game()
{
}


SC_Game::~SC_Game()
{
	SAFE_DELETE(m_pCharacter);
	SAFE_DELETE(m_pNpc);
}

void SC_Game::Release()
{
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pDropManager);
	SAFE_DELETE(m_pMM);
	SAFE_RELEASE(m_pUI);
	for (auto p : m_vecParticle)
		SAFE_DELETE(p);
	m_vecParticle.clear();
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
	if (m_pData[3])
		m_sChrName = *(string*)m_pData[3];

	m_fGenTime = GetTickCount();

	m_pMap = new Map;
	CAMERA->SetFog(false, 0, 0, 0, 0);
	if (m_nStage == 0)
		m_pMap->Load("Map/Sample.map");
	else if (m_nStage == 1)
		m_pMap->Load("Map/Stage 1.map");
	else if (m_nStage == 2)
		m_pMap->Load("Map/Stage 2.map");
	else if (m_nStage == 3)
	{
		m_pMap->Load("Map/Stage 3.map");
		CAMERA->SetFog(true, 120, 150, D3DXCOLOR(0.3, 0.3, 0.3, 1), 0.2);
		for (int i = 0; m_vecParticle.size() < 10; i++)
		{
			D3DXVECTOR3 pos = D3DXVECTOR3(FRand(-100, 100), 0, FRand(-100, 100));
			float height = m_pMap->GetHeight(pos.x, pos.z);
			if (height > 0)
			{
				pos.y = height;
				Particle * particle = PARTICLE->GetParticle("Hell Smoke");
				particle->SetPosition(pos);
				particle->World();
				m_vecParticle.push_back(particle);
			}
		}
	}

	m_pDropManager = new DropManager;
	m_pDropManager->Init();

	m_pMM = new MonsterManager;

	m_pMM->Setup(m_pMap, &m_pCharacter);
	m_pMM->SetSpawnSpat(m_pMap->GetSpawnEnemy());
	m_pMM->MakeMonster(m_pDropManager);

	m_pCharacter->Reset(m_pMap, m_pMM, m_pDropManager);

	m_pNpc = new Npc;
	m_pNpc->Init(m_pMap->GetSpawnPlayer());
	m_pNpc->SetPlayerMemoryAddressLink(m_pCharacter);
	m_pCharacter->SetNpcMemoryAddressLink(m_pNpc);

	m_pUI = new UIObject;
	m_pUI->SetTexture(TEXTUREMANAGER->GetTexture("Game ElapseTime"));
	m_pUI->SetPosition(D3DXVECTOR3(1261, 754, 0));

	m_isRank = false;

	m_fGenTime = (GetTickCount() - m_fGenTime) * 0.001;
	if (m_fElapseTime > 0)
		m_fElapseTime -= m_fGenTime;

	m_pCharacter->Getstage(&m_nStage);
}

void SC_Game::Update()
{
	m_pMM->Update();
	m_pDropManager->GetDropItem(m_pCharacter);
	m_pCharacter->Update();
	m_pUI->Update();
	m_pNpc->Update();
	ShowElapseTime();

	TEXT->Add(to_string(TIME->GetFPS()), 0, 0, 20);

	if (INPUT->KeyDown(VK_RETURN))
		NextStage();

	if (INPUT->KeyDown(VK_ESCAPE))
		ClearStage();

	if (!m_isRank && m_pMM->IsMiddleBossDie(NULL))
	{
		NextStage();
	}

	for (auto p : m_vecParticle)
		p->Update();

	if (m_fElapseTime < 0.0001)
		m_fElapseTime -= m_fGenTime;
	m_fElapseTime += TIME->GetElapsedTime();
}

void SC_Game::Render()
{
	m_pMap->Render();

	m_pDropManager->Render();
	m_pCharacter->Render();
	m_pNpc->Render();
	m_pMM->Render();

	for (auto p : m_vecParticle)
		p->Render();

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
	WriteRank();
	CAMERA->SetTarget(NULL, NULL);
	SAFE_DELETE(m_pCharacter);
	SCENE->ChangeScene("Main");
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

void SC_Game::WriteRank()
{
	ofstream outFile("Ranking.rev", ofstream::out | ofstream::app);

	outFile << endl;

	if (m_pCharacter->Getm_Inventory()->GetWeapon())
		outFile << m_sChrName << "\t" << m_fElapseTime << "\t"
			<< m_pCharacter->Getm_Inventory()->GetWeapon()->GetID();
	else
		outFile << m_sChrName << "\t" << m_fElapseTime << "\t"
		<< -1;

	outFile.close();
}
