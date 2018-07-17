#include "../../stdafx.h"
#include "TextManager.h"
#include <algorithm>

LPD3DXFONT TextManager::GetFont(string fontName, int size)
{
	for (int i = 0; i < m_vecFont.size(); i++)
	{
		D3DXFONT_DESC desc;
		m_vecFont[i]->GetDesc(&desc);
		if (fontName.compare(desc.FaceName) == 0 && size == desc.Height)
			return m_vecFont[i];
	}

	LPD3DXFONT font;
	D3DXCreateFont(
		DEVICE,
		size,
		0,
		FW_NORMAL,
		1,
		FALSE,
		HANGUL_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		fontName.c_str(),
		&font);
	m_vecFont.push_back(font);
	return font;
}

void TextManager::Add(string text, float x, float y, int size, string fontName, DWORD color)
{
	TextInfo info = TextInfo();
	RECT _rc = { x, y, 0, 0 };
	info.rect = _rc;
	info.text = text;
	info.color = color;
	info.size = size;
	if (fontName.length() == 0)
		info.font = "나눔스퀘어 Regular";
	else
		info.font = fontName;

	m_vecText.push_back(info);
}

void TextManager::RegisterFont(string path)
{
	int ret = AddFontResource(path.c_str());
	m_vecRegFont.push_back(path);
	assert(ret > 0 && "폰트 주소가 잘못되었습니다.");
}

void TextManager::Render()
{
	D3DXFONT_DESC des;
	for (int i = 0; i < m_vecText.size(); i++)
	{
		LPD3DXFONT font = GetFont(m_vecText[i].font, m_vecText[i].size);

		font->DrawText(NULL, m_vecText[i].text.c_str(), -1,
			&m_vecText[i].rect, DT_LEFT | DT_NOCLIP, m_vecText[i].color);
	}

	m_vecText.clear();
}

void TextManager::Release()
{
	for (auto font : m_vecFont)
		SAFE_RELEASE(font);
	m_vecFont.clear();
	for (auto path : m_vecRegFont)
		RemoveFontResource(path.c_str());
}

TextManager::TextManager()
{
	RegisterFont("Font/NanumSquareR.ttf");
	RegisterFont("Font/UhBee Yiseul.ttf");
	RegisterFont("Font/NanumMyeongjo.ttf");
}

TextManager::~TextManager()
{
}
