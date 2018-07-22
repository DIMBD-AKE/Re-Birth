#pragma once
#include "CharacterParant.h"
class Character_Sword :
	public CharacterParant
{
private:
	bool m_bIsShunpo;
	int m_nDC;

public:
	Character_Sword();
	virtual ~Character_Sword();


	virtual void Init(CHRTYPE type, CHARSELECT order);
	virtual void Update();
	virtual void Render();
	virtual void KeyControl();
	virtual void Attack();

	//skill
	void Shunpo();

	void SkillDealing();
};
