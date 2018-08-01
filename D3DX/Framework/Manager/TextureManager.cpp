#include "../../stdafx.h"
#include "TextureManager.h"



TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

LPDIRECT3DTEXTURE9 TextureManager::AddTexture(string keyName, string path)
{
	if (m_mTexture.find(keyName) != m_mTexture.end())
		return m_mTexture.find(keyName)->second.texture;

	ST_TEXTUREINFO info;
	HRESULT hr;
	hr = D3DXCreateTextureFromFileEx(
		DEVICE,
		path.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_FROM_FILE,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		0,
		&info.info,
		0,
		&info.texture);

	assert(SUCCEEDED(hr));

	m_mTexture.insert(make_pair(keyName, info));

	return info.texture;
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(string keyName)
{
	if (m_mTexture.find(keyName) != m_mTexture.end())
		return m_mTexture.find(keyName)->second.texture;
	else
		return NULL;
}

D3DXIMAGE_INFO TextureManager::GetInfo(string keyName)
{
	if (m_mTexture.find(keyName) != m_mTexture.end())
		return m_mTexture.find(keyName)->second.info;
	else
		return D3DXIMAGE_INFO();	
}

void TextureManager::Release()
{
	auto iter = m_mTexture.begin();
	for (; iter != m_mTexture.end(); iter++)
		SAFE_RELEASE(iter->second.texture);

	m_mTexture.clear();
}
