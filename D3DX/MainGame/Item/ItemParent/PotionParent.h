#pragma once
#include "../ItemParent.h"

class PotionParent : public ItemParent
{
protected:
	float m_fHealAmount;						//È¸º¹·®

public:
	PotionParent();
	virtual ~PotionParent();

	virtual PotionParent* Clone() override;

	virtual void Use(CharacterParant& pCharacter);
};

