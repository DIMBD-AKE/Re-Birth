#pragma once
#include "../ItemParent.h"

class PotionParent : public ItemParent
{
protected:
	float m_fHealAmount;						//ȸ����

public:
	PotionParent();
	virtual ~PotionParent();

	virtual PotionParent* Clone() override;

	virtual void Use(CharacterParant& pCharacter);
};

