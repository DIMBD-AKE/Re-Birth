#include "../../stdafx.h"
#include "ParticleManager.h"


ParticleManager::ParticleManager()
{
}


ParticleManager::~ParticleManager()
{
}

Particle::Particle()
	: m_pTexture(NULL)
	, m_pVB(NULL)
{
}

Particle::~Particle()
{
	SAFE_RELEASE(m_pVB);
	SAFE_DELETE(m_stOrigAttribute);
	SAFE_DELETE(m_stVarAttribute);
	for (auto a : m_lAttribute)
		SAFE_DELETE(a);
}

void Particle::Init(LPDIRECT3DTEXTURE9 texture, float size, int count,
	ST_PARTICLE_ATTRIBUTE orig, ST_PARTICLE_ATTRIBUTE_VARIABLE var)
{
	m_pTexture = texture;
	m_fParticleSize = size;
	m_nParticleCount = count;
	m_nVertexBatchSize = count / 1;
	m_nVertexOffset = 0;

	SAFE_DELETE(m_pVB);
	DEVICE->CreateVertexBuffer(
		m_nParticleCount * sizeof(ST_PARTICLE),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		ST_PARTICLE::FVF,
		D3DPOOL_DEFAULT,
		&m_pVB, NULL);

	m_stOrigAttribute = new ST_PARTICLE_ATTRIBUTE(orig);
	m_stVarAttribute = new ST_PARTICLE_ATTRIBUTE_VARIABLE(var);

	for (int i = 0; i < m_nParticleCount; i++)
		m_lAttribute.push_back(new ST_PARTICLE_ATTRIBUTE(ResetParticle(var)));
}

ST_PARTICLE_ATTRIBUTE Particle::ResetParticle(ST_PARTICLE_ATTRIBUTE_VARIABLE var)
{
	ST_PARTICLE_ATTRIBUTE att = *m_stOrigAttribute;

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

	return att;
}

void Particle::Update()
{
	auto iter = m_lAttribute.begin();
	for (; iter != m_lAttribute.end(); iter++)
	{
		(*iter)->vPos += 
			(*iter)->vVelocity * TIME->GetElapsedTime() + 
			(*iter)->vAcceleration * TIME->GetElapsedTime() +
			(*iter)->vGravity * TIME->GetElapsedTime();

		(*iter)->vAcceleration += (*iter)->vAcceleration * TIME->GetElapsedTime();
		(*iter)->vGravity += (*iter)->vGravity * TIME->GetElapsedTime();

		(*iter)->fAge += TIME->GetElapsedTime();

		if ((*iter)->fAge > (*iter)->fLifeTime)
			*(*iter) = ResetParticle(*m_stVarAttribute);
	}
}

void Particle::PreRender()
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	DEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, true);

	DWORD b = FtoDw(m_fParticleSize);
	DEVICE->SetRenderState(D3DRS_POINTSIZE, b);

	DEVICE->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0));
	DEVICE->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0));
	DEVICE->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0));
}

void Particle::Render()
{
	PreRender();

	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->SetTexture(0, m_pTexture);
	DEVICE->SetFVF(ST_PARTICLE::FVF);
	DEVICE->SetStreamSource(0, m_pVB, 0, sizeof(ST_PARTICLE::FVF));

	if (m_nVertexOffset >= m_nParticleCount)
		m_nVertexOffset = 0;

	ST_PARTICLE * pV = NULL;
	m_pVB->Lock(
		m_nVertexOffset * sizeof(ST_PARTICLE),
		m_nVertexBatchSize * sizeof(ST_PARTICLE),
		(void**)&pV,
		m_nVertexOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

	int numParticleInBatch = 0;

	auto iter = m_lAttribute.begin();
	for (; iter != m_lAttribute.end(); iter++)
	{
		if ((*iter)->isAlive)
		{
			pV->p = (*iter)->vPos;
			D3DXCOLOR color = (*iter)->colorFade - (*iter)->color;
			color *= (*iter)->fAge / (*iter)->fLifeTime;
			pV->c = (*iter)->color + color;
			pV++;

			numParticleInBatch++;

			if (numParticleInBatch >= m_nVertexBatchSize)
			{
				m_pVB->Unlock();

				DEVICE->DrawPrimitive(D3DPT_POINTLIST, m_nVertexOffset, m_nVertexBatchSize);
				
				m_nVertexOffset += m_nVertexBatchSize;

				if (m_nVertexOffset >= m_nParticleCount)
					m_nVertexOffset = 0;

				m_pVB->Lock(
					m_nVertexOffset * sizeof(ST_PARTICLE),
					m_nVertexBatchSize * sizeof(ST_PARTICLE),
					(void**)&pV,
					m_nVertexOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

				numParticleInBatch = 0;
			}
		}
	}

	m_pVB->Unlock();

	if (numParticleInBatch)
		DEVICE->DrawPrimitive(D3DPT_POINTLIST, m_nVertexOffset, numParticleInBatch);

	m_nVertexOffset += m_nVertexBatchSize;

	PostRender();
}

void Particle::PostRender()
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	DEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, false);
}

void ParticleManager::AddParticle(string keyName, LPDIRECT3DTEXTURE9 texture, float size, int count, ST_PARTICLE_ATTRIBUTE orig, ST_PARTICLE_ATTRIBUTE_VARIABLE var)
{
	if (m_mapParticle.find(keyName) != m_mapParticle.end()) return;
	Particle * particle = new Particle;
	particle->Init(texture, size, count, orig, var);
	m_mapParticle.insert(make_pair(keyName, particle));
}

void ParticleManager::AddParticle(string fullPath)
{
}

void ParticleManager::Update()
{
	auto iter = m_mapParticle.begin();
	for (; iter != m_mapParticle.end(); iter++)
		iter->second->Update();
}

void ParticleManager::Render()
{
	auto iter = m_mapParticle.begin();
	for (; iter != m_mapParticle.end(); iter++)
		iter->second->Render();
}

void ParticleManager::Release()
{
	auto iter = m_mapParticle.begin();
	for (; iter != m_mapParticle.end(); iter++)
		SAFE_DELETE(iter->second);
}
