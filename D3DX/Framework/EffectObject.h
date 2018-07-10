#pragma once
class EffectObject
{
private:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	vector<ST_PCT_VERTEX>		m_vecVertex;
	ST_PCT_VERTEX *				m_pV;

	ST_EFFECT_IMAGE		m_stInfo;
	D3DXVECTOR3			m_vPos;
	D3DXVECTOR3			m_vRot;
	D3DXVECTOR3			m_vDir;
	D3DXMATRIX			m_matWorld;
	float				m_fElapse;

public:
	EffectObject();
	~EffectObject();

	void Init(ST_EFFECT_IMAGE info, D3DXVECTOR3 pos, D3DXVECTOR3 dir);
	void Update();
	void Render();
	bool IsFinish();
};

