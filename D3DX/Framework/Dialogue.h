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

	bool				m_isKeyLock;

public:
	Dialogue();
	~Dialogue();

	void Init(D3DXVECTOR2 pos, int size, string fontName, float interval, DWORD color);
	void SetKey(DWORD next, DWORD prev, DWORD rewrite);
	void AddText(string text) { m_vecAllText.push_back(text); }
	void ChangeText(int index, string text) { m_vecAllText[index] = text; }
	void SetIndex(int index);
	void SetKeyLock(bool lock) { m_isKeyLock = lock; }
	bool CurrentEnd() { return m_vecAllText[m_nIndex].size() - 1 <= m_nChar; }
	int GetIndex() { return m_nIndex; }
	int GetPage() { return m_vecAllText.size(); }
	void Update();
};

