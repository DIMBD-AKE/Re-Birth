#pragma once

enum MainState
{
	MS_TITLE,
	MS_PORTRAIT,
	MS_OPTION,
	MS_RANKING
};

class SC_Main : public Scene, public IUIFunction
{
private:
	UIObject *	m_pUI;
	UIObject *	m_pPortrait;
	UIObject *	m_pSelect;
	UIObject *	m_pChrOver;
	UIObject *	m_pStart;

	MainState	m_eState;

	bool		m_isPortrait;
	string		m_sSelect;
	float		m_fElapse;

	Dialogue*	m_pContext;
	Model *		m_pModel;

	D3DXVECTOR3	m_vPos;

public:
	SC_Main();
	virtual ~SC_Main();

	virtual void OnClick(UIObject * pSender);
	virtual void OnOver(UIObject * pSender);
	virtual void OnExit(UIObject * pSender);

	virtual void Release();
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void MakeModel();
	int GetIndex();
};

