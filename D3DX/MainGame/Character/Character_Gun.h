#pragma once
#include "CharacterParant.h"
class Character_Gun :
	public CharacterParant
{
public:
	Character_Gun();
	virtual ~Character_Gun();


	virtual void Init(CHRTYPE type, CHARSELECT order);
	virtual void Update();
	virtual void Render();
	virtual void KeyControl();

};

