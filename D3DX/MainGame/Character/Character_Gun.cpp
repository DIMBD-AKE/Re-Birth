#include "../../stdafx.h"
#include "Character_Gun.h"
#include "../Map.h"
#include "Inventory.h"


Character_Gun::Character_Gun()
{
}


Character_Gun::~Character_Gun()
{
}


void Character_Gun::Init(Map * map, CHARSELECT order)
{
	if (order == CHAR_ONE)
	{
		m_pCharacter = MODELMANAGER->GetModel("메그너스", MODELTYPE_X);
		CharacterParant::Init(map, order);
	}
	else if (order == CHAR_TWO)
	{
		m_pCharacter = MODELMANAGER->GetModel("스카디", MODELTYPE_X);
		CharacterParant::Init(map, order);
	}
}

void Character_Gun::Update()
{
	if (m_pCharacter)
	{
		m_pCharacter->World();
		m_pCharacter->Update();
		Move();
		ChangeAnimation();
		m_pInventory->Update();
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

void Character_Gun::ChangeAnimation()
{
}
