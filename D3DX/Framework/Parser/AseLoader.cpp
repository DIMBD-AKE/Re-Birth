#include "../../stdafx.h"
#include "AseLoader.h"
#include "Asciitok.h"

AseLoader::AseLoader()
{
}


AseLoader::~AseLoader()
{
}

ST_ASE* AseLoader::Load(string path, string fileName)
{
	FILE* fp;
	fopen_s(&fp, (path + fileName).c_str(), "r");

	ST_ASE_SCENE scene;
	vector<ST_ASE_MATERIAL> material;
	vector<ST_PNT_VERTEX> vecVertex;
	map<string, ST_ASE_GEOMETRY*> geometry;
	ST_ASE_GEOMETRY* root;

	while (!feof(fp))
	{
		char line[256];
		fgets(line, 256, fp);
		
		char * tok;
		char * context;
		tok = strtok_s(line, "\t ", &context);

		if (strcmp(tok, ID_SCENE) == 0)
		{
			scene = ProcessScene(fp);
		}

		if (strcmp(tok, ID_MATERIAL) == 0)
		{
			material.push_back(ProcessMaterial(fp, path));
		}

		if (strcmp(tok, ID_GEOMETRY) == 0)
		{	
			ProcessGeometry(fp, material, geometry, vecVertex);
		}
	}

	fclose(fp);

	ST_ASE* ase = new ST_ASE;
	ase->root = geometry.begin()->second;
	ase->scene = scene;

	for (int i = 0; i < vecVertex.size(); i++)
	{
		if (ase->size.lowX > vecVertex[i].p.x)
			ase->size.lowX = vecVertex[i].p.x;
		if (ase->size.highX < vecVertex[i].p.x)
			ase->size.highX = vecVertex[i].p.x;
		if (ase->size.lowY > vecVertex[i].p.y)
			ase->size.lowY = vecVertex[i].p.y;
		if (ase->size.highY < vecVertex[i].p.y)
			ase->size.highY = vecVertex[i].p.y;
		if (ase->size.lowZ > vecVertex[i].p.z)
			ase->size.lowZ = vecVertex[i].p.z;
		if (ase->size.highZ < vecVertex[i].p.z)
			ase->size.highZ = vecVertex[i].p.z;
	}

	return ase;
}

ST_ASE_SCENE AseLoader::ProcessScene(FILE * fp)
{
	ST_ASE_SCENE scene;
	char line[256];
	char * tok;
	char * context;

	do
	{
		fgets(line, 256, fp);
		tok = strtok_s(line, "\t \"", &context);
		if (strcmp(tok, ID_FILENAME) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			if (tok[0] != '\n')
				scene.fileName = string(tok);
		}
		if (strcmp(tok, ID_FIRSTFRAME) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			scene.firstFrame = atoi(tok);
		}
		if (strcmp(tok, ID_LASTFRAME) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			scene.lastFrame = atoi(tok);
		}
		if (strcmp(tok, ID_FRAMESPEED) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			scene.frameSpeed = atoi(tok);
		}
		if (strcmp(tok, ID_TICKSPERFRAME) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			scene.ticksPerFrame = atoi(tok);
		}
		if (strcmp(tok, ID_STATICBGCOLOR) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			scene.staticColor.r = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			scene.staticColor.g = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			scene.staticColor.b = atof(tok);
			scene.staticColor.a = 0;
		}
		if (strcmp(tok, ID_STATICAMBIENT) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			scene.ambientColor.r = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			scene.ambientColor.g = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			scene.ambientColor.b = atof(tok);
			scene.ambientColor.a = 0;
		}
	} while (tok[0] != '}');

	return scene;
}

ST_ASE_MATERIAL AseLoader::ProcessMaterial(FILE * fp, string path)
{
	ST_ASE_MATERIAL mat;
	ZeroMemory(&mat.mat, sizeof(D3DMATERIAL9));
	mat.tex = NULL;
	char line[256];
	char * tok;
	char * context;

	do
	{
		fgets(line, 256, fp);
		tok = strtok_s(line, "\t \"", &context);
		if (strcmp(tok, ID_AMBIENT) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			mat.mat.Ambient.r = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			mat.mat.Ambient.g = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			mat.mat.Ambient.b = atof(tok);
		}
		if (strcmp(tok, ID_DIFFUSE) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			mat.mat.Diffuse.r = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			mat.mat.Diffuse.g = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			mat.mat.Diffuse.b = atof(tok);
		}
		if (strcmp(tok, ID_SPECULAR) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			mat.mat.Specular.r = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			mat.mat.Specular.g = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			mat.mat.Specular.b = atof(tok);
		}
		if (strcmp(tok, ID_MAP_DIFFUSE) == 0)
		{
			do
			{
				fgets(line, 256, fp);
				tok = strtok_s(line, "\t \"", &context);
				if (strcmp(tok, ID_BITMAP) == 0)
				{
					tok = strtok_s(NULL, "\t \"", &context);
					string s = path + GetFileName(tok);
					mat.tex = TEXTUREMANAGER->AddTexture(s, s);
				}
			} while (tok[0] != '}');
			fgets(line, 256, fp);
			tok = strtok_s(line, "\t \"", &context);
		}
	} while (tok[0] != '}');
	
	return mat;
}

