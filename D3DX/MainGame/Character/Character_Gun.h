#pragma once
#include "CharacterParant.h"
class Character_Gun :
	public CharacterParant
{
public:
	Character_Gun();
	virtual ~Character_Gun();


	virtual void Init(Map* map, CHARSELECT order);
	virtual void Update();
	virtual void Render();

};

