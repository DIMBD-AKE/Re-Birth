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
	SKILLE_TARGET,
	SKILLE_TOTARGET,
	SKILLE_TOTHIS
};

struct ST_SKILL
{
	int				nMaxTarget;
	float			fMinLength;
	float			fMaxLength;
	float			fAngle;
	STATUS			status;
	D3DXVECTOR3*	pPos;
};

class SkillParent
{
private:
	// ó�� ���
	SKILL_PROCESS		m_eDamageProcess;
	SKILL_PROCESS		m_eTargetProcess;
	SKILL_EFFECT		m_eParticleProcess;
	SKILL_EFFECT		m_eEffectProcess;

	// ó�� ����
	CharacterParant *			m_pCharacter;
	vector<MonsterParent*>		m_vecMonster;
	ST_SKILL	m_stSkillInfo;
	bool		m_isCharacter;

	// ȿ�� ����
	vector<Particle*>		m_pParticle;
	vector<EffectObject*>	m_vecEffect;
	ST_EFFECT				m_stEffect;

	// ������
	void SingleDamage();
	void MultipleDamage();

	// Ÿ��
	void * GetSingleTarget();
	vector<MonsterParent*> GetMultipleTarget();

public:
	SkillParent();
	SkillParent(SKILL_PROCESS damage, SKILL_PROCESS target, SKILL_EFFECT effectTarget, string particle, ST_EFFECT effect);
	~SkillParent();

	void Prepare(CharacterParant * pCharacter, vector<MonsterParent*> vecMonster, ST_SKILL skill, bool isCharacter);
	void Update();
	void Render();
};

