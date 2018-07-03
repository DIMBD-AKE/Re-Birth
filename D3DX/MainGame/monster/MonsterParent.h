#pragma once
#include "../Status.h"
//몬스터들의 기본 틀이 되는 클래스이다.

class Map;

class MonsterParent
{

	//리스폰상태인지 확인
	GET(bool, m_bIsRespawn, IsResPawn);

protected:

	//몬스터 스탯
	STATUS m_uMonsterStat;

	//리스폰될떄까지 시간
	int m_nResPawnCount;

	Model* m_pModel;
	
public:
	MonsterParent();
	~MonsterParent();

	void SetCurrentHP(float damage) { m_uMonsterStat.chr.fCurrentHP -= damage; }

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos);
	virtual void Update();
	virtual void Render();
};

