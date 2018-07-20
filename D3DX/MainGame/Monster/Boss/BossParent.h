#pragma once
#include "../MonsterParent.h"

class MagicCircle;
class Skill;

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

	//공격시 생성되는 구
	MagicCircle* m_pMagicCircle;

	//마법타입은 공격중 멀어져도 지속적인 공격이 되어야 한다.
	bool m_bIsAttack;
	bool m_bIsDead;

	BOSS_STATE m_eBossState;

	//3타스킬
	Skill* m_pSkill2;

	//3타스킬 스탯
	ST_SKILL m_stSkill2;

	SET(MonsterManager*, m_pMM, MM);

	float m_fSkillCoolTimeCount2 ;
	int m_nSkillCooltime2;
	bool m_bSkill2Use;
	
	/*
	
	UIObject* m_pHPBar;

	D3DXVECTOR3		m_vDir;

	int				m_nPatternChangeCount;
	int				m_nMinMoveCount, m_nMaxMoveCount;

	int				m_nCount;
	//몬스터 스탯
	STATUS m_pMonsterStat;

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

	virtual void RespawnUpdate() override
	{

	}

	virtual void SetupStat() override;
	virtual void SetupSkill() override;
	//근접 몬스터 공격함수
	virtual void Attack() override;
	//근접 몬스터 스킬함수
	virtual void SkillUse() override;
	//근접 몬스터 기본 이동함수
	virtual void Move() override;

	virtual void DropItemSetup() override;

	virtual void ChangeAni() override;

	virtual void Pattern();

	virtual void SetCurrentHP(int hp);

	bool AbleSkill2();
	void SkillPrepare2();

	
	
public:
	BossParent();
	virtual ~BossParent();

	virtual void SetupBoss(Map* map, D3DXVECTOR3 pos) override;
	virtual void Update() override;
	virtual void Render() override;

	bool IsDie() {
		if (m_eBossState == BS_NONE) return true;
		return false;
	}
	//virtual void Update() override;
};

