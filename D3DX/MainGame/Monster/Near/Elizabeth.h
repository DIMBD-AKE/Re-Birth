#pragma once
#include "NearMonster.h"

class Elizabeth :
	public NearMonster
{
public:
	Elizabeth();
	virtual ~Elizabeth();

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos) override;
	virtual void SetupStat() override;

	//���� ���� �����Լ�
	virtual void Attack() override;
	//���� ���� ��ų�Լ�
	virtual void Skill() override;
	//���� ���� �⺻ �̵��Լ�
	virtual void Move() override;
};
