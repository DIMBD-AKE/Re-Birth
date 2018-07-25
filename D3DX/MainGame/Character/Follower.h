#pragma once

#include "../Status.h"

class Map;

struct ST_FOLLOWER_CELL
{
	D3DXVECTOR3 v0, v1, v2;
	D3DXVECTOR3 center;
};

struct ST_FOLLOWER_NODE
{
	ST_FOLLOWER_CELL c;
	float F, G, H;
	bool isList;
	ST_FOLLOWER_NODE * pParent;
};

class Follower
{
private:
	Model*			m_pModel;

	D3DXVECTOR3*	m_pTarget;
	Map*			m_pMap;
	
	STATUS			m_status;

private:
	vector<ST_FOLLOWER_NODE*>	m_vecFindPath;
	void AStar(vector<D3DXVECTOR3> vecNavMesh);

public:
	Follower();
	~Follower();

	void Init(D3DXVECTOR3* target, Map * map);
	void Update();
	void Render();
};

