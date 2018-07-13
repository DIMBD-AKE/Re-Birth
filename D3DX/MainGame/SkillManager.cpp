#include "../stdafx.h"
#include "SkillManager.h"
#include "monster\MonsterParent.h"
#include "Character\CharacterParant.h"
#include "../Framework/dirent.h"
#include "../Framework/EffectObject.h"

void Skill::DamageSingle()
{
	m_nDamageCount++;

	if (m_nDamageCount > 1) return;

	for (int i = 0; i < m_vecTarget.size(); i++)
	{
		if (m_eOwner == SKILLO_CHARACTER)
			((MonsterParent*)m_vecTarget[i])->CalculDamage(m_stSkill.fDamage);
		else
			((CharacterParant*)m_vecTarget[i])->CalculDamage(m_stSkill.fDamage);
	}
}

void Skill::DamageMultiple()
{
	if (m_fElapseTime < m_fPrevTime + m_stSkill.fDamageInterval) return;

	m_fPrevTime = m_fElapseTime;

	m_nDamageCount++;

	for (int i = 0; i < m_vecTarget.size(); i++)
	{
		if (m_eOwner == SKILLO_CHARACTER)
			((MonsterParent*)m_vecTarget[i])->CalculDamage(m_stSkill.fDamage);
		else
			((CharacterParant*)m_vecTarget[i])->CalculDamage(m_stSkill.fDamage);
	}
}

void Skill::Buff()
{
	if (m_stSkill.fBuffTime < 0)
	{
		if (m_nDamageCount == 1)
		{
			if (m_eOwner == SKILLO_CHARACTER)
			{
				m_pCharacter->Getstatus()->chr.nMaxHp += m_stSkill.buffStatus.chr.nMaxHp;
				m_pCharacter->Getstatus()->chr.nCurrentHP += m_stSkill.buffStatus.chr.nCurrentHP;
			}
			else
			{
				//m_pMonster->get
			}
		}
	}
	else
	{
		m_isBuff = true;
	}
}

void * Skill::GetSingleTarget()
{
	D3DXVECTOR3 posChr = *m_pCharacter->GetCharacter()->GetPosition();
	D3DXVECTOR3 posMon = *m_pMonster->GetModel()->GetPosition();

	if (m_eOwner == SKILLO_MONSTER)
	{
		float length = D3DXVec3Length(&(posMon - posChr));

		if (length >= m_stSkill.fMinLength && length <= m_stSkill.fMaxLength)
		{
			// 시선
			D3DXVECTOR3 front;
			D3DXMATRIX matY;
			D3DXMatrixRotationY(&matY, m_pMonster->GetModel()->GetRotation()->y);
			D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
			D3DXVECTOR3 v0 = front;
			// 대상방향
			D3DXVECTOR3 v1 = posChr - posMon;
			D3DXVec3Normalize(&v1, &v1);
			float dot = D3DXVec3Dot(&v0, &v1) / D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
			if (dot >= cos(m_stSkill.fAngle / 2))
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
				// 시선
				D3DXVECTOR3 front;
				D3DXMATRIX matY;
				D3DXMatrixRotationY(&matY, m_pCharacter->GetCharacter()->GetRotation()->y);
				D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
				D3DXVECTOR3 v0 = front;
				// 대상방향
				D3DXVECTOR3 v1 = posMon - posChr;
				D3DXVec3Normalize(&v1, &v1);
				float dot = D3DXVec3Dot(&v0, &v1) / D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
				if (dot >= cos(m_stSkill.fAngle / 2))
				{
					if (minLength > length)
					{
						minIndex = i;
						minLength = length;
					}
				}
			}
		}

		if (minIndex > 0)
			return m_vecMonster[minIndex];
	}

	return NULL;
}

