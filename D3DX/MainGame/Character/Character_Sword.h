#pragma once
#include "CharacterParant.h"
class Character_Sword :
	public CharacterParant
{
public:
	Character_Sword();
	virtual ~Character_Sword();


	virtual void Init(CHRTYPE type, CHARSELECT order);
	virtual void Update();
	virtual void Render();
	virtual void KeyControl();
};

