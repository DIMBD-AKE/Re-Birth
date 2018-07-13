#pragma once

struct ST_PC_VERTEX
{
	D3DXVECTOR3	p;
	D3DCOLOR	c;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
	};
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3	p;
	D3DXVECTOR2 t;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_TEX1
	};
};

struct ST_PCT_VERTEX
{
	D3DXVECTOR3	p;
	D3DCOLOR	c;
	D3DXVECTOR2 t;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1
	};
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3	p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	};
};

struct ST_PARTICLE
{
	D3DXVECTOR3	p;
	D3DCOLOR	c;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
	};
};

struct ST_PARTICLE_ATTRIBUTE
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vVelocity;
	D3DXVECTOR3 vAcceleration;
	D3DXVECTOR3	vGravity;
	D3DXVECTOR3 vGravityPos;
	float		fGravityForce;
	float		fGravityRadius;
	float		fStartRadius;
	float		fEndRadius;
	float		fRadiusSpeed;
	float		fCurrentRadiusSpeed;
	float		fLifeTime;
	float		fAge;
	D3DXCOLOR	color;
	D3DXCOLOR	colorFade;
	int			nLoop;
	int			nMaxLoop;
	bool		isAlive;
};

struct ST_PARTICLE_ATTRIBUTE_VARIABLE
{
	D3DXVECTOR3 vPosVar;
	D3DXVECTOR3 vVelocityVar;
	D3DXVECTOR3 vAccelerationVar;
	float		fStartRadiusVar;
	float		fEndRadiusVar;
	float		fRadiusSpeedVar;
	float		fLifeTimeVar;
};

struct ST_PARTICLE_INFO
{
	LPDIRECT3DTEXTURE9				pTexture;
	ST_PARTICLE_ATTRIBUTE			origAttribute;
	ST_PARTICLE_ATTRIBUTE_VARIABLE	varAttribute;
	float		fParticleSize;
	int			nParticleCount;
};

struct ST_EFFECT
{
	LPDIRECT3DTEXTURE9 tex;
	D3DXVECTOR3 dir;
	D3DXVECTOR3 rot;
	bool isRX;
	bool isRY;
	bool isRZ;
	bool isSphere;
	float height;
	float time;
	float sc0, sc1, sc2;
	float sp0, sp1, sp2;
	int a0, a1, a2;

	void SetScale(float f0, float f1, float f2)
	{
		sc0 = f0; sc1 = f1; sc2 = f2;
	}

	void SetSpeed(float f0, float f1, float f2)
	{
		sp0 = f0; sp1 = f1; sp2 = f2;
	}

	void SetAlpha(int n0, int n1, int n2)
	{
		a0 = n0; a1 = n1; a2 = n2;
	}

	void SetRandomRot(bool x, bool y, bool z)
	{
		isRX = x; isRY = y; isRZ = z;
	}
};

struct ST_SPHERE
{
	D3DXVECTOR3 center;
	float radius;
};

struct ST_OBB
{
	D3DXVECTOR3 vCenterPos;
	D3DXVECTOR3 vAxisDir[3];
	float fAxisLen[3];
};

struct ST_BOUNDBOX
{
	vector<ST_PC_VERTEX> vecVertex;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 pos;
	ST_OBB obb;
};

struct ST_SIZEBOX
{
	float lowX, highX;
	float lowY, highY;
	float lowZ, highZ;

	ST_SIZEBOX()
	{
		lowX = 0; highX = 0;
		lowY = 0; highY = 0;
		lowZ = 0; highZ = 0;
	}
};

struct Ray
{
	D3DXVECTOR3 dir;
	D3DXVECTOR3 orig;
};