#pragma once
#include "../Status.h"
//몬스터들의 기본 틀이 되는 클래스이다.


class MonsterParent
{
	STATUS m_uMonsterStat;

	//리스폰상태인지 확인
	GET(bool, m_bIsRespawn, IsResPawn);

	//리스폰될떄까지 시간
	int m_nResPawnCount;
	
public:
	MonsterParent();
	~MonsterParent();

	void SetCurrentHP(float damage) { m_uMonsterStat.chr.fCurrentHP -= damage; }
};

