#pragma once
#include "PotionParent.h"
class HealthHighPotion : public PotionParent
{
public:
	HealthHighPotion();
	~HealthHighPotion();

	virtual void SetUp();
	virtual void Use(CharacterParant& pCharacter);
};

