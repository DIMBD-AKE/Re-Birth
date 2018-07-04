#pragma once
#include "Cell.h"

class Cell;

class PathFind
{
	vector<Cell> m_vNaviCell;

public:
	PathFind();
	~PathFind();

	void Setup(vector<D3DXVECTOR3>& Vertex);
	void Update();
	void Render();

							//사이드의 중점		자기자신	
	//ST_CELL* MakeNeighborCell(D3DXVECTOR3 rayPos, int index);

	
	void MakeNeighborCell(int index);

	//실질적인 연결은 여기서		나의 인덱스			연결시켜줄 인덱스
	Cell** SubMakeNeighborCell(int myCellIndex);
};

