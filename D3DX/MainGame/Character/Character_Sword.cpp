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

void Character_Sword::Init(Map* map)
{
	m_pCharacter = MODELMANAGER->GetModel("¾Æ¸°", MODELTYPE_X);
	
	CharacterParant::Init(map);

}

void Character_Sword::Update()
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

void Character_Sword::Render()
{
	if (m_pCharacter)
	{
		m_pCharacter->Render();
		m_pInventory->Render();
	}
}

void Character_Sword::ChangeAnimation()
{
	if (m_bIsPressW)
	{
		m_pCharacter->SetAnimation("RUN");
	}
}
