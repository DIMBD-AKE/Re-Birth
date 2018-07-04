#pragma once
#include "../GameEnum.h"

union STATUS;
struct ST_DAMAGE;

class CharacterParant;
class MonsterParent;
class MonsterManager;
class Model;


class ItemParent
{
protected:
	GET(string, m_sName, Name);									//������ �̸�
	GET(string, m_sItemDescription, Desc);						//������ ����
	GET(int, m_nId, ID);										//������ �����ѹ�
	GET(STATUS*, m_pItemStatus, ItemStat);						//������ ���ݺ���ġ
	GET(EQUIPTYPE, m_stEquipType, EquipType);					//������ ��������
	
	vector<MonsterParent*> m_vecTarget;
	int m_nCurrentTarget;

	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXIMAGE_INFO		m_imageInfo;
	
	float		m_fRange;
	float		m_fScale;


public:
	ItemParent();
	virtual ~ItemParent();

	virtual void SetUp();
	virtual void Use(CharacterParant & pCharacter);
	virtual void Attack(CharacterParant* pCharacter, ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Skill1(CharacterParant* pCharacter, ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Skill2(CharacterParant* pCharacter, ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	
	virtual void SetTarget();
	virtual void SetStatusZero();

	//virtual void Drop();
	void Render(D3DXVECTOR3 pos, float size);
};

