#pragma once
#include "../Status.h"
#define MAXITEMNUM 4
//���͵��� �⺻ Ʋ�� �Ǵ� Ŭ�����̴�.

class Map;
class CharacterParant;
class AStar;
class DropManager;
class UIObject;

enum MON_STATE{
	MS_IDLE,			//���ڸ��� �ִ� ����
	MS_RUN,				//�������� �ȴ� ����
	MS_SKILL,			//��ų ��� ����
	MS_ATTACK,			//���� ����
	MS_MOVEFORATTACK,	//���� �� �̵��ؾ� �ϴ� ����
	MS_DIE,				//���� ����
	MS_NONE,			//�װ��� �ִϾȵ����� ���� ��
};

class MonsterParent
{

	//�������������� Ȯ��
	//���̸� �׾ ��������
	GET(bool, m_bIsRespawn, IsResPawn);
	GET(Model*, m_pModel, Model);
	SET(CharacterParant**, m_ppCharacter, Character);
	SET(DropManager*, m_pDropManager, DropManager);

	//Ÿ������ �Ǿ���(�������� �Ծ���)
	

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

protected:
	virtual void SetupStat();

	virtual void Attack();
	//���� ��ų�Լ�
	virtual void Skill();
	//���� �⺻ �̵��Լ�
	virtual void Move();
	//���� �� ��������� �����Լ�
	virtual void DropItemSetup();
	//������ ���� �����Լ� (�ݴ������� �����ϳ�)
	void MoveReset(bool isReverse, int max= 0 , int min= 0);
	//�����Ҽ� �ִ� �Ÿ����� ���� �Լ�
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

