#include "../stdafx.h"
#include "SkillManager.h"
#include "monster\MonsterParent.h"
#include "Character\CharacterParant.h"
#include "../Framework/dirent.h"

void SkillParent::DamageSingle()
{
	m_nDamageCount++;

	if (m_nDamageCount > 1) return;

	if (m_eTargetProcess == SKILLP_SINGLE)
	{
		void * pSingle = GetSingleTarget();

		if (pSingle)
		{
			if (m_eOwner == SKILLO_CHARACTER)
				((MonsterParent*)pSingle)->CalculDamage(m_stSkill.fDamage);
			else
				((CharacterParant*)pSingle)->CalculDamage(m_stSkill.fDamage);
		}
	}

	if (m_eTargetProcess == SKILLP_MULTIPLE)
	{
		vector<void*> vecMultiple = GetMultipleTarget();

		for (int i = 0; i < vecMultiple.size(); i++)
		{
			if (m_eOwner == SKILLO_CHARACTER)
				((MonsterParent*)vecMultiple[i])->CalculDamage(m_stSkill.fDamage);
			else
				((CharacterParant*)vecMultiple[i])->CalculDamage(m_stSkill.fDamage);
		}
	}
}

void SkillParent::DamageMultiple()
{
	if (m_fElapseTime < m_fPrevTime + m_stSkill.fDamageInterval) return;

	m_fPrevTime = m_fElapseTime;

	m_nDamageCount++;

	if (m_eTargetProcess == SKILLP_SINGLE)
	{
		void * pSingle = GetSingleTarget();

		if (pSingle)
		{
			if (m_eOwner == SKILLO_CHARACTER)
				((MonsterParent*)pSingle)->CalculDamage(m_stSkill.fDamage);
			else
				((CharacterParant*)pSingle)->CalculDamage(m_stSkill.fDamage);
		}
	}

	if (m_eTargetProcess == SKILLP_MULTIPLE)
	{
		vector<void*> vecMultiple = GetMultipleTarget();

		for (int i = 0; i < vecMultiple.size(); i++)
		{
			if (m_eOwner == SKILLO_CHARACTER)
				((MonsterParent*)vecMultiple[i])->CalculDamage(m_stSkill.fDamage);
			else
				((CharacterParant*)vecMultiple[i])->CalculDamage(m_stSkill.fDamage);
		}
	}
}

void SkillParent::DamageBuff()
{
}

void * SkillParent::GetSingleTarget()
{
	D3DXVECTOR3 posChr = *m_pCharacter->GetCharacter()->GetPosition();
	D3DXVECTOR3 posMon = *m_pMonster->GetModel()->GetPosition();

	if (m_eOwner == SKILLO_MONSTER)
	{
		float length = D3DXVec3Length(&(posMon - posChr));

		if (length >= m_stSkill.fMinLength && length <= m_stSkill.fMaxLength)
		{
			float angle = GetAngle(posChr.x, posChr.z, posMon.x, posMon.z);
			float curr = m_pMonster->GetModel()->GetRotation()->y;
			// 각도 조건
			return m_pCharacter;
		}
	}

	if (m_eOwner == SKILLO_CHARACTER)
	{
		int minIndex = -1;
		float minLength = m_stSkill.fMaxLength;
		for (int i = 0; i < m_vecMonster.size(); i++)
		{
			posMon = *m_vecMonster[i]->GetModel()->GetPosition();
			float length = D3DXVec3Length(&(posMon - posChr));

			if (length >= m_stSkill.fMinLength && length <= m_stSkill.fMaxLength)
			{
				// 각도 조건
				if (minLength > length)
				{
					minIndex = i;
					minLength = length;
				}
			}
		}

		if (minIndex > 0)
			return m_vecMonster[minIndex];
	}

	return NULL;
}

vector<void*> SkillParent::GetMultipleTarget()
{
	D3DXVECTOR3 posChr = *m_pCharacter->GetCharacter()->GetPosition();
	D3DXVECTOR3 posMon = *m_pMonster->GetModel()->GetPosition();
	
	vector<void*> vecTarget;

	if (m_eOwner == SKILLO_MONSTER)
	{
		float length = D3DXVec3Length(&(posMon - posChr));

		if (length >= m_stSkill.fMinLength && length <= m_stSkill.fMaxLength)
		{
			float angle = GetAngle(posChr.x, posChr.z, posMon.x, posMon.z);
			float curr = m_pMonster->GetModel()->GetRotation()->y;
			// 각도 조건
			vecTarget.push_back(m_pCharacter);
		}
	}

	if (m_eOwner == SKILLO_CHARACTER)
	{
		for (int i = 0; i < m_vecMonster.size(); i++)
		{
			posMon = *m_vecMonster[i]->GetModel()->GetPosition();
			float length = D3DXVec3Length(&(posMon - posChr));

			if (length >= m_stSkill.fMinLength && length <= m_stSkill.fMaxLength)
			{
				// 각도 조건
				vecTarget.push_back(m_vecMonster[i]);
			}
		}
	}

	return vecTarget;
}

