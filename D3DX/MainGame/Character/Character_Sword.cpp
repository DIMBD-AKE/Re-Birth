#include "../../stdafx.h"
#include "Character_Sword.h"
#include "../Map.h"
#include "Inventory.h"


Character_Sword::Character_Sword()
{
}


Character_Sword::~Character_Sword()
{
}

void Character_Sword::Init(Map* map, CHARSELECT order)
{
	if (order == CHAR_ONE)
	{
		m_pCharacter = MODELMANAGER->GetModel("아린", MODELTYPE_X);
		CharacterParant::Init(map, order);
	}
	else if (order == CHAR_TWO)
	{
		m_pCharacter = MODELMANAGER->GetModel("리아", MODELTYPE_X);
		CharacterParant::Init(map, order);
	}

}

void Character_Sword::Update()
{
	
	if (m_pCharacter)
	{
		m_pCharacter->World();
		m_pCharacter->Update();
		KeyControl();
		Move();
		m_pInventory->Update();


		if(m_eCondition == CHAR_ATTACK) CalActionFrame();
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

void Character_Sword::CalActionFrame()
{
	m_nCalAction++; 
	if (m_nCalAction >= 50)
	{
		m_nCalAction = 0;
		m_eCondition = CHAR_IDLE;
		ChangeAnimation();

	}
}