void AseLoader::ProcessGeometry(FILE * fp, vector<ST_ASE_MATERIAL>& material, map<string, ST_ASE_GEOMETRY*>& geometry, vector<ST_PNT_VERTEX>& vecVertex)
{
	ST_ASE_GEOMETRY* gm = new ST_ASE_GEOMETRY();
	char line[256];
	char * tok;
	char * context;

	do
	{
		fgets(line, 256, fp);
		if (feof(fp)) break;
		tok = strtok_s(line, "\t \"", &context);
		if (strcmp(tok, ID_NODE_NAME) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			string name = string(tok) + " " + string(context);
			tok = strtok_s((char*)name.c_str(), "\"\n", &context);
			gm->nodeName = string(tok);
		}
		if (strcmp(tok, ID_NODE_PARENT) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			string name = string(tok) + " " + string(context);
			tok = strtok_s((char*)name.c_str(), "\"\n", &context);
			if (geometry.find(string(tok)) != geometry.end())
			{
				geometry.find(string(tok))->second->vecChild.push_back(gm);
				gm->nodeParent = geometry.find(string(tok))->second;
			}
		}
		if (strcmp(tok, ID_NODE_TM) == 0)
		{
			gm->tm = ProcessTM(fp);
			if (gm->nodeParent)
			{
				D3DXMATRIX inv;
				D3DXMatrixInverse(&inv, NULL, &gm->nodeParent->tm.world);
				gm->tm.localWorld = gm->tm.world * inv;
			}
			else
			{
				gm->tm.localWorld = gm->tm.world;
			}
		}
		if (strcmp(tok, ID_MESH) == 0)
		{
			vector<ST_PNT_VERTEX> vertex;
			vertex = ProcessMesh(fp);
			for (int i = 0; i < vertex.size(); i++)
				vecVertex.push_back(vertex[i]);
			D3DXMATRIX inv;
			D3DXMatrixInverse(&inv, NULL, &gm->tm.world);
			DEVICE->CreateVertexBuffer(sizeof(ST_PNT_VERTEX) * vertex.size(), 0,
				ST_PNT_VERTEX::FVF, D3DPOOL_DEFAULT, &gm->vb, NULL);
			gm->vb->Lock(0, 0, (void**)&gm->pData, 0);
			for (int i = 0; i < vertex.size(); i++)
				D3DXVec3TransformCoord(&vertex[i].p, &vertex[i].p, &inv);
			memcpy(gm->pData, &vertex[0], sizeof(ST_PNT_VERTEX) * vertex.size());
			gm->priCount = vertex.size() / 3;
			gm->vb->Unlock();
		}
		if (strcmp(tok, ID_TM_ANIMATION) == 0)
		{
			gm->anim = ProcessAnimation(fp);
			fgets(line, 256, fp);
			fgets(line, 256, fp);
			tok = strtok_s(line, "\t \"", &context);
		}
		if (strcmp(tok, ID_MATERIAL_REF) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			int mi = atoi(tok);
			if (material.size() > mi)
			{
				gm->mat.mat = material[mi].mat;
				gm->mat.tex = material[mi].tex;
			}
		}
	} while (tok[0] != '}');

	if (strlen(gm->nodeName.c_str()) > 0)
	{
		geometry.insert(make_pair(gm->nodeName, gm));
	}
}

