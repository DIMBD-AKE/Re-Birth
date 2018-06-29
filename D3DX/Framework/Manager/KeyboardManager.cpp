#include "../../stdafx.h"
#include "KeyboardManager.h"

KeyboardManager* KeyboardManager::instance = NULL;

KeyboardManager::KeyboardManager()
{
	ZeroMemory(KeyState, sizeof(KeyState));
	ZeroMemory(KeyOldState, sizeof(KeyOldState));
	ZeroMemory(KeyMap, sizeof(KeyMap));
}

KeyboardManager::~KeyboardManager()
{
}

KeyboardManager * KeyboardManager::GetInstance()
{
	if(instance == NULL)
		instance = new KeyboardManager;

	return instance;
}

void KeyboardManager::DeleteInstance()
{
	if (instance != NULL)
		delete instance;
}

void KeyboardManager::Update()
{
	memcpy(KeyOldState, KeyState, sizeof(KeyOldState));

	ZeroMemory(KeyState, sizeof(KeyState));
	ZeroMemory(KeyMap, sizeof(KeyMap));

	GetKeyboardState(KeyState);

	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{
		// ASCII 7바이트 00000000 00000000
		//            키보드 A <- ->
		// ASCII 면 false 아니면 true
		byte key = KeyState[i] & 0x80;

		KeyState[i] = key ? 1 : 0;

		int oldState = KeyOldState[i];
		int state = KeyState[i];

		if (oldState == 0 && state == 1)
			KeyMap[i] = KEY_INPUT_STATUS_DOWN;
		else if (oldState == 1 && state == 0)
			KeyMap[i] = KEY_INPUT_STATUS_UP;
		else if (oldState == 1 && state == 1)
			KeyMap[i] = KEY_INPUT_STATUS_PRESS;
		else
			KeyMap[i] = KEY_INPUT_STATUS_NONE;
	}
}
