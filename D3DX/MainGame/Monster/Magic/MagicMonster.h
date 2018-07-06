#pragma once
#include "../MonsterParent.h"

class MagicMonster :
	public MonsterParent
{
public:
	MagicMonster();
	virtual ~MagicMonster();

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

