#pragma once
#include "NearMonster.h"

class Assis :
	public NearMonster
{

private:

	virtual void SetupStat() override;

	virtual void Skill() override;

	virtual void DropItemSetup() override;

public:
	Assis();
	virtual	~Assis();

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos, bool isSummon = false) override;
	
};