void SkillParent::ParticleThis()
{
	if (m_vecParticle.empty())
	{
		PARTICLE->AddParticle(m_sParticle,
			TEXTUREMANAGER->AddTexture("Particle Sphere", "Texture/Particle/Sphere.png"), m_sParticle);
		m_vecParticle.push_back(PARTICLE->GetParticle(m_sParticle));
	}

	for (int i = 0; i < m_vecParticle.size(); i++)
	{
		if (m_eOwner == SKILLO_CHARACTER)
		{
			m_vecParticle[i]->SetPosition(*m_pCharacter->GetCharacter()->GetPosition());
			m_vecParticle[i]->World();
			m_vecParticle[i]->Update();
		}
		else
		{
			m_vecParticle[i]->SetPosition(*m_pMonster->GetModel()->GetPosition());
			m_vecParticle[i]->World();
			m_vecParticle[i]->Update();
		}
	}
}

void SkillParent::ParticleToThis()
{
}

void SkillParent::ParticleTarget()
{
	if (m_eTargetProcess == SKILLP_SINGLE)
	{
		if (m_vecParticle.empty() && m_nDamageCount < m_stSkill.nDamageCount)
		{
			PARTICLE->AddParticle(m_sParticle,
				TEXTUREMANAGER->AddTexture("Particle Sphere", "Texture/Particle/Sphere.png"), m_sParticle);
			m_vecParticle.push_back(PARTICLE->GetParticle(m_sParticle));
		}

		void * target = GetSingleTarget();

		if (!target)
		{
			for (auto p : m_vecParticle)
				SAFE_DELETE(p);
			m_vecParticle.clear();
			return;
		}

		for (int i = 0; i < m_vecParticle.size(); i++)
		{
			if (m_eOwner == SKILLO_CHARACTER)
			{
				m_vecParticle[i]->SetPosition(*((MonsterParent*)target)->GetModel()->GetPosition());
				m_vecParticle[i]->World();
				m_vecParticle[i]->Update();
			}
			else
			{
				m_vecParticle[i]->SetPosition(*((CharacterParant*)target)->GetCharacter()->GetPosition());
				m_vecParticle[i]->World();
				m_vecParticle[i]->Update();
			}
		}
	}

	if (m_eTargetProcess == SKILLP_MULTIPLE)
	{

	}
}

void SkillParent::ParticleToTarget()
{
}

void SkillParent::EffectThis()
{
}

void SkillParent::EffectToThis()
{
}

void SkillParent::EffectTarget()
{
}

void SkillParent::EffectToTarget()
{
}

SkillParent::SkillParent()
{
}

SkillParent::SkillParent(SKILL_PROCESS damage, SKILL_PROCESS target,
	SKILL_EFFECT particleP, SKILL_EFFECT effectP, string particle, ST_EFFECT effect,
	LPDIRECT3DTEXTURE9 tex, string name)
{
	ZeroMemory(this, sizeof(SkillParent));
	m_eDamageProcess = damage;
	m_eTargetProcess = target;
	m_eParticleProcess = particleP;
	m_eEffectProcess = effectP;
	m_sParticle = particle;
	m_stEffect = effect;
	m_sSkillName = name;
	m_pSkillIcon = tex;
}

SkillParent::~SkillParent()
{
	for (auto p : m_vecParticle)
		SAFE_DELETE(p);
	m_vecParticle.clear();
	for (auto e : m_vecEffect)
		SAFE_DELETE(e);
	m_vecEffect.clear();
}

void SkillParent::Prepare(CharacterParant * pCharacter, MonsterParent* pMonster, vector<MonsterParent*> vecMonster, ST_SKILL skill, SKILL_OWNER owner)
{
	m_pCharacter = pCharacter;
	m_pMonster = pMonster;
	m_vecMonster = vecMonster;
	m_stSkill = skill;
	m_eOwner = owner;

	m_fElapseTime = 0;
	m_fPrevTime = 0;
	m_nDamageCount = 0;
	m_isProcess = false;

	for (auto p : m_vecParticle)
		SAFE_DELETE(p);
	m_vecParticle.clear();
	for (auto e : m_vecEffect)
		SAFE_DELETE(e);
	m_vecEffect.clear();
}

