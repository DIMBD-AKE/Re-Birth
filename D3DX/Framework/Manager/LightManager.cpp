#include "../../stdafx.h"
#include "LightManager.h"


LightManager::LightManager()
{
	m_nLightIndex = 0;
}


LightManager::~LightManager()
{
	m_mLight.clear();
}

void LightManager::AddLight(void * object, D3DLIGHT9 light, int index, LPDIRECT3DDEVICE9 device)
{
	LightList ll;
	LightData ld;

	auto objIter = m_mLight.find(object);
	if (objIter != m_mLight.end())
		ll = objIter->second;

	auto listIter = ll.find(index);
	if (listIter == ll.end())
	{
		ld.light = light;
		ld.index = m_nLightIndex++;
		ll.insert(make_pair(index, ld));
		device->LightEnable(ll[index].index, true);
	}
	else
	{
		ld = listIter->second;
		ld.light = light;
		ll.insert(make_pair(index, ld));
	}

	m_mLight[object] = ll;

	device->SetLight(ll[index].index, &light);
}

void LightManager::EnableLight(void * object, int index, bool enable, LPDIRECT3DDEVICE9 device)
{
	auto objIter = m_mLight.find(object);
	if (objIter == m_mLight.end()) return;

	auto listIter = objIter->second.find(index);
	if (listIter == objIter->second.end()) return;

	device->LightEnable(m_mLight[object][index].index, enable);
}

void LightManager::DeleteLight(void * object, LPDIRECT3DDEVICE9 device)
{
	auto objIter = m_mLight.find(object);
	if (objIter == m_mLight.end()) return;

	auto listIter = objIter->second.begin();
	for (; listIter != objIter->second.end(); listIter++)
		device->LightEnable(listIter->second.index, false);

	objIter->second.clear();
	m_mLight.erase(object);
}
