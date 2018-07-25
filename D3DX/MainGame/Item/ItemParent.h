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
class Map;


class ItemParent
{
protected:
	SYNTHESIZE(string, m_sName, Name);									//������ �̸�
	SYNTHESIZE(string, m_sItemDescription, Desc);						//������ ����
	SYNTHESIZE(int, m_nId, ID);											//������ �����ѹ�
	SYNTHESIZE(EQUIPTYPE, m_stEquipType, EquipType);					//������ ��������
	SYNTHESIZE(ITEMRARITY, m_Rarity, Rarity);								
	SYNTHESIZE(Particle*, m_pParticle, Particle);
	SYNTHESIZE(Skill*, m_pSkill1, Skill1);
	SYNTHESIZE(Skill*, m_pSkill2, Skill2);
	SYNTHESIZE(ST_SKILL*, m_Skill1Data, Skill1Data);
	SYNTHESIZE(ST_SKILL*, m_Skill2Data, Skill2Data);
	GET(STATUS*, m_pItemStatus, ItemStat);								//������ ���ݺ���ġ

	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXIMAGE_INFO		m_imageInfo;
	
	float		m_fSkill1CurrentCooltime;								//��ų 1 ��Ÿ��
	float		m_fSkill2CurrentCooltime;								//��ų 2 ��Ÿ��

	bool		m_bSkill1Able;											//��ų ��� ���ɿ��� 
	bool		m_bSkill2Able;											//��ų ��� ���ɿ��� 


	bool		m_bSkillTrig;

	D3DXVECTOR3		m_vMouse;
	
public:
	ItemParent();
	virtual ~ItemParent();
	virtual ItemParent* Clone();

	virtual void SetUp();
	virtual void Update(Map* map);
	virtual void Render(Map* map);

	//��������(���Ƿ�)
	virtual void Use(CharacterParant & pCharacter);

	//�����۽�ų(�����)
	virtual bool Skill1(CharacterParant* pCharacter, MonsterManager* pMonsterManager, Map* map);
	virtual bool Skill2(CharacterParant* pCharacter, MonsterManager* pMonsterManager, Map* map);
	
	virtual void SetStatusZero();								//������ ���� �ʱ�ȭ
	virtual void SetStatus(STATUS stat);						//������ ���� ����

	bool Skill1CoolTime();										//��ų ��Ÿ�� Ȯ��
	bool Skill2CoolTime();										//��ų ��Ÿ�� Ȯ��

	//virtual void Drop();
	void Render(D3DXVECTOR3 pos, float size);
	void EffectRender(D3DXVECTOR3 pos);

	void SkillRange(D3DXVECTOR3 pos, int TriNum, ST_SKILL* skill, Map* map);
};

