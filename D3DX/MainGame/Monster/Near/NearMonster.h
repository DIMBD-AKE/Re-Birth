#pragma once
#include "../MonsterParent.h"

class NearMonster :
	public MonsterParent
{
public:
	NearMonster();
	virtual ~NearMonster();

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos) override;
	virtual void SetupStat() override;

	//근접 몬스터 공격함수
	virtual void Attack() override;
	//근접 몬스터 스킬함수
	virtual void Skill() override;
	//근접 몬스터 기본 이동함수
	virtual void Move() override;
};

