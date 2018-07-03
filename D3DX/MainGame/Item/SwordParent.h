#pragma once
#include "ItemParent.h"

class SwordParent : public ItemParent
{
public:
	SwordParent();
	~SwordParent();
	
	virtual void Skill1(Model* pModel, ST_DAMAGE pStatus, MonsterManager* pMonsterManager) override;
};

