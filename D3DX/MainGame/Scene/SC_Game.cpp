#include "../../stdafx.h"
#include "SC_Game.h"
#include "../Map.h"
#include "../monster/MonsterManager.h"
#include "../Character/CharacterParant.h"
#include "../Character/Npc.h"
#include "../Item/DropManager.h"
#include "../Character/Inventory.h"
#include "../Item/ItemParent.h"
#include "../Character/Pet.h"

SC_Game::SC_Game()
	: m_pNpc(NULL)
{
}


SC_Game::~SC_Game()
{
	SAFE_DELETE(m_pCharacter);
	SAFE_DELETE(m_pNpc);
	SAFE_DELETE(m_pPet);
}

void SC_Game::OnClick(UIObject * pSender)
{
	if (pSender->GetName().compare("Exit") == 0 && PAUSE)
	{
		ClearStage();
		PAUSE = false;
	}
}

void SC_Game::Release()
{
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pDropManager);
	SAFE_DELETE(m_pMM);
	SAFE_RELEASE(m_pGameUI);
	SAFE_RELEASE(m_pPauseUI);
	SAFE_RELEASE(m_pStageUI);

	for (auto p : m_vecParticle)
		SAFE_DELETE(p);
	m_vecParticle.clear();
	if (m_pNpc) m_pNpc->Once();
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

	//m_nStage = 3;

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
	m_pMM->MakeMonster(m_pDropManager, m_nStage);

	if (!m_pNpc)
		m_pNpc = new Npc;

	if (!m_pPet)
		m_pPet = new Pet;

	m_pCharacter->Reset(m_pMap, m_pMM, m_pDropManager, m_pPet);

	//npc구현이 끝나면 이닛부분 지워주세요!
	//m_pNpc->Init(m_pMap->GetSpawnPlayer());
	m_pNpc->SetPlayerMemoryAddressLink(m_pCharacter);
	m_pCharacter->SetNpcMemoryAddressLink(m_pNpc);

	m_pGameUI = new UIObject;
	m_pGameUI->SetTexture(TEXTUREMANAGER->GetTexture("Game ElapseTime"));
	m_pGameUI->SetPosition(D3DXVECTOR3(1261, 754, 0));

	m_pStageUI = new UIObject;
	m_pStageUI->SetTexture(TEXTUREMANAGER->GetTexture("Stage Name"));
	m_pStageUI->SetPosition(D3DXVECTOR3(1520 / 2, 147, 0));
	m_pStageUI->SetAnchor(UIAC_C);

	m_pPauseUI = new UIObject;
	m_pPauseUI->SetTexture(TEXTUREMANAGER->GetTexture("White"));
	m_pPauseUI->SetAlpha(150);
	m_pPauseUI->SetColor(D3DXVECTOR3(0, 0, 0));
	
	UIObject * exitButton = new UIObject;
	exitButton->SetTexture(TEXTUREMANAGER->GetTexture("Main Button"));
	exitButton->SetAnchor(UIAC_C);
	exitButton->SetPosition(D3DXVECTOR3(1520 / 2, 805 / 2, 0));
	exitButton->SetScale(D3DXVECTOR3(0.7, 0.7, 1));
	exitButton->SetFunction(this);
	exitButton->SetAlpha(200);
	exitButton->SetName("Exit");
	m_pPauseUI->AddChild(exitButton);

	m_isStart = false;
	m_fStageElapse = 0;

	m_fGenTime = (GetTickCount() - m_fGenTime) * 0.001;

	m_pCharacter->Getstage(&m_nStage);

	m_pMM->SetNpc(m_pNpc);
}

void SC_Game::Update()
{
	m_pMM->Update(m_nStage);
	m_pDropManager->GetDropItem(m_pCharacter, m_pPet);
	m_pCharacter->Update();
	m_pNpc->Update();
	if (!m_pDropManager->GetDropList().empty() && !m_pCharacter->Getm_Inventory()->IsFull())
		m_pPet->ChangeTarget(&m_pDropManager->GetDropList()[0].pos, 1);
	else
		m_pPet->ChangeTarget(m_pCharacter->GetCharacter()->GetPosition(), 3);

	// 스테이지 이름
	if (m_fStageElapse < 1)
		m_pStageUI->SetAlpha(m_fStageElapse / 1.0f * 255);
	if (m_fStageElapse > 3)
		m_pStageUI->SetAlpha(Clamp(0, 255, (1.0 - (m_fStageElapse - 3) / 1.0f) * 255));
	if (m_fStageElapse < 4)
	{
		if (m_nStage == 0)
			TEXT->Add("테스트", 740, 130, 32, "나눔명조", D3DCOLOR_ARGB(m_pStageUI->GetAlpha(), 255, 255, 255));
		if (m_nStage == 1)
			TEXT->Add("사막 - 중간보스", 670, 130, 32, "나눔명조", D3DCOLOR_ARGB(m_pStageUI->GetAlpha(), 255, 255, 255));
		if (m_nStage == 2)
			TEXT->Add("마을", 750, 130, 32, "나눔명조", D3DCOLOR_ARGB(m_pStageUI->GetAlpha(), 255, 255, 255));
		if (m_nStage == 3)
			TEXT->Add("최종보스", 730, 130, 32, "나눔명조", D3DCOLOR_ARGB(m_pStageUI->GetAlpha(), 255, 255, 255));
	}

	m_pGameUI->Update();
	m_pPauseUI->Update();
	m_pStageUI->Update();

	TEXT->Add(to_string(TIME->GetFPS()), 0, 0, 20);

	if (INPUT->KeyDown(VK_RETURN))
		NextStage();

	if (INPUT->KeyDown(VK_ESCAPE))
		PAUSE = !PAUSE;

	if (m_pMM->isKeyMonsterDie())
	{
		NextStage();
	}

	for (auto p : m_vecParticle)
		p->Update();

	if (!m_isStart)
	{
		m_isStart = true;
		m_fElapseTime -= m_fGenTime;
		m_fStageElapse -= m_fGenTime;
	}
	m_fElapseTime += TIME->GetElapsedTime();
	if (m_fStageElapse < 4)
		m_fStageElapse += TIME->GetElapsedTime();
}

void SC_Game::Render()
{
	m_pMap->Render();

	m_pDropManager->Render();
	m_pNpc->Render();
	m_pMM->Render();
	m_pCharacter->Render();

	if (m_fStageElapse < 4)
		m_pStageUI->Render();

	m_pMap->ObjectRender();
	
	for (auto p : m_vecParticle)
		p->Render();

	if (!m_pNpc->GetCollision())
	{
		ShowElapseTime();
		m_pGameUI->Render();
	}

	if (PAUSE)
	{
		m_pPauseUI->Render();
		TEXT->Add("종료", 734, 388, 30, "나눔명조", 0xFFFFFFFF);
	}
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
	CAMERA->SetTarget(NULL, NULL);
	SAFE_DELETE(m_pCharacter);
	SAFE_DELETE(m_pNpc);
	SAFE_DELETE(m_pPet);
	SCENE->ChangeScene("Main");
}

void SC_Game::NextStage()
{
	ZeroMemory(m_pData, sizeof(void*) * 10);
	m_nStage++;
	if (m_nStage > 3)
	{
		WriteRank();
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
