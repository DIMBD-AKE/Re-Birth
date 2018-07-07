#pragma once
#include "CharacterParant.h"
class Character_Magic :
	public CharacterParant
{
public:
	Character_Magic();
	virtual ~Character_Magic();

	virtual void Init(Map* map, CHARSELECT order, MonsterManager* pMonsterManager);
	virtual void Update();
	virtual void Render();
	
};

