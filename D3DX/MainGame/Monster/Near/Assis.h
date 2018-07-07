#pragma once
#include "NearMonster.h"

class Assis :
	public NearMonster
{
public:
	Assis();
	virtual	~Assis();

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos) override;
	virtual void SetupStat() override;

	//���� ���� �����Լ�
	//virtual void Attack() override;
	//���� ���� ��ų�Լ�
	virtual void Skill() override;
	//���� ���� �⺻ �̵��Լ�
	//virtual void Move() override;

	virtual void DropItemSetup() override;
};

