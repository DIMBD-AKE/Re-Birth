#pragma once
#include "CharacterParant.h"
class Character_Magic :
	public CharacterParant
{
public:
	Character_Magic();
	virtual ~Character_Magic();

	virtual void Init(CHRTYPE type, CHARSELECT order, DropManager* Drop);
	virtual void Update();
	virtual void Render();
	virtual void KeyControl();
	virtual void Attack();
	void targetAttack();
	void CristalField();

	void MgSkill();
	
};

