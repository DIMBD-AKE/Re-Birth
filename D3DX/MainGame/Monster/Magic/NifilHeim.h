#pragma once
#include "MagicMonster.h"

class NifilHeim :
	public MagicMonster
{
public:
	NifilHeim();
	virtual ~NifilHeim();

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

