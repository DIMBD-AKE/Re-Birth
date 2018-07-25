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

	int			m_nVBSize;
	int			m_nVBBatchSize;
	int			m_nVBOffset;

	bool		m_isRegen;
	bool		m_isDie;

	ST_PARTICLE_ATTRIBUTE*			m_pOrigAttribute;
	ST_PARTICLE_ATTRIBUTE*			m_pApplyAttribute;
	ST_PARTICLE_ATTRIBUTE_VARIABLE*	m_pOrigVarAttribute;
	ST_PARTICLE_ATTRIBUTE_VARIABLE*	m_pApplyVarAttribute;

	list<ST_PARTICLE_ATTRIBUTE*>	m_lAttribute;

public:
	ParticleSystem();
	~ParticleSystem();

	void Init(LPDIRECT3DTEXTURE9 texture, float size, int count,
		ST_PARTICLE_ATTRIBUTE * orig, ST_PARTICLE_ATTRIBUTE_VARIABLE * var);

	ST_PARTICLE_ATTRIBUTE ResetParticle(int loop);
	void SetRegen(bool regen) { m_isRegen = regen; }

	ST_PARTICLE_ATTRIBUTE GetOrig() { return *m_pOrigAttribute; }
	ST_PARTICLE_ATTRIBUTE_VARIABLE GetVarOrig() { return *m_pOrigVarAttribute; }
	void SetApply(ST_PARTICLE_ATTRIBUTE apply, ST_PARTICLE_ATTRIBUTE_VARIABLE var) { 
		*m_pApplyAttribute = apply; *m_pApplyVarAttribute = var; }

	void TimeReset();
	void Update();
	void ForceUpdate(int count, float time);
	bool IsDie() { return m_isDie; }

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
	void ApplyWorld();
	void TimeReset() { m_pParticleSystem->TimeReset(); }
	void Update() { m_pParticleSystem->Update(); }
	void ForceUpdate(int count, float time) { m_pParticleSystem->ForceUpdate(count, time); }
	void Render() { m_pParticleSystem->Render(); }
	void SetRegen(bool regen) { m_pParticleSystem->SetRegen(regen); }
	bool IsDie() { return m_pParticleSystem->IsDie(); }
};

class ParticleManager
{
	SINGLETONE(ParticleManager);

private:
	map<string, ST_PARTICLE_INFO> m_mapParticle;

public:
	void AddParticle(string keyName, LPDIRECT3DTEXTURE9 texture, float size, int count,
		ST_PARTICLE_ATTRIBUTE orig, ST_PARTICLE_ATTRIBUTE_VARIABLE var);
	void AddParticle(string keyName, LPDIRECT3DTEXTURE9 texture, string fullPath);

	Particle * GetParticle(string keyName);

	void Release();
};

#define PARTICLE ParticleManager::GetInstance()