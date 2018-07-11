#pragma once
#include "BossParent.h"

class FinalBoss :
	public BossParent
{

protected:

	virtual void DropItemSetup() override;

	virtual void ChangeAni() override;

	virtual void Pattern() override;
	
public:
	FinalBoss();
	~FinalBoss();

	virtual void SetupBoss(Map* map, D3DXVECTOR3 pos) override;

	virtual void SetupStat() override;
};

