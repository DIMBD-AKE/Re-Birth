#pragma once

class EffectObject
{
private:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	vector<ST_PCT_VERTEX>		m_vecVertex;
	ST_PCT_VERTEX *				m_pV;

	ST_EFFECT			m_stInfo;
	D3DXVECTOR3			m_vPos;
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

	void Debug();

	ST_SPHERE GetBoundSphere();
	ST_OBB GetOBB();
};

