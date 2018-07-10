#pragma once
enum FONTTYPE
{
	FT_DEFAULT
};

struct FONT
{
	LPD3DXFONT font;
	RECT rc;
};

class TextManager
{
	SINGLETONE(TextManager);

private:
	struct TextInfo
	{
		FONTTYPE ft;
		string text;
		string font;
		RECT rect;
		DWORD color;
		int size;
		bool center;
	};

	LPD3DXFONT			m_pFont;
	vector<TextInfo>	m_vecText;
	vector<string>		m_vecRegFont;

	static bool SizeComparison(TextInfo i, TextInfo j) { return (i.size < j.size); }

public:
	void Add(string text, float x, float y, int size, string fontName = "나눔스퀘어 Regular", 
		DWORD color = 0xFF000000, bool center = false, const RECT* rc = NULL);
	FONT GetFont(FONTTYPE type, float x, float y);
	void RegisterFont(string path);
	void Render();
	void Release();
};

#define TEXT TextManager::GetInstance()