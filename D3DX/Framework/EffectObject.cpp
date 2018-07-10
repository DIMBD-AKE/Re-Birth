#include "../stdafx.h"
#include "EffectObject.h"



EffectObject::EffectObject()
{
}


EffectObject::~EffectObject()
{
	SAFE_RELEASE(m_pVB);
}

void EffectObject::Init(ST_EFFECT_IMAGE info, D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
	m_stInfo = info;
	m_vPos = pos;
	m_vDir = dir;
	D3DXVec3Normalize(&dir, &dir);

	D3DXVECTOR3 zero = D3DXVECTOR3(0, 0, 0);
	float angle = GetAngle(zero.x, zero.z, dir.x, dir.z);
	m_vRot.y = angle;
	m_vRot.x = D3DX_PI / 2;
	m_vRot.x = FRand(-D3DX_PI / 2, D3DX_PI / 2);

	D3DSURFACE_DESC desc;
	info.tex->GetLevelDesc(0, &desc);

	float rate = info.height / desc.Height;
	float widthH = desc.Width * rate / 2;
	float heightH = desc.Height * rate / 2;

	ST_PCT_VERTEX v;
	v.c = 0xFFFFFFFF;
	v.t = D3DXVECTOR2(0, 1);
	v.p = D3DXVECTOR3(-widthH, -heightH, 0);
	m_vecVertex.push_back(v);
	v.t = D3DXVECTOR2(0, 0);
	v.p = D3DXVECTOR3(-widthH, heightH, 0);
	m_vecVertex.push_back(v);
	v.t = D3DXVECTOR2(1, 0);
	v.p = D3DXVECTOR3(widthH, heightH, 0);
	m_vecVertex.push_back(v);
	v.t = D3DXVECTOR2(0, 1);
	v.p = D3DXVECTOR3(-widthH, -heightH, 0);
	m_vecVertex.push_back(v);
	v.t = D3DXVECTOR2(1, 0);
	v.p = D3DXVECTOR3(widthH, heightH, 0);
	m_vecVertex.push_back(v);
	v.t = D3DXVECTOR2(1, 1);
	v.p = D3DXVECTOR3(widthH, -heightH, 0);
	m_vecVertex.push_back(v);

	DEVICE->CreateVertexBuffer(m_vecVertex.size() * sizeof(ST_PCT_VERTEX),
		D3DUSAGE_DYNAMIC, ST_PCT_VERTEX::FVF, D3DPOOL_DEFAULT, &m_pVB, NULL);

	m_pVB->Lock(0, 0, (void**)&m_pV, 0);
	memcpy(m_pV, &m_vecVertex[0], sizeof(ST_PCT_VERTEX) * m_vecVertex.size());
	m_pVB->Unlock();
}

void EffectObject::Update()
{
	float t = m_fElapse / m_stInfo.time;
	float speed = pow(1 - t, 2) * m_stInfo.sp0 +
		2 * t *(1 - t) * m_stInfo.sp1 +
		pow(t, 2) * m_stInfo.sp2;
	float scale = pow(1 - t, 2) * m_stInfo.sc0 +
		2 * t *(1 - t) * m_stInfo.sc1 +
		pow(t, 2) * m_stInfo.sc2;
	int alpha = pow(1 - t, 2) * m_stInfo.a0 +
		2 * t *(1 - t) * m_stInfo.a1 +
		pow(t, 2) * m_stInfo.a2;

	m_fElapse += TIME->GetElapsedTime();
	m_vPos += m_vDir * speed;

	for (int i = 0; i < m_vecVertex.size(); i++)
		m_vecVertex[i].c = D3DCOLOR_ARGB(alpha, 255, 255, 255);

	m_pVB->Lock(0, 0, (void**)&m_pV, 0);
	memcpy(m_pV, &m_vecVertex[0], sizeof(ST_PCT_VERTEX) * m_vecVertex.size());
	m_pVB->Unlock();

	D3DXMATRIX matS, matR, matT;
	D3DXMatrixRotationYawPitchRoll(&matR, m_vRot.y, m_vRot.x, m_vRot.z);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y + m_stInfo.height / 2, m_vPos.z);
	D3DXMatrixScaling(&matS, scale, scale, scale);

	m_matWorld = matS * matR * matT;
}

void EffectObject::Render()
{
	DEVICE->SetTransform(D3DTS_WORLD, &m_matWorld);
	DEVICE->SetTexture(0, m_stInfo.tex);
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG0, D3DTA_DIFFUSE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, false);

	DEVICE->SetFVF(ST_PCT_VERTEX::FVF);
	DEVICE->SetStreamSource(0, m_pVB, 0, sizeof(ST_PCT_VERTEX));
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG0, D3DTA_CURRENT);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

bool EffectObject::IsFinish()
{
	return (m_stInfo.time <= m_fElapse);
}
