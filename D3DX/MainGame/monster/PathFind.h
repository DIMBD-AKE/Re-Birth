#pragma once

struct ST_CELL
{
	D3DXVECTOR3 vertex[3];		//�ϳ��� �ﰢ���� �� ���� ���� ����
	D3DXVECTOR3 center;			//�ﰢ���� ����
	D3DXVECTOR3 vertexCenter[3]; //���̵� ������ ����

	float arrivalCost[3];		//���� - ���̵尣 �Ÿ�

	ST_CELL* neighborCell[3];	//���� �̿��� �ﰢ���� ������
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

							//���̵��� ����		�ڱ��ڽ�	
	ST_CELL* MakeNeighborCell(D3DXVECTOR3 rayPos, int index);
};

