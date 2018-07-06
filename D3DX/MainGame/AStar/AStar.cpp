#include "../../stdafx.h"
#include "AStar.h"
#include "PathFind.h"
#include "Cell.h"

AStar::AStar()
{
}


AStar::~AStar()
{

}

void AStar::SetCurrentCell(vector<D3DXVECTOR3> Vertex)
{

	m_pPathFind = new PathFind;
	m_pPathFind->Setup(Vertex);

	m_vCurrentCell = m_pPathFind->GetNaviCell();
}

void AStar::SetCell(int MyCellIndex, int TargetIndex)
{
	//�⺻ �ʱ�ȭ �ܰ�
	//�ؿ��� ������ �Ӽ��� �����ϴ°� �ǵ������۾�
	for (int i = 0; i < m_vCurrentCell.size(); i++)
	{
		m_vCurrentCell[i]->ZeroReset();
		//m_vCurrentCell[i]->
		//m_vCurrentCell[i]->
	}

	/*
	SYNTHESIZE(float, m_fTotalCost, TotalCost);
	
	//���ۺ��� ��������� �ڽ�Ʈ
	SYNTHESIZE(float, m_fCostFromStart, CostFromStart);
	
	//���ۺ��� �������� �ڽ�Ʈ
	SYNTHESIZE(float, m_fCostToGoal, CostToGal);
	
	//�� Ÿ�� ���� ���� Ÿ��
	SYNTHESIZE(Cell*, m_pParentCell, ParentCell);
	
	//���� �ִ� Ÿ���̳�
	SYNTHESIZE(bool, m_bIsOpen, IsOpen);
	*/
	//��Ƶ� ���� Ŭ���� �ϰ� �ٽ� ��´�.
	m_vTotalList.clear();
	m_vOpenList.clear();
	m_vCloseList.clear();

	//����Ÿ��
	//m_pStartCell = m_vCurrentCell[0];
	m_pStartCell = m_vCurrentCell[MyCellIndex];
	m_pStartCell->SetAttribute("start");
	
	//����Ÿ��
	//m_pEndCell = m_vCurrentCell[m_vCurrentCell.size() - 1];
	m_pEndCell = m_vCurrentCell[TargetIndex];
	m_pEndCell->SetAttribute("end");

	//����
	m_pCurrentCell = m_pStartCell;

	for (int i = 0; i < m_vCurrentCell.size(); i++)
	{
		//�ϴ� ������ 0��°�� ��ŸƮ
		//���߿� ���� �ε����� ���ڷ� �޾Ƽ� ��ŸƮ�� ����
		if (i == 0)
		//if (i == MyCellIndex)
		{
			//m_vCurrentCell[i]->SetAttribute("start");
			m_vTotalList.push_back(m_vCurrentCell[i]);
		}
		//�ϴ� ������ ������ ���� ������
		else if (i == m_vCurrentCell.size() - 1)
		{
			//m_vCurrentCell[i]->SetAttribute("end");
			m_vTotalList.push_back(m_vCurrentCell[i]);
		}
		//������ �� ����ھ��ش�.
		else
		{
			m_vTotalList.push_back(m_vCurrentCell[i]);
		}
	}
}

vector<Cell*> AStar::addOpenList(Cell* currentCell)
{
	//�ﰢ�� �ϳ��� ���� �ﰢ���� 3���̹Ƿ�
	for (int i = 0; i < 3; i++)
	{
		//���� �ﰢ���� ���ٸ� �������� �Ѿ��
		if (!currentCell->GetNeighborCell()[i]) continue;

		//���� �ﰢ���� �ִٸ� �ϴ� ���������� �ݵ��
		Cell* tempCell = currentCell->GetNeighborCell()[i];

		//���� ���� ��, ����, �� Ÿ���� �����Ѵ�.
		if (!tempCell->GetIsOpen()) continue;
		if (tempCell->GetAttribute() == "start") continue;
		if (tempCell->GetAttribute() == "wall") continue;

		//�������� ���� ���̴�.
		tempCell->SetParentCell(m_pCurrentCell);

		//üũ�� �Ұ�
		bool addCell = true;
		for (m_viOpenList = m_vOpenList.begin();
			m_viOpenList != m_vOpenList.end(); ++m_viOpenList)
		{
			//�� �� üũ �� �ִ� �ߺ� ���� ���� �ʴ´�
			if (*m_viOpenList == tempCell)
			{
				addCell = false;
				break;
			}
		}

		//�̹� ���¸���Ʈ�� �������� ��Ƽ��
		if (!addCell) continue;

		m_vOpenList.push_back(tempCell);

	}

	return m_vOpenList;
}

