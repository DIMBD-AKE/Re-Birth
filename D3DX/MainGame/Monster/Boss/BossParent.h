#pragma once
#include "../MonsterParent.h"

enum BOSS_STATE{
	BS_ENTER,			//���� �������
	BS_IDLE,			//���ڸ��� �ִ� ����
	BS_RUN,				//���� �ٴ� ����
	BS_PASSIVE,			//���� �нú� ����
	BS_ATTACK,			//���� ���� ����
	BS_SKILL1,			//��ų1 ����
	BS_SKILL2,			//��ų2 ����
	BS_CASTING,			//��ų2 ĳ������
	BS_DIE,				//���� �������
	BS_NONE				//��� �ִϸ��̼� ������ ���߱� ���� ����
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
	//���� ����
	STATUS m_uMonsterStat;

	//����ī��Ʈ
	//int m_nAttackDelay;
	
	//Model* m_pDeathModel;
	
	MON_STATE m_eState;
	Map* m_pMap;

	AStar* m_pAStar;

	//��� ������ ���
	int m_nItemID[MAXITEMNUM];
	*/


protected:

	virtual void SetupStat() override;

	//���� ���� �����Լ�
	virtual void Attack() override;
	//���� ���� ��ų�Լ�
	virtual void Skill() override;
	//���� ���� �⺻ �̵��Լ�
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

