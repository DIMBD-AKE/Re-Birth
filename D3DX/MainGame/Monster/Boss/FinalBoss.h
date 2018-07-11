#pragma once
#include "BossParent.h"

class FinalBoss :
	public BossParent
{
public:
	FinalBoss();
	~FinalBoss();

	virtual void SetupBoss(Map* map, D3DXVECTOR3 pos) override;
};

