#include "../../../stdafx.h"
#include "MagicCircle.h"


MagicCircle::MagicCircle()
{
}


MagicCircle::~MagicCircle()
{
	SAFE_DELETE(m_pParticle);
}

void MagicCircle::Setup()
{
	//PARTICLE->AddParticle("ttest", TEXTUREMANAGER->GetTexture("파티클시험"), "./Particle/ttest.ptc");
	m_pParticle = PARTICLE->GetParticle("마법기본공격");
	//
	
}

void MagicCircle::Update()
{
	m_pParticle->World();
	m_pParticle->Update();
}

void MagicCircle::Render()
{
	m_pParticle->Render();
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