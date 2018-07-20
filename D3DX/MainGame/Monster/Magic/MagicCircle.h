#pragma once
class MagicCircle
{
	D3DXVECTOR3 m_vPos;
	float m_fRadius;

	Particle* m_pParticle;
public:
	MagicCircle();
	~MagicCircle();

	void Setup();
	void Update();
	void Render();

	void SetPosAndRad(D3DXVECTOR3 pos, float r)
	{
		m_vPos = pos, m_fRadius = r;
		
	}
	bool PlayerCollision(D3DXVECTOR3 targetPos, float targetR);

	void SetParticlePos(D3DXVECTOR3 pos){ m_pParticle->SetPosition(m_vPos); }
};

