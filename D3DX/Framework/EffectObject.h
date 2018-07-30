#pragma once

class EffectObject
{
private:
	Model *						m_pModel;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	vector<ST_PCT_VERTEX>		m_vecVertex;
	ST_PCT_VERTEX *				m_pV;

	SYNTHESIZE(ST_EFFECT, m_stInfo, Info);

private:
	D3DXVECTOR3			m_vPos;
	D3DXVECTOR3			m_vMot;
	D3DXMATRIX			m_matWorld;
	float				m_fElapse;
	bool				m_isFlash;
	
	ST_OBB				m_stOBB;
	ST_SPHERE			m_stSphere;

public:
	EffectObject();
	~EffectObject();

	void Init(ST_EFFECT info, D3DXVECTOR3 pos);
	void Update();
	void Render();
	bool IsFinish();

	D3DXVECTOR3* GetPosition() { return &m_vPos; }

	void Debug();

	ST_SPHERE GetBoundSphere();
	ST_OBB GetOBB();
};

