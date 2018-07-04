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

							//���̵��� ����		�ڱ��ڽ�	
	//ST_CELL* MakeNeighborCell(D3DXVECTOR3 rayPos, int index);

	
	void MakeNeighborCell(int index);

	//�������� ������ ���⼭		���� �ε���			��������� �ε���
	Cell** SubMakeNeighborCell(int myCellIndex);
};

