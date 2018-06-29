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

struct ST_PNT_VERTEX
{
	D3DXVECTOR3	p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	};
};

struct ST_SPHERE
{
	D3DXVECTOR3 center;
	float radius;
};

struct ST_BOUNDBOX
{
	vector<ST_PC_VERTEX> vecVertex;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 pos;
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