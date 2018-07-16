#include "../../stdafx.h"
#include "SoundManager.h"

SoundManager* SoundManager::instance = NULL;

SoundManager::SoundManager()
{
	// 사운드 시스템 생성
	System_Create(&m_system);

	// 사운드 채널 수 생성
	m_system->init(MAXCHANNEL, FMOD_INIT_NORMAL, 0);

	// 사운드 채널 동적할당
	m_sound = new Sound*[MAXCHANNEL];
	m_channel = new Channel*[MAXCHANNEL];

	memset(m_sound, 0, sizeof(Sound*) * (MAXCHANNEL));
	memset(m_channel, 0, sizeof(Channel*) * (MAXCHANNEL));
}


SoundManager::~SoundManager()
{
}

SoundManager * SoundManager::GetInstance()
{
	if (instance == NULL)
		instance = new SoundManager();

	return instance;
}

void SoundManager::DeleteInstance()
{
	SAFE_DELETE(instance);
}

void SoundManager::Release()
{
	if (m_channel != nullptr || m_sound != nullptr)
	{
		for (int i = 0; i < MAXCHANNEL; i++)
		{
			if (m_channel != nullptr)
			{
				if (m_channel[i]) m_channel[i]->stop();
			}
			if (m_sound != nullptr)
			{
				if (m_sound[i]) m_sound[i]->release();
			}
		}
	}
	SAFE_DELETE(m_channel);
	SAFE_DELETE(m_sound);

	// 시스템 닫기
	if (m_system != nullptr)
	{
		m_system->release();
		m_system->close();
	}
}

void SoundManager::Update()
{
	m_system->update();
}

void SoundManager::AddSound(string keyName, string soundName, bool loop)
{
	assert(m_totalSounds.count(keyName) <= 0);

	HRESULT hr;
	if (loop)
	{
		hr = m_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, nullptr, &m_sound[m_totalSounds.size()]);
	}
	else
	{
		hr = m_system->createSound(soundName.c_str(), FMOD_DEFAULT, nullptr, &m_sound[m_totalSounds.size()]);
	}

	assert(hr == 0);

	m_totalSounds.insert(make_pair(keyName, &m_sound[m_totalSounds.size()]));
}

void SoundManager::Play(string keyName, float volume)
{
	int count = 0;
	arrSoundIter iter = m_totalSounds.begin();
	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			m_system->playSound(*iter->second, m_channelGroup, false, &m_channel[count]);
			m_channel[count]->setVolume(volume);
		}
	}
}

void SoundManager::Stop(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalSounds.begin();
	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			m_channel[count]->stop();
			break;
		}
	}
}

void SoundManager::Pause(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalSounds.begin();
	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			m_channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::Resume(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalSounds.begin();
	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			m_channel[count]->setPaused(false);
			break;
		}
	}
}

bool SoundManager::IsPlaySound(string keyName)
{
	int count = 0;
	bool isPlay;
	arrSoundIter iter = m_totalSounds.begin();
	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			m_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool SoundManager::IsPauseSound(string keyName)
{
	int count = 0;
	bool isPause;
	arrSoundIter iter = m_totalSounds.begin();
	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			m_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}
