#include "../stdafx.h"
#include "Map.h"



Map::Map()
{
}


Map::~Map()
{
	for (int i = 0; i < m_vecModel.size(); i++)
		SAFE_DELETE(m_vecModel[i]);
	SAFE_RELEASE(m_pTerrainMesh);
}

void Map::Setup()
{
	for (int z = 0; z < MAPSIZE; z++)
	{
		for (int x = 0; x < MAPSIZE; x++)
		{
			ST_PNT_VERTEX vertex;
			vertex.n = D3DXVECTOR3(0, 1, 0);
			vertex.p = D3DXVECTOR3(x - MAPSIZE / 2.0f, 0, -z + MAPSIZE / 2.0f);
			vertex.t = D3DXVECTOR2(z / 256.0f, x / 256.0f);
			m_vecTerrain.push_back(vertex);
		}
	}

	for (int z = 0; z < MAPSIZE - 1; z++)
	{
		for (int x = 0; x < MAPSIZE - 1; x++)
		{
			int index = MAPSIZE * (z + 1) + x;
			m_vecIndex.push_back(index);
			index = MAPSIZE * z + x;
			m_vecIndex.push_back(index);
			index = MAPSIZE * z + x + 1;
			m_vecIndex.push_back(index);

			index = MAPSIZE * (z + 1) + x;
			m_vecIndex.push_back(index);
			index = MAPSIZE * z + x + 1;
			m_vecIndex.push_back(index);
			index = MAPSIZE * (z + 1) + x + 1;
			m_vecIndex.push_back(index);
		}
	}

	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Ambient = D3DXCOLOR(0.2, 0.2, 0.2, 1);
	m_mtl.Diffuse = D3DXCOLOR(0.8, 0.8, 0.8, 1);

	D3DXMatrixIdentity(&m_matWorld);

	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void Map::Load(string mapPath)
{
	FILE* fp;
	fopen_s(&fp, mapPath.c_str(), "r");

	if (fp)
		Setup();

	char line[256];
	while (true)
	{
		fgets(line, 256, fp);
		if (feof(fp)) break;

		char * context;
		char * tok = strtok_s(line, "\t", &context);
		if (tok[0] == 'o')
		{
			tok = strtok_s(NULL, "\t", &context);
			string key = string(tok);
			string folder = Util::GetFileFolder((char*)string(tok).c_str());
			string file = Util::GetFileName((char*)string(tok).c_str());
			MODELMANAGER->AddModel(key, folder, file, MODELTYPE_OBJ);
			tok = strtok_s(NULL, "\t", &context);
			D3DXVECTOR3 p, r, s;
			int b;
			sscanf_s(tok, "%f %f %f %f %f %f %f %f %f %d",
				&p.x, &p.y, &p.z, &r.x, &r.y, &r.z, &s.x, &s.y, &s.z, &b);

			Model * model = MODELMANAGER->GetModel(key, MODELTYPE_OBJ);
			model->SetKeyName(key);
			model->SetPosition(p);
			model->SetRotation(r);
			model->SetScale(s);
			model->SetBlend(b);
			model->World();
			m_vecModel.push_back(model);
		}

		if (tok[0] == 't')
		{
			tok = strtok_s(NULL, "\t\n", &context);
			string name = string(tok);
			TEXTUREMANAGER->AddTexture(name.c_str(), name.c_str());
			m_pTexture = TEXTUREMANAGER->GetTexture(name.c_str());
		}

		if (tok[0] == 'c')
		{
			tok = strtok_s(NULL, "\t", &context);
			D3DXVECTOR3 v0, v1, v2;
			sscanf_s(tok, "%f %f %f %f %f %f %f %f %f",
				&v0.x, &v0.y, &v0.z, &v1.x, &v1.y, &v1.z, &v2.x, &v2.y, &v2.z);
			m_vecSurface.push_back(v0);
			m_vecSurface.push_back(v1);
			m_vecSurface.push_back(v2);
		}

		if (tok[0] == 's')
		{
			if (tok[1] == 'P')
			{
				tok = strtok_s(NULL, "\t", &context);
				sscanf_s(tok, "%f %f %f", &m_vSpawnPlayer.x, &m_vSpawnPlayer.y, &m_vSpawnPlayer.z);
			}
			if (tok[1] == 'B')
			{
				tok = strtok_s(NULL, "\t", &context);
				sscanf_s(tok, "%f %f %f", &m_vSpawnBoss.x, &m_vSpawnBoss.y, &m_vSpawnBoss.z);
			}
			if (tok[1] == 'E')
			{
				D3DXVECTOR3 vE;
				tok = strtok_s(NULL, "\t", &context);
				sscanf_s(tok, "%f %f %f", &vE.x, &vE.y, &vE.z);
				m_vecSpawnEnemy.push_back(vE);
			}
		}
	}

	fclose(fp);

	LPDIRECT3DTEXTURE9 heightMap;
	string bmp = mapPath;
	bmp[bmp.size() - 3] = 'b';
	bmp[bmp.size() - 2] = 'm';
	bmp[bmp.size() - 1] = 'p';
	D3DXCreateTextureFromFile(DEVICE, bmp.c_str(), &heightMap);

	D3DLOCKED_RECT lrc;
	heightMap->LockRect(0, &lrc, NULL, 0);
	DWORD* pColorSrc = (DWORD*)lrc.pBits;
	heightMap->UnlockRect(0);

	for (int z = 0; z < MAPSIZE; z++)
	{
		for (int x = 0; x < MAPSIZE; x++)
		{
			int index = z * MAPSIZE + x;
			D3DXCOLOR color = pColorSrc[index];
			float gray = (color.r + color.g + color.b) / 3.0f;
			m_vecTerrain[index].p.y = gray * 255;
		}
	}

	heightMap->Release();

	for (int z = 1; z < MAPSIZE - 1; z++)
	{
		for (int x = 1; x < MAPSIZE - 1; x++)
		{
			D3DXVECTOR3 vL = m_vecTerrain[z * MAPSIZE + x - 1].p;
			D3DXVECTOR3 vR = m_vecTerrain[z * MAPSIZE + x + 1].p;
			D3DXVECTOR3 vD = m_vecTerrain[(z + 1) * MAPSIZE + x].p;
			D3DXVECTOR3 vU = m_vecTerrain[(z - 1) * MAPSIZE + x].p;

			D3DXVECTOR3 vLR = vR - vL;
			D3DXVECTOR3 vDU = vU - vD;
			D3DXVECTOR3 vN;
			D3DXVec3Cross(&vN, &vDU, &vLR);
			D3DXVec3Normalize(&vN, &vN);
			m_vecTerrain[z * MAPSIZE + x].n = vN;
		}
	}

	D3DXCreateMeshFVF(m_vecIndex.size() / 3, m_vecTerrain.size(),
		D3DXMESH_32BIT | D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF, DEVICE, &m_pTerrainMesh);

	ST_PNT_VERTEX * vtx = NULL;
	m_pTerrainMesh->LockVertexBuffer(0, (void**)&vtx);
	memcpy(vtx, &m_vecTerrain[0], sizeof(ST_PNT_VERTEX) * m_vecTerrain.size());
	m_pTerrainMesh->UnlockVertexBuffer();

	DWORD * idx = NULL;
	m_pTerrainMesh->LockIndexBuffer(0, (void**)&idx);
	memcpy(idx, &m_vecIndex[0], sizeof(DWORD) * m_vecIndex.size());
	m_pTerrainMesh->UnlockIndexBuffer();

	DWORD * att = NULL;
	m_pTerrainMesh->LockAttributeBuffer(0, &att);
	ZeroMemory(att, sizeof(DWORD) * m_vecIndex.size() / 3);
	m_pTerrainMesh->UnlockAttributeBuffer();

	vector<DWORD> adjBuffer(m_vecIndex.size());
	m_pTerrainMesh->GenerateAdjacency(0.0f, &adjBuffer[0]);
	m_pTerrainMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&adjBuffer[0],
		NULL, NULL, NULL);
}

