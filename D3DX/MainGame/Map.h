#pragma once
#define MAPSIZE 256

class Map
{
private:
	GET(vector<Model*>, m_vecModel, Model);
	GET(D3DXVECTOR3, m_vSpawnPlayer, SpawnPlayer);
	GET(D3DXVECTOR3, m_vSpawnBoss, SpawnBoss);
	GET(vector<D3DXVECTOR3>, m_vecSpawnEnemy, SpawnEnemy);

	vector<ST_PNT_VERTEX>	m_vecTerrain;
	vector<DWORD>			m_vecIndex;
	LPD3DXMESH				m_pTerrainMesh;

	LPD3DXMESH				m_pSkyboxMesh;
	LPDIRECT3DTEXTURE9		m_pSkyboxTex;

	vector<D3DXVECTOR3>		m_vecSurface;
	LPDIRECT3DTEXTURE9		m_pTexture;
	D3DMATERIAL9			m_mtl;

	D3DXMATRIX				m_matWorld;
	D3DXMATRIX				m_matSkybox;

	void Setup();
	void Debug();
public:
	Map();
	~Map();

	void Load(string mapPath);
	void Render();


	float GetHeight(D3DXVECTOR3 rayPos);
};
