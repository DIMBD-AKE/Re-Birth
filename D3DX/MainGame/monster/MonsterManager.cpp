#include "../../stdafx.h"
#include "MonsterManager.h"
#include "MonsterParent.h"
#include "Elizabeth.h"
#include <time.h>


MonsterManager::MonsterManager()
{
	MonsterParent* test;
	test = new MonsterParent;

	m_vMM.push_back(test);
}


MonsterManager::~MonsterManager()
{

}

void MonsterManager::Setup(Map* map)
{
	m_pMap = map;
}

void MonsterManager::Update()
{
	assert(m_vSpawnSpot.size() > 0 && "만들어진 몬스터가 없습니다.");

	for (int i = 0; i < m_vMM.size(); i++)
	{
		if (m_vMM[i]->GetIsResPawn())
		{

			//리스폰 중이면 일정 시간동안 돌아간다.
			m_vMM[i]->RespawnUpdate();

			//리스폰 특정시간이 되면 이 부울값은 false가 되고 전환시키면 참이되므로
			//특정 위치에 재생성 시킨다.
			if (!m_vMM[i]->GetIsResPawn())
			{
				int spotSize = m_vSpawnSpot.size();

				srand(time(NULL));

				//벡터에서 랜덤 인덱스 추출
				int spotIndex = rand() % spotSize;

				//셋업 호출하여 다시 재생성한다.
				m_vMM[i]->Setup(m_pMap, m_vSpawnSpot[spotIndex]);
			}
		}
		{
			m_vMM[i]->Update();
		}
	}
}

void MonsterManager::Render()
{
	assert(m_vSpawnSpot.size() > 0 && "만들어진 몬스터가 없습니다.");

	for (int i = 0; i < m_vMM.size(); i++)
	{
		m_vMM[i]->Render();
	}
}


//몬스터 만드는 함수
void MonsterManager::MakeMonster()
{
	//나중에 전체적으로 수정해야함

	//벡터의 사이즈를 저장
	int spotSize = m_vSpawnSpot.size();

	srand(time(NULL));

	//벡터에서 랜덤 인덱스 추출
	int spotIndex = rand() % spotSize;

	//몬스터 생성
	MonsterParent* test;
	test = new Elizabeth;
	test->Setup(m_pMap, m_vSpawnSpot[spotIndex]);

	//몬스터 벡터에 저장
	m_vMM.push_back(test);
}
