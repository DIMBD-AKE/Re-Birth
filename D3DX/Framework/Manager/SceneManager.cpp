#include "../../stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager()
	: m_pCurrentScene(NULL)
{
}


SceneManager::~SceneManager()
{
	auto iter = m_mScene.begin();
	for (; iter != m_mScene.end(); iter++)
		SAFE_DELETE(iter->second);
	m_mScene.clear();
}

void SceneManager::AddScene(string name, Scene * scene)
{
	auto find = m_mScene.find(name);
	if (find != m_mScene.end()) return;

	m_mScene.insert(make_pair(name, scene));
}

void SceneManager::ChangeScene(string name, bool init)
{
	if (m_pCurrentScene)
		m_pCurrentScene->Release();

	auto find = m_mScene.find(name);
	if (find != m_mScene.end())
		m_pCurrentScene = find->second;
	else
		m_pCurrentScene = NULL;

	if (init && m_pCurrentScene)
		m_pCurrentScene->Init();
}

void SceneManager::Update()
{
	if (m_pCurrentScene)
		m_pCurrentScene->Update();
}

void SceneManager::Render()
{
	if (m_pCurrentScene)
		m_pCurrentScene->Render();
}

void SceneManager::Destroy()
{
	auto iter = m_mScene.begin();
	for (; iter != m_mScene.end(); iter++)
	{
		SAFE_RELEASE(iter->second);
		SAFE_DELETE(iter->second);
	}

	m_mScene.clear();
}
