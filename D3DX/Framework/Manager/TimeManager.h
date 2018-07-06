#pragma once
class TimeManager
{
	SINGLETONE(TimeManager);

private:
	DWORD	m_dwLastUpdateTime;
	float	m_fElapsedTime;

public:
	void Update();
	float GetElapsedTime();
	float GetLastUpdateTime();
	DWORD GetFPS();
};

#define TIME TimeManager::GetInstance()