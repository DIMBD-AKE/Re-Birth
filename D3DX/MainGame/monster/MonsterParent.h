#pragma once
#include "../Status.h"
#define MAXITEMNUM 4
//���͵��� �⺻ Ʋ�� �Ǵ� Ŭ�����̴�.

class Map;
class CharacterParant;
class AStar;
class DropManager;
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

	D3DXVECTOR3		m_vDir;

	int				m_nPatternChangeCount;
	int				m_nMinMoveCount, m_nMaxMoveCount;

	int				m_nCount;
protected:

	//���� ����
	STATUS m_uMonsterStat;

	//�������ɋ����� �ð�
	int m_nResPawnCount;

	//����ī��Ʈ
	int m_nAttackDelay;
	
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
		m_uMonsterStat.chr.nCurrentHP -= hp;
		if (m_uMonsterStat.chr.nCurrentHP <= 0)
		{
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

	void Update();

	void RespawnUpdate();

	void Render();
	
	void Respawn(D3DXVECTOR3 spawnPos);
};

