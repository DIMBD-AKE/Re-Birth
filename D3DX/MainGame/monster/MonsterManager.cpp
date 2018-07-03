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
	assert(m_vSpawnSpot.size() > 0 && "������� ���Ͱ� �����ϴ�.");

	for (int i = 0; i < m_vMM.size(); i++)
	{
		if (m_vMM[i]->GetIsResPawn())
		{

			//������ ���̸� ���� �ð����� ���ư���.
			m_vMM[i]->RespawnUpdate();

			//������ Ư���ð��� �Ǹ� �� �οﰪ�� false�� �ǰ� ��ȯ��Ű�� ���̵ǹǷ�
			//Ư�� ��ġ�� ����� ��Ų��.
			if (!m_vMM[i]->GetIsResPawn())
			{
				int spotSize = m_vSpawnSpot.size();

				srand(time(NULL));

				//���Ϳ��� ���� �ε��� ����
				int spotIndex = rand() % spotSize;

				//�¾� ȣ���Ͽ� �ٽ� ������Ѵ�.
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
	assert(m_vSpawnSpot.size() > 0 && "������� ���Ͱ� �����ϴ�.");

	for (int i = 0; i < m_vMM.size(); i++)
	{
		m_vMM[i]->Render();
	}
}


//���� ����� �Լ�
void MonsterManager::MakeMonster()
{
	//���߿� ��ü������ �����ؾ���

	//������ ����� ����
	int spotSize = m_vSpawnSpot.size();

	srand(time(NULL));

	//���Ϳ��� ���� �ε��� ����
	int spotIndex = rand() % spotSize;

	//���� ����
	MonsterParent* test;
	test = new Elizabeth;
	test->Setup(m_pMap, m_vSpawnSpot[spotIndex]);

	//���� ���Ϳ� ����
	m_vMM.push_back(test);
}
