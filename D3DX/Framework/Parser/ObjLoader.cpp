#include "../../stdafx.h"
#include "ObjLoader.h"


ObjLoader::ObjLoader()
{
}


ObjLoader::~ObjLoader()
{
}

ST_OBJECT* ObjLoader::Load(string path, string fileName)
{
	vector<D3DXVECTOR3>	vecV;
	vector<D3DXVECTOR2>	vecT;
	vector<D3DXVECTOR3>	vecVN;
	vector<ST_PNT_VERTEX> vecPNT;

	vector<DWORD> vecIndex;
	vector<DWORD> vecAttri;
	int mtlIndex;

	FILE* fp;
	fopen_s(&fp, (path + fileName).c_str(), "r");

	int partNum = 0;
	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
			continue;
		// 파츠 추가
		else if (szTemp[0] == 'u' || feof(fp))
		{
			char matName[128];
			sscanf_s(szTemp, "%*s %s", &matName, 128);
			mtlIndex = GetMaterialIndex(matName);
		}
		// 매티리얼 정보
		else if (szTemp[0] == 'm')
		{
			char * context;
			char * tok = strtok_s(szTemp, " ", &context);
			tok = strtok_s(NULL, " ", &context);
			string sName = string(tok) + " " + string(context);
			auto find = sName.find('\n');
			if (find != string::npos) sName = sName.erase(find);
			if (sName[0] == '.') sName = sName.substr(1, sName.size());
			if (sName[0] == '/') sName = sName.substr(1, sName.size());
			m_mMat = LoadMtlLib(path, sName);
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szTemp[1] == 't')
			{
				float u, v;
				sscanf_s(szTemp, "%*s %f %f", &u, &v);
				vecT.push_back(D3DXVECTOR2(u, v));
			}
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'f')
		{
			vector<ST_PNT_VERTEX> vPnt;
			char * context;
			char * split = strtok_s(szTemp, " ", &context);
			split = strtok_s(NULL, " ", &context);
			while (true)
			{
				if (!split || split[0] == '\n') break;
				ST_PNT_VERTEX pnt;
				pnt.t = D3DXVECTOR2(0, 0);
				char * sc;
				char * s = strtok_s(split, "/", &sc);
				int temp;
				if (s)
				{
					temp = atoi(s) - 1;
					if (temp < 0) temp = vecV.size() + temp + 1;
					pnt.p = vecV[temp];
					if (sc[0] == '/')
					{
						s = strtok_s(NULL, "/", &sc);
						temp = atoi(s) - 1;
						if (temp < 0) temp = vecVN.size() + temp + 1;
						pnt.n = vecVN[temp];
						continue;
					}
					else
						s = strtok_s(NULL, "/", &sc);
				}
				if (s)
				{
					temp = atoi(s) - 1;
					if (temp < 0) temp = vecT.size() + temp + 1;
					pnt.t = vecT[temp];
					s = strtok_s(NULL, "/", &sc);
				}
				if (s)
				{
					temp = atoi(s) - 1;
					if (temp < 0) temp = vecV.size() + temp + 1;
					pnt.n = vecVN[temp];
					s = strtok_s(NULL, "/", &sc);
				}
				vPnt.push_back(pnt);
				split = strtok_s(NULL, " ", &context);
			}
			vecPNT.push_back(vPnt[0]);
			vecAttri.push_back(mtlIndex);
			if (vPnt.size() >= 2)
				vecPNT.push_back(vPnt[1]);
			if (vPnt.size() >= 3)
				vecPNT.push_back(vPnt[2]);
			if (vPnt.size() == 4)
			{
				vecAttri.push_back(mtlIndex);
				vecPNT.push_back(vPnt[2]);
				vecPNT.push_back(vPnt[3]);
				vecPNT.push_back(vPnt[0]);
			}
		}
	}

	fclose(fp);

	ST_OBJECT * obj = new ST_OBJECT();

	for (int i = 0; i < vecPNT.size(); i++)
	{
		if (obj->size.lowX > vecPNT[i].p.x)
			obj->size.lowX = vecPNT[i].p.x;
		if (obj->size.highX < vecPNT[i].p.x)
			obj->size.highX = vecPNT[i].p.x;
		if (obj->size.lowY > vecPNT[i].p.y)
			obj->size.lowY = vecPNT[i].p.y;
		if (obj->size.highY < vecPNT[i].p.y)
			obj->size.highY = vecPNT[i].p.y;
		if (obj->size.lowZ > vecPNT[i].p.z)
			obj->size.lowZ = vecPNT[i].p.z;
		if (obj->size.highZ < vecPNT[i].p.z)
			obj->size.highZ = vecPNT[i].p.z;
	}

	DWORD face = vecPNT.size() / 3;
	DWORD vertex = vecPNT.size();
	D3DXCreateMeshFVF(face, vertex, D3DXMESH_32BIT | D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF, DEVICE, &obj->mesh);

	// 버텍스
	ST_PNT_VERTEX* vtx = NULL;
	obj->mesh->LockVertexBuffer(0, (LPVOID*)&vtx);
	memcpy(vtx, &vecPNT[0], sizeof(ST_PNT_VERTEX) * vecPNT.size());
	obj->mesh->UnlockVertexBuffer();

	// 인덱스
	DWORD* ind = NULL;
	obj->mesh->LockIndexBuffer(0, (void**)&ind);
	for (int i = 0; i < face; i++)
	{
		vecIndex.push_back(i * 3);
		vecIndex.push_back(i * 3 + 1);
		vecIndex.push_back(i * 3 + 2);
	}
	memcpy(ind, &vecIndex[0], sizeof(DWORD) * vecIndex.size());
	obj->mesh->UnlockIndexBuffer();

	// 서브셋
	DWORD* att = NULL;
	obj->mesh->LockAttributeBuffer(0, &att);
	memcpy(att, &vecAttri[0], sizeof(DWORD) * vecAttri.size());
	obj->mesh->UnlockAttributeBuffer();

	vector<DWORD> adjBuffer(obj->mesh->GetNumFaces() * 3);
	obj->mesh->GenerateAdjacency(0.0f, &adjBuffer[0]);
	obj->mesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&adjBuffer[0],
		0, 0, 0
	);

	auto iter = m_mMat.begin();
	for (; iter != m_mMat.end(); iter++)
	{
		obj->mat.push_back(iter->second);
		if (iter->second.a)
			obj->alpha = true;
	}

	return obj;
}

