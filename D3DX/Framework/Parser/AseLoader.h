#pragma once

struct ST_ASE_MATERIAL
{
	LPDIRECT3DTEXTURE9 tex;
	D3DMATERIAL9 mat;
};

struct ST_ASE_TM
{
	D3DXMATRIX world;
	D3DXMATRIX localWorld;
	D3DXMATRIX anim;
	D3DXVECTOR3 rotAxis;
	float rotAngle;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 scaleAxis;

	ST_ASE_TM()
	{
		D3DXMatrixIdentity(&world);
		D3DXMatrixIdentity(&localWorld);
		D3DXMatrixIdentity(&anim);
	}
};

struct ST_ASE_SCENE
{
	string fileName;
	int firstFrame;
	int lastFrame;
	int frameSpeed;
	int ticksPerFrame;
	D3DXCOLOR staticColor;
	D3DXCOLOR ambientColor;
};

struct ST_ASE_TRACK
{
	int frame;
	D3DXVECTOR3 pos;
	D3DXQUATERNION quater;
};

struct ST_ASE_ANIMATION
{
	vector<ST_ASE_TRACK>	posTrack;
	vector<ST_ASE_TRACK>	rotTrack;
};

struct ST_ASE_GEOMETRY
{
	string nodeName;
	ST_ASE_GEOMETRY* nodeParent;
	vector<ST_ASE_GEOMETRY*> vecChild;
	ST_ASE_TM tm;

	LPDIRECT3DVERTEXBUFFER9 vb;
	ST_PNT_VERTEX* pData;
	int priCount;

	ST_ASE_MATERIAL mat;
	ST_ASE_ANIMATION anim;

	ST_ASE_GEOMETRY();

	D3DXMATRIX CalcRotAnim(int frame);
	D3DXMATRIX CalcPosAnim(int frame);
	void Update(int frame, D3DXMATRIX * rootWorld = NULL);
	void Render();
	void Release();
};

struct ST_ASE
{
	ST_ASE_SCENE scene;
	ST_ASE_GEOMETRY* root;
	ST_SIZEBOX size;

	int GetKeyFrame();
	void Update(int tick, D3DXMATRIX * rootWorld = NULL);
	void Render();
	void Release();
};

class AseLoader
{
public:
	AseLoader();
	~AseLoader();

	ST_ASE* Load(string path, string fileName);

	ST_ASE_SCENE ProcessScene(FILE* fp);
	ST_ASE_MATERIAL ProcessMaterial(FILE* fp, string path);
	void ProcessGeometry(FILE* fp, vector<ST_ASE_MATERIAL>& material, 
		map<string, ST_ASE_GEOMETRY*>& geometry, vector<ST_PNT_VERTEX>& vecVertex);
	ST_ASE_TM ProcessTM(FILE* fp);
	ST_ASE_ANIMATION ProcessAnimation(FILE* fp);
	vector<ST_PNT_VERTEX> ProcessMesh(FILE* fp);
};

