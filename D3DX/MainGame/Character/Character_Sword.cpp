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
		//일본도여캐
		m_pCharacter = MODELMANAGER->GetModel("베카", MODELTYPE_X);
		
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 72.0f;
		m_Status->chr.fCheRate = 5.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 25.0f;
		m_Status->chr.fPhyRate = 60.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 60;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 10;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 10;
		CharacterParant::Init(map, order);
	}
	else if (order == CHAR_TWO)
	{
		//긴칼여캐
		m_pCharacter = MODELMANAGER->GetModel("리아", MODELTYPE_X);
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 72.0f;
		m_Status->chr.fCheRate = 5.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 25.0f;
		m_Status->chr.fPhyRate = 60.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 60;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 10;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 10;
		CharacterParant::Init(map, order);
	}
	else if (order == CHAR_THREE)
	{
		//전기톱 여캐
		m_pCharacter = MODELMANAGER->GetModel("벨벳", MODELTYPE_X);
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 72.0f;
		m_Status->chr.fCheRate = 5.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 25.0f;
		m_Status->chr.fPhyRate = 60.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 60;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 10;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 10;
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



