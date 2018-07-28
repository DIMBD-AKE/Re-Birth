#pragma once

enum CAMERAMODE
{
	CAMERA_FREE,
	CAMERA_FOLLOW_HOLD,
	CAMERA_FOLLOW_FREE
};

enum CAMERAACTION
{
	CAMERAA_NONE,
	CAMERAA_SHAKE,
	CAMERAA_CINEMATIC,
	CAMERAA_SHAKECINEMATIC
};

class CameraManager
{
	SINGLETONE(CameraManager);

private:
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vRotation, Rotation);
	SYNTHESIZE(D3DXVECTOR3, m_vCamOffset, CamOffset);
	SYNTHESIZE(D3DXVECTOR3, m_vTargetOffset, TargetOffset);

	vector<D3DXVECTOR3>		m_vecProjVertex;
	vector<D3DXVECTOR3>		m_vecWorldVertex;
	vector<D3DXPLANE>		m_vecPlane;

private:
	D3DXVECTOR3		m_vEye, m_vCalcEye;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3		m_vLookAt;

	D3DXVECTOR3*	m_pTargetPos;
	D3DXVECTOR3*	m_pTargetRot;

	float			m_fElapse;
	float			m_fShakePower;

	float			m_fActionTime;

	CAMERAMODE		m_eMode;
	CAMERAACTION	m_eAction;

	POINT			m_ptPrevMouse;
	float			m_fSpeed;
	float			m_fSmooth;
	float			m_fDistance;

	D3DXVECTOR2		m_vCinDir;
	D3DXVECTOR2		m_vCinRot;
	float			m_fCinZoom;
	float			m_fCinZoomSpeed;

	void UpdateFrustum();

public:
	void Setup();
	void Update();
	void SetTarget(D3DXVECTOR3* targetPos, D3DXVECTOR3* targetRot);
	void SetMode(CAMERAMODE cm) { m_eMode = cm; }
	void SetFog(bool enable, float start, float end, DWORD color, float density);
	bool IsFrustum(ST_SPHERE sphere);
	void Shake(float power, float time);
	void Cinematic(D3DXVECTOR2 startDir, D3DXVECTOR2 rotDir, float zoomStart, float zoomSpeed, float time);
	bool IsActionEnd() { return m_fActionTime <= m_fElapse; }
	D3DXVECTOR3 GetEye() { return m_vCalcEye; }
};

#define CAMERA CameraManager::GetInstance()
