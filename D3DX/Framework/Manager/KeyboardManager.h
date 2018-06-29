#pragma once

#define MAX_INPUT_KEY 255
#define MAX_INPUT_MOUSE 8

class KeyboardManager
{
private:
	KeyboardManager();
	~KeyboardManager();

	static KeyboardManager* instance;

	byte KeyState[MAX_INPUT_KEY];
	byte KeyOldState[MAX_INPUT_KEY];
	byte KeyMap[MAX_INPUT_KEY];

	enum
	{
		KEY_INPUT_STATUS_NONE,
		KEY_INPUT_STATUS_DOWN,
		KEY_INPUT_STATUS_UP,
		KEY_INPUT_STATUS_PRESS
	};

public:
	static KeyboardManager* GetInstance();
	static void DeleteInstance();

	void Update();

	bool KeyDown(DWORD key) 
	{
		return KeyMap[key] == KEY_INPUT_STATUS_DOWN;
	}

	bool KeyUp(DWORD key)
	{
		return KeyMap[key] == KEY_INPUT_STATUS_UP;
	}

	bool KeyPress(DWORD key)
	{
		return KeyMap[key] == KEY_INPUT_STATUS_PRESS;
	}
};

#define INPUT KeyboardManager::GetInstance()