vector<void*> Skill::GetMultipleTarget()
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
			// 시선
			D3DXVECTOR3 front;
			D3DXMATRIX matY;
			D3DXMatrixRotationY(&matY, m_pMonster->GetModel()->GetRotation()->y);
			D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, 1), &matY);
			D3DXVECTOR3 v0 = front;
			// 대상방향
			D3DXVECTOR3 v1 = posChr - posMon;
			D3DXVec3Normalize(&v1, &v1);
			float dot = D3DXVec3Dot(&v0, &v1) / D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
			if (dot >= cos(m_stSkill.fAngle / 2))
				vecTarget.push_back(m_pCharacter);
		}
	}

	if (m_eOwner == SKILLO_CHARACTER)
	{
		for (int i = 0; i < m_vecMonster.size(); i++)
		{
			posMon = *m_vecMonster[i]->GetModel()->GetPosition();
			float length = D3DXVec3Length(&(posMon - posChr));

			if (length >= m_stSkill.fMinLength && length <= m_stSkill.fMaxLength
				&& m_stSkill.nMaxTarget > vecTarget.size())
			{
				// 시선
				D3DXVECTOR3 front;
				D3DXMATRIX matY;
				D3DXMatrixRotationY(&matY, m_pCharacter->GetCharacter()->GetRotation()->y);
				D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
				D3DXVECTOR3 v0 = front;
				// 대상방향
				D3DXVECTOR3 v1 = posMon - posChr;
				D3DXVec3Normalize(&v1, &v1);
				float dot = D3DXVec3Dot(&v0, &v1) / D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
				if (dot >= cos(m_stSkill.fAngle / 2))
					vecTarget.push_back(m_vecMonster[i]);
			}
		}
	}

	return vecTarget;
}

void Skill::ParticleThis()
{
	float fTimeOffset = m_stSkill.fDamageDelay + m_stSkill.fDamageInterval * m_stSkill.nDamageCount;

	if (m_fElapseTime > fTimeOffset + m_stSkill.fParticleTime)
	{
		for (auto p : m_vecParticle)
		{
			p->SetRegen(false);
			p->Update();
		}
		return;
	}

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
			m_vecParticle[i]->SetPosition(*m_pCharacter->GetCharacter()->GetPosition() + 
				D3DXVECTOR3(0, m_stSkill.fYOffset, 0));
			if (m_stSkill.isAutoRot)
			{
				D3DXVECTOR3 rot = *m_pCharacter->GetCharacter()->GetRotation();
				rot.y += D3DX_PI;
				m_vecParticle[i]->SetRotation(rot);
			}
			m_vecParticle[i]->World();
			m_vecParticle[i]->Update();
		}
		else
		{
			m_vecParticle[i]->SetPosition(*m_pMonster->GetModel()->GetPosition() +
				D3DXVECTOR3(0, m_stSkill.fYOffset, 0));
			m_vecParticle[i]->World();
			m_vecParticle[i]->Update();
		}
	}
}

void Skill::ParticleTarget()
{
	float fTimeOffset = m_stSkill.fDamageDelay + m_stSkill.fDamageInterval * m_stSkill.nDamageCount;

	if (m_fElapseTime > fTimeOffset + m_stSkill.fParticleTime)
	{
		for (auto p : m_vecParticle)
			p->SetRegen(false);
	}
	
	for (int i = 0; i < m_vecTarget.size(); i++)
	{
		for (int j = 0; j < m_vecParticle.size(); j++)
		{
			float t = (m_fElapseTime - fTimeOffset) / m_stSkill.fParticleTime;
			if (m_eOwner == SKILLO_CHARACTER)
			{
				D3DXVECTOR3 pos = *((MonsterParent*)m_vecTarget[i])->GetModel()->GetPosition();

				if (m_eParticleProcess == SKILLE_TOTHIS && m_nDamageCount >= m_stSkill.nDamageCount)
				{
					pos = Linear(*((MonsterParent*)m_vecTarget[i])->GetModel()->GetPosition(),
						*m_pCharacter->GetCharacter()->GetPosition(), t);
				}

				m_vecParticle[i]->SetPosition(pos + D3DXVECTOR3(0, m_stSkill.fYOffset, 0));
				m_vecParticle[i]->World();
				m_vecParticle[i]->Update();
			}
			else
			{
				D3DXVECTOR3 pos = *((CharacterParant*)m_vecTarget[i])->GetCharacter()->GetPosition();

				if (m_eParticleProcess == SKILLE_TOTHIS && m_nDamageCount >= m_stSkill.nDamageCount)
				{
					pos = Linear(*((CharacterParant*)m_vecTarget[i])->GetCharacter()->GetPosition(),
						*m_pMonster->GetModel()->GetPosition(), t);
				}

				m_vecParticle[i]->SetPosition(pos +	D3DXVECTOR3(0, m_stSkill.fYOffset, 0));
				m_vecParticle[i]->World();
				m_vecParticle[i]->Update();
			}
		}
	}
}

