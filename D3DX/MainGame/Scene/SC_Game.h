#pragma once

class SC_Game : public Scene
{
public:
	SC_Game();
	~SC_Game();

	virtual void Release();
	virtual void Init();
	virtual void Update();
	virtual void Render();
};

