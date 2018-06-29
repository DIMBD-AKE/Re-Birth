#pragma once

class Map;

class SC_Test : public Scene
{
private:
	Model *		m_pTestModel;
	Map *		m_pSampleMap;

public:
	SC_Test();
	~SC_Test();

	void Release();
	void Init();
	void Update();
	void Render();
};

