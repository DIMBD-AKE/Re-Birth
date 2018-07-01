#pragma once
#include "CharacterParant.h"
class Character_Sword :
	public CharacterParant
{
public:
	Character_Sword();
	virtual ~Character_Sword();


	virtual void Init(Map* map);
	virtual void Update();
	virtual void Render();
	virtual void ChangeAnimation();
};

