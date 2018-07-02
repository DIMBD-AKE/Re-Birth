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
			D3DXVECTOR3(plusV/3);

		//사이드라인 3개 연산을 위한 반복문
		for (int j = 0; j < 3; j++)
		{
			//코드 길이가 길어지지만 좀더 알기 편하기 위해 미리 연산
			D3DXVECTOR3 plusV2 = m_vNaviCell[index].vertex[j % 3] + m_vNaviCell[index].vertex[(j + 1) % 3];
			m_vNaviCell[index].vertexCenter[j] = plusV2 / 2;

			m_vNaviCell[index].arrivalCost[j] = D3DXVec3Length(&m_vNaviCell[index].vertexCenter[j]);
		}										 

	}

	
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
