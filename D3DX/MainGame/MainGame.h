#pragma once

class MainGame
{
private:
	bool		m_isWire;

public:
	MainGame();
	~MainGame();

	void Setup();
	void Update();
	void Render();

	void SetLight();
};

