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
		wstring text;
		wstring font;
		RECT rect;
		DWORD color;
		int size;
		bool center;
	};

	LPD3DXFONT			m_pFont;
	vector<TextInfo>	m_vecText;

public:
	void Add(wstring text, float x, float y, int size, wstring fontName = L"굴림", 
		DWORD color = 0xFF000000, bool center = false, const RECT* rc = NULL);
	FONT GetFont(FONTTYPE type, float x, float y);
	void Render();
	void Release();
};

#define TEXT TextManager::GetInstance()