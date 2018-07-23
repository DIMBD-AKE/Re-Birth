#pragma once

enum UITEXTURE
{
	UITEX_NORMAL,
	UITEX_OVER,
	UITEX_DOWN,
	UITEX_END
};

enum UIANCHOR
{
	UIAC_LT,
	UIAC_LB,
	UIAC_RT,
	UIAC_RB,
	UIAC_C
};

class UIObject;

class IUIFunction
{
public:
	virtual void OnClick(UIObject * pSender) {}
	virtual void OnOver(UIObject * pSender) {}
	virtual void OnExit(UIObject * pSender) {}
	virtual void OnEntrance(UIObject * pSender) {}
};

class UIObject
{
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vScale, Scale);
	SYNTHESIZE(string, m_sName, Name);
	SYNTHESIZE(int, m_nAlpha, Alpha);
	SYNTHESIZE(D3DXVECTOR3, m_vColor, Color);

protected:
	vector<UIObject*>		m_vecChild;
	LPDIRECT3DTEXTURE9		m_pTex[UITEX_END];
	POINT					m_ptTexWH[UITEX_END];
	UIObject *				m_pParent;
	D3DXMATRIX				m_matWorld;
	IUIFunction *			m_pFunction;
	UIANCHOR				m_eAnchor;
	bool					m_isOver;

	void FindAllChild(vector<UIObject*>& vecChild);

public:
	UIObject();
	~UIObject();

	void Update();
	void Render();

	void AddChild(UIObject * pChild);
	void SetTexture(LPDIRECT3DTEXTURE9 normal, LPDIRECT3DTEXTURE9 over = NULL, LPDIRECT3DTEXTURE9 down = NULL);
	void SetFunction(IUIFunction * function);
	void SetAnchor(UIANCHOR anchor) { m_eAnchor = anchor; }
	UIObject * Find(string name);
	void Release();
};

