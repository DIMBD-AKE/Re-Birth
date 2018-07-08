#pragma once
#include "../MonsterParent.h"

class DistanceMonster :
	public MonsterParent
{
protected:
	vector<D3DXVECTOR3> m_vWallVertex;

protected:

	//원거리 몬스터 공격함수
	virtual void Attack() override;
	//원거리 몬스터 스킬함수
	virtual void Skill() override;
	//원거리 몬스터 기본 이동함수
	virtual void Move() override;

	virtual void DropItemSetup() override;

	virtual void SetupStat() override;

	bool AttackPossible();
public:
	DistanceMonster();
	~DistanceMonster();

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos) override;
	

	
};

