#pragma once
#include "CharacterParant.h"
class Character_Sword :
	public CharacterParant
{
public:
	Character_Sword();
	virtual ~Character_Sword();


	virtual void Init(Map* map, CHRTYPE type, CHARSELECT order, MonsterManager* pMonsterManager);
	virtual void Update();
	virtual void Render();
	virtual void KeyControl();
};

