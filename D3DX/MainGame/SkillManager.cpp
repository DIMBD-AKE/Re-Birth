#include "../stdafx.h"
#include "SkillManager.h"


void SkillParent::SingleDamage()
{
}

void SkillParent::MultipleDamage()
{
}

void * SkillParent::GetSingleTarget()
{
	return nullptr;
}

vector<MonsterParent*> SkillParent::GetMultipleTarget()
{
	return vector<MonsterParent*>();
}

SkillParent::SkillParent()
{
}

SkillParent::SkillParent(SKILL_PROCESS damage, SKILL_PROCESS target, SKILL_EFFECT effectTarget, string particle, ST_EFFECT effect)
{
	
	PARTICLE->GetParticle(particle);
}


SkillParent::~SkillParent()
{
}

void SkillParent::Prepare(CharacterParant * pCharacter, vector<MonsterParent*> vecMonster, ST_SKILL skill, bool isCharacter)
{
	m_pCharacter = pCharacter;
	m_vecMonster = vecMonster;
	m_stSkillInfo = skill;
	m_isCharacter = isCharacter;
}

void SkillParent::Update()
{
}

void SkillParent::Render()
{
}
