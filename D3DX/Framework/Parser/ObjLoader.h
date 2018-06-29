#pragma once

struct ST_MATERIAL
{
	D3DMATERIAL9 m;
	LPDIRECT3DTEXTURE9 t;
};

struct ST_OBJECT
{
	LPD3DXMESH mesh;
	vector<ST_MATERIAL> mat;
	ST_SIZEBOX size;
	bool alpha;
};

class ObjLoader
{
private:
	map<string, ST_MATERIAL> m_mMat;

public:
	ObjLoader();
	~ObjLoader();

	ST_OBJECT* Load(string path, string fileName);
	map<string, ST_MATERIAL> LoadMtlLib(string path, string fileName);
	int GetMaterialIndex(string matName);
};

