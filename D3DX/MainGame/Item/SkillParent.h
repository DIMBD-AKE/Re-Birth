#pragma once

union STATUS;
struct ST_DAMAGE;

class CharacterParant;
class MonsterParent;
class MonsterManager;
class Model;
class SkillManager;

enum SKILLINDEX
{
	RAY,
	MULTIHIT,
	EXPLOSION,
	FIELD,
	GAURD,
	BUFF
};

class SkillParent
{
protected:
	int			m_nSkillNum;
	int			m_nSkillInd;
	float		m_fScale;
	float		m_fRange;
	int			m_nTargetNum;
	Particle*	m_Particle;
	float		m_fDps;

public:
	SkillParent();
	~SkillParent();

	void MakeSkill(int nSkillNum, int nIndex, float fScale, float fRange, int mTargetNum, Particle* Particle);
	void Update(D3DXVECTOR3 charPos);
	void Attack(CharacterParant* pCharacter, ST_DAMAGE pStatus, MonsterManager* pMonsterManager);
};

