#pragma once
#include "CharacterParant.h"
class Character_Gun :
	public CharacterParant
{
protected:

public:
	Character_Gun();
	virtual ~Character_Gun();


	virtual void Init();
	virtual void Update();
	virtual void Render();
};

