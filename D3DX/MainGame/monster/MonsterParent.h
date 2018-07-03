#pragma once
#include "../Status.h"
//���͵��� �⺻ Ʋ�� �Ǵ� Ŭ�����̴�.

class Map;

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
	
public:
	MonsterParent();
	~MonsterParent();

	void SetCurrentHP(float damage) { m_uMonsterStat.chr.fCurrentHP -= damage; }

	virtual void Setup(Map* map, D3DXVECTOR3 spawnPos);
	virtual void Update();
	virtual void Render();
};

