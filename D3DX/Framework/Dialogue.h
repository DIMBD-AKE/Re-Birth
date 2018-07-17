#pragma once
class Dialogue
{
private:
	vector<string>		m_vecAllText;
	vector<string>		m_vecCurrentText;

	D3DXVECTOR2			m_vPos;
	int					m_nSize;
	string				m_sFont;
	float				m_fInterval;
	DWORD				m_nColor;

	int					m_nIndex;
	int					m_nChar;
	int					m_nLine;

	DWORD				m_nNext;
	DWORD				m_nPrev;
	DWORD				m_nReWrite;

	float				m_fElapse;
	float				m_fPrevTime;

public:
	Dialogue();
	~Dialogue();

	void Init(D3DXVECTOR2 pos, int size, string fontName, float interval, DWORD color);
	void SetKey(DWORD next, DWORD prev, DWORD rewrite);
	void AddText(string text) { m_vecAllText.push_back(text); }
	void SetIndex(int index);
	void Update();
};

