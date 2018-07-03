#include "../../stdafx.h"
#include "PathFind.h"

#define FONTSIZE 20
PathFind::PathFind()
{
}


PathFind::~PathFind()
{

}

void PathFind::Setup(vector<D3DXVECTOR3>& Vertex)
{
	//인자값 사이즈 예외처리
	assert(Vertex.size() >= 0 && "인자값의 벡터사이즈가 0입니다.");

	//인자값 사이즈만큼 메모리 할당하고 
	m_vNaviCell.resize(Vertex.size() / 3);

	int index = 0;
	for (int i = 0; i < Vertex.size(); i += 3)
	{
		//하나의 삼각형 세점 넣기
		m_vNaviCell[index].vertex[0] = Vertex[i];
		m_vNaviCell[index].vertex[1] = Vertex[i+1];
		m_vNaviCell[index].vertex[2] = Vertex[i+2];

		//코드 길이가 길어지지만 좀더 알기 편하기 위해 미리 연산
		D3DXVECTOR3 plusV = m_vNaviCell[index].vertex[0] + m_vNaviCell[index].vertex[1] + m_vNaviCell[index].vertex[2];
		
		//float x = m_vNaviCell[index].vertex[0].x + m_vNaviCell[index].vertex[1].x + m_vNaviCell[index].vertex[2].x;
		//float y = m_vNaviCell[index].vertex[0].y + m_vNaviCell[index].vertex[1].y + m_vNaviCell[index].vertex[2].y;
		//float z = m_vNaviCell[index].vertex[0].z + m_vNaviCell[index].vertex[1].z + m_vNaviCell[index].vertex[2].z;

		//중점좌표 
		m_vNaviCell[index].center =
			D3DXVECTOR3(plusV/3.0f);

		//사이드라인 3개 연산을 위한 반복문
		for (int j = 0; j < 3; j++)
		{
			//코드 길이가 길어지지만 좀더 알기 편하기 위해 미리 연산
			D3DXVECTOR3 plusV2 = m_vNaviCell[index].vertex[j % 3] + m_vNaviCell[index].vertex[(j + 1) % 3];
			m_vNaviCell[index].vertexCenter[j] = plusV2 / 2.0f;

			m_vNaviCell[index].arrivalCost[j] = D3DXVec3Length(&m_vNaviCell[index].vertexCenter[j]);
		}										 

		index++;
	}

	

	//인접한 삼각형 기본 NULL 초기화
	for (int i = 0; i < m_vNaviCell.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_vNaviCell[i].neighborCell[j] = NULL;
		}
	}

	//이웃 만들어주기
	for (int i = 0; i < m_vNaviCell.size(); i++)
	{
		MakeNeighborCell(i);
		//i번쨰 삼각형들의 인접 삼각형은 이것이다!!
		//m_vNaviCell[i].neighborCell[0] = MakeNeighborCell(m_vNaviCell[i].vertexCenter[0],i);
		//m_vNaviCell[i].neighborCell[1] = MakeNeighborCell(m_vNaviCell[i].vertexCenter[1], i);
		//m_vNaviCell[i].neighborCell[2] = MakeNeighborCell(m_vNaviCell[i].vertexCenter[2], i);
	}

	int a = 10;
	
}

void PathFind::Update()
{
	/*
	D3DXVECTOR3 vertex[3];		//하나의 삼각형중 세 점을 담을 변수
	D3DXVECTOR3 center;			//삼각형의 센터
	D3DXVECTOR3 vertexCenter[3]; //사이드 라인의 중점

	float arrivalCost[3];
	*/
	char test[1111];
	sprintf_s(test, sizeof(test), "점1 : %f, %f, %f  점2 : %f, %f, %f  점3 : %f, %f, %f",
		
		m_vNaviCell[0].vertex[0].x, m_vNaviCell[0].vertex[0].y, m_vNaviCell[0].vertex[0].z,
		m_vNaviCell[0].vertex[1].x, m_vNaviCell[0].vertex[1].y, m_vNaviCell[0].vertex[1].z,
		m_vNaviCell[0].vertex[2].x, m_vNaviCell[0].vertex[2].y, m_vNaviCell[0].vertex[2].z
		);

	TEXT->Add(test, 10, 10, FONTSIZE);

	sprintf_s(test, sizeof(test), "센터 점 : %f, %f, %f",

		m_vNaviCell[0].center.x, m_vNaviCell[0].center.y, m_vNaviCell[0].center.z
		);

	TEXT->Add(test, 10, 50, FONTSIZE);

	sprintf_s(test, sizeof(test), "사이드 중점1 : %f, %f, %f  사이드 중점2 : %f, %f, %f  사이드 중점3 : %f, %f, %f",

		m_vNaviCell[0].vertexCenter[0].x, m_vNaviCell[0].vertexCenter[0].y, m_vNaviCell[0].vertexCenter[0].z,
		m_vNaviCell[0].vertexCenter[1].x, m_vNaviCell[0].vertexCenter[1].y, m_vNaviCell[0].vertexCenter[1].z,
		m_vNaviCell[0].vertexCenter[2].x, m_vNaviCell[0].vertexCenter[2].y, m_vNaviCell[0].vertexCenter[2].z
		);

	TEXT->Add(test, 10, 90, FONTSIZE);

	sprintf_s(test, sizeof(test), "점1의 cost : %f 점2의 cost : %f  점3의 cost :  %f",

		m_vNaviCell[0].arrivalCost[0],
		m_vNaviCell[0].arrivalCost[1],
		m_vNaviCell[0].arrivalCost[2]
		);

	TEXT->Add(test, 10, 130, FONTSIZE);
	
}

