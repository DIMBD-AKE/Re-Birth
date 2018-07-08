#pragma once
class MagicCircle
{
	D3DXVECTOR3 m_vPos;
	float m_fRadius;

public:
	MagicCircle();
	~MagicCircle();

	void SetPosAndRad(D3DXVECTOR3 pos, float r)
	{
		m_vPos = pos, m_fRadius = r;
	}
	bool PlayerCollision(D3DXVECTOR3 targetPos, float targetR);
};

