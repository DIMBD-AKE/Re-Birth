#pragma once
#include "../Status.h"
//���͵��� �⺻ Ʋ�� �Ǵ� Ŭ�����̴�.

class Map;

enum MON_STATE{
	MS_IDLE,
	MS_RUN,
	MS_SKILL,
	MS_ATTACK,
	MS_DIE,
	MS_NONE,
};

class MonsterParent
{

	//�������������� Ȯ��
	//���̸� �׾ ��������
	GET(bool, m_bIsRespawn, IsResPawn);
	GET(Model*, m_pModel, Model);

protected:

	//���� ����
	STATUS m_uMonsterStat;

	//�������ɋ����� �ð�
	int m_nResPawnCount;

	
	//Model* m_pDeathModel;
	
	MON_STATE m_eState;
	Map* m_pMap;
public:
	MonsterParent();
	~MonsterParent();

	void SetCurrentHP(int hp)
	{ m_uMonsterStat.chr.nCurrentHP -= hp; 
	if (m_uMonsterStat.chr.nCurrentHP <= 0)
		m_bIsRespawn = true;
	}

	void CalculDamage(float damage);

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos);
	virtual void SetupStat() = 0;
	virtual void Update();
	virtual void RespawnUpdate();
	virtual void Render();
	

	void ChangeAni();
	void Respawn(D3DXVECTOR3 spawnPos);
};

