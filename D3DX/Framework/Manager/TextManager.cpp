#include "../../stdafx.h"
#include "TextManager.h"

void TextManager::Add(string text, float x, float y, int size, string fontName, DWORD color, bool center, const RECT * rc)
{
	TextInfo info = TextInfo();
	RECT _rc = { x, y, x + size * text.length(), y + size };
	info.text = text;
	if (rc == NULL) info.rect = _rc;
	else info.rect = *rc;
	info.color = color;
	info.size = size;
	info.font = fontName;
	info.center = center;

	m_vecText.push_back(info);
}

FONT TextManager::GetFont(FONTTYPE type, float x, float y)
{
	FONT font;
	D3DXFONT_DESC desc;
	ZeroMemory(&desc, sizeof(D3DXFONT_DESC));

	D3DXCreateFontIndirect(DEVICE, &desc, &font.font);
	return font;
}

void TextManager::Render()
{
	D3DXFONT_DESC des;
	for (int i = 0; i < m_vecText.size(); i++)
	{
		m_pFont->GetDesc(&des);

		if (des.Height != m_vecText[i].size || m_vecText[i].font.compare(des.FaceName))
		{
			SAFE_RELEASE(m_pFont);
			D3DXCreateFont(
				DEVICE,
				m_vecText[i].size,
				0,
				FW_NORMAL,
				1,
				FALSE,
				HANGUL_CHARSET,
				OUT_DEFAULT_PRECIS, // ���� ũ��� ������� ���
				ANTIALIASED_QUALITY,
				FF_DONTCARE,
				m_vecText[i].font.c_str(),
				&m_pFont);
		}

		if (!m_vecText[i].center)
			m_pFont->DrawText(NULL, m_vecText[i].text.c_str(), -1,
				&m_vecText[i].rect, NULL | DT_NOCLIP, m_vecText[i].color);
		else
			m_pFont->DrawText(NULL, m_vecText[i].text.c_str(), -1,
				&m_vecText[i].rect, DT_CENTER | DT_NOCLIP, m_vecText[i].color);
	}

	m_vecText.clear();
}

void TextManager::Release()
{
	SAFE_RELEASE(m_pFont);
}

TextManager::TextManager()
{
	D3DXCreateFont(
		DEVICE,
		16,
		0,
		FW_NORMAL,
		1,
		FALSE,
		HANGUL_CHARSET,
		OUT_DEFAULT_PRECIS, // ���� ũ��� ������� ���
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		"����",
		&m_pFont);
}

TextManager::~TextManager()
{
}