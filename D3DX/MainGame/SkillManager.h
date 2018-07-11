#pragma once

#include "Status.h"

class CharacterParant;
class MonsterParent;
class EffectObject;

enum SKILL_PROCESS
{
	SKILLP_SINGLE,
	SKILLP_MULTIPLE,
	SKILLP_BUFF
};

enum SKILL_EFFECT
{
	SKILLE_THIS,
	SKILLE_TOTHIS,
	SKILLE_TARGET,
	SKILLE_TOTARGET
};

enum SKILL_OWNER
{
	SKILLO_CHARACTER,
	SKILLO_MONSTER
};

struct ST_SKILL
{
	int			nMaxTarget;
	float		fMinLength;
	float		fMaxLength;
	float		fAngle;

	float		fDamage;
	int			nDamageCount;
	float		fDamageInterval;
	float		fDamageDelay;

	float		fBuffTime;
	STATUS		buffStatus;
};

class SkillParent
{
private:
	LPDIRECT3DTEXTURE9	m_pSkillIcon;
	string				m_sSkillName;

	// 贸府 规侥
	SKILL_PROCESS		m_eDamageProcess;
	SKILL_PROCESS		m_eTargetProcess;
	SKILL_EFFECT		m_eParticleProcess;
	SKILL_EFFECT		m_eEffectProcess;

	// 贸府 沥焊
	CharacterParant *		m_pCharacter;
	MonsterParent *			m_pMonster;
	vector<MonsterParent*>	m_vecMonster;
	ST_SKILL				m_stSkill;
	SKILL_OWNER				m_eOwner;
	int						m_nDamageCount;
	float					m_fElapseTime;
	float					m_fPrevTime;
	bool					m_isBuff;

	// 瓤苞 沥焊
	string					m_sParticle;
	vector<Particle*>		m_vecParticle;
	ST_EFFECT				m_stEffect;
	vector<EffectObject*>	m_vecEffect;

	bool					m_isProcess;

	// 单固瘤 贸府
	void DamageSingle();
	void DamageMultiple();
	void DamageBuff();

	// 鸥百 贸府
	void * GetSingleTarget();
	vector<void*> GetMultipleTarget();

	// 颇萍努 贸府
	void ParticleThis();
	void ParticleToThis();
	void ParticleTarget();
	void ParticleToTarget();

	// 捞棋飘 贸府
	void EffectThis();
	void EffectToThis();
	void EffectTarget();
	void EffectToTarget();


public:
	SkillParent();
	SkillParent(SKILL_PROCESS damage, SKILL_PROCESS target, 
		SKILL_EFFECT particleP, SKILL_EFFECT effectP, string particle, ST_EFFECT effect,
		LPDIRECT3DTEXTURE9 tex, string name);
	~SkillParent();

	void Prepare(CharacterParant * pCharacter, MonsterParent* pMonster, vector<MonsterParent*> vecMonster, ST_SKILL skill, SKILL_OWNER owner);
	void Trigger() { m_isProcess = true; }
	void Update();
	void Render();
};

class SkillManager
{
	SINGLETONE(SkillManager);

private:
	map<string, SkillParent>	m_mapSkill;

	void LoadSkill();
	SkillParent SkillParse(string name, string path);

public:
	SkillParent * GetSkill(string keyName);
};

#define SKILL SkillManager::GetInstance()