map<string, ST_MATERIAL> ObjLoader::LoadMtlLib(string path, string fileName)
{
	map<string, ST_MATERIAL> ret;

	FILE* fp;
	fopen_s(&fp, (path + fileName).c_str(), "r");
	if (!fp) return ret;

	D3DMATERIAL9 mat;
	ZeroMemory(&mat, sizeof(D3DMATERIAL9));

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		if (szTemp[0] != 'n') fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
			continue;
		else if (szTemp[0] == 'n')
		{
			char name[128];
			char mapT[128] = "";
			sscanf_s(szTemp, "%*s %s", name, 128);
			while (true)
			{				
				fgets(szTemp, 1024, fp);

				if (szTemp[0] == 'K')
				{
					if (szTemp[1] == 'a')
						sscanf_s(szTemp, "%*s %f %f %f", &mat.Ambient.r, &mat.Ambient.g, &mat.Ambient.b);
					if (szTemp[1] == 'd')
						sscanf_s(szTemp, "%*s %f %f %f", &mat.Diffuse.r, &mat.Diffuse.g, &mat.Diffuse.b);
					if (szTemp[1] == 's')
						sscanf_s(szTemp, "%*s %f %f %f", &mat.Specular.r, &mat.Specular.g, &mat.Specular.b);
				}
				if (szTemp[0] == 'm' && szTemp[5] == 'd')
					sscanf_s(szTemp, "%*s %s", &mapT, 128);

				if (szTemp[0] == 'n' || szTemp[0] == '\0' || feof(fp))
					break;
			}
			ST_MATERIAL m;
			m.m = mat;
			m.t = NULL;
			string t = path + mapT;
			if (strcmp(mapT, "") != 0)
				m.t = TEXTUREMANAGER->AddTexture(mapT, t);
			m.a = TEXTUREMANAGER->GetInfo(mapT).Format == D3DFMT_A8R8G8B8;
			ret.insert(make_pair(name, m));
			ZeroMemory(&mat, sizeof(D3DMATERIAL9));
		}
	}

	fclose(fp);

	return ret;
}

int ObjLoader::GetMaterialIndex(string matName)
{
	int idx = 0;
	auto iter = m_mMat.begin();
	for (; iter != m_mMat.end(); iter++)
	{
		if (strcmp(iter->first.c_str(), matName.c_str()) == 0)
			return idx;
		idx++;
	}
	return -1;
}
