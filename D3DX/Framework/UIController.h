#pragma once

enum UITEXTURE
{
	UITEX_NORMAL,
	UITEX_OVER,
	UITEX_DOWN,
	UITEX_END
};

class IUIFunction
{
public:
	virtual void OnClick() = 0;
	virtual void OnOver() = 0;
	virtual void OnExit() = 0;
};

class UIObject
{
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vScale, Scale);

protected:
	vector<UIObject*>		m_vecChild;
	LPDIRECT3DTEXTURE9		m_pTex[UITEX_END];
	POINT					m_ptTexWH[UITEX_END];
	UIObject *				m_pParent;
	D3DXMATRIX				m_matWorld;
	IUIFunction *			m_pFunction;
	bool					m_isOver;

public:
	UIObject();
	virtual ~UIObject();

	virtual void Update();
	virtual void Render();

	void AddChild(UIObject * pChild);
	void SetTexture(LPDIRECT3DTEXTURE9 normal, LPDIRECT3DTEXTURE9 over = NULL, LPDIRECT3DTEXTURE9 down = NULL);
	void SetFunction(IUIFunction * function);
	void Release();
};

