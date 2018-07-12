#pragma once
#include "DistanceMonster.h"

class Nike :
	public DistanceMonster
{

private:

	virtual void SetupStat() override;
	
	virtual void Skill() override;

	virtual void DropItemSetup() override;

public:
	Nike();
	virtual ~Nike();

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos, bool isSummon = false) override;

};

