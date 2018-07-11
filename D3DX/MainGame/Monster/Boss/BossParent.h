#pragma once
#include "../MonsterParent.h"

class BossParent :
	public MonsterParent
{
protected : 

	bool m_bIsDead;

	/*
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
	*/

public:

protected:

	virtual void SetupStat() override;

	//근접 몬스터 공격함수
	virtual void Attack() override;
	//근접 몬스터 스킬함수
	virtual void Skill() override;
	//근접 몬스터 기본 이동함수
	virtual void Move() override;

	virtual void DropItemSetup() override;
public:
	BossParent();
	virtual ~BossParent();

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos) override;
};

