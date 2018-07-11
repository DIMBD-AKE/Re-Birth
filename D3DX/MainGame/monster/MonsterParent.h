#pragma once
#include "../Status.h"
#define MAXITEMNUM 4
//몬스터들의 기본 틀이 되는 클래스이다.

class Map;
class CharacterParant;
class AStar;
class DropManager;
class UIObject;

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
	SET(CharacterParant**, m_ppCharacter, Character);
	SET(DropManager*, m_pDropManager, DropManager);

	//타겟팅이 되었냐(데미지를 입었냐)
	

protected:

	float m_fUIMoveX;
	float m_fUIMoveY;

	bool m_bIsTargeting;
	int m_nTargetingCount;

	UIObject* m_pHPBar;

	D3DXVECTOR3		m_vDir;

	int				m_nPatternChangeCount;
	int				m_nMinMoveCount, m_nMaxMoveCount;

	int				m_nCount;
	//몬스터 스탯
	STATUS m_uMonsterStat;

	//리스폰될떄까지 시간
	int m_nResPawnCount;

	//공격카운트
	//int m_nAttackDelay;
	
	//Model* m_pDeathModel;
	
	MON_STATE m_eState;
	Map* m_pMap;

	AStar* m_pAStar;

	//드랍 아이템 목록
	int m_nItemID[MAXITEMNUM];

protected:
	virtual void SetupStat();

	virtual void Attack();
	//몬스터 스킬함수
	virtual void Skill();
	//몬스터 기본 이동함수
	virtual void Move();
	//몬스터 별 드랍아이템 세팅함수
	virtual void DropItemSetup();
	//움직임 관련 리셋함수 (반대편으로 가야하냐)
	void MoveReset(bool isReverse, int max= 0 , int min= 0);
	//공격할수 있는 거리까지 가는 함수
	POINT MoveForAttack();
	void ItemDrop();

	void SetCurrentHP(int hp)
	{
		CURRENTHP(m_uMonsterStat) -= hp;
		m_bIsTargeting = true;
		m_nTargetingCount = 0;
		if (CURRENTHP(m_uMonsterStat) <= 0)
		{
			CURRENTHP(m_uMonsterStat) = 0;
			m_bIsRespawn = true;
			m_eState = MS_DIE;
			ChangeAni();
			ItemDrop();
		}
	}

	void ChangeAni();
	

public:
	MonsterParent();
	virtual ~MonsterParent();

	

	void CalculDamage(float damage);

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos);

	virtual void SetupBoss(Map* map, D3DXVECTOR3 pos);

	virtual void Update();

	void RespawnUpdate();

	void Render();
	
	void Respawn(D3DXVECTOR3 spawnPos);
};

