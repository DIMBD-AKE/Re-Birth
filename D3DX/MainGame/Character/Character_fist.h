#pragma once
#include "CharacterParant.h"
class Character_fist :
	public CharacterParant
{
public:
	Character_fist();
	virtual ~Character_fist();


	virtual void Init(CHRTYPE type, CHARSELECT order);
	virtual void Update();
	virtual void Render();
	virtual void KeyControl();
	virtual void Attack();

};

