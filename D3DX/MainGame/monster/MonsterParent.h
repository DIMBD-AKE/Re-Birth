#pragma once
#include "../Status.h"
//몬스터들의 기본 틀이 되는 클래스이다.

class Map;
class CharacterParant;
class AStar;

enum MON_STATE{
	MS_IDLE,			//제자리에 있는 상태
	MS_RUN,				//비전투에 걷는 상태
	MS_SKILL,			//스킬 사용 상태
	MS_ATTACK,			//전투 상태
	MS_MOVEFORATTACK,	//전투 중 이동해야 하는 상태
	MS_DIE,				//죽은 상태
	MS_NONE,			//죽고나서 애니안돌리기 위한 값
};

class MonsterParent
{

	//리스폰상태인지 확인
	//참이면 죽어서 리스폰중
	GET(bool, m_bIsRespawn, IsResPawn);
	GET(Model*, m_pModel, Model);
	SET(CharacterParant*, m_pCharacter, Character);

	D3DXVECTOR3		m_vDir;
	int				m_nPatternChangeCount;
	int				m_nCount;
protected:

	//몬스터 스탯
	STATUS m_uMonsterStat;

	//리스폰될떄까지 시간
	int m_nResPawnCount;

	
	//Model* m_pDeathModel;
	
	MON_STATE m_eState;
	Map* m_pMap;

	AStar* m_pAStar;

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
	//움직임 관련 리셋함수 (반대편으로 가야하냐)
	void MoveReset(bool isReverse);
	//공격할수 있는 거리까지 가는 함수
	void MoveForAttack();
};

