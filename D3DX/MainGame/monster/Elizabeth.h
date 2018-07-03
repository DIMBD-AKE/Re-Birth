#pragma once
#include "C:\Users\woght\Documents\Github\Re-Birth\D3DX\MainGame\monster\MonsterParent.h"

class Elizabeth :
	public MonsterParent
{
public:
	Elizabeth();
	~Elizabeth();

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos) override;
	virtual void Update() override;
	virtual void Render() override;
};

