#pragma once
struct ST_TEXTUREINFO
{
	LPDIRECT3DTEXTURE9	texture;
	D3DXIMAGE_INFO		info;
};

class TextureManager
{
	SINGLETONE(TextureManager)

private:
	map<string, ST_TEXTUREINFO>	m_mTexture;

public:
	LPDIRECT3DTEXTURE9 AddTexture(string keyName, string path);
	LPDIRECT3DTEXTURE9 GetTexture(string keyName);
	D3DXIMAGE_INFO GetInfo(string keyName);

	void Release();
};

#define TEXTUREMANAGER TextureManager::GetInstance()