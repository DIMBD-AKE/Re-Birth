#pragma once
class LoadingSC : public Scene
{
private:
	UIObject*		LoadingImg;		//로딩 이미지
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

