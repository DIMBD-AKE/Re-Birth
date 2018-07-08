#pragma once
#include "MagicMonster.h"

class DarkHell :
	public MagicMonster
{
public:
	DarkHell();
	virtual ~DarkHell();

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

