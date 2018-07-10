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
	};

	vector<LPD3DXFONT>	m_vecFont;
	vector<TextInfo>	m_vecText;
	vector<string>		m_vecRegFont;

	LPD3DXFONT GetFont(string fontName, int size);

public:
	void Add(string text, float x, float y, int size, string fontName = "", 
		DWORD color = 0xFF000000);
	void RegisterFont(string path);
	void Render();
	void Release();
};

#define TEXT TextManager::GetInstance()