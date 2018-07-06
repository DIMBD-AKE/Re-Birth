#pragma once

class Particle
{
private:
	LPDIRECT3DTEXTURE9			m_pTexture;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;

	float		m_fParticleSize;
	int			m_nParticleCount;
	int			m_nVertexBatchSize;
	int			m_nVertexOffset;

	ST_PARTICLE_ATTRIBUTE*			m_stOrigAttribute;
	ST_PARTICLE_ATTRIBUTE_VARIABLE*	m_stVarAttribute;

	list<ST_PARTICLE_ATTRIBUTE*>	m_lAttribute;

public:
	Particle();
	~Particle();

	void Init(LPDIRECT3DTEXTURE9 texture, float size, int count,
		ST_PARTICLE_ATTRIBUTE orig, ST_PARTICLE_ATTRIBUTE_VARIABLE var);
	ST_PARTICLE_ATTRIBUTE ResetParticle(ST_PARTICLE_ATTRIBUTE_VARIABLE var);

	void Update();

	void PreRender();
	void Render();
	void PostRender();

	DWORD FtoDw(float f) { return *((DWORD*)&f); }
};

class ParticleManager
{
	SINGLETONE(ParticleManager);

private:
	map<string, Particle*> m_mapParticle;

public:
	void AddParticle(string keyName, LPDIRECT3DTEXTURE9 texture, float size, int count,
		ST_PARTICLE_ATTRIBUTE orig, ST_PARTICLE_ATTRIBUTE_VARIABLE var);
	void AddParticle(string fullPath);

	void Update();
	void Render();

	void Release();
};

#define PARTICLE ParticleManager::GetInstance()