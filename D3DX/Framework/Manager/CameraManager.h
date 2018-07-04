#pragma once

enum CAMERAMODE
{
	CAMERA_FREE,
	CAMERA_FOLLOW_HOLD,
	CAMERA_FOLLOW_FREE
};

class CameraManager
{
	SINGLETONE(CameraManager);

private:
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vRotation, Rotation);
	SYNTHESIZE(D3DXVECTOR3, m_vCamOffset, CamOffset);
	SYNTHESIZE(D3DXVECTOR3, m_vTargetOffset, TargetOffset);

private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3		m_vLookAt;

	D3DXVECTOR3*	m_pTargetPos;
	D3DXVECTOR3*	m_pTargetRot;


	CAMERAMODE		m_eMode;

	POINT			m_ptPrevMouse;
	float			m_fSpeed;
	float			m_fSmooth;

public:
	void Setup();
	void Update();
	void SetTarget(D3DXVECTOR3* targetPos, D3DXVECTOR3* targetRot);
	void SetMode(CAMERAMODE cm) { m_eMode = cm; }
	void SetFog(bool enable, float start, float end, DWORD color);
};

#define CAMERA CameraManager::GetInstance()
