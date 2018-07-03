#pragma once

union STATUS;
struct ST_DAMAGE;

class CharacterParant;
class MonsterManager;
class Model;

class ItemParent
{
protected:
	GET(string, m_sName, Name);									//������ �̸�
	GET(string, m_sItemDescription, Desc);						//������ ����
	GET(int, m_nId, ID);										//������ �����ѹ�
	GET(STATUS*, m_pItemStatus, ItemStat);						//������ ���ݺ���ġ
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXIMAGE_INFO		m_imageInfo;
	
	float		m_fRange;
	float		m_fScale;


public:
	ItemParent();
	virtual ~ItemParent();

	virtual void SetUp();
	virtual void Use(CharacterParant* & pCharacter);
	virtual void Attack(Model* pModel, ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Skill1(Model* pModel, ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Skill2(Model* pModel, ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	//virtual void Drop();
	void Render(D3DXVECTOR3 pos, float size);
};

