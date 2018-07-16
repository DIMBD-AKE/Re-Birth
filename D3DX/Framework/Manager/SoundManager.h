#pragma once
#include "../FMOD/inc/fmod.hpp"
#pragma comment(lib, "Framework/FMOD/lib/fmod_vc.lib")

using namespace FMOD;

// �� ���� ����
#define MAXCHANNEL 100

class SoundManager
{
private:
	static SoundManager* instance;

	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;

	System* m_system;     // fmod�� �ý��� Ŭ����
	Sound** m_sound;      // fmod�� ���� Ŭ����
	Channel** m_channel;  // fmod�� ä�� Ŭ����
	ChannelGroup* m_channelGroup;

	arrSounds m_totalSounds;

public:
	SoundManager();
	~SoundManager();

	static SoundManager* GetInstance();
	static void DeleteInstance();

	void Release();
	void Update();

	// ���� �߰�(Ű��, �����̸�, loop)
	void AddSound(string keyName, string soundName, bool loop = false);

	// ���� �÷���(Ű��, ����) 0.0f ~ 1.0f
	void Play(string keyName, float volume = 1.0f);
	// ���� ����
	void Stop(string keyName);
	// ���� �Ͻ� ����
	void Pause(string keyName);
	// ���� �ٽ� ���
	void Resume(string keyName);

	// �÷��� ���̳�?
	bool IsPlaySound(string keyName);
	// �Ͻ����� ���̳�?
	bool IsPauseSound(string keyName);
};

#define SOUND SoundManager::GetInstance()