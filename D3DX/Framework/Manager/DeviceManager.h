#pragma once

#define DEVICEMANAGER DeviceManager::GetInstance()
#define DEVICE DeviceManager::GetInstance()->GetDevice()

class DeviceManager
{
	SINGLETONE(DeviceManager)

private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;

public:
	LPDIRECT3DDEVICE9 GetDevice();
	void Destroy();
};

