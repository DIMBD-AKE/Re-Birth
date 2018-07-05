#pragma once
#include "../Status.h"
//몬스터들의 기본 틀이 되는 클래스이다.

class Map;
class CharacterParant;

enum MON_STATE{
	MS_IDLE,
	MS_RUN,
	MS_SKILL,
	MS_ATTACK,
	MS_DIE,
	MS_NONE,
};

class MonsterParent
{

	//리스폰상태인지 확인
	//참이면 죽어서 리스폰중
	GET(bool, m_bIsRespawn, IsResPawn);
	GET(Model*, m_pModel, Model);
	SET(CharacterParant*, m_pCharacter, Character);

protected:

	//몬스터 스탯
	STATUS m_uMonsterStat;

	//리스폰될떄까지 시간
	int m_nResPawnCount;

	
	//Model* m_pDeathModel;
	
	MON_STATE m_eState;
	Map* m_pMap;
public:
	MonsterParent();
	virtual ~MonsterParent();

	void SetCurrentHP(int hp)
	{ m_uMonsterStat.chr.nCurrentHP -= hp; 
	if (m_uMonsterStat.chr.nCurrentHP <= 0)
		m_bIsRespawn = true;
	}

	void CalculDamage(float damage);

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos);
	virtual void SetupStat();
	void Update();

	void RespawnUpdate();

	void Render();
	

	void ChangeAni();
	void Respawn(D3DXVECTOR3 spawnPos);

	/*
	MS_IDLE,
	MS_RUN,
	MS_SKILL,
	MS_ATTACK,
	MS_DIE,
	MS_NONE,
	*/
	//몬스터 공격함수
	virtual void Attack();
	//몬스터 스킬함수
	virtual void Skill();
	//몬스터 기본 이동함수
	virtual void Move();
};

