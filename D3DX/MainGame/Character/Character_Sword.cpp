#include "../../stdafx.h"
#include "Character_Sword.h"
#include "../Map.h"
#include "Inventory.h"
#include "../Status.h"


Character_Sword::Character_Sword()
{
}


Character_Sword::~Character_Sword()
{
}

void Character_Sword::Init(Map* map, CHARSELECT order)
{
	m_eChrType = CHRTYPE_SWORD;

	if (order == CHAR_ONE)
	{
		m_pCharacter = MODELMANAGER->GetModel("베카", MODELTYPE_X);
		
		m_Status->chr.fAgi = 1.0f;
		m_Status->chr.fAtk = 1.0f;
		m_Status->chr.fAtkSpeed = 1.0f;
		m_Status->chr.fCheRate = 1.0f;
		m_Status->chr.fCurrentHP = 1.0f;
		m_Status->chr.fDef = 1.0f;
		m_Status->chr.fHit = 1.0f;
		m_Status->chr.fMagicRate = 1.0f;
		m_Status->chr.fMaxHp = 1.0f;
		m_Status->chr.fPhyRate = 1.0f;
		m_Status->chr.fSpeed = 1.0f;
		CharacterParant::Init(map, order);
	}
	else if (order == CHAR_TWO)
	{
		m_pCharacter = MODELMANAGER->GetModel("리아", MODELTYPE_X);
		m_Status->chr.fAgi = 1.0f;
		m_Status->chr.fAtk = 1.0f;
		m_Status->chr.fAtkSpeed = 1.0f;
		m_Status->chr.fCheRate = 1.0f;
		m_Status->chr.fCurrentHP = 1.0f;
		m_Status->chr.fDef = 1.0f;
		m_Status->chr.fHit = 1.0f;
		m_Status->chr.fMagicRate = 1.0f;
		m_Status->chr.fMaxHp = 1.0f;
		m_Status->chr.fPhyRate = 1.0f;
		m_Status->chr.fSpeed = 1.0f;
		CharacterParant::Init(map, order);


	}

}

void Character_Sword::Update()
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

void Character_Sword::Render()
{
	if (m_pCharacter)
	{
		m_pCharacter->Render();
		m_pInventory->Render();
	}
}



