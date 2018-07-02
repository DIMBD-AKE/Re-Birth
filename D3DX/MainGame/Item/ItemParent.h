#pragma once

union STATUS;
struct ST_DAMAGE;

class MonsterManager;

class ItemParent
{
protected:
	GET(string, m_sName, Name);									//������ �̸�
	GET(string, m_sItemDescription, Desc);						//������ ����
	GET(int, m_nId, ID);										//������ �����ѹ�
	GET(STATUS*, m_pItemStatus, ItemStat);						//������ ���ݺ���ġ

public:
	ItemParent();
	~ItemParent();

	virtual void Attack(ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Skill1(ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Skill2(ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Render();
};

