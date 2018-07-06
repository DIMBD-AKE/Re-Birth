#pragma once
#include "../MonsterParent.h"

class DistanceMonster :
	public MonsterParent
{
public:
	DistanceMonster();
	~DistanceMonster();

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos) override;
	virtual void SetupStat() override;

	//���� ���� �����Լ�
	virtual void Attack() override;
	//���� ���� ��ų�Լ�
	virtual void Skill() override;
	//���� ���� �⺻ �̵��Լ�
	virtual void Move() override;

	virtual void DropItemSetup() override;
};

