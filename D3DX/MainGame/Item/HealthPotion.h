#pragma once
#include "PotionParent.h"
class HealthPotion : public PotionParent
{
public:
	HealthPotion();
	~HealthPotion();

	virtual void SetUp();
};

