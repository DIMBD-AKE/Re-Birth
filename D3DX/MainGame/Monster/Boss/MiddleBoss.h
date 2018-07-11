#pragma once
#include "bossparent.h"

class MiddleBoss :
	public BossParent
{

protected:

	virtual void DropItemSetup() override;

	virtual void ChangeAni() override;
	
	virtual void Pattern() override;

	virtual void Move() override;
	virtual void Attack() override;
	virtual void Skill() override;
public:
	MiddleBoss();
	~MiddleBoss();

	virtual void SetupBoss(Map* map, D3DXVECTOR3 pos) override;

	virtual void SetupStat() override;
};

