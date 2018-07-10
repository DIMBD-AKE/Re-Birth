#include "MonsterUseHeader.h"
#include "MonsterManager.h"
#include "TotalMonster.h"


MonsterManager::MonsterManager()
{

}


MonsterManager::~MonsterManager()
{
	//
	/*
	GET(vector<MonsterParent*>, m_vMM, MonsterVector);
	SET(vector<D3DXVECTOR3>, m_vSpawnSpot, SpawnSpat);


	Map* m_pMap;

	CharacterParant** m_ppCharacter;
	*/
	//SAFE_DELETE(m_pMap);
	for (int i = 0; i < m_vMM.size(); i++)
	{
		SAFE_DELETE(m_vMM[i]);
	}

	m_pMap = NULL;
	m_ppCharacter = NULL;
}

void MonsterManager::Setup(Map* map, CharacterParant** character)
{
	m_pMap = map;
	m_ppCharacter = character;
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
				//m_vMM[i]->~MonsterParent();

				int spotSize = m_vSpawnSpot.size();

				srand(time(NULL));

				//���Ϳ��� ���� �ε��� ����
				int spotIndex = rand() % spotSize;

				m_vMM[i]->Respawn(m_vSpawnSpot[spotIndex]);
				//�¾� ȣ���Ͽ� �ٽ� ������Ѵ�.
				//m_vMM[i]->Setup(m_pMap, m_vSpawnSpot[spotIndex]);


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
void MonsterManager::MakeMonster(DropManager* pDropManager)
{

	MakeElizabeth(pDropManager);
	
	//MakeAssis(pDropManager);

	//MakeDarkHell(pDropManager);
	
	//MakeNifilHeim(pDropManager);
	
	//MakeNerisa(pDropManager);
	
	//MakeNike(pDropManager);
}
//����
void MonsterManager::MakeElizabeth(DropManager* pDropManager)
{
	int spotSize = m_vSpawnSpot.size();

	srand(time(NULL));

	//���Ϳ��� ���� �ε��� ����
	int spotIndex = rand() % spotSize;

	//���� ����
	MonsterParent* elizabeth;
	elizabeth = new Elizabeth;
	elizabeth->Setup(m_pMap, m_vSpawnSpot[spotIndex]);
	elizabeth->SetCharacter(m_ppCharacter);
	elizabeth->SetDropManager(pDropManager);

	m_vMM.push_back(elizabeth);
}

void MonsterManager::MakeAssis(DropManager* pDropManager)
{
	int spotSize = m_vSpawnSpot.size();

	srand(time(NULL));

	//���Ϳ��� ���� �ε��� ����
	int spotIndex = rand() % spotSize;

	//���� ����
	MonsterParent* assis;
	assis = new Assis;
	assis->Setup(m_pMap, m_vSpawnSpot[spotIndex]);
	assis->SetCharacter(m_ppCharacter);
	assis->SetDropManager(pDropManager);

	m_vMM.push_back(assis);
}


//���Ÿ�
void MonsterManager::MakeNerisa(DropManager* pDropManager)
{
	int spotSize = m_vSpawnSpot.size();

	srand(time(NULL));

	//���Ϳ��� ���� �ε��� ����
	int spotIndex = rand() % spotSize;

	//���� ����
	MonsterParent* nerisa;
	nerisa = new Nerisa;
	nerisa->Setup(m_pMap, m_vSpawnSpot[spotIndex]);
	nerisa->SetCharacter(m_ppCharacter);
	nerisa->SetDropManager(pDropManager);

	m_vMM.push_back(nerisa);
}

void MonsterManager::MakeNike(DropManager* pDropManager)
{
	int spotSize = m_vSpawnSpot.size();

	srand(time(NULL));

	//���Ϳ��� ���� �ε��� ����
	int spotIndex = rand() % spotSize;

	//���� ����
	MonsterParent* nike;
	nike = new Nike;
	nike->Setup(m_pMap, m_vSpawnSpot[spotIndex]);
	nike->SetCharacter(m_ppCharacter);
	nike->SetDropManager(pDropManager);

	m_vMM.push_back(nike);
}


//����
void MonsterManager::MakeDarkHell(DropManager* pDropManager)
{
	int spotSize = m_vSpawnSpot.size();

	srand(time(NULL));

	//���Ϳ��� ���� �ε��� ����
	int spotIndex = rand() % spotSize;

	//���� ����
	MonsterParent* darkHell;
	darkHell = new DarkHell;
	darkHell->Setup(m_pMap, m_vSpawnSpot[spotIndex]);
	darkHell->SetCharacter(m_ppCharacter);
	darkHell->SetDropManager(pDropManager);

	m_vMM.push_back(darkHell);
}

void MonsterManager::MakeNifilHeim(DropManager* pDropManager)
{
	int spotSize = m_vSpawnSpot.size();

	srand(time(NULL));

	//���Ϳ��� ���� �ε��� ����
	int spotIndex = rand() % spotSize;

	//���� ����
	MonsterParent* nifilHeim;
	nifilHeim = new NifilHeim;
	nifilHeim->Setup(m_pMap, m_vSpawnSpot[spotIndex]);
	nifilHeim->SetCharacter(m_ppCharacter);
	nifilHeim->SetDropManager(pDropManager);

	m_vMM.push_back(nifilHeim);
}
