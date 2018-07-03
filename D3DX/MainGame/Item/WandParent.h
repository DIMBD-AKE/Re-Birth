#pragma once
#include "ItemParent.h"

class WandParent : public ItemParent
{
public:
	WandParent();
	virtual ~WandParent();

	virtual void Skill1(Model* pModel, ST_DAMAGE pStatus, MonsterManager* pMonsterManager) override;
};

