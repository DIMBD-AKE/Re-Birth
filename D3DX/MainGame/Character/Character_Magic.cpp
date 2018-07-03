#include "../../stdafx.h"
#include "Character_Magic.h"
#include "../Map.h"
#include "Inventory.h"


Character_Magic::Character_Magic()
{
}


Character_Magic::~Character_Magic()
{
}


void Character_Magic::Init(Map * map, CHARSELECT order)
{
	if (order == CHAR_ONE)
	{
		m_pCharacter = MODELMANAGER->GetModel("아카날", MODELTYPE_X);
		CharacterParant::Init(map, order);
	}
	else if (order == CHAR_TWO)
	{
		m_pCharacter = MODELMANAGER->GetModel("헤스티아", MODELTYPE_X);
		CharacterParant::Init(map, order);
	}
}

void Character_Magic::Update()
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

void Character_Magic::Render()
{
	if (m_pCharacter)
	{
		m_pCharacter->Render();
		m_pInventory->Render();
	}
}

void Character_Magic::ChangeAnimation()
{
	
}
