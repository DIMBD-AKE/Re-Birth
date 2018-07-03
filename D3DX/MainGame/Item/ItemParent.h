#pragma once

union STATUS;
struct ST_DAMAGE;

class MonsterManager;
class Model;

class ItemParent
{
protected:
	GET(string, m_sName, Name);									//아이템 이름
	GET(string, m_sItemDescription, Desc);						//아이템 서술
	GET(int, m_nId, ID);										//아이템 고유넘버
	GET(STATUS*, m_pItemStatus, ItemStat);						//아이템 스텟보정치
	float		m_fRange;
	float		m_fScale;


public:
	ItemParent();
	virtual ~ItemParent();

	virtual void Attack(Model* pModel, ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Skill1(Model* pModel, ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Skill2(Model* pModel, ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	//virtual void Drop();
	virtual void Render();
};

