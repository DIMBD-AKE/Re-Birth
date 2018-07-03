#include "../../stdafx.h"
#include "SC_Test.h"
#include "../Map.h"
#include "../Character/Inventory.h"
#include "../Character/Character_Sword.h"
#include "../Character/Character_Gun.h"
#include "../Character/Character_Magic.h"

#include "../monster/PathFind.h"
#include "../monster/MonsterManager.h"

#include "../Item/ItemParent.h"

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
}

void SC_Test::Init()
{

	m_pSampleMap = new Map;
	m_pSampleMap->Load("Map/Sample.map");


	m_pTestModel = new Character_Sword;
	m_pTestModel->Init(m_pSampleMap, CHAR_ONE);


	
	
	D3DXVECTOR3 startPos = m_pSampleMap->GetSpawnPlayer();
	float y = m_pSampleMap->GetHeight(startPos.x, startPos.z);
	

	
	Inventory inv;
	inv.CreateInventory(3, 5);


	m_pMM = new MonsterManager;
	m_pMM->Setup(m_pSampleMap);

	m_pMM->SetSpawnSpat(m_pSampleMap->GetSpawnEnemy());
	m_pMM->MakeMonster();

	m_pItem = new ItemParent;
	m_pItem->SetUp();


}

void SC_Test::Update()
{
	if (m_pTestModel)
	{
		m_pTestModel->Update();


		if (INPUT->KeyPress('1'))
		{
			
			SAFE_DELETE(m_pTestModel);
			m_pTestModel = new Character_Sword;
			m_pTestModel->Init(m_pSampleMap, CHAR_TWO);
		}
	}
	
	//여기 한줄
	if (m_pMM) m_pMM->Update();
}

void SC_Test::Render()
{
	if (m_pTestModel)
		m_pTestModel->Render();


	if (m_pSampleMap)
		m_pSampleMap->Render();
	//여기 한줄
	if (m_pMM) m_pMM->Render();

	if (m_pItem)m_pItem->Render(D3DXVECTOR3(0, 0, 0), 50);
}