void Skill::ParticleDamage()
{
	if (m_fElapseTime > m_stSkill.fDamageDelay + m_stSkill.fParticleTime ||
		m_nDamageCount >= m_stSkill.nDamageCount)
	{
		for (auto p : m_vecParticle)
			p->SetRegen(false);
	}

	for (int i = 0; i < m_vecParticle.size(); i++)
	{
		D3DXVECTOR3 pos = *m_vecParticle[i]->GetPosition() + m_vecTargetDir[i] * m_stSkill.fParticleSpeed;
		m_vecParticle[i]->SetPosition(pos);
		m_vecParticle[i]->World();
		m_vecParticle[i]->Update();
	}

	for (int i = 0; i < m_vecTarget.size(); i++)
	{
		for (int j = 0; j < m_vecParticle.size(); j++)
		{
			ST_SPHERE sphere = m_stSphere;
			sphere.center = *m_vecParticle[j]->GetPosition();
			if (m_eOwner == SKILLO_CHARACTER)
			{
				if (IntersectSphere(sphere, ((MonsterParent*)m_vecTarget[i])->GetModel()->GetBoundSphere()))
				{
					if (m_fElapseTime < m_fPrevTime + m_stSkill.fDamageInterval) return;
					m_fPrevTime = m_fElapseTime;
					m_nDamageCount++;
					((MonsterParent*)m_vecTarget[i])->CalculDamage(m_stSkill.fDamage);
				}
			}
			else
			{
				if (IntersectSphere(sphere, ((CharacterParant*)m_vecTarget[i])->GetCharacter()->GetBoundSphere()))
				{
					if (m_fElapseTime < m_fPrevTime + m_stSkill.fDamageInterval) return;
					m_fPrevTime = m_fElapseTime;
					m_nDamageCount++;
					((CharacterParant*)m_vecTarget[i])->CalculDamage(m_stSkill.fDamage);
				}
			}
		}
	}
}

void Skill::EffectDamage()
{
	for (int i = 0; i < m_vecTarget.size(); i++)
	{
		for (int j = 0; j < m_vecEffect.size(); j++)
		{
			ST_SPHERE sphere = m_vecEffect[j]->GetBoundSphere();
			if (m_eOwner == SKILLO_CHARACTER)
			{
				if (IntersectSphere(sphere, ((MonsterParent*)m_vecTarget[i])->GetModel()->GetBoundSphere()))
				{
					if (m_fElapseTime < m_fPrevTime + m_stSkill.fDamageInterval) return;
					m_fPrevTime = m_fElapseTime;
					m_nDamageCount++;
					((MonsterParent*)m_vecTarget[i])->CalculDamage(m_stSkill.fDamage);
				}
			}
			else
			{
				if (IntersectSphere(sphere, ((CharacterParant*)m_vecTarget[i])->GetCharacter()->GetBoundSphere()))
				{
					if (m_fElapseTime < m_fPrevTime + m_stSkill.fDamageInterval) return;
					m_fPrevTime = m_fElapseTime;
					m_nDamageCount++;
					((CharacterParant*)m_vecTarget[i])->CalculDamage(m_stSkill.fDamage);
				}
			}
		}
	}
}

Skill::Skill()
{
}

