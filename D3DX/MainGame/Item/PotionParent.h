#pragma once
#include "ItemParent.h"

class PotionParent : public ItemParent
{
protected:
	float m_fHealAmount;						//ȸ����

public:
	PotionParent();

	virtual ~PotionParent();

	virtual void Use(CharacterParant& pCharacter);
};

