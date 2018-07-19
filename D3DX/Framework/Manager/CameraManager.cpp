#include "../../stdafx.h"
#include "CameraManager.h"



CameraManager::CameraManager()
	: m_vEye(0, 0, -10)
	, m_vUp(0, 1, 0)
	, m_vLookAt(0, 0, 0)
	, m_vRotation(0, 0, 0)
	, m_vPosition(0, 0, 0)
	, m_vCamOffset(0, 0, 0)
	, m_vTargetOffset(0, 0, 0)
	, m_pTargetPos(NULL)
	, m_pTargetRot(NULL)
	, m_eMode(CAMERA_FREE)
	, m_fSpeed(0.5f)
	, m_fSmooth(0.1f)
	, m_fDistance(0)
{
	Setup();
}


CameraManager::~CameraManager()
{
}

void CameraManager::UpdateFrustum()
{
	D3DXMATRIX matView, matProj;
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
	DEVICE->GetTransform(D3DTS_VIEW, &matView);

	for (int i = 0; i < m_vecProjVertex.size(); i++)
	{
		D3DXVec3Unproject(&m_vecWorldVertex[i],
			&m_vecProjVertex[i],
			NULL,
			&matProj,
			&matView,
			NULL);
	}

	D3DXPlaneFromPoints(&m_vecPlane[0], &m_vecWorldVertex[0], &m_vecWorldVertex[1], &m_vecWorldVertex[2]);
	D3DXPlaneFromPoints(&m_vecPlane[1], &m_vecWorldVertex[6], &m_vecWorldVertex[5], &m_vecWorldVertex[4]);
	D3DXPlaneFromPoints(&m_vecPlane[2], &m_vecWorldVertex[1], &m_vecWorldVertex[5], &m_vecWorldVertex[6]);
	D3DXPlaneFromPoints(&m_vecPlane[3], &m_vecWorldVertex[0], &m_vecWorldVertex[3], &m_vecWorldVertex[7]);
	D3DXPlaneFromPoints(&m_vecPlane[4], &m_vecWorldVertex[1], &m_vecWorldVertex[0], &m_vecWorldVertex[4]);
	D3DXPlaneFromPoints(&m_vecPlane[5], &m_vecWorldVertex[2], &m_vecWorldVertex[6], &m_vecWorldVertex[7]);
}

void CameraManager::Setup()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DX_PI / 4.0f,
		rc.right / (float)rc.bottom,
		1.0f,
		10000.0f);

	DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);

	D3DVIEWPORT9 vp;
	DEVICE->GetViewport(&vp);

	// 프러스텀 셋팅
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, 1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, 1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, -1, 0));

	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1, 1));
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, 1, 1));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, 1, 1));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, -1, 1));

	m_vecWorldVertex.resize(8);
	m_vecPlane.resize(6);
}

void CameraManager::Update()
{
	D3DXMATRIX matView, matR;
	D3DXVECTOR3 vEye = m_vEye;
	D3DXVECTOR3 vLookAt = m_vLookAt;
	D3DXVECTOR3 vCamOffset = m_vCamOffset;
	D3DXMatrixRotationYawPitchRoll(&matR, m_vRotation.y, m_vRotation.x, m_vRotation.z);

	if (m_eMode == CAMERA_FREE)
	{

		if (INPUT->KeyDown(VK_RBUTTON))
			m_ptPrevMouse = MOUSE_POS;

		if (INPUT->KeyPress(VK_RBUTTON))
		{
			m_vRotation.x += D3DXToRadian(MOUSE_POS.y - m_ptPrevMouse.y);
			m_vRotation.y += D3DXToRadian(MOUSE_POS.x - m_ptPrevMouse.x);
			if (m_vRotation.x > D3DX_PI * 0.49f) m_vRotation.x = D3DX_PI * 0.49f;
			if (m_vRotation.x < D3DX_PI * -0.49f) m_vRotation.x = D3DX_PI * -0.49f;
			m_ptPrevMouse = MOUSE_POS;
		}

		D3DXVECTOR3 front, right;
		D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, 1), &matR);
		D3DXVec3TransformNormal(&right, &D3DXVECTOR3(1, 0, 0), &matR);
		if (INPUT->KeyPress('W')) m_vPosition += front * m_fSpeed;
		if (INPUT->KeyPress('S')) m_vPosition -= front * m_fSpeed;
		if (INPUT->KeyPress('A')) m_vPosition -= right * m_fSpeed;
		if (INPUT->KeyPress('D')) m_vPosition += right * m_fSpeed;
		if (INPUT->KeyPress('E')) m_vPosition.y += m_fSpeed;
		if (INPUT->KeyPress('Q')) m_vPosition.y -= m_fSpeed;
		vEye = m_vPosition;
		vLookAt = m_vPosition + front;
	}

	if (m_eMode == CAMERA_FOLLOW_HOLD)
	{
		if (m_pTargetPos && m_pTargetRot)
		{
			m_vRotation += m_fSmooth * (*m_pTargetRot - m_vRotation);

			vLookAt = *m_pTargetPos + m_vTargetOffset;
			D3DXVec3TransformCoord(&vEye, &vEye, &matR);
			D3DXVec3TransformCoord(&vCamOffset, &vCamOffset, &matR);
			vEye = *m_pTargetPos + vCamOffset + m_vTargetOffset + vEye;
		}
	}

	if (m_eMode == CAMERA_FOLLOW_FREE)
	{
		if (m_pTargetPos)
		{
			m_vRotation.x -= D3DXToRadian(MOUSE_POS.y - m_ptPrevMouse.y) * 0.5;
			m_vRotation.y += D3DXToRadian(MOUSE_POS.x - m_ptPrevMouse.x) * 0.5;
			if (m_vRotation.x > D3DX_PI * 0.49f) m_vRotation.x = D3DX_PI * 0.49f;
			if (m_vRotation.x < D3DX_PI * -0.49f) m_vRotation.x = D3DX_PI * -0.49f;
			m_ptPrevMouse = MOUSE_POS;

			m_fDistance -= MOUSE_WHEEL * 0.005;

			vLookAt = *m_pTargetPos + m_vTargetOffset;
			vCamOffset.z += m_fDistance;
			vCamOffset.y = 0;
			D3DXVec3TransformCoord(&vEye, &(vEye + vCamOffset), &matR);
			vEye = *m_pTargetPos + m_vTargetOffset + vEye;
		}
	}

	D3DXMatrixLookAtLH(&matView, &vEye, &vLookAt, &m_vUp);
	DEVICE->SetTransform(D3DTS_VIEW, &matView);

	UpdateFrustum();
}

void CameraManager::SetTarget(D3DXVECTOR3 * targetPos, D3DXVECTOR3 * targetRot)
{
	m_pTargetPos = targetPos;
	m_pTargetRot = targetRot;
}

void CameraManager::SetFog(bool enable, float start, float end, DWORD color, float density)
{
	DEVICE->SetRenderState(D3DRS_FOGENABLE, enable);
	if (enable)
	{
		DEVICE->SetRenderState(D3DRS_FOGCOLOR, color);
		DEVICE->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
		DEVICE->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
		DEVICE->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&start));
		DEVICE->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&end));
		DEVICE->SetRenderState(D3DRS_FOGDENSITY, density);
	}
}

bool CameraManager::IsFrustum(ST_SPHERE sphere)
{
	for (D3DXPLANE p : m_vecPlane)
		if (D3DXPlaneDotCoord(&p, &sphere.center) > sphere.radius)
			return false;
	return true;
}