void AStar::pathFinder(Cell* currentCell)
{
	float tempTotalCost = 5000;
	Cell* tempCell = NULL;

	for (int i = 0; i < addOpenList(currentCell).size(); ++i)
	{
		/*
		����Ʈ�� �ִ°�
		deltax = (��ǥ��.x - ����������.x)
		deltay = (��ǥ��.y - ����������.y)
		deltaz = (��ǥ��.z - ����������.z)
		max(max(deltax, deltay), deltaz)

		�ϴ� ����������
		*/
		//��ǥ�� - ���� �� ����
		D3DXVECTOR3 tempVec;
		tempVec = m_pEndCell->GetCenter() - m_vOpenList[i]->GetCenter();
		m_vOpenList[i]->SetCostToGal(
			D3DXVec3Length(&tempVec)
			);

		D3DXVECTOR3 center1 = m_vOpenList[i]->GetParentCell()->GetCenter();
		D3DXVECTOR3 center2 = m_vOpenList[i]->GetCenter();

		m_vOpenList[i]->SetCostFromStart(
			D3DXVec3Length(&(center1 - center2)));

		m_vOpenList[i]->SetTotalCost(m_vOpenList[i]->GetCostToGal()
			+ m_vOpenList[i]->GetCostFromStart());

		if (tempTotalCost > m_vOpenList[i]->GetTotalCost())
		{
			tempTotalCost = m_vOpenList[i]->GetTotalCost();
			tempCell = m_vOpenList[i];
		}

		//�ߺ�����
		bool addObj = true;
		for (m_viOpenList = m_vOpenList.begin();
			m_viOpenList != m_vOpenList.end(); ++m_viOpenList)
		{
			if (*m_viOpenList == tempCell)
			{
				addObj = false;
				break;
			}
		}

		//�˻� �Ϸ� ��
		m_vOpenList[i]->SetIsOpen(false);
		if (!addObj) continue;

		m_vOpenList.push_back(tempCell);
	}

		if (tempCell->GetAttribute() == "end")
		{
			while (m_pCurrentCell->GetParentCell() != NULL)
			{

				m_pCurrentCell = m_pCurrentCell->GetParentCell();
			}
			return;
		}
		m_vCloseList.push_back(tempCell);
		//_vDibugList.push_back(tempTile);

		for (m_viOpenList = m_vOpenList.begin();
			m_viOpenList != m_vOpenList.end(); ++m_viOpenList)
		{
			if (*m_viOpenList == tempCell)
			{
				m_viOpenList = m_vOpenList.erase(m_viOpenList);
				break;
			}
		}

		m_pCurrentCell = tempCell;
		pathFinder(m_pCurrentCell);
}

D3DXVECTOR3 AStar::GetNextCell()
{
	if (m_pStartCell == m_pEndCell)
	{
		return D3DXVECTOR3(-1, -1, -1);
	}

	pathFinder(m_pCurrentCell);
	if (m_vCloseList.size() <= 0)
	{
		return D3DXVECTOR3(-1, -1, -1);
	}
	return m_vCloseList[0]->GetCenter();
}

int AStar::GetCellIndex(D3DXVECTOR3 pos)
{
	return m_pPathFind->GetCellIndex(pos);
}

void AStar::Render(int MyCellIndex, int TargetIndex)
{
	
	if (DEBUG)
	{
		SetCell(MyCellIndex, TargetIndex);
		GetNextCell();
		vector<D3DXVECTOR3> tempVector;
		for (int i = 0; i < m_vCloseList.size(); i++)
		{
			tempVector.push_back(m_vCloseList[i]->GetCenter());
		}

		DEVICE->SetTexture(0, NULL);
		DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP,
			//��� �ﰢ������
			tempVector.size(),
			//ù �ּ�
			&tempVector[0],
			//ũ��
			sizeof(D3DXVECTOR3));
	}
}