#include "../../stdafx.h"
#include "SC_Test.h"
#include "../Map.h"
#include "../Character/Inventory.h"
#include "../Character/Character_Sword.h"
#include "../Character/Character_Gun.h"
#include "../Character/Character_Magic.h"

//몬스터 관련 헤더
#include "../Astar/PathFind.h"
#include "../monster/MonsterManager.h"

//아이템 관련 헤더
#include "../Item/ItemParent.h"
#include "../Item/Potion/HealthPotion.h"
#include "../Item/DropManager.h"


DWORD FtoDw(float f) { return *((DWORD*)&f); }


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
	SAFE_DELETE(m_pPathFind);
	SAFE_DELETE(m_pMM);
	SAFE_DELETE(m_pItem);
	SAFE_DELETE(m_pPotion);
	SAFE_DELETE(m_pDropManager);
}

void SC_Test::Init()
{

	m_pSampleMap = new Map;
	m_pSampleMap->Load("Map/Sample.map");
	//m_pSampleMap->Load("Map/Nav.map");


	m_pTestModel = new Character_Sword;


	
	
	D3DXVECTOR3 startPos = m_pSampleMap->GetSpawnPlayer();
	float y = m_pSampleMap->GetHeight(startPos.x, startPos.z);
	

	
	Inventory inv;
	inv.CreateInventory(3, 5);

	//m_pPathFind = new PathFind;
	//m_pPathFind->Setup(m_pSampleMap->GetNavMesh());

	m_pDropManager = new DropManager;
	m_pDropManager->Init();

	m_pMM = new MonsterManager;
	m_pMM->Setup(m_pSampleMap, m_pTestModel);
	m_pTestModel->Init(m_pSampleMap, CHAR_ONE, m_pMM);

	m_pMM->SetSpawnSpat(m_pSampleMap->GetSpawnEnemy());
	m_pMM->MakeMonster(m_pDropManager);

	m_pItem = new ItemParent;
	m_pItem->SetUp();

	m_pPotion = new HealthPotion;
	m_pPotion->SetUp();

}

void SC_Test::Update()
{
	if (m_pTestModel && m_pTestModel->GetCondition() != CHAR_NONE)
	{
		m_pTestModel->Update();


		if (INPUT->KeyPress('0'))
		{
			CharacterParant* L_TestModel = m_pTestModel;
			CharacterParant* L_TestModel2;
			L_TestModel2 = new Character_Sword;
			L_TestModel2->Init(m_pSampleMap, CHAR_ONE, m_pMM);
			m_pTestModel = L_TestModel2;
			L_TestModel2 = NULL;
			SAFE_DELETE(L_TestModel);
		}
		if (INPUT->KeyPress('1'))
		{
			CharacterParant* L_TestModel = m_pTestModel;
			CharacterParant* L_TestModel2;
			L_TestModel2 = new Character_Sword;
			L_TestModel2->Init(m_pSampleMap, CHAR_TWO, m_pMM);
			m_pTestModel = L_TestModel2;
			L_TestModel2 = NULL;
			SAFE_DELETE(L_TestModel);
		}
		if (INPUT->KeyPress('2'))
		{
			CharacterParant* L_TestModel = m_pTestModel;
			CharacterParant* L_TestModel2;
			L_TestModel2 = new Character_Gun;
			L_TestModel2->Init(m_pSampleMap, CHAR_ONE, m_pMM);
			m_pTestModel = L_TestModel2;
			L_TestModel2 = NULL;
			SAFE_DELETE(L_TestModel);
		}
		if (INPUT->KeyPress('3'))
		{
			CharacterParant* L_TestModel = m_pTestModel;
			CharacterParant* L_TestModel2;
			L_TestModel2 = new Character_Gun;
			L_TestModel2->Init(m_pSampleMap, CHAR_TWO, m_pMM);
			m_pTestModel = L_TestModel2;
			L_TestModel2 = NULL;
			SAFE_DELETE(L_TestModel);
		}
		if (INPUT->KeyPress('4'))
		{
			CharacterParant* L_TestModel = m_pTestModel;
			CharacterParant* L_TestModel2;
			L_TestModel2 = new Character_Magic;
			L_TestModel2->Init(m_pSampleMap, CHAR_ONE, m_pMM);
			m_pTestModel = L_TestModel2;
			L_TestModel2 = NULL;
			SAFE_DELETE(L_TestModel);
		}
		if (INPUT->KeyPress('5'))
		{
			CharacterParant* L_TestModel = m_pTestModel;
			CharacterParant* L_TestModel2;
			L_TestModel2 = new Character_Magic;
			L_TestModel2->Init(m_pSampleMap, CHAR_TWO, m_pMM);
			m_pTestModel = L_TestModel2;
			L_TestModel2 = NULL;
			SAFE_DELETE(L_TestModel);
		}
		if (INPUT->KeyPress('6'))
		{
			CharacterParant* L_TestModel = m_pTestModel;
			CharacterParant* L_TestModel2;
			L_TestModel2 = new Character_Sword;
			L_TestModel2->Init(m_pSampleMap, CHAR_THREE, m_pMM);
			m_pTestModel = L_TestModel2;
			L_TestModel2 = NULL;
			SAFE_DELETE(L_TestModel);
		}
	}
	if (m_pTestModel->GetCondition() == CHAR_NONE)
	{
		CharacterParant* L_TestModel = m_pTestModel;
		CharacterParant* L_TestModel2;
		L_TestModel2 = new Character_Sword;
		L_TestModel2->Init(m_pSampleMap, CHAR_TWO, m_pMM);
		m_pTestModel = L_TestModel2;
		L_TestModel2 = NULL;
		SAFE_DELETE(L_TestModel);
	}
	//여기 한줄
	if (m_pMM) m_pMM->Update();
}

void SC_Test::Render()
{
	if (m_pTestModel)
		m_pTestModel->Render();


	if (m_pSampleMap)
	{
		DEVICE->SetRenderState(D3DRS_FOGENABLE, true);
		DEVICE->SetRenderState(D3DRS_FOGCOLOR, 0xffffffff);
		DEVICE->SetRenderState(D3DRS_FOGDENSITY, FtoDw(0.1f));         // 안개의 강도
		DEVICE->SetRenderState(D3DRS_FOGSTART, FtoDw(50.0f));         // 안개의 시작 위치
		DEVICE->SetRenderState(D3DRS_FOGEND, FtoDw(100.0f));         // 안개 강도의 최대값 위치
		DEVICE->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);      // 안개 중간 보간값
		

		m_pSampleMap->Render();
		//여기 한줄
		if (m_pMM) m_pMM->Render();

		if (m_pItem)m_pItem->Render(D3DXVECTOR3(0, 0, 0), 50);
		if (m_pPotion)m_pPotion->Render(D3DXVECTOR3(0, 0, 0), 50);
		m_pDropManager->Render();
		
		DEVICE->SetRenderState(D3DRS_FOGENABLE, false);
	}
}
