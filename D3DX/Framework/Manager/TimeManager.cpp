#include "../../stdafx.h"
#include "TimeManager.h"



TimeManager::TimeManager()
	: m_fElapsedTime(0)
{
	m_dwLastUpdateTime = GetTickCount();
}


TimeManager::~TimeManager()
{
}

void TimeManager::Update()
{
	DWORD dwCurrentTime = GetTickCount();
	m_fElapsedTime = (dwCurrentTime - m_dwLastUpdateTime) / 1000.0f;
	m_dwLastUpdateTime = dwCurrentTime;
}

float TimeManager::GetElapsedTime()
{
	return m_fElapsedTime;
}

float TimeManager::GetLastUpdateTime()
{
	return m_dwLastUpdateTime / 1000.0f;
}
