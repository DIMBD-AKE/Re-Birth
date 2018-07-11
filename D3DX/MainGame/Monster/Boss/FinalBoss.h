#pragma once
#include "BossParent.h"

class FinalBoss :
	public BossParent
{

protected:

	virtual void DropItemSetup() override;

	virtual void ChangeAni() override;

	virtual void Pattern() override;

	virtual void SetupStat() override;


	virtual void Attack() override;
	virtual void Move() override;
	void Skill1();
	void Skill2();
	void Casting();

public:
	FinalBoss();
	virtual ~FinalBoss();

	virtual void SetupBoss(Map* map, D3DXVECTOR3 pos) override;

	
};

