#pragma once

#include "../Status.h"

class Map;

struct ST_PET_CELL
{
	D3DXVECTOR3 v0, v1, v2;
	D3DXVECTOR3 center;
};

struct ST_PET_NODE
{
	ST_PET_CELL c;
	float F, G, H;
	bool isList;
	ST_PET_NODE * pParent;
};

class Pet
{
private:
	Model*			m_pModel;

	D3DXVECTOR3*	m_pTarget;
	Map*			m_pMap;
	
	STATUS			m_status;

private:
	vector<ST_PET_NODE>	m_vecFindPath;
	ST_PET_CELL			m_stTargetCell;
	bool TargetUpdate(vector<D3DXVECTOR3> vecNavMesh);
	void AStar(vector<D3DXVECTOR3> vecNavMesh);

	void Move();
	void Debug();

public:
	Pet();
	~Pet();

	void Init(D3DXVECTOR3* target, Map * map);
	void Update();
	void Render();
};

