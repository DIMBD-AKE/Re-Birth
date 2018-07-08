#pragma once
#include "MagicMonster.h"

class NifilHeim :
	public MagicMonster
{

private:
	virtual void SetupStat() override;

	virtual void Skill() override;

	virtual void DropItemSetup() override;

public:
	NifilHeim();
	virtual ~NifilHeim();

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos) override;
	
};

