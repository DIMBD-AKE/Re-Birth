#pragma once
#include "bossparent.h"

class MiddleBoss :
	public BossParent
{
public:
	MiddleBoss();
	~MiddleBoss();

	virtual void SetupBoss(Map* map, D3DXVECTOR3 pos) override;
};

