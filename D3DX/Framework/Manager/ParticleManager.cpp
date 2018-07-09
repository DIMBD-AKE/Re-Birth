#include "../../stdafx.h"
#include "ParticleManager.h"


ParticleManager::ParticleManager()
{
}


ParticleManager::~ParticleManager()
{
}

ParticleSystem::ParticleSystem()
	: m_pTexture(NULL)
	, m_pVB(NULL)
{
}

ParticleSystem::~ParticleSystem()
{
	SAFE_RELEASE(m_pVB);
	for (auto a : m_lAttribute)
		SAFE_DELETE(a);
}

void ParticleSystem::Init(LPDIRECT3DTEXTURE9 texture, float size, int count,
	ST_PARTICLE_ATTRIBUTE * orig, ST_PARTICLE_ATTRIBUTE_VARIABLE * var)
{
	m_pTexture = texture;
	m_fParticleSize = size;
	m_nParticleCount = count;
	m_nVBBatchSize = count / 1;
	m_nVBOffset = 0;

	SAFE_DELETE(m_pVB);
	DEVICE->CreateVertexBuffer(
		m_nParticleCount * sizeof(ST_PARTICLE),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		ST_PARTICLE::FVF,
		D3DPOOL_DEFAULT,
		&m_pVB, NULL);

	m_pOrigAttribute = orig;
	m_pVarAttribute = var;

	m_isRegen = true;

	D3DXMatrixIdentity(&m_matWorld);

	for (int i = 0; i < m_nParticleCount; i++)
		m_lAttribute.push_back(new ST_PARTICLE_ATTRIBUTE(ResetParticle(0)));

	// 시간 재설정
	TimeReset();
}

ST_PARTICLE_ATTRIBUTE ParticleSystem::ResetParticle(int loop)
{
	ST_PARTICLE_ATTRIBUTE att = *m_pOrigAttribute;
	ST_PARTICLE_ATTRIBUTE_VARIABLE var = *m_pVarAttribute;

	att.nLoop = loop;
	att.nLoop++;
	if (att.nLoop > att.nMaxLoop && att.nMaxLoop > 0)
		att.isAlive = false;
	else
		att.isAlive = true;

	att.fLifeTime += Util::FRand(-var.fLifeTimeVar, var.fLifeTimeVar);

	att.vPos.x += Util::FRand(-var.vPosVar.x, var.vPosVar.x);
	att.vPos.y += Util::FRand(-var.vPosVar.y, var.vPosVar.y);
	att.vPos.z += Util::FRand(-var.vPosVar.z, var.vPosVar.z);
	
	att.vVelocity.x += Util::FRand(-var.vVelocityVar.x, var.vVelocityVar.x);
	att.vVelocity.y += Util::FRand(-var.vVelocityVar.y, var.vVelocityVar.y);
	att.vVelocity.z += Util::FRand(-var.vVelocityVar.z, var.vVelocityVar.z);

	att.vAcceleration.x += Util::FRand(-var.vAccelerationVar.x, var.vAccelerationVar.x);
	att.vAcceleration.y += Util::FRand(-var.vAccelerationVar.y, var.vAccelerationVar.y);
	att.vAcceleration.z += Util::FRand(-var.vAccelerationVar.z, var.vAccelerationVar.z);

	att.vGravity.x += Util::FRand(-var.vGravityVar.x, var.vGravityVar.x);
	att.vGravity.y += Util::FRand(-var.vGravityVar.y, var.vGravityVar.y);
	att.vGravity.z += Util::FRand(-var.vGravityVar.z, var.vGravityVar.z);

	att.fStartRadius += Util::FRand(-var.fStartRadiusVar, var.fStartRadiusVar);
	att.fEndRadius += Util::FRand(-var.fEndRadiusVar, var.fEndRadiusVar);
	att.fRadiusSpeed += Util::FRand(-var.fRadiusSpeedVar, var.fRadiusSpeedVar);

	return att;
}

void ParticleSystem::Attribute(ST_PARTICLE_ATTRIBUTE orig, ST_PARTICLE_ATTRIBUTE_VARIABLE var)
{
	*m_pOrigAttribute = orig;
	*m_pVarAttribute = var;
}

void ParticleSystem::TimeReset()
{
	auto iter = m_lAttribute.begin();
	for (; iter != m_lAttribute.end(); iter++)
	{
		(*iter)->nLoop = 0;
		(*iter)->isAlive = true;
	}

	iter = m_lAttribute.begin();
	for (;; iter++)
	{
		if (iter == m_lAttribute.end())
			iter = m_lAttribute.begin();
		(*iter)->fAge += 0.1;
		if ((*iter)->fAge > (*iter)->fLifeTime)
			break;
	}
}

