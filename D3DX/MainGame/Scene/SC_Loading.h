#pragma once

class Loading;

class SC_Loading : public Scene
{
private:

	Loading* m_pLoading;

private:
	//SINGLETONE
	void SingletoneInit();
	void AddModel();
	void AddTexture();

public:
	SC_Loading();
	~SC_Loading();

	void Release();
	void Init();
	void Update();
	void Render();

	
};

