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
	PET_SPAWN,
	PET_HIDE,
	PET_DISAPPEAR,
	PET_IDLE,
	PET_MOVE,
	PET_ATTACK,
};

enum PETTYPE
{
	PETTYPE_BENTLEY,
	PETTYPE_BUNNY,
	PETTYPE_MIHO,
	PETTYPE_MIRI,
	PETTYPE_NERO,
	PETTYPE_NIR,
	PETTYPE_NIX,
	PETTYPE_PANDA,
	PETTYPE_PENNY
};

struct ST_PET_STATUS
{
	float speed;
};

class Pet
{
	GET(Model*, m_pModel, Model);
private:
	D3DXVECTOR3*	m_pTarget;
	Map*			m_pMap;

	PETSTATE		m_eState;
	ST_PET_STATUS	m_eStatus;

	bool			m_isOptimize;

	Particle *		m_pSpawnParticle;

private:
	vector<ST_PET_NODE>	m_vecFindPath;
	ST_PET_CELL			m_stTargetCell;
	float				m_fStopDist;
	bool TargetUpdate();
	bool TargetEqualCell();
	void AStar();
	void OptimizePath();

	void Move();
	void StateControll();

	void Debug();

public:
	Pet();
	~Pet();

	void Init(D3DXVECTOR3* target, Map * map, PETTYPE type);
	void Update();
	void Render();

	void ChangeTarget(D3DXVECTOR3* target, float dist);

	void AttackMode();
	void Spawn();

	bool IsSpawn() { return m_eState != PET_HIDE; }
};

