#include "../../stdafx.h"
#include "SC_Test.h"
#include "../Map.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../Character/Character_Sword.h"
#include "../Item/DropManager.h"
#include "../../Framework/EffectObject.h"
#include "../SkillManager.h"

SC_Test::SC_Test()
{
}


SC_Test::~SC_Test()
{
}

void SC_Test::Release()
{
	SAFE_DELETE(m_pSampleMap);
	SAFE_DELETE(m_pCharacter);
	SAFE_DELETE(m_pDropManager);
	SAFE_DELETE(m_pMM);
	SAFE_DELETE(m_pSkill);
}

void SC_Test::Init()
{
	m_pSampleMap = new Map;
	m_pSampleMap->Load("Map/Sample.map");

	m_pDropManager = new DropManager;
	m_pDropManager->Init();

	m_pCharacter = new Character_Sword;
	m_pMM = new MonsterManager;

	m_pCharacter->Init(m_pSampleMap, CHAR_ONE, m_pMM);

	m_pMM->Setup(m_pSampleMap, &m_pCharacter);
	m_pMM->SetSpawnSpat(m_pSampleMap->GetSpawnEnemy());
	m_pMM->MakeMonster(m_pDropManager);

	//CAMERA->SetMode(CAMERA_FOLLOW_FREE);
	CAMERA->SetTargetOffset(D3DXVECTOR3(0, 4, 0));
	CAMERA->SetCamOffset(D3DXVECTOR3(0, 3, 17));
	CAMERA->SetFog(true, 50, 100, D3DCOLOR_XRGB(255, 255, 255), 1.0f);

	m_pSkill = SKILL->GetSkill("Test Skill");
}

void SC_Test::Update()
{
	if (INPUT->KeyDown('R'))
	{
		ST_SKILL skill;
		ZeroMemory(&skill, sizeof(ST_SKILL));
		skill.fDamage = 200;
		skill.fDamageDelay = 0;
		skill.fDamageInterval = 0;
		skill.fMaxLength = 15;
		skill.fAngle = 60;
		skill.nMaxTarget = 5;
		skill.nDamageCount = 100;
		skill.fYOffset = 1;
		skill.fEffectTime = 3;
		skill.fBuffTime = -1;
		skill.buffStatus.chr.nCurrentHP = 100;
		m_pSkill->Prepare(m_pCharacter, m_pMM->GetMonsterVector()[0], m_pMM->GetMonsterVector(),
			skill, SKILLO_CHARACTER);
	}

	if (INPUT->KeyDown('F'))
		m_pSkill->Trigger();

	m_pSkill->Update();
	
	m_pCharacter->Update();
	m_pMM->Update();
	m_pDropManager->GetDropItem(m_pCharacter);

	TEXT->Add(to_string(TIME->GetFPS()), 0, 0, 20);
}

void SC_Test::Render()
{
	if (m_pSampleMap)
		m_pSampleMap->Render();

	m_pDropManager->Render();
	m_pCharacter->Render();
	m_pMM->Render();

	m_pSkill->Render();

	TEXT->Render();
}