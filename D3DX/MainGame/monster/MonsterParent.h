#pragma once
#include "../Status.h"
//���͵��� �⺻ Ʋ�� �Ǵ� Ŭ�����̴�.


class MonsterParent
{
	STATUS m_uMonsterStat;

	//�������������� Ȯ��
	GET(bool, m_bIsRespawn, IsResPawn);

	//�������ɋ����� �ð�
	int m_nResPawnCount;
	
public:
	MonsterParent();
	~MonsterParent();

	void SetCurrentHP(float damage) { m_uMonsterStat.chr.fCurrentHP -= damage; }
};