void ParticleSystem::Update()
{
	auto iter = m_lAttribute.begin();
	for (; iter != m_lAttribute.end(); iter++)
	{
		if (!(*iter)->isAlive) continue;

		(*iter)->vPos += 
			(*iter)->vVelocity * TIME->GetElapsedTime() + 
			(*iter)->vAcceleration * TIME->GetElapsedTime() +
			(*iter)->vGravity * TIME->GetElapsedTime();

		(*iter)->vAcceleration += (*iter)->vAcceleration * TIME->GetElapsedTime();
		(*iter)->vGravity += (*iter)->vGravity * TIME->GetElapsedTime();

		(*iter)->fCurrentRadiusSpeed += (*iter)->fRadiusSpeed * TIME->GetElapsedTime();

		(*iter)->fAge += TIME->GetElapsedTime();

		if ((*iter)->fAge > (*iter)->fLifeTime && m_isRegen)
			*(*iter) = ResetParticle((*iter)->nLoop);
	}
}

void ParticleSystem::PreRender()
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	DEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, false);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	DWORD b = FtoDw(m_fParticleSize);
	DEVICE->SetRenderState(D3DRS_POINTSIZE, b);

	DEVICE->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0));
	DEVICE->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0));
	DEVICE->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0));
	DEVICE->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0));
}

