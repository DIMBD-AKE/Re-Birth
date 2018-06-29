#pragma once

class LightManager
{
	SINGLETONE(LightManager)

	struct LightData
	{
		D3DLIGHT9 light;
		int index;
	};

	typedef map<int, LightData> LightList;

private:
	map<void*, LightList>	m_mLight;
	int						m_nLightIndex;

public:
	void AddLight(void * object, D3DLIGHT9 light, int index, LPDIRECT3DDEVICE9 device = DEVICE);
	void EnableLight(void * object, int index, bool enable, LPDIRECT3DDEVICE9 device = DEVICE);
	void DeleteLight(void * object, LPDIRECT3DDEVICE9 device = DEVICE);
};

#define LIGHTMANAGER LightManager::GetInstance()