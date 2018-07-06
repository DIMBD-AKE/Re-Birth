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
	SET(CharacterParant*, m_pCharacter, Character);
	SET(DropManager*, m_pDropManager, DropManager);

	D3DXVECTOR3		m_vDir;
	int				m_nPatternChangeCount;
	int				m_nCount;
protected:

	//���� ����
	STATUS m_uMonsterStat;

	//�������ɋ����� �ð�
	int m_nResPawnCount;

	
	//Model* m_pDeathModel;
	
	MON_STATE m_eState;
	Map* m_pMap;

	AStar* m_pAStar;

	//��� ������ ���
	int m_nItemID[MAXITEMNUM];

protected:
	virtual void Attack();
	//���� ��ų�Լ�
	virtual void Skill();
	//���� �⺻ �̵��Լ�
	virtual void Move();
	//���� �� ��������� �����Լ�
	virtual void DropItemSetup();
	//������ ���� �����Լ� (�ݴ������� �����ϳ�)
	void MoveReset(bool isReverse);
	//�����Ҽ� �ִ� �Ÿ����� ���� �Լ�
	POINT MoveForAttack();
	void ItemDrop();

public:
	MonsterParent();
	virtual ~MonsterParent();

	void SetCurrentHP(int hp)
	{ m_uMonsterStat.chr.nCurrentHP -= hp; 
	if (m_uMonsterStat.chr.nCurrentHP <= 0)
	{
		m_bIsRespawn = true;
		ItemDrop();
	}
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
	//���� �����Լ�
	
};

