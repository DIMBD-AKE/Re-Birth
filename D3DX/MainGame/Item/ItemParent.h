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
	SYNTHESIZE(string, m_sName, Name);									//아이템 이름
	SYNTHESIZE(string, m_sItemDescription, Desc);						//아이템 서술
	SYNTHESIZE(int, m_nId, ID);											//아이템 고유넘버
	SYNTHESIZE(EQUIPTYPE, m_stEquipType, EquipType);					//아이템 장착슬롯
	SYNTHESIZE(ITEMRARITY, m_Rarity, Rarity);								
	SYNTHESIZE(Particle*, m_pParticle, Particle);
	SYNTHESIZE(Skill*, m_pSkill1, Skill1);
	SYNTHESIZE(Skill*, m_pSkill2, Skill2);
	SYNTHESIZE(ST_SKILL*, m_Skill1Data, Skill1Data);
	SYNTHESIZE(ST_SKILL*, m_Skill2Data, Skill2Data);
	GET(STATUS*, m_pItemStatus, ItemStat);								//아이템 스텟보정치

	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXIMAGE_INFO		m_imageInfo;
	
	float		m_fSkill1CurrentCooltime;								//스킬 1 쿨타임
	float		m_fSkill2CurrentCooltime;								//스킬 2 쿨타임

	bool		m_bSkill1Able;											//스킬 사용 가능여부 
	bool		m_bSkill2Able;											//스킬 사용 가능여부 


public:
	ItemParent();
	virtual ~ItemParent();
	virtual ItemParent* Clone();

	virtual void SetUp();
	virtual void Update();
	virtual void Render();

	//사용아이템(포션류)
	virtual void Use(CharacterParant & pCharacter);

	//아이템스킬(무기류)
	virtual void Skill1(CharacterParant* pCharacter, MonsterManager* pMonsterManager);
	virtual void Skill2(CharacterParant* pCharacter, MonsterManager* pMonsterManager);
	
	virtual void SetStatusZero();								//아이템 스텟 초기화
	virtual void SetStatus(STATUS stat);						//아이템 스텟 설정

	bool Skill1CoolTime();										//스킬 쿨타임 확인
	bool Skill2CoolTime();										//스킬 쿨타임 확인

	//virtual void Drop();
	void Render(D3DXVECTOR3 pos, float size);
	void EffectRender(D3DXVECTOR3 pos);
};

