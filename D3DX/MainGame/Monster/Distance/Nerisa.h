#pragma once
#include "DistanceMonster.h"

class Nerisa :
	public DistanceMonster
{

private:

	virtual void SetupStat() override;

	//���Ÿ� ���� ��ų�Լ�
	virtual void Skill() override;

	virtual void DropItemSetup() override;

public:
	Nerisa();
	virtual ~Nerisa();

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos) override;

};

