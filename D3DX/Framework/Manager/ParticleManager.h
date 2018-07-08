#pragma once

class ParticleSystem
{
private:
	SYNTHESIZE_PT(D3DXMATRIX, m_matWorld, World);

private:
	LPDIRECT3DTEXTURE9			m_pTexture;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;

	float		m_fParticleSize;
	int			m_nParticleCount;
	int			m_nVBBatchSize;
	int			m_nVBOffset;

	ST_PARTICLE_ATTRIBUTE*			m_pOrigAttribute;
	ST_PARTICLE_ATTRIBUTE_VARIABLE*	m_pVarAttribute;

	list<ST_PARTICLE_ATTRIBUTE*>	m_lAttribute;

public:
	ParticleSystem();
	~ParticleSystem();

	void Init(LPDIRECT3DTEXTURE9 texture, float size, int count,
		ST_PARTICLE_ATTRIBUTE * orig, ST_PARTICLE_ATTRIBUTE_VARIABLE * var);

	ST_PARTICLE_ATTRIBUTE ResetParticle(int loop);

	void Attribute(ST_PARTICLE_ATTRIBUTE orig, ST_PARTICLE_ATTRIBUTE_VARIABLE var);

	void Update();

	void PreRender();
	void Render();
	void PostRender();

	DWORD FtoDw(float f) { return *((DWORD*)&f); }
};

class Particle
{
private:
	SYNTHESIZE_PT(D3DXVECTOR3, m_vRotation, Rotation);
	SYNTHESIZE_PT(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE_PT(D3DXVECTOR3, m_vScale, Scale);

private:
	ParticleSystem *	m_pParticleSystem;

public:
	Particle();
	~Particle();

	void Init(ST_PARTICLE_INFO * info);
	void World();
	void Update() { m_pParticleSystem->Update(); }
	void Render() { m_pParticleSystem->Render(); }
};

class ParticleManager
{
	SINGLETONE(ParticleManager);

private:
	map<string, ST_PARTICLE_INFO> m_mapParticle;

public:
	void AddParticle(string keyName, LPDIRECT3DTEXTURE9 texture, float size, int count,
		ST_PARTICLE_ATTRIBUTE orig, ST_PARTICLE_ATTRIBUTE_VARIABLE var);
	void AddParticle(string fullPath);

	Particle * GetParticle(string keyName);

	void Release();
};

#define PARTICLE ParticleManager::GetInstance()