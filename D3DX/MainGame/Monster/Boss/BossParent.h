#pragma once
#include "../MonsterParent.h"

enum BOSS_STATE{
	BS_ENTER,			//보스 등장상태
	BS_IDLE,			//제자리에 있는 상태
	BS_RUN,				//보스 뛰는 상태
	BS_PASSIVE,			//보스 패시브 상태
	BS_ATTACK,			//보스 공격 상태
	BS_SKILL1,			//스킬1 상태
	BS_SKILL2,			//스킬2 상태
	BS_CASTING,			//스킬2 캐스팅중
	BS_DIE,				//보스 사망상태
	BS_NONE				//사망 애니메이션 끝나고 멈추기 위한 상태
};

class BossParent :
	public MonsterParent
{
protected : 

	bool m_bIsDead;

	BOSS_STATE m_eBossState;
	/*
	
	UIObject* m_pHPBar;

	D3DXVECTOR3		m_vDir;

	int				m_nPatternChangeCount;
	int				m_nMinMoveCount, m_nMaxMoveCount;

	int				m_nCount;
	//몬스터 스탯
	STATUS m_uMonsterStat;

	//공격카운트
	//int m_nAttackDelay;
	
	//Model* m_pDeathModel;
	
	MON_STATE m_eState;
	Map* m_pMap;

	AStar* m_pAStar;

	//드랍 아이템 목록
	int m_nItemID[MAXITEMNUM];
	*/


protected:

	virtual void SetupStat() override;

	//근접 몬스터 공격함수
	virtual void Attack() override;
	//근접 몬스터 스킬함수
	virtual void Skill() override;
	//근접 몬스터 기본 이동함수
	virtual void Move() override;

	virtual void DropItemSetup() override;

	virtual void ChangeAni() override;

	virtual void Pattern();
	
public:
	BossParent();
	virtual ~BossParent();

	virtual void SetupBoss(Map* map, D3DXVECTOR3 pos) override;
	virtual void Update() override;
	virtual void Render() override;
	//virtual void Update() override;
};