ST_ASE_TM AseLoader::ProcessTM(FILE * fp)
{
	ST_ASE_TM tm;
	char line[256];
	char * tok;
	char * context;

	D3DXMatrixIdentity(&tm.world);
	do
	{
		fgets(line, 256, fp);
		tok = strtok_s(line, "\t \"", &context);
		if (strcmp(tok, ID_TM_ROW0) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			tm.world._11 = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			tm.world._13 = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			tm.world._12 = atof(tok);
		}
		if (strcmp(tok, ID_TM_ROW1) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			tm.world._31 = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			tm.world._33 = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			tm.world._32 = atof(tok);
		}
		if (strcmp(tok, ID_TM_ROW2) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			tm.world._21 = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			tm.world._23 = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			tm.world._22 = atof(tok);
		}
		if (strcmp(tok, ID_TM_ROW3) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			tm.world._41 = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			tm.world._43 = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			tm.world._42 = atof(tok);
		}
		if (strcmp(tok, ID_TM_ROTAXIS) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			tm.rotAxis.x = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			tm.rotAxis.y = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			tm.rotAxis.z = atof(tok);
		}
		if (strcmp(tok, ID_TM_ROTANGLE) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			tm.rotAngle = atof(tok);
		}
		if (strcmp(tok, ID_TM_SCALE) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			tm.scale.x = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			tm.scale.y = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			tm.scale.z = atof(tok);
		}
		if (strcmp(tok, ID_TM_SCALEAXIS) == 0)
		{
			tok = strtok_s(NULL, "\t \"", &context);
			tm.scaleAxis.x = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			tm.scaleAxis.y = atof(tok);
			tok = strtok_s(NULL, "\t \"", &context);
			tm.scaleAxis.z = atof(tok);
		}
	} while (tok[0] != '}');

	return tm;
}

