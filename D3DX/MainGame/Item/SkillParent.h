#pragma once

enum SKILLINDEX
{
	MULTIHIT,
	EXPLOSION,
	FIELD,
	GAURD,
	BUFF
};

class SkillParent
{
private:
	int			m_nSkillNum;
	int			m_nSkillInd;
	float		m_fScale;
	float		m_fRange;
	int			m_nTargetNum;
	Particle*	m_Particle;


public:
	SkillParent();
	~SkillParent();

	void MakeSkill(int nSkillNum, int nIndex, float fScale, float fRange, int mTargetNum, Particle* Particle);
	void Update(D3DXVECTOR3 charPos);
};

