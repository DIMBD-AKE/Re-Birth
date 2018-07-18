#pragma once
#include "../GameEnum.h"

union STATUS;
struct ST_DAMAGE;
struct ST_SKILL;

class CharacterParant;
class MonsterParent;
class MonsterManager;
class Model;
class SkillManager;
class Skill;


class ItemParent
{
protected:
	SYNTHESIZE(string, m_sName, Name);									//������ �̸�
	SYNTHESIZE(string, m_sItemDescription, Desc);						//������ ����
	SYNTHESIZE(int, m_nId, ID);											//������ �����ѹ�
	GET(STATUS*, m_pItemStatus, ItemStat);						//������ ���ݺ���ġ
	SYNTHESIZE(EQUIPTYPE, m_stEquipType, EquipType);					//������ ��������
	SYNTHESIZE(ITEMRARITY, m_Rarity, Rarity);								
	SYNTHESIZE(Particle*, m_pParticle, Particle);
	GET(float, m_fRange, Range);
	GET(float, m_fScale, Scale);
	SYNTHESIZE(Skill*, m_pSkill1, Skill1);
	SYNTHESIZE(Skill*, m_pSkill2, Skill2);
	SYNTHESIZE(ST_SKILL*, m_Skill1Data, Skill1Data);
	SYNTHESIZE(ST_SKILL*, m_Skill2Data, Skill2Data);

	vector<MonsterParent*> m_vecTarget;
	int m_nCurrentTarget;

	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXIMAGE_INFO		m_imageInfo;
	
	float		m_RotX;
	float		m_RotY;
	float		m_RotZ;


public:
	ItemParent();
	virtual ~ItemParent();
	virtual ItemParent* Clone();

	virtual void SetUp();
	virtual void Use(CharacterParant & pCharacter);
	virtual void Attack(CharacterParant* pCharacter, ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
	virtual void Skill1(CharacterParant* pCharacter, MonsterManager* pMonsterManager);
	virtual void Skill2(CharacterParant* pCharacter, MonsterManager* pMonsterManager);
	
	virtual void SetTarget();
	virtual void SetStatusZero();
	virtual void SetStatus(STATUS stat);


	//virtual void Drop();
	void Render(D3DXVECTOR3 pos, float size);
	void EffectRender(D3DXVECTOR3 pos);
};

