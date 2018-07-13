#pragma once
#include "../GameEnum.h"

union STATUS;
struct ST_DAMAGE;

class CharacterParant;
class MonsterParent;
class MonsterManager;
class Model;
class SkillManager;

class ItemParent
{
protected:
	SYNTHESIZE(string, m_sName, Name);									//������ �̸�
	SYNTHESIZE(string, m_sItemDescription, Desc);						//������ ����
	SYNTHESIZE(int, m_nId, ID);											//������ �����ѹ�
	SYNTHESIZE(STATUS*, m_pItemStatus, ItemStat);						//������ ���ݺ���ġ
	SYNTHESIZE(EQUIPTYPE, m_stEquipType, EquipType);					//������ ��������
	SYNTHESIZE(string, m_sRarity, Rarity);								
	SYNTHESIZE(Particle*, m_pParticle, Particle);
	GET(float, m_fRange, Range);
	GET(float, m_fScale, Scale);

	vector<MonsterParent*> m_vecTarget;
	int m_nCurrentTarget;

	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXIMAGE_INFO		m_imageInfo;
	
	


public:
	ItemParent();
	virtual ~ItemParent();
	virtual ItemParent* Clone() = 0;

	virtual void SetUp();
	virtual void Use(CharacterParant & pCharacter);
	virtual void Attack(CharacterParant* pCharacter, ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Skill1(CharacterParant* pCharacter, ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Skill2(CharacterParant* pCharacter, ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	
	virtual void SetTarget();
	virtual void SetStatusZero();

	//virtual void Drop();
	void Render(D3DXVECTOR3 pos, float size);
	void EffectRender(D3DXVECTOR3 pos);
};

