#pragma once

#include "Status.h"

class CharacterParant;
class MonsterParent;
class EffectObject;

enum SKILL_PROCESS
{
	SKILLP_SINGLE,
	SKILLP_MULTIPLE
};

enum SKILL_EFFECT
{
	SKILLE_THIS,
	SKILLE_TOTHIS,
	SKILLE_TARGET,
	SKILLE_TOTARGET,
	SKILLE_NONE
};

enum SKILL_BUFF
{
	SKILLB_BEGIN,
	SKILLB_HIT,
	SKILLB_END
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

	float		fYOffset;
	bool		isAutoRot;
	float		fParticleTime;
	float		fParticleSpeed;
	float		fEffectTime;
};

class Skill
{
	SYNTHESIZE(ST_EFFECT, m_stEffect, Effect);

private:
	LPDIRECT3DTEXTURE9	m_pSkillIcon;
	LPDIRECT3DTEXTURE9	m_pParticleTexture;
	string				m_sSkillName;

	// 贸府 规侥
	SKILL_PROCESS		m_eDamageProcess;
	SKILL_PROCESS		m_eTargetProcess;
	SKILL_EFFECT		m_eParticleProcess;
	SKILL_EFFECT		m_eEffectProcess;
	SKILL_BUFF			m_eBuffProcess;

	// 贸府 沥焊
	CharacterParant *		m_pCharacter;
	MonsterParent *			m_pMonster;
	vector<MonsterParent*>	m_vecMonster;
	vector<void*>			m_vecTarget;
	vector<D3DXVECTOR3>		m_vecTargetDir;
	ST_SKILL				m_stSkill;
	ST_SPHERE				m_stSphere;
	SKILL_OWNER				m_eOwner;
	int						m_nDamageCount;
	int						m_nPrevCount;
	float					m_fElapseTime;
	float					m_fPrevTime;
	float					m_fBuffTime;
	bool					m_isBuff;

	// 瓤苞 沥焊
	string					m_sParticle;

	vector<Particle*>		m_vecParticle;
	vector<EffectObject*>	m_vecEffect;

	bool					m_isProcess;

	// 单固瘤 贸府
	void DamageSingle();
	void DamageMultiple();

	// 滚橇 贸府
	void Buff();

	// 鸥百 贸府
	void * GetSingleTarget();
	vector<void*> GetMultipleTarget();

	// 颇萍努 贸府
	void ParticleThis();
	void ParticleTarget();
	void ParticleDamage();

	// 捞棋飘 贸府
	void EffectDamage();

public:
	Skill();
	Skill(SKILL_PROCESS damage, SKILL_PROCESS target, 
		SKILL_EFFECT particleP, SKILL_EFFECT effectP, SKILL_BUFF buff, string particle, ST_EFFECT effect,
		LPDIRECT3DTEXTURE9 iconTex, string name, LPDIRECT3DTEXTURE9 particleTex);
	~Skill();

	void Prepare(CharacterParant * pCharacter, MonsterParent* pMonster, vector<MonsterParent*> vecMonster, ST_SKILL skill, SKILL_OWNER owner);
	void Trigger();
	void Update();
	void Render();

	LPDIRECT3DTEXTURE9 GetIcon() { return m_pSkillIcon; }

	void Debug();
};

class SkillManager
{
	SINGLETONE(SkillManager);

private:
	map<string, Skill>	m_mapSkill;

	void LoadSkill();
	Skill SkillParse(string name, string path);

public:
	Skill * GetSkill(string keyName);
};

#define SKILL SkillManager::GetInstance()