#pragma once
#include "ItemParent.h"

class GunParent : public ItemParent
{
public:
	GunParent();
	~GunParent();

	virtual void Skill1(Model* pModel, ST_DAMAGE pStatus, MonsterManager* pMonsterManager) override;
};