Skill::Skill(SKILL_PROCESS damage, SKILL_PROCESS target,
	SKILL_EFFECT particleP, SKILL_EFFECT effectP, string particle, ST_EFFECT effect,
	LPDIRECT3DTEXTURE9 iconTex, string name)
{
	ZeroMemory(this, sizeof(Skill));
	m_eDamageProcess = damage;
	m_eTargetProcess = target;
	m_eParticleProcess = particleP;
	m_eEffectProcess = effectP;
	m_sParticle = particle;
	m_stEffect = effect;
	m_sSkillName = name;
	m_pSkillIcon = iconTex;

	m_stSphere.radius = 1;
	m_stSphere.center = D3DXVECTOR3(0, 0, 0);

	PARTICLE->AddParticle(m_sParticle,
		TEXTUREMANAGER->AddTexture("Particle Sphere", "Texture/Particle/Sphere.png"), m_sParticle);
}

Skill::~Skill()
{
	if (!m_vecParticle.empty())
	{
		for (auto p : m_vecParticle)
			SAFE_DELETE(p);
		m_vecParticle.clear();
	}
	if (!m_vecEffect.empty())
	{
		for (auto e : m_vecEffect)
			SAFE_DELETE(e);
		m_vecEffect.clear();
	}
}

void Skill::Prepare(CharacterParant * pCharacter, MonsterParent* pMonster, vector<MonsterParent*> vecMonster, ST_SKILL skill, SKILL_OWNER owner)
{
	m_pCharacter = pCharacter;
	m_pMonster = pMonster;
	m_vecMonster = vecMonster;
	m_stSkill = skill;
	m_eOwner = owner;

	if (m_eDamageProcess == SKILLP_SINGLE)
		m_stSkill.nDamageCount = 1;

	m_stSkill.fAngle = D3DXToRadian(m_stSkill.fAngle);

	m_stEffect.time = m_stSkill.fEffectTime;

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

	m_vecTarget.clear();
	m_vecTargetDir.clear();
}

void Skill::Trigger()
{
	if (!m_isProcess)
	{
		m_isProcess = true;
		
		if (m_eTargetProcess == SKILLP_SINGLE)
		{
			void * target = GetSingleTarget();
			if (target)
				m_vecTarget.push_back(target);
		}
		else
			m_vecTarget = GetMultipleTarget();

		for (int i = 0; i < m_vecTarget.size(); i++)
		{
			if (m_eParticleProcess != SKILLE_NONE)
			{
				m_vecParticle.push_back(PARTICLE->GetParticle(m_sParticle));
				if (m_eOwner == SKILLO_CHARACTER)
					m_vecParticle.back()->SetPosition(*m_pCharacter->GetCharacter()->GetPosition());
				else
					m_vecParticle.back()->SetPosition(*m_pMonster->GetModel()->GetPosition());
			}
			if (m_eEffectProcess != SKILLE_NONE)
			{
				EffectObject * object = new EffectObject;
				if (m_eOwner == SKILLO_CHARACTER)
				{
					if (m_eEffectProcess == SKILLE_TOTARGET)
						m_stEffect.dir = *((MonsterParent*)m_vecTarget[i])->GetModel()->GetPosition() -
							*m_pCharacter->GetCharacter()->GetPosition();
					if (m_eEffectProcess == SKILLE_TOTHIS)
						m_stEffect.dir = *m_pCharacter->GetCharacter()->GetPosition() - 
						*((MonsterParent*)m_vecTarget[i])->GetModel()->GetPosition();

					if (m_eEffectProcess == SKILLE_THIS || m_eEffectProcess == SKILLE_TOTARGET)
						object->Init(m_stEffect, *m_pCharacter->GetCharacter()->GetPosition());
					else
						object->Init(m_stEffect, *((MonsterParent*)m_vecTarget[i])->GetModel()->GetPosition());
				}
				else
				{
					if (m_eEffectProcess == SKILLE_TOTARGET)
						m_stEffect.dir = *((CharacterParant*)m_vecTarget[i])->GetCharacter()->GetPosition() -
							*m_pMonster->GetModel()->GetPosition();
					if (m_eEffectProcess == SKILLE_TOTHIS)
						m_stEffect.dir = *m_pMonster->GetModel()->GetPosition() - 
						*((CharacterParant*)m_vecTarget[i])->GetCharacter()->GetPosition();

					if (m_eEffectProcess == SKILLE_THIS || m_eEffectProcess == SKILLE_TOTARGET)
						object->Init(m_stEffect, *m_pMonster->GetModel()->GetPosition());
					else
						object->Init(m_stEffect, *((CharacterParant*)m_vecTarget[i])->GetCharacter()->GetPosition());
				}
				m_vecEffect.push_back(object);
			}
		}

		if (m_eOwner == SKILLO_CHARACTER)
		{
			for (int i = 0; i < m_vecTarget.size(); i++)
			{
				D3DXVECTOR3 dir = *((MonsterParent*)m_vecTarget[i])->GetModel()->GetPosition() -
					*m_pCharacter->GetCharacter()->GetPosition();
				D3DXVec3Normalize(&dir, &dir);
				m_vecTargetDir.push_back(dir);
			}
		}
		else
		{
			D3DXVECTOR3 dir = *m_pCharacter->GetCharacter()->GetPosition() -
				*m_pMonster->GetModel()->GetPosition();
			D3DXVec3Normalize(&dir, &dir);
			m_vecTargetDir.push_back(dir);
		}
	}
}

