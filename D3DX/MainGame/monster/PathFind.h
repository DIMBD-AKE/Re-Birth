#pragma once

struct ST_CELL
{
	D3DXVECTOR3 vertex[3];		//하나의 삼각형중 세 점을 담을 변수
	D3DXVECTOR3 center;			//삼각형의 센터
	D3DXVECTOR3 vertexCenter[3]; //사이드 라인의 중점

	float arrivalCost[3];		//중점 - 사이드간 거리

	ST_CELL* neighborCell[3];	//나랑 이웃한 삼각형의 포인터
};

class PathFind
{
	vector<ST_CELL> m_vNaviCell;

public:
	PathFind();
	~PathFind();

	void Setup(vector<D3DXVECTOR3>& Vertex);
	void Update();
	void Render();

							//사이드의 중점		자기자신	
	ST_CELL* MakeNeighborCell(D3DXVECTOR3 rayPos, int index);
};

