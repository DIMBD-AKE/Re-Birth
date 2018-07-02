#pragma once

union STATUS;
struct ST_DAMAGE;

class MonsterManager;

class ItemParent
{
protected:
	GET(string, m_sName, Name);									//아이템 이름
	GET(string, m_sItemDescription, Desc);						//아이템 서술
	GET(int, m_nId, ID);										//아이템 고유넘버
	GET(STATUS*, m_pItemStatus, ItemStat);						//아이템 스텟보정치

public:
	ItemParent();
	~ItemParent();

	virtual void Attack(ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Skill1(ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Skill2(ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Render();
};

