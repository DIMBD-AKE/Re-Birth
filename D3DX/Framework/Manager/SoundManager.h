#pragma once
#include "../FMOD/inc/fmod.hpp"
#pragma comment(lib, "Framework/FMOD/lib/fmod_vc.lib")

using namespace FMOD;

// 총 사운드 버퍼
#define MAXCHANNEL 100

class SoundManager
{
private:
	static SoundManager* instance;

	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;

	System* m_system;     // fmod의 시스템 클래스
	Sound** m_sound;      // fmod의 사운드 클래스
	Channel** m_channel;  // fmod의 채널 클래스
	ChannelGroup* m_channelGroup;

	arrSounds m_totalSounds;

public:
	SoundManager();
	~SoundManager();

	static SoundManager* GetInstance();
	static void DeleteInstance();

	void Release();
	void Update();

	// 사운드 추가(키값, 파일이름, loop)
	void AddSound(string keyName, string soundName, bool loop = false);

	// 사운드 플레이(키값, 볼륨) 0.0f ~ 1.0f
	void Play(string keyName, float volume = 1.0f);
	// 사운드 정지
	void Stop(string keyName);
	// 사운드 일시 정지
	void Pause(string keyName);
	// 사운드 다시 재생
	void Resume(string keyName);

	// 플레이 중이냐?
	bool IsPlaySound(string keyName);
	// 일시정지 중이냐?
	bool IsPauseSound(string keyName);
};

#define SOUND SoundManager::GetInstance()