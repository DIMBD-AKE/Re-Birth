#include "../../stdafx.h"
#include "Character_Magic.h"
#include "../Map.h"
#include "Inventory.h"
#include "../Status.h"


Character_Magic::Character_Magic()
{
}


Character_Magic::~Character_Magic()
{
}


void Character_Magic::Init(Map * map, CHARSELECT order)
{
	m_eChrType = CHRTYPE_MAGIC;

	if (order == CHAR_ONE)
	{
		m_pCharacter = MODELMANAGER->GetModel("아카날", MODELTYPE_X);
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
		m_pCharacter = MODELMANAGER->GetModel("헤스티아", MODELTYPE_X);
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

void Character_Magic::Update()
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

void Character_Magic::Render()
{
	if (m_pCharacter)
	{
		m_pCharacter->Render();
		m_pInventory->Render();
	}
}