void ParticleSystem::Render()
{
	PreRender();

	DEVICE->SetTransform(D3DTS_WORLD, &m_matWorld);
	DEVICE->SetTexture(0, m_pTexture);
	DEVICE->SetFVF(ST_PARTICLE::FVF);
	DEVICE->SetStreamSource(0, m_pVB, 0, sizeof(ST_PARTICLE::FVF));

	if (m_nVBOffset >= m_nParticleCount)
		m_nVBOffset = 0;

	ST_PARTICLE * pV = NULL;
	m_pVB->Lock(
		m_nVBOffset * sizeof(ST_PARTICLE),
		m_nVBBatchSize * sizeof(ST_PARTICLE),
		(void**)&pV,
		m_nVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

	int numParticleInBatch = 0;

	auto iter = m_lAttribute.begin();
	for (; iter != m_lAttribute.end(); iter++)
	{
		if ((*iter)->isAlive && (*iter)->nLoop > 1)
		{
			float rate = (*iter)->fAge / (*iter)->fLifeTime;

			float radius = (*iter)->fStartRadius + (*iter)->fEndRadius * rate;
			D3DXVECTOR3 vRad = D3DXVECTOR3(0, 0, 0);
			vRad.x = cos((*iter)->fCurrentRadiusSpeed) * radius;
			vRad.z = -sin((*iter)->fCurrentRadiusSpeed) * radius;
			pV->p = (*iter)->vPos + vRad;

			D3DXCOLOR color = (*iter)->colorFade - (*iter)->color;
			color *= rate;
			pV->c = (*iter)->color + color;

			pV++;

			numParticleInBatch++;

			if (numParticleInBatch == m_nVBBatchSize)
			{
				m_pVB->Unlock();

				DEVICE->DrawPrimitive(D3DPT_POINTLIST, m_nVBOffset, m_nVBBatchSize);
				
				m_nVBOffset += m_nVBBatchSize;

				if (m_nVBOffset >= m_nParticleCount)
					m_nVBOffset = 0;

				m_pVB->Lock(
					m_nVBOffset * sizeof(ST_PARTICLE),
					m_nVBBatchSize * sizeof(ST_PARTICLE),
					(void**)&pV,
					m_nVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

				numParticleInBatch = 0;
			}
		}
	}

	m_pVB->Unlock();

	if (numParticleInBatch)
		DEVICE->DrawPrimitive(D3DPT_POINTLIST, m_nVBOffset, numParticleInBatch);

	m_nVBOffset += m_nVBBatchSize;

	PostRender();
}

void ParticleSystem::PostRender()
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	DEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

void ParticleManager::AddParticle(string keyName, LPDIRECT3DTEXTURE9 texture, float size, int count, 
	ST_PARTICLE_ATTRIBUTE orig, ST_PARTICLE_ATTRIBUTE_VARIABLE var)
{
	if (m_mapParticle.find(keyName) != m_mapParticle.end()) return;
	ST_PARTICLE_INFO info;
	info.fParticleSize = size;
	info.nParticleCount = count;
	info.origAttribute = orig;
	info.varAttribute = var;
	info.pTexture = texture;
	if (info.origAttribute.nMaxLoop > 0)
		info.origAttribute.nMaxLoop++;
	m_mapParticle.insert(make_pair(keyName, info));
}

void ParticleManager::AddParticle(string keyName, LPDIRECT3DTEXTURE9 texture, string fullPath)
{
	if (m_mapParticle.find(keyName) != m_mapParticle.end()) return;

	FILE * fp;
	fopen_s(&fp, fullPath.c_str(), "r");

	ST_PARTICLE_ATTRIBUTE orig;
	ST_PARTICLE_ATTRIBUTE_VARIABLE var;
	int count;
	float size;

	ZeroMemory(&orig, sizeof(ST_PARTICLE_ATTRIBUTE));
	ZeroMemory(&var, sizeof(ST_PARTICLE_ATTRIBUTE_VARIABLE));

	char line[256];
	while (true)
	{
		fgets(line, 256, fp);
		if (feof(fp)) break;

		char * context;
		char * tok = strtok_s(line, "\t\n", &context);
		if (strcmp(tok, "A_CNT") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%d", &count);
		}
		if (strcmp(tok, "A_SIZ") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &size);
		}
		if (strcmp(tok, "A_POS") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &orig.vPos.x, &orig.vPos.y, &orig.vPos.z);
		}
		if (strcmp(tok, "A_VEL") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &orig.vVelocity.x, &orig.vVelocity.y, &orig.vVelocity.z);
		}
		if (strcmp(tok, "A_ACL") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &orig.vAcceleration.x, &orig.vAcceleration.y, &orig.vAcceleration.z);
		}
		if (strcmp(tok, "A_GRV") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &orig.vGravity.x, &orig.vGravity.y, &orig.vGravity.z);
		}
		if (strcmp(tok, "A_STR") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &orig.fStartRadius);
		}
		if (strcmp(tok, "A_EDR") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &orig.fEndRadius);
		}
		if (strcmp(tok, "A_RSD") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &orig.fRadiusSpeed);
		}
		if (strcmp(tok, "A_LIF") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &orig.fLifeTime);
		}
		if (strcmp(tok, "A_COL") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			DWORD temp;
			sscanf_s(tok, "%d", &temp);
			orig.color = D3DXCOLOR(temp);
		}
		if (strcmp(tok, "A_CLF") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			DWORD temp;
			sscanf_s(tok, "%d", &temp);
			orig.colorFade = D3DXCOLOR(temp);
		}
		if (strcmp(tok, "A_LOP") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%d", &orig.nMaxLoop);
		}

		if (strcmp(tok, "V_POS") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &var.vPosVar.x, &var.vPosVar.y, &var.vPosVar.z);
		}
		if (strcmp(tok, "V_VEL") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &var.vVelocityVar.x, &var.vVelocityVar.y, &var.vVelocityVar.z);
		}
		if (strcmp(tok, "V_ACL") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &var.vAccelerationVar.x, &var.vAccelerationVar.y, &var.vAccelerationVar.z);
		}
		if (strcmp(tok, "V_GRV") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &var.vGravityVar.x, &var.vGravityVar.y, &var.vGravityVar.z);
		}
		if (strcmp(tok, "V_STR") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &var.fStartRadiusVar);
		}
		if (strcmp(tok, "V_EDR") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &var.fEndRadiusVar);
		}
		if (strcmp(tok, "V_RSD") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &var.fRadiusSpeedVar);
		}
		if (strcmp(tok, "V_LIF") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &var.fLifeTimeVar);
		}
	}

	fclose(fp);

	ST_PARTICLE_INFO info;
	info.fParticleSize = size;
	info.nParticleCount = count;
	info.pTexture = texture;
	info.origAttribute = orig;
	info.varAttribute = var;

	if (info.origAttribute.nMaxLoop > 0)
		info.origAttribute.nMaxLoop++;
	m_mapParticle.insert(make_pair(keyName, info));
}

Particle * ParticleManager::GetParticle(string keyName)
{
	if (m_mapParticle.find(keyName) == m_mapParticle.end())
		return NULL;

	Particle * particle = new Particle;
	particle->Init(&m_mapParticle[keyName]);
	return particle;
}

void ParticleManager::Release()
{
	m_mapParticle.clear();
}

Particle::Particle()
	: m_pParticleSystem(NULL)
{
	m_vPosition = D3DXVECTOR3(0, 0, 0);
	m_vRotation = D3DXVECTOR3(0, 0, 0);
	m_vScale = D3DXVECTOR3(1, 1, 1);
}

Particle::~Particle()
{
	SAFE_DELETE(m_pParticleSystem);
}

void Particle::Init(ST_PARTICLE_INFO * info)
{
	SAFE_DELETE(m_pParticleSystem);
	m_pParticleSystem = new ParticleSystem;
	m_pParticleSystem->Init(info->pTexture, info->fParticleSize, info->nParticleCount,
		&info->origAttribute, &info->varAttribute);
}

void Particle::World()
{
	D3DXMATRIX matS, matR, matT;

	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, m_vRotation.y, m_vRotation.x, m_vRotation.z);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_pParticleSystem->SetWorld(matS * matR * matT);
}
