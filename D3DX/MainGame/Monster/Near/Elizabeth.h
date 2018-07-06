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

	//근접 몬스터 공격함수
	virtual void Attack() override;
	//근접 몬스터 스킬함수
	virtual void Skill() override;
	//근접 몬스터 기본 이동함수
	virtual void Move() override;

	virtual void DropItemSetup() override;
};