ST_ASE_ANIMATION AseLoader::ProcessAnimation(FILE * fp)
{
	char line[256];
	char * tok;
	char * context;
	ST_ASE_ANIMATION anim;

	do
	{
		ST_ASE_TRACK track;

		fgets(line, 256, fp);
		tok = strtok_s(line, "\t \"", &context);
		if (strcmp(tok, ID_POS_TRACK) == 0)
		{
			while (tok[0] != '}')
			{
				if (strcmp(tok, ID_POS_SAMPLE) == 0)
				{
					tok = strtok_s(NULL, "\t \"", &context);
					track.frame = atoi(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					track.pos.x = atof(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					track.pos.z = atof(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					track.pos.y = atof(tok);
					anim.posTrack.push_back(track);
				}
				fgets(line, 256, fp);
				tok = strtok_s(line, "\t \"", &context);
			}
			fgets(line, 256, fp);
			tok = strtok_s(line, "\t \"", &context);
		}
		if (strcmp(tok, ID_ROT_TRACK) == 0)
		{
			while (tok[0] != '}')
			{
				if (strcmp(tok, ID_ROT_SAMPLE) == 0)
				{
					D3DXVECTOR3 v;
					tok = strtok_s(NULL, "\t \"", &context);
					track.frame = atoi(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					v.x = atof(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					v.z = atof(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					v.y = atof(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					float angle = atof(tok);
					D3DXQuaternionRotationAxis(&track.quater, &v, angle);
					anim.rotTrack.push_back(track);
				}
				fgets(line, 256, fp);
				tok = strtok_s(line, "\t \"", &context);
			}
			for (int i = 1; i < anim.rotTrack.size(); i++)
				anim.rotTrack[i].quater = anim.rotTrack[i - 1].quater * anim.rotTrack[i].quater;
		}
	} while (tok[0] != '}');


	return anim;
}

vector<ST_PNT_VERTEX> AseLoader::ProcessMesh(FILE * fp)
{
	vector<ST_PNT_VERTEX> vertex;
	vector<ST_PNT_VERTEX> index;
	vector<D3DXVECTOR2> uv;

	char line[256];
	char * tok;
	char * context;

	do
	{
		fgets(line, 256, fp);
		tok = strtok_s(line, "\t \"", &context);
		if (strcmp(tok, ID_MESH_VERTEX_LIST) == 0)
		{
			while (tok[0] != '}')
			{
				ST_PNT_VERTEX v;
				v.t = D3DXVECTOR2(0, 0);
				fgets(line, 256, fp);
				tok = strtok_s(line, "\t \"", &context);
				if (strcmp(tok, ID_MESH_VERTEX) == 0)
				{
					tok = strtok_s(NULL, "\t \"", &context);
					tok = strtok_s(NULL, "\t \"", &context);
					v.p.x = atof(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					v.p.z = atof(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					v.p.y = atof(tok);
					vertex.push_back(v);
				}
			}
			fgets(line, 256, fp);
			tok = strtok_s(line, "\t \"", &context);
		}		
		if (strcmp(tok, ID_MESH_FACE_LIST) == 0)
		{
			while (tok[0] != '}')
			{
				fgets(line, 256, fp);
				tok = strtok_s(line, "\t \"", &context);
				if (strcmp(tok, ID_MESH_FACE) == 0)
				{
					tok = strtok_s(NULL, "\t \":", &context);
					tok = strtok_s(NULL, "\t \":", &context);
					tok = strtok_s(NULL, "\t \":", &context);
					int v0 = atoi(tok);
					tok = strtok_s(NULL, "\t \":", &context);
					tok = strtok_s(NULL, "\t \":", &context);
					int v1 = atoi(tok);
					tok = strtok_s(NULL, "\t \":", &context);
					tok = strtok_s(NULL, "\t \":", &context);
					int v2 = atoi(tok);

					index.push_back(vertex[v2]);
					index.push_back(vertex[v1]);
					index.push_back(vertex[v0]);
				}
			}
			fgets(line, 256, fp);
			tok = strtok_s(line, "\t \"", &context);
		}
		if (strcmp(tok, ID_MESH_TVERTLIST) == 0)
		{
			while (tok[0] != '}')
			{
				fgets(line, 256, fp);
				tok = strtok_s(line, "\t \"", &context);
				if (strcmp(tok, ID_MESH_TVERT) == 0)
				{
					D3DXVECTOR2 t;
					tok = strtok_s(NULL, "\t \"", &context);
					tok = strtok_s(NULL, "\t \"", &context);
					t.x = atof(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					t.y = 1 - atof(tok);
					uv.push_back(t);
				}
			}
			fgets(line, 256, fp);
			tok = strtok_s(line, "\t \"", &context);
		}
		if (strcmp(tok, ID_MESH_TFACELIST) == 0)
		{
			while (tok[0] != '}')
			{
				fgets(line, 256, fp);
				tok = strtok_s(line, "\t \"", &context);
				if (strcmp(tok, ID_MESH_TFACE) == 0)
				{
					tok = strtok_s(NULL, "\t \"", &context);
					int ti = atoi(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					int t0 = atoi(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					int t1 = atoi(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					int t2 = atoi(tok);

					index[ti * 3].t = uv[t2];
					index[ti * 3 + 1].t = uv[t1];
					index[ti * 3 + 2].t = uv[t0];
				}
			}
			fgets(line, 256, fp);
			tok = strtok_s(line, "\t \"", &context);
		}
		if (strcmp(tok, ID_MESH_NORMALS) == 0)
		{
			while (tok[0] != '}')
			{
				fgets(line, 256, fp);
				tok = strtok_s(line, "\t \"", &context);
				if (strcmp(tok, ID_MESH_FACENORMAL) == 0)
				{
					tok = strtok_s(NULL, "\t \"", &context);
					int ni = atoi(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					index[ni * 3].n.x = atof(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					index[ni * 3].n.z = atof(tok);
					tok = strtok_s(NULL, "\t \"", &context);
					index[ni * 3].n.y = atof(tok);

					index[ni * 3 + 1].n = index[ni * 3].n;
					index[ni * 3 + 2].n = index[ni * 3].n;
				}
			}
			fgets(line, 256, fp);
			tok = strtok_s(line, "\t \"", &context);
		}
	} while (tok[0] != '}');

	return index;
}

ST_ASE_GEOMETRY::ST_ASE_GEOMETRY()
{
	mat.tex = NULL;
	ZeroMemory(&mat.mat, sizeof(D3DMATERIAL9));
	nodeParent = NULL;
	nodeName = "";
}

D3DXMATRIX ST_ASE_GEOMETRY::CalcRotAnim(int frame)
{
	D3DXQUATERNION out;
	D3DXMATRIX rot;
	D3DXMatrixIdentity(&rot);

	if (anim.rotTrack.size() == 0)
	{
		rot = tm.localWorld;
		rot._41 = 0.0f;
		rot._42 = 0.0f;
		rot._43 = 0.0f;
		return rot;
	}
	else
	{
		if (anim.rotTrack[anim.rotTrack.size() - 1].frame < frame)
		{
			out = anim.rotTrack[anim.rotTrack.size() - 1].quater;
		}
		else if (anim.rotTrack.front().frame >= frame)
		{
			D3DXMatrixRotationQuaternion(&rot, &anim.rotTrack.front().quater);
			return rot;
		}
		else if (anim.rotTrack.back().frame <= frame)
		{
			D3DXMatrixRotationQuaternion(&rot, &anim.rotTrack.back().quater);
			return rot;
		}
		else
		{
			int nextIndex = 0;
			for (int i = 0; i < anim.rotTrack.size(); i++)
				if (anim.rotTrack[i].frame > frame)
				{
					nextIndex = i;
					break;
				}

			int prevIndex = nextIndex - 1;
			if (prevIndex < 0) prevIndex = 0;

			float t = (frame - anim.rotTrack[prevIndex].frame)
				/ (float)(anim.rotTrack[nextIndex].frame - 
					anim.rotTrack[prevIndex].frame);

			for (int i = 0; i < anim.rotTrack.size(); i++)
			{
				if (anim.rotTrack[i].frame == frame)
				{
					out = anim.rotTrack[i].quater;
				}
				else
				{
					D3DXQuaternionSlerp(&out, 
						&anim.rotTrack[prevIndex].quater,
						&anim.rotTrack[nextIndex].quater, t);
				}
			}
		}
	}

	D3DXMatrixRotationQuaternion(&rot, &out);

	return rot;
}

D3DXMATRIX ST_ASE_GEOMETRY::CalcPosAnim(int frame)
{
	D3DXVECTOR3 out;
	D3DXMATRIX pos;
	D3DXMatrixIdentity(&pos);

	if (anim.posTrack.size() == 0)
	{
		pos._41 = tm.localWorld._41;
		pos._42 = tm.localWorld._42;
		pos._43 = tm.localWorld._43;
		return pos;
	}
	else
	{
		if (anim.posTrack[anim.posTrack.size() - 1].frame < frame)
		{
			out = anim.posTrack[anim.posTrack.size() - 1].pos;
		}
		else if (anim.posTrack.front().frame >= frame)
		{
			pos._41 = anim.posTrack.front().pos.x;
			pos._42 = anim.posTrack.front().pos.y;
			pos._43 = anim.posTrack.front().pos.z;
			return pos;
		}
		else if (anim.posTrack.back().frame <= frame)
		{
			pos._41 = anim.posTrack.back().pos.x;
			pos._42 = anim.posTrack.back().pos.y;
			pos._43 = anim.posTrack.back().pos.z;
			return pos;
		}
		else
		{
			int nextIndex = 0;
			for (int i = 0; i < anim.posTrack.size(); i++)
				if (anim.posTrack[i].frame > frame)
				{
					nextIndex = i;
					break;
				}

			int prevIndex = nextIndex - 1;
			if (prevIndex < 0) prevIndex = 0;

			float t = (frame - anim.posTrack[prevIndex].frame)
				/ (float)(anim.posTrack[nextIndex].frame -
					anim.posTrack[prevIndex].frame);

			for (int i = 0; i < anim.posTrack.size(); i++)
			{
				if (anim.posTrack[i].frame == frame)
				{
					out = anim.posTrack[i].pos;
				}
				else
				{
					D3DXVec3Lerp(&out,
						&anim.posTrack[prevIndex].pos,
						&anim.posTrack[nextIndex].pos, t);
				}
			}
		}
	}

	pos._41 = out.x;
	pos._42 = out.y;
	pos._43 = out.z;

	return pos;
}

void ST_ASE_GEOMETRY::Update(int frame, D3DXMATRIX * rootWorld)
{
	D3DXMATRIX matR = CalcRotAnim(frame);
	D3DXMATRIX matT = CalcPosAnim(frame);

	tm.anim = matR * matT;

	if (nodeParent)
		tm.world = tm.anim * nodeParent->tm.world;
	else if (rootWorld)
		tm.world = tm.anim * *rootWorld;
	else
		tm.world = tm.anim;

	for (int i = 0; i < vecChild.size(); i++)
		vecChild[i]->Update(frame);
}

void ST_ASE_GEOMETRY::Render()
{
	if (mat.tex)
	{
		DEVICE->SetTexture(0, mat.tex);
		DEVICE->SetMaterial(&mat.mat);
		DEVICE->SetFVF(ST_PNT_VERTEX::FVF);
		DEVICE->SetTransform(D3DTS_WORLD, &tm.world);
		DEVICE->SetStreamSource(0, vb, 0, sizeof(ST_PNT_VERTEX));
		DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, priCount);
	}

	for (int i = 0; i < vecChild.size(); i++)
		vecChild[i]->Render();
}

void ST_ASE_GEOMETRY::Release()
{
	SAFE_RELEASE(vb);

	for (int i = 0; i < vecChild.size(); i++)
		vecChild[i]->Release();
}

int ST_ASE::GetKeyFrame()
{
	int first = scene.firstFrame * scene.ticksPerFrame;
	int last = scene.lastFrame * scene.ticksPerFrame;
	return (GetTickCount() * scene.ticksPerFrame / scene.frameSpeed) % (last - first) + first;
}

void ST_ASE::Update(int tick, D3DXMATRIX * rootWorld)
{
	if (root)
		root->Update(tick, rootWorld);
}

void ST_ASE::Render()
{
	if (root)
		root->Render();
}

void ST_ASE::Release()
{
	if (root)
		root->Release();
}
