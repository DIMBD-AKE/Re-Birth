#pragma once
#include "MagicMonster.h"

class DarkHell :
	public MagicMonster
{

private:

	virtual void SetupStat() override;

	virtual void Skill() override;

	virtual void DropItemSetup() override;

public:
	DarkHell();
	virtual ~DarkHell();

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos) override;
	
};

