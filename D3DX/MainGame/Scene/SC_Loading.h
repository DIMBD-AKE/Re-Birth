#pragma once

class Loading;

class SC_Loading : public Scene
{
private:

	Loading* m_pLoading;
	UIObject * m_pUI;

private:
	//SINGLETONE
	void SingletoneInit();
	void AddModel();
	void AddTexture();
	void AddSound();

	void InitUI();

public:
	SC_Loading();
	~SC_Loading();

	void Release();
	void Init();
	void Update();
	void Render();

	
};

