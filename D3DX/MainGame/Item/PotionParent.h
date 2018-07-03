#pragma once
#include "ItemParent.h"

class PotionParent : public ItemParent
{
public:
	PotionParent();
	virtual ~PotionParent();

	virtual void Use(CharacterParant& pCharacter);
};

