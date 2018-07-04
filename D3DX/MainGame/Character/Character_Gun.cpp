#include "../../stdafx.h"
#include "Character_Gun.h"
#include "../Map.h"
#include "Inventory.h"
#include "../Status.h"


Character_Gun::Character_Gun()
{
}


Character_Gun::~Character_Gun()
{
}


void Character_Gun::Init(Map * map, CHARSELECT order)
{
	m_eChrType = CHRTYPE_GUN;
	if (order == CHAR_ONE)
	{
		m_pCharacter = MODELMANAGER->GetModel("메그너스", MODELTYPE_X);
		m_Status->chr.fAgi = 1.0f;
		m_Status->chr.fAtkSpeed = 1.0f;
		m_Status->chr.fCheRate = 1.0f;
		m_Status->chr.fHit = 1.0f;
		m_Status->chr.fMagicRate = 1.0f;
		m_Status->chr.fPhyRate = 1.0f;
		m_Status->chr.fSpeed = 1.0f;
		m_Status->chr.nAtk = 1;
		m_Status->chr.nCurrentHP = 1;
		m_Status->chr.nDef = 1;
		m_Status->chr.nMaxHp = 1;
		CharacterParant::Init(map, order);
	}
	else if (order == CHAR_TWO)
	{
		m_pCharacter = MODELMANAGER->GetModel("스카디", MODELTYPE_X);
		m_Status->chr.fAgi = 1.0f;
		m_Status->chr.fAtkSpeed = 1.0f;
		m_Status->chr.fCheRate = 1.0f;
		m_Status->chr.fHit = 1.0f;
		m_Status->chr.fMagicRate = 1.0f;
		m_Status->chr.fPhyRate = 1.0f;
		m_Status->chr.fSpeed = 1.0f;
		m_Status->chr.nAtk = 1;
		m_Status->chr.nCurrentHP = 1;
		m_Status->chr.nDef = 1;
		m_Status->chr.nMaxHp = 1;
		CharacterParant::Init(map, order);
	}
}

void Character_Gun::Update()
{
	if (m_pCharacter)
	{
		Controller();
		KeyControl();
		Move();
		m_pInventory->Update();

		m_pCharacter->World();
		m_pCharacter->Update();
	}
}

void Character_Gun::Render()
{
	if (m_pCharacter)
	{
		m_pCharacter->Render();
		m_pInventory->Render();
	}
}