void Skill::Update()
{
	if (!m_isProcess) return;

	// 데미지 및 타겟 처리
	if (m_stSkill.fDamageDelay < m_fElapseTime)
	{
		if (m_eParticleProcess == SKILLE_TOTARGET || m_eEffectProcess == SKILLE_TOTARGET)
		{
			if (m_eParticleProcess == SKILLE_TOTARGET)
				ParticleDamage();
			if (m_eEffectProcess == SKILLE_TOTARGET)
				EffectDamage();
		}
		else if(m_nDamageCount < m_stSkill.nDamageCount)
		{
			if (m_eDamageProcess == SKILLP_SINGLE)
				DamageSingle();
			if (m_eDamageProcess == SKILLP_MULTIPLE)
				DamageMultiple();
		}
	}

	if (m_stSkill.fDamageDelay < m_fElapseTime)
		Buff();

	// 파티클 처리
	if (m_eParticleProcess == SKILLE_THIS)
		ParticleThis();
	if (m_eParticleProcess == SKILLE_TARGET ||	m_eParticleProcess == SKILLE_TOTHIS)
		ParticleTarget();

	// 이펙트 처리
	for (int i = 0; i < m_vecEffect.size();)
	{
		if (!m_vecEffect[i]->IsFinish())
		{
			m_vecEffect[i]->Update();
			i++;
		}
		else
			m_vecEffect.erase(m_vecEffect.begin() + i);
	}

	m_fElapseTime += TIME->GetElapsedTime();
}

void Skill::Render()
{
	if (!m_isProcess) return;

	if (DEBUG)
		Debug();

	if (m_pSkillIcon)
	{
		SPRITE_BEGIN;
		D3DXMATRIX world;
		D3DXMatrixIdentity(&world);
		world._41 = 100;
		world._42 = 200;
		SPRITE->SetTransform(&world);
		SPRITE->Draw(m_pSkillIcon, NULL, NULL, NULL, 0xFFFFFFFF);
		SPRITE_END;
	}

	for (auto p : m_vecParticle)
		p->Render();

	for (auto e : m_vecEffect)
		e->Render();
}