void SkillParent::Update()
{
	if (!m_isProcess) return;

	TEXT->Add("진행시간 : " + to_string(m_fElapseTime), 10, 20, 20, "", 0xFFFFFFFF);
	TEXT->Add("이전시간 : " + to_string(m_fPrevTime), 10, 40, 20, "", 0xFFFFFFFF);
	TEXT->Add("데미지카운트 : " + to_string(m_nDamageCount), 10, 60, 20, "", 0xFFFFFFFF);

	// 데미지 및 타겟 처리
	if (m_nDamageCount < m_stSkill.nDamageCount)
	{
		if (m_stSkill.fDamageDelay < m_fElapseTime)
		{
			if (m_eDamageProcess == SKILLP_SINGLE)
				DamageSingle();
			if (m_eDamageProcess == SKILLP_MULTIPLE)
				DamageMultiple();
			if (m_eDamageProcess == SKILLP_BUFF)
				DamageBuff();
		}
	}

	// 파티클 처리
	if (m_eParticleProcess == SKILLE_THIS)
		ParticleThis();
	if (m_eParticleProcess == SKILLE_TOTHIS)
		ParticleToThis();
	if (m_eParticleProcess == SKILLE_TARGET)
		ParticleTarget();
	if (m_eParticleProcess == SKILLE_TOTARGET)
		ParticleToTarget();

	// 이펙트 처리
	if (m_eEffectProcess == SKILLE_THIS)
		EffectThis();
	if (m_eEffectProcess == SKILLE_TOTHIS)
		EffectToThis();
	if (m_eEffectProcess == SKILLE_TARGET)
		EffectTarget();
	if (m_eEffectProcess == SKILLE_TOTARGET)
		EffectToTarget();

	m_fElapseTime += TIME->GetElapsedTime();
}

void SkillParent::Render()
{
	if (!m_isProcess) return;

	for (auto p : m_vecParticle)
		p->Render();
}

SkillManager::SkillManager()
{
	LoadSkill();
}

SkillManager::~SkillManager()
{
}

void SkillManager::LoadSkill()
{
	dirent * ent;
	DIR * dir;
	string dirPath = "Skill/";

	if ((dir = opendir(dirPath.c_str())) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			char * fileType = GetFileType(ent->d_name);
			if (fileType)
			{
				if (strcmp(fileType, "sk") == 0)
				{
					SkillParent skill = SkillParse(ent->d_name, dirPath + ent->d_name + ".sk");
					m_mapSkill.insert(make_pair(ent->d_name, skill));
				}
			}
		}
	}
}

SkillParent SkillManager::SkillParse(string name, string path)
{
	FILE * fp;
	fopen_s(&fp, path.c_str(), "r");

	SkillParent skill;

	SKILL_PROCESS damage, target;
	SKILL_EFFECT particleP = SKILLE_THIS, effectP = SKILLE_THIS;
	string particle;
	ST_EFFECT effect;
	LPDIRECT3DTEXTURE9 tex = NULL;

	ZeroMemory(&effect, sizeof(ST_EFFECT));

	while (true)
	{
		if (feof(fp))
			break;

		char line[128];
		fgets(line, 128, fp);

		char * tok;
		char * context;
		tok = strtok_s(line, "\t\n ", &context);

		if (!tok) continue;

		if (strcmp(tok, "SKILL_PROCESS_DAMAGE") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			if (strcmp(tok, "SINGLE") == 0)
				damage = SKILLP_SINGLE;
			else if (strcmp(tok, "MULTIPLE") == 0)
				damage = SKILLP_MULTIPLE;
			else if (strcmp(tok, "BUFF") == 0)
				damage = SKILLP_BUFF;
		}
		if (strcmp(tok, "SKILL_PROCESS_TARGET") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			if (strcmp(tok, "SINGLE") == 0)
				target = SKILLP_SINGLE;
			if (strcmp(tok, "MULTIPLE") == 0)
				target = SKILLP_MULTIPLE;
			if (strcmp(tok, "BUFF") == 0)
				target = SKILLP_BUFF;
		}
		if (strcmp(tok, "SKILL_EFFECT_PARTICLE") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			if (strcmp(tok, "THIS") == 0)
				particleP = SKILLE_THIS;
			if (strcmp(tok, "TOTHIS") == 0)
				particleP = SKILLE_TOTHIS;
			if (strcmp(tok, "TARGET") == 0)
				particleP = SKILLE_TARGET;
			if (strcmp(tok, "TOTARGET") == 0)
				particleP = SKILLE_TOTARGET;
		}
		if (strcmp(tok, "SKILL_EFFECT_EFFECT") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			if (strcmp(tok, "THIS") == 0)
				effectP = SKILLE_THIS;
			if (strcmp(tok, "TOTHIS") == 0)
				effectP = SKILLE_TOTHIS;
			if (strcmp(tok, "TARGET") == 0)
				effectP = SKILLE_TARGET;
			if (strcmp(tok, "TOTARGET") == 0)
				effectP = SKILLE_TOTARGET;
		}
		if (strcmp(tok, "PARTICLE") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			particle = string(tok);
		}
		if (strcmp(tok, "EFFECT_") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
		}
		if (strcmp(tok, "ICON") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
		}
	}

	fclose(fp);

	skill = SkillParent(damage, target, particleP, effectP, particle, effect, tex, name);

	return skill;
}

SkillParent * SkillManager::GetSkill(string keyName)
{
	if (m_mapSkill.find(keyName) == m_mapSkill.end())
		return NULL;
	
	SkillParent * skill = new SkillParent;
	*skill = m_mapSkill[keyName];

	return skill;
}
