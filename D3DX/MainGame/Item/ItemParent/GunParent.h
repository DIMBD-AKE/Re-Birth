#pragma once
#include "../ItemParent.h"

class GunParent : public ItemParent
{
public:
	GunParent();
	virtual ~GunParent();

	virtual GunParent* Clone() override;

	virtual void Skill1(CharacterParant* pCharacter, ST_DAMAGE pStatus, MonsterManager* pMonsterManager) override;
};

