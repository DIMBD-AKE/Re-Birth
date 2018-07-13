#pragma once
#include "../ItemParent.h"

class SwordParent : public ItemParent
{
public:
	SwordParent();
	virtual ~SwordParent();
	virtual SwordParent* Clone() override;

	virtual void Skill1(CharacterParant* pCharacter, ST_DAMAGE pStatus, MonsterManager* pMonsterManager) override;
};