void Map::Render()
{
	Debug();

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->SetTransform(D3DTS_WORLD, &m_matWorld);
	DEVICE->SetTexture(0, m_pTexture);
	DEVICE->SetMaterial(&m_mtl);
	m_pTerrainMesh->DrawSubset(0);

	for (int i = 0; i < m_vecModel.size(); i++)
		m_vecModel[i]->Render();
}

void Map::Debug()
{
	if (!g_isDebug) return;

	vector<ST_PC_VERTEX> vecVertex;
	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(65, 178, 244);
	for (int i = 0; i < m_vecSurface.size(); i++)
	{
		v.p = m_vecSurface[i];
		v.p.y += 0.1;
		vecVertex.push_back(v);
	}

	if (vecVertex.empty()) return;

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetTexture(0, NULL);
	DEVICE->SetFVF(ST_PC_VERTEX::FVF);
	DEVICE->SetTransform(D3DTS_WORLD, &m_matWorld);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, vecVertex.size() / 3, &vecVertex[0], sizeof(ST_PC_VERTEX));
}

float Map::GetHeight(D3DXVECTOR3 rayPos)
{
	for (int i = 0; i < m_vecSurface.size(); i += 3)
	{
		D3DXVECTOR3 v0 = m_vecSurface[i];
		D3DXVECTOR3 v1 = m_vecSurface[i + 1];
		D3DXVECTOR3 v2 = m_vecSurface[i + 2];

		float dist;
		if (D3DXIntersectTri(&v0, &v1, &v2, &rayPos, &D3DXVECTOR3(0, -1, 0), NULL, NULL, &dist))
		{
			return rayPos.y - dist;
		}
	}
	return -1;
}
