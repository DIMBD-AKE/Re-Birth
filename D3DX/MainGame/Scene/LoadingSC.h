#pragma once

class Loading;

class LoadingSC : public Scene
{
private:

	Loading* m_pLoading;

private:
	//SINGLETONE
	void SingletoneInit();
	void AddModel();
	void AddTexture();

public:
	LoadingSC();
	~LoadingSC();

	void Release();
	void Init();
	void Update();
	void Render();

	
};

