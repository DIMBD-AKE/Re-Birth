#include "../../../stdafx.h"
#include "MagicCircle.h"


MagicCircle::MagicCircle()
{
}


MagicCircle::~MagicCircle()
{
}

bool MagicCircle::PlayerCollision(D3DXVECTOR3 targetPos, float targetR)
{
	D3DXVECTOR3 tempVec = targetPos - m_vPos;
	float tempLength = D3DXVec3Length(&tempVec);

	if (m_fRadius + targetR > tempLength)
	{
		return true;
	}

	return false;
}