void PathFind::Render()
{
	TEXT->Render();
	//넣을 문자열, 좌표, 글자 크기
	
}

//ST_CELL* PathFind::MakeNeighborCell(D3DXVECTOR3 rayPos, int index)
//{
//	for (int i = 0; i < m_vNaviCell.size(); i++)
//	{
//		//자기 자신이면 컨티뉴
//		if (i == index) continue;
//
//		
//		if (D3DXIntersectTri(
//			&m_vNaviCell[i].vertex[0],
//			&m_vNaviCell[i].vertex[1],
//			&m_vNaviCell[i].vertex[2],
//			&D3DXVECTOR3(rayPos.x+0.1f, 10000, rayPos.z+0.1f),
//			&D3DXVECTOR3(0, -1, 0),
//			NULL, NULL, NULL))
//		{
//			return &m_vNaviCell[i];
//
//			//return;
//		}
//	}
//
//	return NULL;
//
//}

void PathFind::MakeNeighborCell(int index)
{
	m_vNaviCell[index].neighborCell[0] = SubMakeNeighborCell(index, 0);
	m_vNaviCell[index].neighborCell[1] = SubMakeNeighborCell(index, 1);
	m_vNaviCell[index].neighborCell[2] = SubMakeNeighborCell(index, 2);
	//for (int i = 0; i < m_vNaviCell.size(); i++)
		//	{
		//		//자기 자신이면 컨티뉴
		//		if (i == index) continue;
		//
		//		
		//		if (D3DXIntersectTri(
		//			&m_vNaviCell[i].vertex[0],
		//			&m_vNaviCell[i].vertex[1],
		//			&m_vNaviCell[i].vertex[2],
		//			&D3DXVECTOR3(rayPos.x+0.1f, 10000, rayPos.z+0.1f),
		//			&D3DXVECTOR3(0, -1, 0),
		//			NULL, NULL, NULL))
		//		{
		//			return &m_vNaviCell[i];
		//
		//			//return;
		//		}
		//	}
		//
		//	return NULL;
}

ST_CELL* PathFind::SubMakeNeighborCell(int myCellIndex, int linkCellIndex)
{
	//초기 레이의 위치는 사이드라인의 중점
	D3DXVECTOR3 rayPos = m_vNaviCell[myCellIndex].vertexCenter[linkCellIndex];
	//rayPos.y = 1000;

	//우선 다른 한점의 좌표를 저장
	D3DXVECTOR3 otherV = m_vNaviCell[myCellIndex].vertex[(linkCellIndex + 2) % 3];

	//다른 한점 - 사이드 중앙 을 통해 방향벡터 구하고
	D3DXVECTOR3 dir = rayPos - otherV;
	//노멀라이즈
	D3DXVec3Normalize(&dir, &dir);
	//0.1배화
	dir = dir * 0.1f;

	//레이의 위치에서 아주 약간 앞으로 이동
	rayPos = rayPos + dir;
	rayPos.y = 10000;

	for (int i = 0; i < m_vNaviCell.size(); i++)
		{
			//자기 자신이면 컨티뉴
		if (i == myCellIndex) continue;
			
			if (D3DXIntersectTri(
				&m_vNaviCell[i].vertex[0],
				&m_vNaviCell[i].vertex[1],
				&m_vNaviCell[i].vertex[2],
				&rayPos,
				&D3DXVECTOR3(0, -1, 0),
				NULL, NULL, NULL))
			{
				return &m_vNaviCell[i];
	
				//return;
			}
		}
	
		return NULL;
}