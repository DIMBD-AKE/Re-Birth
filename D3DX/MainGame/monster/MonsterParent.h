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
	GET(bool, m_bIsRespawn, IsResPawn);

protected:

	//���� ����
	STATUS m_uMonsterStat;

	//�������ɋ����� �ð�
	int m_nResPawnCount;

	Model* m_pModel;
	//Model* m_pDeathModel;
	
	MON_STATE m_eState;
public:
	MonsterParent();
	~MonsterParent();

	void SetCurrentHP(float damage) { m_uMonsterStat.chr.fCurrentHP -= damage; }

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos);
	virtual void Update();
	virtual void RespawnUpdate();
	virtual void Render();
	void ChangeAni();
};

