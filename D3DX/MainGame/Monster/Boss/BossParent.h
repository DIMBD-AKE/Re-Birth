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
	//���� ����
	STATUS m_uMonsterStat;

	//�������ɋ����� �ð�
	int m_nResPawnCount;

	//����ī��Ʈ
	//int m_nAttackDelay;
	
	//Model* m_pDeathModel;
	
	MON_STATE m_eState;
	Map* m_pMap;

	AStar* m_pAStar;

	//��� ������ ���
	int m_nItemID[MAXITEMNUM];
	*/

public:

protected:

	virtual void SetupStat() override;

	//���� ���� �����Լ�
	virtual void Attack() override;
	//���� ���� ��ų�Լ�
	virtual void Skill() override;
	//���� ���� �⺻ �̵��Լ�
	virtual void Move() override;

	virtual void DropItemSetup() override;
public:
	BossParent();
	virtual ~BossParent();

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos) override;
};

