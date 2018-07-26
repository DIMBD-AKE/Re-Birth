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

enum PETSTATE
{
	PET_IDLE,
	PET_MOVE,
	PET_ATTACK,
};

class Pet
{
private:
	Model*			m_pModel;
	D3DXVECTOR3*	m_pTarget;
	Map*			m_pMap;	

	STATUS			m_status;
	PETSTATE		m_eState;

	bool			m_isOptimize;

private:
	vector<ST_PET_NODE>	m_vecFindPath;
	ST_PET_CELL			m_stTargetCell;
	bool TargetUpdate();
	bool TargetEqualCell();
	void AStar();
	void OptimizePath();

	void Move();
	void Debug();
	void StateControll();

public:
	Pet();
	~Pet();

	void Init(D3DXVECTOR3* target, Map * map);
	void Update();
	void Render();

	void Attack() { m_eState = (m_eState == PET_ATTACK ? PET_IDLE : PET_ATTACK); }
};

