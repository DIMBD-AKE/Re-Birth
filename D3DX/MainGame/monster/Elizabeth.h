#pragma once
#include "MonsterParent.h"

class Elizabeth :
	public MonsterParent
{
public:
	Elizabeth();
	~Elizabeth();

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void SetupStat() override;
};

