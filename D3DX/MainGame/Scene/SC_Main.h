#pragma once

class SC_Main : public Scene, public IUIFunction
{
private:
	UIObject * m_pUI;

public:
	SC_Main();
	~SC_Main();

	virtual void OnClick(UIObject * pSender);

	virtual void Release();
	virtual void Init();
	virtual void Update();
	virtual void Render();
};

