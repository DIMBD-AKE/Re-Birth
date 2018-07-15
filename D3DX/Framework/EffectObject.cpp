#include "../stdafx.h"
#include "EffectObject.h"



EffectObject::EffectObject()
{
}


EffectObject::~EffectObject()
{
	SAFE_RELEASE(m_pVB);
}

void EffectObject::Init(ST_EFFECT info, D3DXVECTOR3 pos)
{
	m_stInfo = info;
	m_vPos = pos;
	D3DXVec3Normalize(&m_stInfo.dir, &m_stInfo.dir);

	if (D3DXVec3Length(&m_stInfo.dir) < 0.1)
		m_isFlash = true;
	else
		m_isFlash = false;

	m_stInfo.rot.x = D3DXToRadian(m_stInfo.rot.x);
	m_stInfo.rot.y = D3DXToRadian(m_stInfo.rot.y);
	m_stInfo.rot.z = D3DXToRadian(m_stInfo.rot.z);

	if (m_stInfo.isRX)
		m_stInfo.rot.x = FRand(-D3DX_PI / 2, D3DX_PI);
	if (m_stInfo.isRY)
		m_stInfo.rot.y = FRand(-D3DX_PI / 2, D3DX_PI);
	if (m_stInfo.isRZ)
		m_stInfo.rot.z = FRand(-D3DX_PI / 2, D3DX_PI);

	if (!m_isFlash && !m_stInfo.isRY)
	{
		D3DXVECTOR3 zero = D3DXVECTOR3(0, 0, 0);
		float angle = GetAngle(zero.x, zero.z, m_stInfo.dir.x, m_stInfo.dir.z);
		m_stInfo.rot.y = angle;
	}

	D3DSURFACE_DESC desc;
	info.tex->GetLevelDesc(0, &desc);

	float rate = info.height / desc.Height;
	float widthH = desc.Width * rate / 2;
	float heightH = desc.Height * rate / 2;

	m_stSphere.radius = heightH;
	m_stSphere.center = D3DXVECTOR3(0, heightH, 0);

	m_stOBB.fAxisLen[0] = widthH;
	m_stOBB.fAxisLen[1] = heightH;
	m_stOBB.fAxisLen[2] = 0.5;
	m_stOBB.vAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_stOBB.vAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_stOBB.vAxisDir[2] = D3DXVECTOR3(0, 0, 1);
	m_stOBB.vCenterPos = D3DXVECTOR3(0, heightH, 0);

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

	if (!m_isFlash)
		m_vPos += m_stInfo.dir * speed;

	for (int i = 0; i < m_vecVertex.size(); i++)
		m_vecVertex[i].c = D3DCOLOR_ARGB(alpha, 255, 255, 255);

	m_pVB->Lock(0, 0, (void**)&m_pV, 0);
	memcpy(m_pV, &m_vecVertex[0], sizeof(ST_PCT_VERTEX) * m_vecVertex.size());
	m_pVB->Unlock();

	if (m_stInfo.isSphere)
	{
		m_stInfo.rot.x = CAMERA->GetRotation().x;
		m_stInfo.rot.y = CAMERA->GetRotation().y;
	}

	D3DXMATRIX matS, matR, matT;
	D3DXMatrixRotationYawPitchRoll(&matR, m_stInfo.rot.y, m_stInfo.rot.x, m_stInfo.rot.z);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y + m_stInfo.height / 2, m_vPos.z);
	D3DXMatrixScaling(&matS, scale, scale, scale);

	m_matWorld = matS * matR * matT;
}

void EffectObject::Render()
{
	if (DEBUG)
		Debug();

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

void EffectObject::Debug()
{
	DWORD prevFillMode;
	DEVICE->GetRenderState(D3DRS_FILLMODE, &prevFillMode);
	DEVICE->SetTexture(0, NULL);
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// BoundSphere
	LPD3DXMESH mesh;
	D3DXMATRIX matT;
	D3DXCreateSphere(DEVICE, GetBoundSphere().radius, 8, 8, &mesh, NULL);
	D3DXVECTOR3 pos = GetBoundSphere().center;
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);
	DEVICE->SetTransform(D3DTS_WORLD, &matT);
	mesh->DrawSubset(0);
	SAFE_RELEASE(mesh);

	DEVICE->SetRenderState(D3DRS_FILLMODE, prevFillMode);
}

ST_SPHERE EffectObject::GetBoundSphere()
{
	float t = m_fElapse / m_stInfo.time;
	float scale = pow(1 - t, 2) * m_stInfo.sc0 +
		2 * t *(1 - t) * m_stInfo.sc1 +
		pow(t, 2) * m_stInfo.sc2;

	ST_SPHERE sphere = m_stSphere;
	sphere.radius *= scale;
	sphere.center += m_vPos;

	return sphere;
}

ST_OBB EffectObject::GetOBB()
{
	float t = m_fElapse / m_stInfo.time;
	float scale = pow(1 - t, 2) * m_stInfo.sc0 +
		2 * t *(1 - t) * m_stInfo.sc1 +
		pow(t, 2) * m_stInfo.sc2;

	D3DXMATRIX matR;
	D3DXMatrixRotationYawPitchRoll(&matR, m_stInfo.rot.y, m_stInfo.rot.x, m_stInfo.rot.z);

	ST_OBB obb = m_stOBB;
	for (int i = 0; i < 3; i++)
		obb.fAxisLen[i] *= scale;
	for (int i = 0; i < 3; i++)
		D3DXVec3TransformNormal(&obb.vAxisDir[i], &obb.vAxisDir[i], &matR);

	obb.vCenterPos += m_vPos;

	return obb;
}