void Skill::Debug()
{
	TEXT->Add("진행시간 : " + to_string(m_fElapseTime), 10, 20, 20, "", 0xFFFFFFFF);
	TEXT->Add("이전시간 : " + to_string(m_fPrevTime), 10, 40, 20, "", 0xFFFFFFFF);
	TEXT->Add("데미지카운트 : " + to_string(m_nDamageCount), 10, 60, 20, "", 0xFFFFFFFF);

	DWORD prevFillMode;
	DEVICE->GetRenderState(D3DRS_FILLMODE, &prevFillMode);
	DEVICE->SetTexture(0, NULL);
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// BoundSphere
	if (m_nDamageCount < m_stSkill.nDamageCount)
	{
		LPD3DXMESH mesh;
		D3DXMATRIX matT;
		D3DXCreateSphere(DEVICE, m_stSphere.radius, 8, 8, &mesh, NULL);
		for (int i = 0; i < m_vecParticle.size(); i++)
		{
			D3DXVECTOR3 pos = *m_vecParticle[i]->GetPosition();
			D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);
			DEVICE->SetTransform(D3DTS_WORLD, &matT);
			mesh->DrawSubset(0);
		}
		SAFE_RELEASE(mesh);
	}

	DEVICE->SetRenderState(D3DRS_FILLMODE, prevFillMode);
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
					Skill skill = SkillParse(ent->d_name, dirPath + ent->d_name + ".sk");
					m_mapSkill.insert(make_pair(ent->d_name, skill));
				}
			}
		}
	}
}

Skill SkillManager::SkillParse(string name, string path)
{
	FILE * fp;
	fopen_s(&fp, path.c_str(), "r");

	Skill skill;

	SKILL_PROCESS damage, target;
	SKILL_EFFECT particleP = SKILLE_THIS, effectP = SKILLE_THIS;
	string particle;
	ST_EFFECT effect;
	LPDIRECT3DTEXTURE9 iconTex = NULL;

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

		if (strcmp(tok, "ICON") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			iconTex = TEXTUREMANAGER->AddTexture(name + " Icon", tok);
		}

		if (strcmp(tok, "SKILL_PROCESS_DAMAGE") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			if (strcmp(tok, "SINGLE") == 0)
				damage = SKILLP_SINGLE;
			else if (strcmp(tok, "MULTIPLE") == 0)
				damage = SKILLP_MULTIPLE;
		}
		if (strcmp(tok, "SKILL_PROCESS_TARGET") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			if (strcmp(tok, "SINGLE") == 0)
				target = SKILLP_SINGLE;
			if (strcmp(tok, "MULTIPLE") == 0)
				target = SKILLP_MULTIPLE;
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
			if (strcmp(tok, "NONE") == 0)
				particleP = SKILLE_NONE;
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
			if (strcmp(tok, "NONE") == 0)
				effectP = SKILLE_NONE;
		}

		if (strcmp(tok, "PARTICLE") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			particle = string(tok);
		}

		if (strcmp(tok, "EFFECT_TEXTURE") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			effect.tex = TEXTUREMANAGER->AddTexture(name + " Effect", tok);
		}
		if (strcmp(tok, "EFFECT_ROTATION") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &effect.rot.x, &effect.rot.y, &effect.rot.z);
		}
		if (strcmp(tok, "EFFECT_RANDOM") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%d %d %d", &effect.isRX, &effect.isRY, &effect.isRZ);
		}
		if (strcmp(tok, "EFFECT_SPHERE") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%d", &effect.isSphere);
		}
		if (strcmp(tok, "EFFECT_HEIGHT") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &effect.height);
		}
		if (strcmp(tok, "EFFECT_SCALE") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &effect.sc0, &effect.sc1, &effect.sc2);
		}
		if (strcmp(tok, "EFFECT_SPEED") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &effect.sp0, &effect.sp1, &effect.sp2);
		}
		if (strcmp(tok, "EFFECT_ALPHA") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%d %d %d", &effect.a0, &effect.a1, &effect.a2);
		}
	}

	fclose(fp);

	if (effectP == SKILLE_TOTARGET || effectP == SKILLE_TOTHIS)
		effect.dir = D3DXVECTOR3(0, 0, 1);

	skill = Skill(damage, target, particleP, effectP, particle, effect, iconTex, name);

	return skill;
}

Skill * SkillManager::GetSkill(string keyName)
{
	if (m_mapSkill.find(keyName) == m_mapSkill.end())
		return NULL;
	
	Skill * skill = new Skill;
	*skill = m_mapSkill[keyName];

	return skill;
}
