#include "../stdafx.h"
#include "Dialogue.h"

Dialogue::Dialogue()
{
	ZeroMemory(this, sizeof(Dialogue));
}


Dialogue::~Dialogue()
{
}

void Dialogue::Init(D3DXVECTOR2 pos, int size, string fontName, float interval, DWORD color)
{
	m_vPos = pos;
	m_nSize = size;
	m_sFont = string(fontName);
	m_fInterval = interval;
	m_nColor = color;
}

void Dialogue::SetKey(DWORD next, DWORD prev, DWORD rewrite)
{
	m_nNext = next;
	m_nPrev = prev;
	m_nReWrite = rewrite;
}

void Dialogue::SetIndex(int index)
{
	m_nIndex = index;
	m_nChar = 0;
	m_nLine = 0;
	m_vecCurrentText.clear();
}

void Dialogue::Update()
{
	m_fElapse += TIME->GetElapsedTime();

	if (INPUT->KeyDown(m_nPrev) && m_nIndex > 0)
	{
		m_nIndex--;
		m_nChar = 0;
		m_nLine = 0;
		m_vecCurrentText.clear();
	}

	if (INPUT->KeyDown(m_nNext) && m_nIndex < m_vecAllText.size() - 1)
	{
		m_nIndex++;
		m_nChar = 0;
		m_nLine = 0;
		m_vecCurrentText.clear();
	}

	if (INPUT->KeyDown(m_nReWrite))
	{
		m_nChar = 0;
		m_nLine = 0;
		m_vecCurrentText.clear();
	}

	if (m_vecCurrentText.empty())
		m_vecCurrentText.push_back("");

	if (m_fElapse > m_fPrevTime + m_fInterval)
	{
		m_fPrevTime = m_fElapse;

		int size = 0;
		for (int i = 0; i < m_vecCurrentText.size(); i++)
			size += m_vecCurrentText[i].size() + ((m_vecCurrentText.size() > 1) ? 1 : 0);

		if (size > 2)
			size -= 1;

		if (size < m_vecAllText[m_nIndex].size())
		{
			if (m_vecAllText[m_nIndex][m_nChar] == '\n')
			{
				m_vecCurrentText.push_back("");
				m_nLine++;
				m_nChar++;
			}
			if (m_vecAllText[m_nIndex][m_nChar] & 0x80)
				m_vecCurrentText[m_nLine] += m_vecAllText[m_nIndex][m_nChar++];
			m_vecCurrentText[m_nLine] += m_vecAllText[m_nIndex][m_nChar];
		}

		if (m_vecAllText[m_nIndex].size() - 1 > m_nChar)
			m_nChar++;
	}

	for (int i = 0; i < m_vecCurrentText.size(); i++)
		TEXT->Add(m_vecCurrentText[i], m_vPos.x, m_vPos.y + m_nSize * i, m_nSize, m_sFont, m_nColor);
}
